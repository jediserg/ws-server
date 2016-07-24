cmake_minimum_required(VERSION 3.2)
project(ws_server)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_subdirectory(3rdparty/cpptoml)
add_subdirectory(3rdparty/websocketpp)
add_subdirectory(3rdparty/json11)
add_subdirectory(3rdparty/googletest)

include_directories(src 3rdparty/json11 3rdparty/cpptoml/include 3rdparty/websocketpp)

set(SOURCE_FILES
        src/net/auth.hpp
        src/net/server.hpp
        src/net/session.hpp
        src/net/simple_policy.h
        src/net/ws_server_impl.cpp
        src/net/ws_server_impl.h
        src/utils/md5.cpp
        src/utils/md5.h
        src/handler.h
        src/user.cpp
        src/user.h src/handler.cpp src/handler_manager.cpp src/handler_manager.h src/user_manager.cpp src/user_manager.h src/net/policy.h tests/fake_user.h src/ws_server.h src/simple_user_factory.h src/simple_user_factory.cpp)

add_library(ws-server ${SOURCE_FILES})
target_link_libraries(ws-server json11)

add_executable(ws-server-tests tests/user_test.cpp tests/handlers_test.cpp tests/user_manager_test.cpp tests/simple_auth_test.cpp tests/md5_test.cpp tests/fake_policy.h tests/fake_hash.h tests/auth_test.cpp tests/fake_ws_server_impl.h tests/fake_ws_server_impl.cpp tests/server_test.cpp)

add_executable(example-echo examples/echo/main.cpp)

target_link_libraries(ws-server-tests gtest gtest_main ws-server)
target_link_libraries(example-echo ws-server boost_system)
