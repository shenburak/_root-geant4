cmake_minimum_required(VERSION 3.18)
project(emShowcase LANGUAGES CXX)

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

add_executable(emShowcase ${sources} ${headers})

target_include_directories(emShowcase PRIVATE include ${Geant4_INCLUDE_DIR})

target_link_libraries(emShowcase PRIVATE ${Geant4_LIBRARIES})

set_target_properties(emShowcase PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}
)

install(TARGETS emShowcase DESTINATION bin)
install(DIRECTORY macros/ DESTINATION share/macros)
