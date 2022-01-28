cmake_minimum_required(VERSION 3.15)

project(mustard-bastard-model)

add_executable(${PROJECT_NAME}-test
    modelTest.cpp

    Entity.h
    Player.h

    WorldPosition.cpp
    Player.cpp
)

target_include_directories(${PROJECT_NAME}-test
PUBLIC .)