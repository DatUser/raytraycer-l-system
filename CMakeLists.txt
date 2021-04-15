set(OPT_FLAGS
    "-Ofast -mtune=native -floop-parallelize-all -fgcse-sm"
)


# Directories containing headers must be specified in the include_directories()
include_directories(
    "src"
    "src/utils"
    "src/parser"
)

# Searches for all .cc files
set(SRC
        "src/utils/vector3.cc"
    "src/utils/image.cc"
    "src/utils/sphere.cc"
    "src/utils/scene.cc"
    "src/utils/cylinder.cc"
    "src/utils/uniform-texture.cc"
    "src/utils/camera.cc"
    "src/utils/triangle.cc"
    "src/utils/ppm-texture.cc"
    "src/parser/parser.cc"
    "src/parser/node-f.cc"
    "src/parser/print-visitor.cc"
    "src/parser/node-start.cc"
    "src/parser/node-rotate.cc"
    "src/parser/generate-visitor.cc"
    "src/parser/node-rule.cc"
    "src/parser/node-diameter.cc"
    "src/parser/dot-visitor.cc"
    "src/tp1.cc")


# SETUP
cmake_minimum_required(VERSION 3.12)
project(Raytracer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OPT_FLAGS} -Wall -Werror -Wextra -pedantic -fopenmp")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g3")# -fsanitize=address")

if (NOT CMAKE_BUILD_TYPE)
    message("No build type selected, default release")
    set(CMAKE_BUILD_TYPE "Release")
endif()

if (CMAKE_BUILD_TYPE STREQUAL "Test")
    message("Test Mode")
    add_executable(raytracer)
    target_sources(raytracer PRIVATE "tests/main.cc" ${SRC})
    target_link_libraries(raytracer PRIVATE ${LIBRARIES})
else()
    add_executable(raytracer)
    target_sources(raytracer PRIVATE "src/tp1.cc" ${SRC})
    target_link_libraries(raytracer PRIVATE ${LIBRARIES})
endif()
