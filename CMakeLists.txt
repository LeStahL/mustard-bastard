cmake_minimum_required(VERSION 3.15)

project(mustard-bastard)

add_subdirectory(thirdparty/SFML)
set(SFML_BUILD_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/thirdparty/SFML/lib/Release")

add_executable(mustard-bastard Main.cpp
    model/Model.cpp
    model/Entity.cpp
    model/WorldPosition.cpp
    model/Player.cpp
)
target_include_directories(mustard-bastard PUBLIC "${PROJECT_SOURCE_DIR}/thirdparty/SFML/include/" "${PROJECT_SOURCE_DIR}/model/")
target_link_directories(mustard-bastard PUBLIC ${SFML_BUILD_DIRECTORY})
set(SFML_LIBRARIES
    SFML-window
    SFML-system
)
target_link_libraries(mustard-bastard ${SFML_LIBRARIES})

foreach(SFML_LIB ${SFML_LIBRARIES})
    add_custom_command(TARGET mustard-bastard POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy "${SFML_BUILD_DIRECTORY}/${SFML_LIB}-3.dll" $<TARGET_FILE_DIR:mustard-bastard>
    )
endforeach()

add_subdirectory(model)