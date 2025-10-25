cmake_minimum_required(VERSION 3.18)
project(mtCalorimeter LANGUAGES CXX)

find_package(Geant4 REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB sources CONFIGURE_DEPENDS
    src/*.cc
)
file(GLOB headers CONFIGURE_DEPENDS
    include/*.hh
)

add_executable(mtCalorimeter ${sources} ${headers})

target_include_directories(mtCalorimeter PRIVATE include ${Geant4_INCLUDE_DIR})

target_link_libraries(mtCalorimeter PRIVATE ${Geant4_LIBRARIES})

set_target_properties(mtCalorimeter PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}
)

install(TARGETS mtCalorimeter DESTINATION bin)
install(DIRECTORY macros/ DESTINATION share/macros)
