cmake_minimum_required(VERSION 3.27)
project(CUDA_Project LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CUDA_STANDARD 14)
option(CMAKE_EXPORT_COMPILE_COMMANDS "Generate compile_commands.json" ON) # for clang-tidy

# Check if CUDA is available quietly (don't log warnings, if not available)
find_package(CUDAToolkit QUIET)

# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/cuda ${CMAKE_CURRENT_SOURCE_DIR}/cpu)

add_executable(cc_code src/main.cc)


if(CUDAToolkit_FOUND)
    enable_language(CUDA)
    message(STATUS "======================================")
    message(STATUS "CUDA found. Enabling CUDA support.")
    message(STATUS "======================================")

    add_compile_definitions(CUDA_AVAILABLE)

    # Set CUDA architectures globally (for all targets using CUDA)
    set(CMAKE_CUDA_ARCHITECTURES "all")

    # Add the CUDA library
    add_library(my_cuda_library STATIC cuda/kernel.cu)

    # Set CUDA compilation options
    set_target_properties(my_cuda_library PROPERTIES
        CUDA_SEPARABLE_COMPILATION ON
    )

    # Include directories for the library
    target_include_directories(my_cuda_library PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

    # Link the CUDA library with the executable
    target_link_libraries(cc_code PRIVATE my_cuda_library)

    # Set CUDA architectures for cc_code explicitly
    set_target_properties(cc_code PROPERTIES CUDA_ARCHITECTURES "all")
else()
    message(STATUS "======================================")
    message(STATUS "CUDA not found. Skipping CUDA support.")
    message(STATUS "======================================")
endif()

add_library(my_cpu_library STATIC cpu/cpu.cc)

# Link the CUDA library with the executable
target_link_libraries(cc_code PRIVATE my_cpu_library)
