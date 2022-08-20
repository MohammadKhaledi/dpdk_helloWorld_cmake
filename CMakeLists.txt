cmake_minimum_required(VERSION 3.0.2)

project(dp_test)

# For understanding what is going on here check: https://www.linuxfixes.com/2021/11/solved-dpdk-example-application.html

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add flags for .cpp files
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -g -O0")

find_package(PkgConfig REQUIRED)
pkg_check_modules(DPDK_LIB REQUIRED libdpdk)

set(MAIN_CODE utils/main.cc)
add_executable(main_dp_test ${MAIN_CODE})

target_link_libraries(main_dp_test ${DPDK_LIB_LIBRARIES})
target_include_directories(main_dp_test PUBLIC ${DPDK_LIB__INCLUDE_DIRS})
target_compile_options(main_dp_test PUBLIC ${DPDK_LIB_CFLAGS_OTHER})
