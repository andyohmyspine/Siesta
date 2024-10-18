set(TF_BUILD_TESTS OFF CACHE BOOL "")
set(TF_BUILD_EXAMPLES OFF CACHE BOOL "")
add_subdirectory(taskflow)

add_library(spdlog INTERFACE)
target_include_directories(spdlog INTERFACE spdlog/include)

add_library(json INTERFACE)
target_include_directories(json INTERFACE json/single_include)

add_library(dynalo INTERFACE)
target_include_directories(dynalo INTERFACE dynalo/include)