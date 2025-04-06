cmake_minimum_required(VERSION 3.10)
project(tmz)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_TYPE Debug)

include(FetchContent)
FetchContent_Declare(
    ftxui
    GIT_REPOSITORY https://github.com/ArthurSonzogni/FTXUI.git
    GIT_TAG        v6.0.0
)
FetchContent_GetProperties(ftxui)
if(NOT ftxui_POPULATED)
  FetchContent_Populate(ftxui)
  add_subdirectory(${ftxui_SOURCE_DIR} ${ftxui_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

include_directories(${CMAKE_SOURCE_DIR}/utils ${CMAKE_SOURCE_DIR}/include)
add_executable(tmz src/main.cpp src/sys_monitor.cpp src/kernel_info.cpp src/formatter.cpp src/process_monitor.cpp)

target_link_libraries(tmz PRIVATE ftxui::dom ftxui::screen ftxui::component)
