#include <iostream>

struct Char
{
    char bit: 1;
};

int main()
{
    Char bool8 = {0,1,0,0,0,0,0,1};
    std::cout << sizeof(Char) << std::endl;

    std::cout << (unsigned int) bool8.bit : 1 << std::endl;
    std::cout << (unsigned int) bool8.bit2 << std::endl;
    std::cout << (unsigned int) bool8.bit3 << std::endl;
    std::cout << (unsigned int) bool8.bit4 << std::endl;
    std::cout << (unsigned int) bool8.bit5 << std::endl;
    std::cout << (unsigned int) bool8.bit6 << std::endl;
    std::cout << (unsigned int) bool8.bit7 << std::endl;
    std::cout << (unsigned int) bool8.bit8 << std::endl;
    std::cout << *((char*) &bool8);

}

//#define TRISYCL_OPENCL
//#define OMP_NUM_THREADS 8
//#define BOOST_COMPUTE_USE_CPP11
//
////standart libraries
//#include <iostream>
//
////deps
//#include "CL/sycl.hpp"
//
//struct Color
//{
//    float r, g, b, a;
//
//    friend std::ostream& operator<<(std::ostream& os, const Color& c)
//    {
//        os << "(" << c.r << ", " << c.g << ", " << c.b << ", " << c.a << ")";
//        return os;
//    }
//};
//
//struct Vertex
//{
//    float x, y;
//    Color color;
//
//    friend std::ostream& operator<<(std::ostream& os, const Vertex& v)
//    {
//        os << "x: " << v.x << ", y: " << v.y << ", color: " << v.color;
//        return os;
//    }
//};
//
//template<typename T>
//T mapNumber(T x, T a, T b, T c, T d)
//{
//    return (x - a) / (b - a) * (d - c) + c;
//}
//
//int windowWidth = 640;
//int windowHeight = 720;
//
//int main()
//{
//    auto exception_handler = [](cl::sycl::exception_list exceptions) {
//        for (std::exception_ptr const& e : exceptions)
//        {
//            try
//            {
//                std::rethrow_exception(e);
//            } catch (cl::sycl::exception const& e)
//            {
//                std::cout << "Caught asynchronous SYCL exception: " << e.what() << std::endl;
//            }
//        }
//    };
//
//    cl::sycl::default_selector defaultSelector;
//    cl::sycl::context context(defaultSelector, exception_handler);
//    cl::sycl::queue queue(context, defaultSelector, exception_handler);
//
//        auto* pixelColors = new Color[windowWidth * windowHeight];
//        {
//            cl::sycl::buffer<Color, 2> color_buffer(pixelColors, cl::sycl::range < 2 > {(unsigned long) windowWidth,
//                                                                                        (unsigned long) windowHeight});
//
//            cl::sycl::buffer<int, 1> b_windowWidth(&windowWidth, cl::sycl::range < 1 > {1});
//            cl::sycl::buffer<int, 1> b_windowHeight(&windowHeight, cl::sycl::range < 1 > {1});
//
//            queue.submit([&](cl::sycl::handler& cgh) {
//                auto color_buffer_acc = color_buffer.get_access<cl::sycl::access::mode::write>(cgh);
//                auto width_buffer_acc = b_windowWidth.get_access<cl::sycl::access::mode::read>(cgh);
//                auto height_buffer_acc = b_windowHeight.get_access<cl::sycl::access::mode::read>(cgh);
//
//                cgh.parallel_for<class init_pixelColors>(
//                        cl::sycl::range<2>((unsigned long) width_buffer_acc[0], (unsigned long) height_buffer_acc[0]),
//                        [=](cl::sycl::id<2> index) {
//                            color_buffer_acc[index[0]][index[1]] = {
//                                    mapNumber<float>(index[0], 0.f, width_buffer_acc[0], 0.f, 1.f),
//                                    mapNumber<float>(index[1], 0.f, height_buffer_acc[0], 0.f, 1.f),
//                                    0.f,
//                                    1.f};
//                        });
//            });
//
//            std::cout << "cl::sycl::queue check - selected device: "
//                      << queue.get_device().get_info<cl::sycl::info::device::name>() << std::endl;
//        }
//
//        delete[] pixelColors;
//    return 0;
//}
//try
//{
//    queue.wait_and_throw();
//} catch (cl::sycl::exception const& e)
//{
//    std::cout << "Caught synchronous SYCL exception: " << e.what() << std::endl;
//}