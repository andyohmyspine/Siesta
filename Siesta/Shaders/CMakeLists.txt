file(GLOB_RECURSE Shaders *.hlsl LIST_DIRECTORIES ON)
add_custom_target(Shaders SOURCES ${Shaders})
source_group(TREE ${CMAKE_CURRENT_LIST_DIR} FILES ${Shaders})

set_target_properties(Shaders PROPERTIES FOLDER Siesta/Shaders)