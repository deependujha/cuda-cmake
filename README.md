# CUDA with CMake

![cuda cmake](./assets/ben-10-cuda-mode.jpg)

---

## Setup

```bash
# clone and cd into it
git clone https://github.com/deependujha/cuda-cmake.git
cd cuda-cmake

# create build/ dir
mkdir build && cd build

# generate build files
cmake ..
cmake --build .

# run executable
./cc_code
```

---

## Using CMAKE to conditionally compile cuda kernels 🔥

- Use `ifdef` and `ifndef` preprocessor directives, while including header files or calling functions.

```cpp
#ifdef CUDA_AVAILABLE
#include "../cuda/kernel.cuh"
#else
#include "../cpu/cpu.h"
#endif

// ---

  // Call the appropriate vector add function
#ifdef CUDA_AVAILABLE
  vectorAddCUDA(A, B, C, N);
  std::cout << "CUDA Vector addition successful." << std::endl;
#else
  vectorAddCPU(A, B, C, N);
  std::cout << "CPU Vector addition successful." << std::endl;
#endif
```

- Find `CUDA` in Quiet mode in CMAKE

```cmake
# Check if CUDA is available quietly (don't log warnings, if not available)
find_package(CUDAToolkit QUIET)
```

- If `CUDA_FOUND`, define identifier, build library and link to executable.

```cmake
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
```
