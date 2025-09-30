cmake_minimum_required(VERSION 4.1)
set(CMAKE_CXX_COMPILER "/opt/homebrew/opt/llvm@21/bin/clang")
set(CLANG_DEFAULT_LINKER "/opt/homebrew/opt/lld@21/bin/lld")
project(main C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(libraries/juce)
file(GLOB SOURCE ./*.cpp)
add_executable(main ${SOURCE})

target_compile_options(main PRIVATE -Wall -Wpedantic -g)
target_link_options(main PRIVATE -lc++)
target_link_libraries(main juce::juce_gui_basics juce::juce_audio_formats juce::juce_audio_utils)
