cmake_minimum_required(VERSION 3.10)
project(CppBankingServer)

set(CMAKE_CXX_STANDARD 17)

add_executable(server
    src/main.cpp
    src/server_epoll.cpp
    src/thread_pool.cpp
    src/client_handler.cpp
    src/database.cpp
    src/logger.cpp
)
