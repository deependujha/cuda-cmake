# CUDA with CMake

![cuda cmake](./assets/ben-10-cuda-mode.jpg)

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
find_package(CUDA QUIET)
```

- If `CUDA_FOUND`, define identifier, build library and link to executable.

```cmake
if(CUDA_FOUND)
    enable_language(CUDA)
    message(STATUS "CUDA found. Enabling CUDA support.")

    # defining identifier, will be used in cc code for conditional compilation
    add_compile_definitions(CUDA_AVAILABLE)
    
    # Add the CUDA library
    add_library(my_cuda_library STATIC cuda/kernel.cu)

    # Set CUDA compilation options
    set_target_properties(my_cuda_library PROPERTIES
        CUDA_SEPARABLE_COMPILATION ON
        CUDA_ARCHITECTURES "all"
    )

    # Include directories for the library
    target_include_directories(my_cuda_library PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

    # Link the CUDA library with the executable
    target_link_libraries(cc_code PRIVATE my_cuda_library)
else()
    message(STATUS "CUDA not found. Skipping CUDA support.")
endif()
```

---
