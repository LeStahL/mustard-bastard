cmake_minimum_required(VERSION 3.15)

project(mustard-bastard)

add_subdirectory(thirdparty/SFML)
set(SFML_BUILD_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/thirdparty/SFML/lib/Release")

add_executable(mustard-bastard Main.cpp
    model/Model.cpp
    model/Entity.cpp
    model/WorldPosition.cpp
    model/WorldOrientation.cpp
    model/Player.cpp
    model/Enemy.cpp
    model/FloorThing.cpp
    model/MainMenuState.cpp
    model/MenuState.cpp
    model/HighscoreList.cpp

    view/ViewStuff.cpp
    view/GameView.cpp
    view/MainMenuView.cpp
    view/HighscoreMenuView.cpp
    view/HeadsUpDisplayView.cpp

    logic/GameLogic.cpp

    utility/Animation.cpp
    utility/MusicPlayer.cpp

    controller/MainMenuInputController.cpp
    controller/GameInputController.cpp
    controller/MenuController.cpp
    controller/HighscoreMenuInputController.cpp
)
target_include_directories(mustard-bastard PUBLIC
    "${PROJECT_SOURCE_DIR}/thirdparty/SFML/include/"
    "${PROJECT_SOURCE_DIR}/."
    "${PROJECT_SOURCE_DIR}/model/"
    "${PROJECT_SOURCE_DIR}/view/"
    "${PROJECT_SOURCE_DIR}/controller/"
    "${PROJECT_SOURCE_DIR}/utility/"
    "${PROJECT_SOURCE_DIR}/logic/"
)
target_link_directories(mustard-bastard PUBLIC ${SFML_BUILD_DIRECTORY})
set(SFML_LIBRARIES
    SFML-window
    SFML-system
    SFML-graphics
    SFML-audio
)
target_link_libraries(mustard-bastard ${SFML_LIBRARIES})
set_property(TARGET mustard-bastard PROPERTY CXX_STANDARD 17)

# Put SFML libraries into place
foreach(SFML_LIB ${SFML_LIBRARIES})
    add_custom_command(TARGET mustard-bastard POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy "${SFML_BUILD_DIRECTORY}/${SFML_LIB}-3.dll" $<TARGET_FILE_DIR:mustard-bastard>
    )
endforeach()
add_custom_command(TARGET mustard-bastard POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${PROJECT_SOURCE_DIR}/assets" "$<TARGET_FILE_DIR:mustard-bastard>/assets"
)
add_custom_command(TARGET mustard-bastard POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy "${PROJECT_SOURCE_DIR}/thirdparty/SFML/extlibs/bin/x64/openal32.dll" "$<TARGET_FILE_DIR:mustard-bastard>"
)

find_file(FONT NAMES Fira_Code_v6.2.zip HINTS ${CMAKE_CURRENT_BINARY_DIR})
if(${FONT} MATCHES FONT-NOTFOUND)
    message(STATUS "Font not found. Will download.")
    file(DOWNLOAD https://github.com/tonsky/FiraCode/releases/download/6.2/Fira_Code_v6.2.zip Fira_Code_v6.2.zip SHOW_PROGRESS)
    file(ARCHIVE_EXTRACT INPUT Fira_Code_v6.2.zip DESTINATION Fira_Code_v6.2 VERBOSE)
endif()
add_custom_command(TARGET mustard-bastard POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/Fira_Code_v6.2/ttf/FiraCode-Regular.ttf" "$<TARGET_FILE_DIR:mustard-bastard>/assets/FiraCode-Regular.ttf"
)

# Pack release archive
add_custom_command(TARGET mustard-bastard POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E tar "cfv" "mustard-bastard-team210.zip" --format=zip "$<TARGET_FILE_DIR:mustard-bastard>"
)
