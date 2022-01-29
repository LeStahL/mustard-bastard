cmake_minimum_required(VERSION 3.15)

project(mustard-bastard-model)

add_executable(${PROJECT_NAME}-test
    modelTest.cpp

    Model.h
    Entity.h
    WorldPosition.h
    Player.h

    Model.cpp
    Entity.cpp
    WorldPosition.cpp
    Player.cpp
)

target_include_directories(${PROJECT_NAME}-test
PUBLIC .)