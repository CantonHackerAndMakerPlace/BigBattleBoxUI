cmake_minimum_required(VERSION 3.5)

project(BattleBox VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Multimedia Core SerialPort)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Multimedia Core SerialPort)

include_directories(${CMAKE_SOURCE_DIR})

set(PROJECT_SOURCES
    battleboxmainwindow.cpp
    battleboxmainwindow.h
    battleboxmainwindow.ui
    durationwidget.h
    durationwidget.cpp
    durationwidget.ui
    battleboxviewmodel.h
    battleboxviewmodel.cpp
    deathmatchplayerreadymodel.h
    deathmatchplayerreadymodel.cpp
    deathmatchconfig.h
    deathmatchconfig.cpp
    deathmatchrunningclockwidget.h
    deathmatchrunningclockwidget.cpp
    deathmatchrunningclockwidget.ui
    deathmatchcompletewidget.h
    deathmatchcompletewidget.cpp
    deathmatchcompletewidget.ui
    soccerconfig.h
    soccerconfig.cpp
    soccermatch.h
    soccermatch.cpp
    soccerteamready.h
    soccerteamready.cpp
    soccerrunningclockwidget.h
    soccerrunningclockwidget.cpp
    soccerrunningclockwidget.ui
    soccergameoverwidget.h
    soccergameoverwidget.cpp
    soccergameoverwidget.ui
    soccerresumecountdownwidget.h
    soccerresumecountdownwidget.cpp
    soccerresumecountdownwidget.ui
    mediadialog.h
    mediadialog.cpp
    mediadialog.ui
    resources.qrc
    media.h
    media.cpp
    triggeringanimation.h
    triggeringanimation.cpp
    battleboxphysicalstate.h
    battleboxphysicalstate.cpp
    physicalbutton.h
    physicalbutton.cpp
    physicalplayerstate.h
    physicalplayerstate.cpp
    arduinoconnectionmanager.h
    arduinoconnectionmanager.cpp
    configurationwidget.h
    configurationwidget.cpp
    configurationwidget.ui
    configurationcontentwidget.h
    configurationcontentwidget.cpp
    configurationcontentwidget.ui
    physicalrelay.h
    physicalrelay.cpp
    buttonconfigwidget.h
    buttonconfigwidget.cpp
    buttonconfigwidget.ui
    playerstatuslights.h
    playerstatuslights.cpp
    playerstatuslights.ui
    stateindicatorwidget.h
    stateindicatorwidget.cpp
    stateindicatorwidget.ui
    soundeffectmedia.h
    soundeffectmedia.cpp
    main.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(BattleBox
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET BattleBox APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(BattleBox SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(BattleBox
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(BattleBox PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Multimedia Qt${QT_VERSION_MAJOR}::SerialPort)
target_compile_features(BattleBox PRIVATE cxx_std_17)
set_target_properties(BattleBox PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)
add_compile_definitions(RESOURCE_LOCATION="${CMAKE_SOURCE_DIR}/resources")

install(TARGETS BattleBox
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(BattleBox)
endif()
