#include "pch.h"

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

//TODO: implement this function properly
//at the moment she's implemented in the main function because of performance improvements
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

    //converting colorArray to vertexBuffer
    queue.submit([&](cl::sycl::handler& cgh) {
        auto vb_buffer_acc = vb_buffer.get_access<cl::sycl::access::mode::write>(cgh);
        auto color_buffer_acc = color_buffer.get_access<cl::sycl::access::mode::read>(cgh);

        cgh.parallel_for<class kernel2>(cl::sycl::range<2>((unsigned long) windowWidth, (unsigned long) windowHeight),
                                        [=](cl::sycl::id<2> index) {
                                            vb_buffer_acc[index[0]][index[1]] = {
                                                    mapNumber<float>(index[0], 0, windowWidth, -1, 1),
                                                    mapNumber<float>(index[1], 0, windowHeight, -1,
                                                                1),
                                                    color_buffer_acc[index[0]][index[1]]};
                                        });
    });

    //setting up things for the Renderer
    vertexBuffer.data(vb_Data, windowWidth * windowHeight, GL_STATIC_DRAW);
    vertexArray.push(&vertexBuffer, layouts, 2);
    queue.wait();

    //actually drawing to the window
    renderer.draw(windowWidth * windowHeight, (GLenum) GL_POINTS);

    delete[] vb_Data;
    delete[] colorArray;
}

int main()
{
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

    cl::sycl::queue queue;

    while (!glfwWindowShouldClose(window))
    {
        glfwGetWindowSize(window, &windowWidth, &windowHeight);

        glCall(glClear(GL_COLOR_BUFFER_BIT));

        auto* pixelColors = new Color[windowWidth * windowHeight];
        cl::sycl::buffer<Color, 2> color_buffer(pixelColors, cl::sycl::range<2>{(unsigned long) windowWidth,
                                                                                (unsigned long) windowHeight});
        queue.submit([&](cl::sycl::handler& cgh) {
            auto color_buffer_acc = color_buffer.get_access<cl::sycl::access::mode::write>(cgh);

            cgh.parallel_for<class kernel>(
                    cl::sycl::range<2>((unsigned long) windowWidth, (unsigned long) windowHeight),
                    [=](cl::sycl::id<2> index) {
                        color_buffer_acc[index[0]][index[1]] = {
                                mapNumber<float>(index[0], 0.f, windowWidth, 0.f, 1.f),
                                mapNumber<float>(index[1], 0.f, windowHeight, 0.f, 1.f),
                                0.f,
                                1.f};
                    });
        });
        queue.wait();

        pixelColors[700 + 600 * windowWidth] = {1.f, 1.f, 1.f, 1.f};

        setScreenPixels(pixelColors, renderer, shader, vertexBuffer, vertexArray, layouts, queue, windowWidth,
                        windowHeight);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}