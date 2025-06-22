# Add executable with main source
add_executable(${PROJECT_NAME} main.cxx
                                composite_renderer.cxx 
                                vtk_generators.cxx)

# To add more sources: add them to the add_executable line above
# Example: add_executable(${PROJECT_NAME} main.cxx other_source.cxx another_file.cxx)
# To add headers: they don't need to be explicitly listed in CMake unless they're public headers

# Set up precompiled headers
target_precompile_headers(${PROJECT_NAME} PRIVATE pch.h)

target_include_directories(${PROJECT_NAME} PRIVATE 
    ${VTK_INCLUDE_DIRS}
    /usr/include/vtk
)

# Link VTK libraries
target_link_libraries(${PROJECT_NAME} ${VTK_LIBRARIES})

