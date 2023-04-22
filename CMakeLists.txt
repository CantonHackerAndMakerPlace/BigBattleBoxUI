cmake_minimum_required(VERSION 3.5)

project(BattleBox VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(ExternalProject)

set(THIRDPARTY_SOURCE_ROOT ${CMAKE_BINARY_DIR}/thirdparty)
set(BOX2D_ROOT ${THIRDPARTY_SOURCE_ROOT}/Box2D)
ExternalProject_Add(Box2d_external
                    PREFIX ${BOX2D_ROOT}
                    GIT_REPOSITORY "https://github.com/erincatto/box2d.git"
                    GIT_TAG "411acc32eb6d4f2e96fc70ddbdf01fe5f9b16230"
                    UPDATE_COMMAND ""
                    PATCH_COMMAND ""
                    BINARY_DIR ${BOX2D_ROOT}/build
                    INSTALL_DIR ${BOX2D_ROOT}/bin
                    BUILD_ALWAYS false
                    INSTALL_COMMAND ""
                    BUILD_BYPRODUCTS ${BOX2D_ROOT}/build/bin/libbox2d.a
                )


link_directories(${BOX2D_ROOT}/build/bin)
ExternalProject_Get_Property(Box2d_external source_dir)
include_directories(${source_dir}/include)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets Multimedia Core SerialPort QuickWidgets Quick Qml)
find_package(Qt6 REQUIRED COMPONENTS Widgets Multimedia Core SerialPort QuickWidgets Quick Qml)

set(BOX2DQML_ROOT ${THIRDPARTY_SOURCE_ROOT}/Box2DQML)

ExternalProject_Add(Box2dQML_external
                    PREFIX ${BOX2DQML_ROOT}
                    CMAKE_ARGS -DQt6_DIR=${Qt6_DIR} -DCMAKE_INSTALL_PREFIX=${BOX2DQML_ROOT}/bin
                    GIT_REPOSITORY "https://github.com/qml-box2d/qml-box2d.git"
                    BINARY_DIR ${BOX2DQML_ROOT}/build
                    INSTALL_DIR ${BOX2DQML_ROOT}/bin/lib
                )

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
    deathmatchruntime.h
    deathmatchruntime.cpp
    util.h
    playerwinswidget.h
    playerwinswidget.cpp
    playerwinswidget.ui
    confettigi.h
    confettigi.cpp
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

qt_add_qml_module(BattleBox
    URI qmlproject
    VERSION 1.0
    QML_FILES
        qmlproject/main.qml

        qmlproject/cannon/Wall.qml
        qmlproject/cannon/main.qml

        qmlproject/shared/BoxBody.qml
        qmlproject/shared/ChainBody.qml
        qmlproject/shared/CircleBody.qml
        qmlproject/shared/EdgeBody.qml
        qmlproject/shared/ImageBoxBody.qml
        qmlproject/shared/PhysicsItem.qml
        qmlproject/shared/PolygonBody.qml
        qmlproject/shared/RectangleBoxBody.qml
        qmlproject/shared/ScreenBoundaries.qml
    RESOURCES
        qmlproject/cannon/images/cannon.png
        qmlproject/cannon/images/cannon_base.png
        qmlproject/cannon/images/wall.jpg

        qmlproject/cannon/sounds/cannon.wav
        qmlproject/cannon/sounds/gear.wav

)


target_link_libraries(BattleBox PRIVATE
    ${BOX2D_ROOT}/build/bin/libbox2d.a
    Qt6::Core
    Qt6::Widgets
    Qt6::Multimedia
    Qt6::SerialPort
    Qt6::QuickWidgets
    Qt6::Quick
    Qt6::Qml
)

target_compile_features(BattleBox PRIVATE cxx_std_17)
set_target_properties(BattleBox PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)
qt_import_plugins(BattleBox INCLUDE qmlproject)

add_compile_definitions(RESOURCE_LOCATION="${CMAKE_SOURCE_DIR}/resources")

install(TARGETS BattleBox
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(BattleBox)
endif()


