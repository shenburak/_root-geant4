cmake_minimum_required(VERSION 3.18)
project(telescope LANGUAGES CXX)

find_package(Geant4 REQUIRED)
find_package(ROOT COMPONENTS Hist Tree RIO REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB sources CONFIGURE_DEPENDS
    src/*.cc
)
file(GLOB headers CONFIGURE_DEPENDS
    include/*.hh
)

add_executable(telescope ${sources} ${headers})

target_include_directories(telescope PRIVATE include ${Geant4_INCLUDE_DIR} ${ROOT_INCLUDE_DIRS})

target_link_libraries(telescope PRIVATE ${Geant4_LIBRARIES} ${ROOT_LIBRARIES})

set_target_properties(telescope PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}
)

install(TARGETS telescope DESTINATION bin)
install(DIRECTORY macros/ DESTINATION share/macros)
