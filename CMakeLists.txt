cmake_minimum_required(VERSION 3.21)

set(CMAKE_OSX_DEPLOYMENT_TARGET "10.9" CACHE STRING "Minimum macOS version for deployment")

project ("slurps")

find_library(COREFOUNDATION_LIB CoreFoundation FRAMEWORK REQUIRED)
find_library(COREGRAPHICS_LIB  CoreGraphics  FRAMEWORK REQUIRED)
find_library(IMAGEIO_LIB       ImageIO       FRAMEWORK REQUIRED)

add_executable(slurps "src/main.cpp" "src/Image/Image.cpp" "src/Processor/Processor.cpp" 
    "src/Serializer/Serializer.cpp" "src/Rules/RulesParsing.cpp")

target_link_libraries(slurps PRIVATE
    ${COREFOUNDATION_LIB}
    ${COREGRAPHICS_LIB}
    ${IMAGEIO_LIB}
)

target_compile_options(slurps PRIVATE -mmacosx-version-min=${CMAKE_OSX_DEPLOYMENT_TARGET})
target_link_options(slurps PRIVATE -mmacosx-version-min=${CMAKE_OSX_DEPLOYMENT_TARGET})

target_compile_features(slurps PRIVATE cxx_std_20)

target_include_directories(slurps PRIVATE "src")