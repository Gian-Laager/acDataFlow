#include "pch.h"

void helloSycl()
{
    using namespace cl::sycl;

    constexpr size_t N = 2000;
    constexpr size_t M = 3000;
    // Create a queue to work on
    queue q;

    // Create some 2D buffers of N*M floats for our matrices
    buffer<float, 2> a{{N, M}};
    buffer<float, 2> b{{N, M}};
    buffer<float, 2> c{{N, M}};

    // Launch a first asynchronous kernel to initialize a
    q.submit([&](handler& cgh) {
        // The kernel writes a, so get a write accessor on it
        auto A = a.get_access<access::mode::write>(cgh);

        // Enqueue a parallel kernel iterating on a N*M 2D iteration space
        cgh.parallel_for<class init_a>({N, M},
                                       [=](id<2> index) {
                                           A[index] = index[0] * 2 + index[1];
                                       });
    });

    // Launch an asynchronous kernel to initialize b
    q.submit([&](handler& cgh) {
        // The kernel writes b, so get a write accessor on it
        auto B = b.get_access<access::mode::write>(cgh);
        /* From the access pattern above, the SYCL runtime detects this
           command group is independent from the first one and can be
           scheduled independently */

        // Enqueue a parallel kernel iterating on a N*M 2D iteration space
        cgh.parallel_for<class init_b>({N, M},
                                       [=](id<2> index) {
                                           B[index] = index[0] * 2014 + index[1] * 42;
                                       });
    });

    // Launch an asynchronous kernel to compute matrix addition c = a + b
    q.submit([&](handler& cgh) {
        // In the kernel a and b are read, but c is written
        auto A = a.get_access<access::mode::read>(cgh);
        auto B = b.get_access<access::mode::read>(cgh);
        auto C = c.get_access<access::mode::write>(cgh);
        // From these accessors, the SYCL runtime will ensure that when
        // this kernel is run, the kernels computing a and b completed

        // Enqueue a parallel kernel iterating on a N*M 2D iteration space
        cgh.parallel_for<class matrix_add>({N, M},
                                           [=](id<2> index) {
                                               C[index] = A[index] + B[index];
                                           });
    });

    /* Request an accessor to read c from the host-side. The SYCL runtime
       ensures that c is ready when the accessor is returned */
    auto C = c.get_access<access::mode::read>();
    std::cout << std::endl << "Result:" << std::endl;
    for (size_t i = 0; i < N; i++)
        for (size_t j = 0; j < M; j++)
            // Compare the result to the analytic value
            if (C[i][j] != i * (2 + 2014) + j * (1 + 42))
            {
                std::cout << "Wrong value " << C[i][j] << " on element "
                          << i << ' ' << j << std::endl;
                exit(-1);
            }

    std::cout << "Accurate computation!" << std::endl;
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
        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_POLYGON);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.5, 0.0, 0.0);
        glVertex3f(0.5, 0.5, 0.0);
        glVertex3f(0.0, 0.5, 0.0);
        glEnd();

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}