cmake_minimum_required(VERSION 3.16.2)

project(acMandelbrotSet)

set(CMAKE_CXX_STANDARD 17)

set(SRC_FILES
        ${CMAKE_CURRENT_LIST_DIR}/src/acMandalbrotset.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/GLAbstraction/Buffer.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/GLAbstraction/Renderer.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/GLAbstraction/Shader.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/GLAbstraction/VertexArray.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/GLAbstraction/VertexBuffer.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/GLAbstraction/VertexBufferLayout.cpp
        ${CMAKE_CURRENT_LIST_DIR}/deps/imgui/imgui.cpp
        ${CMAKE_CURRENT_LIST_DIR}/deps/imgui/examples/imgui_impl_opengl3.cpp
        ${CMAKE_CURRENT_LIST_DIR}/deps/imgui/examples/imgui_impl_glfw.cpp
        ${CMAKE_CURRENT_LIST_DIR}/deps/imgui/imgui_demo.cpp
        ${CMAKE_CURRENT_LIST_DIR}/deps/imgui/imgui_draw.cpp
        ${CMAKE_CURRENT_LIST_DIR}/deps/imgui/imgui_widgets.cpp
        )

set(PREC_H "${CMAKE_CURRENT_LIST_DIR}/src/pch.h")
set(HEADER_FILES
        ${PREC_H}
        ${CMAKE_CURRENT_LIST_DIR}/src/GLAbstraction/Buffer.h
        ${CMAKE_CURRENT_LIST_DIR}/src/GLAbstraction/Renderer.h
        ${CMAKE_CURRENT_LIST_DIR}/src/GLAbstraction/Shader.h
        ${CMAKE_CURRENT_LIST_DIR}/src/GLAbstraction/VertexArray.h
        ${CMAKE_CURRENT_LIST_DIR}/src/GLAbstraction/VertexBuffer.h
        ${CMAKE_CURRENT_LIST_DIR}/src/GLAbstraction/VertexBufferLayout.h
        ${CMAKE_CURRENT_LIST_DIR}/deps/imgui/examples/imgui_impl_glfw.h
        ${CMAKE_CURRENT_LIST_DIR}/deps/imgui/imgui.h
        ${CMAKE_CURRENT_LIST_DIR}/deps/imgui/examples/imgui_impl_opengl3.h
        ${CMAKE_CURRENT_LIST_DIR}/deps/imgui/imconfig.h
        ${CMAKE_CURRENT_LIST_DIR}/deps/imgui/imgui_internal.h
        ${CMAKE_CURRENT_LIST_DIR}/deps/imgui/imstb_truetype.h
        ${CMAKE_CURRENT_LIST_DIR}/deps/imgui/imstb_textedit.h
        ${CMAKE_CURRENT_LIST_DIR}/deps/imgui/imstb_rectpack.h
        )

include_directories(${CMAKE_CURRENT_LIST_DIR}/src)

find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED CONFIG)
find_package(OpenGL REQUIRED)

include_directories("deps/imgui")

include_directories("deps/glew/include" "deps/glfw/include")
link_directories("deps/glew/lib" "deps/glfw/src/")

set(LIBS PRIVATE GLEW::GLEW ${OPENGL_LIBRARIES} glfw)

include_directories(${CMAKE_CURRENT_LIST_DIR}/include)

set(Boost_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/deps/boost)
include_directories(${CMAKE_CURRENT_LIST_DIR}/deps/boost)

include_directories(${CMAKE_CURRENT_LIST_DIR}/deps/SYCL/include)

add_executable(${PROJECT_NAME} ${SRC_FILES} ${HEADER_FILES})
target_precompile_headers(${PROJECT_NAME} PRIVATE ${PREC_H})

set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX _d)
target_link_libraries(${PROJECT_NAME} ${LIBS})
target_include_directories(${PROJECT_NAME} PRIVATE ${OPENGL_INCLUDE_DIR})

set(cgex $<CONFIGURATION>)

target_compile_definitions(${PROJECT_NAME} PRIVATE
        -DGLEW_CMAKE_TEST_CONFIG=${cgex}
        -DGLEW_CMAKE_TEST_TARGET_FILE_NAME=$<TARGET_FILE_NAME:GLEW::GLEW>
        -DGLEW_CMAKE_TEST_TARGET_TYPE=$<TARGET_PROPERTY:GLEW::GLEW,TYPE>
        )

install(TARGETS ${PROJECT_NAME} DESTINATION bin)