cmake_minimum_required(VERSION 3.10)
project(LoadBalancer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(utils)

set(SOURCES
    main.cpp
    src/Balancer.cpp
    src/Request.cpp
    src/Server.cpp
    src/PortHashing.cpp
    src/LeastConnections.cpp
)

add_executable(LoadBalancer ${SOURCES})
