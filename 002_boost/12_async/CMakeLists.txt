cmake_minimum_required(VERSION 3.28)
project(boost_learn)
add_executable(server 12_async_tcp_service.cpp)
target_include_directories(server PUBLIC "D:\\tools\\gitee\\something\\libs\\include\\boost-1_86")


add_executable(client 12_async_tcp_client.cpp)
target_include_directories(client PUBLIC "D:\\tools\\gitee\\something\\libs\\include\\boost-1_86")
