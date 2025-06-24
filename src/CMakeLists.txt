# Add executable with main source
add_executable(${PROJECT_NAME}  main.cxx
                                composite_renderer.cxx 
                                utils.cxx
                                vtk_generators.cxx
                                common_types.cxx)

# To add more sources: add them to the add_executable line above
# Example: add_executable(${PROJECT_NAME} main.cxx other_source.cxx another_file.cxx)
# To add headers: they don't need to be explicitly listed in CMake unless they're public headers

# Set up precompiled headers

find_package(VTK 9.2 REQUIRED COMPONENTS 
    CommonCore
    CommonDataModel
    RenderingCore
    RenderingOpenGL2
    InteractionStyle
    RenderingFreeType
    FiltersSources
)

message("VTK_FOUND: ${VTK_FOUND}")
message("VTK_INCLUDE_DIRS: ${VTK_INCLUDE_DIRS}")
message("VTK_LIBRARIES: ${VTK_LIBRARIES}")

target_precompile_headers(${PROJECT_NAME} PRIVATE pch.h)

target_include_directories(${PROJECT_NAME} PRIVATE 
    ${VTK_INCLUDE_DIRS}
    /usr/include/vtk
)

# Make VTK modules available to the project
vtk_module_autoinit(
    TARGETS ${PROJECT_NAME}
    MODULES ${VTK_LIBRARIES}
)

message(STATUS "VTK wants to link: ${VTK_LIBRARIES}")

# Link VTK libraries
target_link_libraries(${PROJECT_NAME} ${VTK_LIBRARIES})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
