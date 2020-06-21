#include "pch.h"

struct Color
{
    int r, g, b, a;
};

struct Vertex
{
    float x, y;
    Color color;
};

float mapNumber(float x, float a, float b, float c, float d)
{
    return (x - a) / (b - a) * (d - c) + c;
}

template<unsigned int width, unsigned int height>
void setScreenPixels(const Color* colorArray)
{
    //converting colorArray to vertexBuffer
    auto* vb_Data = new Vertex[width * height];

    cl::sycl::queue queue;
    cl::sycl::buffer<Vertex, 2> vb_buffer(vb_Data, cl::sycl::range<2>{width, height});
    cl::sycl::buffer<Color, 2> color_buffer(colorArray, cl::sycl::range<2>{width, height});

    cl::sycl::id<2> index;

    queue.submit([&](cl::sycl::handler& cgh) {
        auto vb_buffer_acc = vb_buffer.get_access<cl::sycl::access::mode::write>(cgh);
        auto color_buffer_acc = color_buffer.get_access<cl::sycl::access::mode::read>(cgh);

        cgh.parallel_for(cl::sycl::range<2>{width, height}, cl::sycl::id<2>(), [=](cl::sycl::item<2> index) {
            vb_buffer_acc[index[0]][index[1]] = {mapNumber(index[0], 0, width, -1, 1),
                                                 mapNumber(index[1], 0, height, -1, 1),
                                                 color_buffer_acc[index[0]][index[1]]};
        });
    });

    //setting up things for the Renderer
    VertexArray vertexArray;
    VertexBuffer vertexBuffer;
    vertexBuffer.data(vb_Data, width * height, GL_STATIC_DRAW);

    Shader shader("../res/shaders/basicShader.glsl");
    VertexBufferLayout positionLayout(0, 2, GL_FLOAT, false, sizeof(Vertex), nullptr);
    VertexBufferLayout colorLayout(0, 4, GL_FLOAT, false, sizeof(Vertex), (void*) &(((Vertex*) nullptr)->color));

    VertexBufferLayout layouts[] = {positionLayout, colorLayout};
    vertexArray.push(&vertexBuffer, layouts, 2);

    Renderer renderer(&vertexArray, &shader);
    renderer.draw(width * height, GL_POINTS);
}

int main()
{
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    while (!glfwWindowShouldClose(window))
    {
        glCall(glClear(GL_COLOR_BUFFER_BIT));


        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}