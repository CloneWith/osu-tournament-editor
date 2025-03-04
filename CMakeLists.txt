cmake_minimum_required(VERSION 3.16)

project(osu-tournament-editor VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)

set(TS_FILES osu-tournament-editor_zh_CN.ts)

set(PROJECT_SOURCES
        main.cpp
        MainWindow.cpp
        MainWindow.h
        MainWindow.ui
        ${TS_FILES}
        ProjectAboutDialog.cpp
        ProjectAboutDialog.h
        ProjectAboutDialog.ui
        Tabs/BasicInformationTab.cpp
        Tabs/BasicInformationTab.h
        Tabs/BasicInformationTab.ui
        Models/EditorTab.cpp
        Models/EditorTab.h
        Models/LadderInfo.h
        Models/RulesetInfo.h
        Models/TournamentMatch.cpp
        Models/TournamentMatch.h
        Models/TournamentRound.h
        Models/TournamentTeam.cpp
        Models/TournamentTeam.h
        Models/TournamentProgression.cpp
        Models/TournamentProgression.h
        Models/TournamentUser.h
        Models/RoundBeatmap.h
        Models/TeamColour.h
        Models/BeatmapChoice.h
        Models/SeedingResult.h
        Models/TournamentBeatmap.h
        Models/SeedingBeatmap.h
        Tabs/WelcomeTab.cpp
        Tabs/WelcomeTab.h
        Tabs/WelcomeTab.ui
        Common.h
        libs/qserializer.h
        Models/ChoiceType.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(osu-tournament-editor
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET osu-tournament-editor APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(osu-tournament-editor SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(osu-tournament-editor
            ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(osu-tournament-editor PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.osu-tournament-editor)
endif()
set_target_properties(osu-tournament-editor PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS osu-tournament-editor
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(osu-tournament-editor)
endif()
