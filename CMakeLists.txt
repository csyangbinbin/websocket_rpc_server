cmake_minimum_required(VERSION 3.9.3)

include(cmake/cable/bootstrap.cmake)
include(CableBuildInfo)
include(CableBuildType)
include(CableToolchains)
include(GNUInstallDirs)

cable_configure_toolchain(DEFAULT cxx17-pic)

set(CFX_CPP_CMAKE_DIR "${CMAKE_CURRENT_LIST_DIR}/cmake" CACHE PATH "The path to the cmake directory")
list(APPEND CMAKE_MODULE_PATH ${CFX_CPP_CMAKE_DIR})

set(HUNTER_CONFIGURATION_TYPES Release CACHE STRING "Hunter configuration types")
set(HUNTER_JOBS_NUMBER 4 CACHE STRING "Hunter jobs number")
#set(HUNTER_CACHE_SERVERS "https://github.com/ethereum/hunter-cache" CACHE STRING "Hunter cache servers")
#set(HUNTER_PASSWORDS_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Hunter/passwords.cmake CACHE STRING "Hunter password path")

include(HunterGate)
HunterGate(
    URL "https://github.com/ruslo/hunter/archive/v0.23.211.tar.gz"
    SHA1 "c022f0c2480e835a6bafdd734035ec2071b51897"
    LOCAL
)
cable_set_build_type(DEFAULT Release CONFIGURATION_TYPES Debug;Release;RelWithDebInfo)

project(WSRPC)
set(PROJECT_VERSION 0.0.1)


hunter_add_package(jsoncpp)
find_package(jsoncpp CONFIG REQUIRED)

hunter_add_package(libjson-rpc-cpp)
find_package(libjson-rpc-cpp CONFIG REQUIRED)

include_directories(${CMAKE_SOURCE_DIR})

add_executable(ws_rpc
       src/main.cpp
       include/abstractstubserver.h
       src/stubserver.cpp
       include/websocket_server.h
       include/MyStubServer.h
       src/websocket_server.cpp
        )

target_link_libraries( ws_rpc 
libjson-rpc-cpp::server
)