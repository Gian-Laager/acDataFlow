#include "pch.h"

struct Color
{
    float r, g, b, a;
};

struct Vertex
{
    float x, y;
    Color color;
};

template<typename T>
T mapNumber(T x, T a, T b, T c, T d)
{
    return (x - a) / (b - a) * (d - c) + c;
}

template<int windowWidth, int height>
void setScreenPixels(const Color* colorArray, Shader& shader)
{

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

        auto* pixelColors = new Color[windowWidth * windowHeight];
        auto* vb_Data = new Vertex[windowWidth * windowHeight];

        cl::sycl::buffer<Vertex, 2> vb_buffer(vb_Data, cl::sycl::range<2>{(unsigned long) windowWidth,
                                                                          (unsigned long) windowHeight});
        cl::sycl::buffer<Color, 2> color_buffer(pixelColors, cl::sycl::range<2>{(unsigned long) windowWidth,
                                                                                (unsigned long) windowHeight});

        glCall(glClear(GL_COLOR_BUFFER_BIT));

        for (int i = 0; i < windowWidth; i++)
        {
            for (int j = 0; j < windowHeight; j++)
            {
                pixelColors[i + j * windowWidth] = {(float) i, (float) j, fmod((float) (i + j * windowWidth), 1.f),
                                                    1.f};
            }
        }

        //converting colorArray to vertexBuffer

        queue.submit([&](cl::sycl::handler& cgh) {
            auto vb_buffer_acc = vb_buffer.get_access<cl::sycl::access::mode::write>(cgh);
            auto color_buffer_acc = color_buffer.get_access<cl::sycl::access::mode::read>(cgh);

            cgh.parallel_for(cl::sycl::range<2>{(unsigned long) windowWidth, (unsigned long) windowHeight},
                             cl::sycl::id<2>(),
                             [=](cl::sycl::item<2> index) {
                                 vb_buffer_acc[index[0]][index[1]] = {mapNumber<float>(index[0], 0, windowWidth, -1, 1),
                                                                      mapNumber<float>(index[1], 0, windowHeight, -1,
                                                                                       1),
                                                                      color_buffer_acc[index[0]][index[1]]};
                             });
        });

        //setting up things for the Renderer
        vertexBuffer.data(vb_Data, windowWidth * windowHeight, GL_STATIC_DRAW);

        vertexArray.push(&vertexBuffer, layouts, 2);

        //actually drawing to the window
        queue.wait();
        renderer.draw(windowWidth * windowHeight, (GLenum) GL_POINTS);

        // setScreenPixels<windowWidth, windowHeight>(pixelColors, shader);

        glfwSwapBuffers(window);

        glfwPollEvents();

        delete[] vb_Data;
        delete[] pixelColors;
    }

    glfwTerminate();
    return 0;
}