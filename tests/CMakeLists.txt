enable_testing()
# find_package(GTest REQUIRED)

add_executable(test_mandelbrot mandelbrot.cpp)
target_link_libraries(test_mandelbrot PUBLIC GTest::gtest_main)
add_test(test_mandelbrot test_mandelbrot)
