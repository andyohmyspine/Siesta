set(TF_BUILD_TESTS OFF CACHE BOOL "")
set(TF_BUILD_EXAMPLES OFF CACHE BOOL "")
add_subdirectory(taskflow)

add_library(spdlog INTERFACE)
target_include_directories(spdlog INTERFACE spdlog/include)