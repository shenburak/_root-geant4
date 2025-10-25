cmake_minimum_required(VERSION 3.18)
project(minimalDetector LANGUAGES CXX)

find_package(Geant4 REQUIRED ui_all vis_all)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB sources CONFIGURE_DEPENDS
    src/*.cc
)
file(GLOB headers CONFIGURE_DEPENDS
    include/*.hh
)

add_executable(minimalDetector ${sources} ${headers})

target_include_directories(minimalDetector PRIVATE include ${Geant4_INCLUDE_DIR})

target_link_libraries(minimalDetector PRIVATE ${Geant4_LIBRARIES})

set(example_macro_dir ${PROJECT_SOURCE_DIR}/macros)
set_target_properties(minimalDetector PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}
)

install(TARGETS minimalDetector DESTINATION bin)
install(DIRECTORY macros/ DESTINATION share/macros)
