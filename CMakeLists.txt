cmake_minimum_required( VERSION 2.8 )

project( json2svg )

FIND_PACKAGE( Boost 1.40 COMPONENTS program_options REQUIRED )

add_executable( json2svg
    src/main.cpp
)

target_link_libraries( json2svg
    ${Boost_LIBRARIES}
)

target_compile_options( json2svg PUBLIC -std=c++14 )
