cmake_minimum_required(VERSION 3.10)
project(BidirectionalBFS)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add compiler flags
if(MSVC)
    # Visual Studio specific flags
    add_compile_options(/W4 /O2)
else()
    # GCC/Clang flags
    add_compile_options(-Wall -Wextra -O2)
endif()

# Source files
set(SOURCES
    main.cpp
    BidirectionalBFS.cpp
)

# Header files
set(HEADERS
    BidirectionalBFS.h
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Set output directory (optional)
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

