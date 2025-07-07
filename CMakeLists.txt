cmake_minimum_required(VERSION 3.10)
project(FibonacciRoutingSimulation)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -O2")

# Añade los archivos fuente
add_executable(sim
        main.cpp
        SimulationScenario.cpp
        SimulationScenario.h
        Graph.h
        Router.h
        FibonacciHeap.h
)

# Incluye los headers
target_include_directories(sim PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)
