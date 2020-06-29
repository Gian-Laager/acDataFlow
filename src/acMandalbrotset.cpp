#include "pch.h"

class Timer
{
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
    std::chrono::time_point<std::chrono::high_resolution_clock> end;

public:
    const char* name;
    std::function<void()> callback;

    Timer(const char* name, std::function<void()> callback = []() {}) : start(
            std::chrono::high_resolution_clock::now()), name(name), callback(std::move(callback)) {}

    ~Timer()
    {
        end = std::chrono::high_resolution_clock::now();
        auto mic_start = std::chrono::time_point_cast<std::chrono::microseconds>(start).time_since_epoch().count();
        auto mic_end = std::chrono::time_point_cast<std::chrono::microseconds>(end).time_since_epoch().count();
        std::cout << "Timer '" << name << "' destructed after: " << (mic_end - mic_start) * 0.001 << " milliseconds"
                  << std::endl;

        callback();
    }

    std::chrono::time_point<std::chrono::high_resolution_clock> getStart() const { return start; }

    std::chrono::time_point<std::chrono::high_resolution_clock> getEnd() const { return end; }
};

struct Color
{
    float r, g, b, a;

    friend std::ostream& operator<<(std::ostream& os, const Color& c)
    {
        os << "(" << c.r << ", " << c.g << ", " << c.b << ", " << c.a << ")";
        return os;
    }
};

struct Vertex
{
    float x, y;
    Color color;

    friend std::ostream& operator<<(std::ostream& os, const Vertex& v)
    {
        os << "x: " << v.x << ", y: " << v.y << ", color: " << v.color;
        return os;
    }
};

template<typename T>
T mapNumber(T x, T a, T b, T c, T d)
{
    return (x - a) / (b - a) * (d - c) + c;
}

void setScreenPixels(Color* colorArray, Renderer& renderer, Shader& shader, VertexBuffer& vertexBuffer,
                     VertexArray& vertexArray, VertexBufferLayout* layouts, cl::sycl::queue& queue, int windowWidth,
                     int windowHeight)
{
    // initialize all variables
    auto* vb_Data = new Vertex[windowWidth * windowHeight];

    cl::sycl::buffer<Vertex, 2> vb_buffer(vb_Data, cl::sycl::range<2>{(unsigned long) windowWidth,
                                                                      (unsigned long) windowHeight});
    cl::sycl::buffer<Color, 2> color_buffer(colorArray, cl::sycl::range<2>{(unsigned long) windowWidth,
                                                                           (unsigned long) windowHeight});
    cl::sycl::buffer<int, 1> b_windowWidth(&windowWidth, cl::sycl::range<1>{1});
    cl::sycl::buffer<int, 1> b_windowHeight(&windowHeight, cl::sycl::range<1>{1});

    //converting colorArray to vertexBuffer
    queue.submit([&](cl::sycl::handler& cgh) {
        auto vb_buffer_acc = vb_buffer.get_access<cl::sycl::access::mode::write>(cgh);
        auto color_buffer_acc = color_buffer.get_access<cl::sycl::access::mode::read>(cgh);
        auto width_buffer_acc = b_windowWidth.get_access<cl::sycl::access::mode::read>(cgh);
        auto height_buffer_acc = b_windowHeight.get_access<cl::sycl::access::mode::read>(cgh);

        cgh.parallel_for<class create_vertex_buffer>(
                cl::sycl::range<2>((unsigned long) width_buffer_acc[0], (unsigned long) height_buffer_acc[0]),
                [=](cl::sycl::id<2> index) {
                    vb_buffer_acc[index[0]][index[1]] = {
                            mapNumber<float>(index[0], 0, width_buffer_acc[0], -1, 1),
                            mapNumber<float>(index[1], 0, height_buffer_acc[0], -1,
                                             1),
                            color_buffer_acc[index[0]][index[1]]};
//                    std::cout << "i: " << index[0] << " j: " << index[1] << std::endl;
                });
    });

    //setting up things for the Renderer
    vertexBuffer.data(vb_Data, windowWidth * windowHeight, GL_STATIC_DRAW);
    vertexArray.push(&vertexBuffer, layouts, 2);
    queue.wait();

    //actually drawing to the window
    renderer.draw(windowWidth * windowHeight, (GLenum) GL_POINTS);

    delete[] vb_Data;
}

int main()
{
    std::vector<long> syclTimes;
    std::vector<long> asyncTimes;

    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    int windowWidth = 640;
    int windowHeight = 720;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true);

    window = glfwCreateWindow(windowWidth, windowHeight, "Mandelbrot set", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    glewExperimental = true;
    if (GLEW_OK != glewInit())
    {
        std::cout << "something with glew went wrong" << std::endl;
        return -1;
    }
    glCall(glEnable(GL_BLEND));
    glCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    glCall(glfwSwapInterval(1));

    // initializing variables for setScreenPixels() to get more performance
    Shader shader("../res/shaders/basicShader.glsl");

    VertexArray vertexArray;
    VertexBuffer vertexBuffer;

    VertexBufferLayout positionLayout(0, 2, GL_FLOAT, false, sizeof(Vertex), nullptr);
    VertexBufferLayout colorLayout(1, 4, GL_FLOAT, false, sizeof(Vertex), (void*) &(((Vertex*) nullptr)->color));
    Renderer renderer(&vertexArray, &shader);

    VertexBufferLayout layouts[] = {positionLayout, colorLayout};

    auto exception_handler = [](cl::sycl::exception_list exceptions) {
        for (std::exception_ptr const& e : exceptions)
        {
            try
            {
                std::rethrow_exception(e);
            } catch (cl::sycl::exception const& e)
            {
                std::cout << "Caught asynchronous SYCL exception: " << e.what() << std::endl;
            }
        }
    };

    cl::sycl::default_selector defaultSelector;
    cl::sycl::context context(defaultSelector, exception_handler);
    cl::sycl::queue queue(context, defaultSelector, exception_handler);

    while (!glfwWindowShouldClose(window))
    {
        glCall(glClear(GL_COLOR_BUFFER_BIT));

        auto* pixelColors = new Color[windowWidth * windowHeight];

        queue.submit([&](cl::sycl::handler& c) {
            Timer syclTimer("sycl", [&syclTimes, &syclTimer]() {
                auto mic_start = std::chrono::time_point_cast<std::chrono::microseconds>(
                        syclTimer.getStart()).time_since_epoch().count();
                auto mic_end = std::chrono::time_point_cast<std::chrono::microseconds>(
                        syclTimer.getEnd()).time_since_epoch().count();
                syclTimes.push_back((mic_end - mic_start) * 0.001);
            });
            cl::sycl::buffer<Color, 2> color_buffer(pixelColors, cl::sycl::range<2>{(unsigned long) windowWidth,
                                                                                    (unsigned long) windowHeight});

            cl::sycl::buffer<int, 1> b_windowWidth(&windowWidth, cl::sycl::range<1>{1});
            cl::sycl::buffer<int, 1> b_windowHeight(&windowHeight, cl::sycl::range<1>{1});

            queue.submit([&](cl::sycl::handler& cgh) {
                auto color_buffer_acc = color_buffer.get_access<cl::sycl::access::mode::write, cl::sycl::access::target::global_buffer>(
                        cgh);
                auto width_buffer_acc = b_windowWidth.get_access<cl::sycl::access::mode::read, cl::sycl::access::target::global_buffer>(
                        cgh);
                auto height_buffer_acc = b_windowHeight.get_access<cl::sycl::access::mode::read, cl::sycl::access::target::global_buffer>(
                        cgh);

                cgh.parallel_for<class init_pixelColors>(
                        cl::sycl::range<2>((unsigned long) width_buffer_acc[0], (unsigned long) height_buffer_acc[0]),
                        [=](cl::sycl::id<2> index) {
                            color_buffer_acc[index[0]][index[1]] = {
                                    mapNumber<float>(index[0], 0.f, width_buffer_acc[0], 0.f, 1.f),
                                    mapNumber<float>(index[1], 0.f, height_buffer_acc[0], 0.f, 1.f),
                                    0.f,
                                    1.f};
//                        std::cout << "i: " << index[0] << " j: " << index[1] << std::endl;
                        });
            });
        });

        pixelColors[700 + 600 * windowWidth] = {1.f, 1.f, 1.f, 1.f};

        setScreenPixels(pixelColors, renderer, shader, vertexBuffer, vertexArray, layouts, queue, windowWidth,
                        windowHeight);

        delete[] pixelColors;

        queue.submit([&](cl::sycl::handler& c) {
            Timer asyncTimer("async", [&asyncTimes, &asyncTimer]() {
                auto mic_start = std::chrono::time_point_cast<std::chrono::microseconds>(
                        asyncTimer.getStart()).time_since_epoch().count();
                auto mic_end = std::chrono::time_point_cast<std::chrono::microseconds>(
                        asyncTimer.getEnd()).time_since_epoch().count();
                asyncTimes.push_back((mic_end - mic_start) * 0.001);
            });
            pixelColors = new Color[windowWidth * windowHeight];

            std::vector<std::future<void>> futures;
            futures.reserve(windowWidth * windowHeight);

            for (int i = 0; i < windowWidth; i++)
            {
                for (int j = 0; j < windowHeight; j++)
                {
                    futures.push_back(std::async(std::launch::async, [pixelColors, i, j, windowWidth, windowHeight] {
                        pixelColors[i + j * windowWidth] = {
                                mapNumber<float>(i, 0.f, windowWidth, 0.f, 1.f),
                                mapNumber<float>(j, 0.f, windowHeight, 0.f, 1.f),
                                0.f,
                                1.f};
                    }));
                }
            }

            for (auto& future : futures)
                future.wait();
        });


        glfwSwapBuffers(window);

        glfwPollEvents();
        glfwGetWindowSize(window, &windowWidth, &windowHeight);
        queue.wait();
    }
    long syclTotalTime = 0;
    for (auto& t : syclTimes)
        syclTotalTime += t;

    long asyncTotalTime = 0;
    for (auto& t : asyncTimes)
        asyncTotalTime += t;

    std::cout << "average sycl: " << syclTotalTime / syclTimes.size() << std::endl;
    std::cout << "average async: " << asyncTotalTime / asyncTimes.size() << std::endl;
    glfwTerminate();
    return 0;
}