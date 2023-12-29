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
include_directories(${CMAKE_SOURCE_DIR}/widgets)
include_directories(${CMAKE_SOURCE_DIR}/screens/configuration)

set(PROJECT_SOURCES
    battleboxmainwindow.cpp
    battleboxmainwindow.h
    battleboxmainwindow.ui
    durationwidget.h
    durationwidget.cpp
    durationwidget.ui
    deathmatchrunningclockwidget.h
    deathmatchrunningclockwidget.cpp
    deathmatchrunningclockwidget.ui
    deathmatchcompletewidget.h
    deathmatchcompletewidget.cpp
    deathmatchcompletewidget.ui
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
    triggeringanimation.h
    triggeringanimation.cpp
    configurationwidget.h
    configurationwidget.cpp
    configurationwidget.ui
    configurationcontentwidget.h
    configurationcontentwidget.cpp
    configurationcontentwidget.ui


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
    util.h
    playerwinswidget.h
    playerwinswidget.cpp
    playerwinswidget.ui

    integerobject.h
    integerobject.cpp
    unificationkindobject.h
    unificationkindobject.cpp

    physical_state/arduinoconnectionmanager.h
    physical_state/arduinoconnectionmanager.cpp
    physical_state/battleboxphysicalstate.h
    physical_state/battleboxphysicalstate.cpp
    physical_state/physicalbutton.h
    physical_state/physicalbutton.cpp
    physical_state/physicalplayerstate.h
    physical_state/physicalplayerstate.cpp
    physical_state/physicalrelay.h
    physical_state/physicalrelay.cpp
    physical_state/arduinomessanger.h
    physical_state/arduinomessanger.cpp
    physical_state/ledcontroller.h
    physical_state/ledcontroller.cpp

    physical_state/arduinoclient.h
    physical_state/arduinoclient.cpp

    physical_state/ledalgo/ledalgo.h
    physical_state/ledalgo/ledalgo.cpp
    physical_state/ledalgo/breath.h
    physical_state/ledalgo/breath.cpp
    physical_state/ledalgo/countdownfill.h
    physical_state/ledalgo/countdownfill.cpp
    physical_state/ledalgo/blink.h
    physical_state/ledalgo/blink.cpp
    physical_state/ledalgo/cylon.h
    physical_state/ledalgo/cylon.cpp
    physical_state/ledalgo/rampup.h
    physical_state/ledalgo/rampup.cpp
    physical_state/ledalgo/solidcolors.h
    physical_state/ledalgo/solidcolors.cpp
    physical_state/ledalgo/lightoff.h
    physical_state/ledalgo/lightoff.cpp

    app_state/applicationstate.h
    app_state/applicationstate.cpp
    app_state/screen.h
    app_state/screen.cpp
    app_state/deathmatchgamesession.h
    app_state/deathmatchgamesession.cpp
    app_state/battleboxviewmodel.h
    app_state/battleboxviewmodel.cpp
    app_state/deathmatchplayerreadymodel.h
    app_state/deathmatchplayerreadymodel.cpp
    app_state/deathmatchconfig.h
    app_state/deathmatchconfig.cpp
    app_state/deathmatchruntime.h
    app_state/deathmatchruntime.cpp
    app_state/soccerconfig.h
    app_state/soccerconfig.cpp
    app_state/soccermatch.h
    app_state/soccermatch.cpp
    app_state/soccerteamready.h
    app_state/soccerteamready.cpp

    # LED configuration files
    app_state/led/ledconfiguration.h
    app_state/led/ledconfiguration.cpp
    app_state/led/generalledconfiguration.h
    app_state/led/generalledconfiguration.cpp
    app_state/led/ledidleconfiguration.h
    app_state/led/ledidleconfiguration.cpp
    app_state/led/interpolation.h
    app_state/led/interpolation.cpp
    app_state/led/ledalgoconfig/ledalgoconfig.h
    app_state/led/ledalgoconfig/ledalgoconfig.cpp
    app_state/led/ledalgoconfig/breathconfig.h
    app_state/led/ledalgoconfig/breathconfig.cpp
    app_state/led/ledalgoconfig/blinkconfig.h
    app_state/led/ledalgoconfig/blinkconfig.cpp
    app_state/led/ledalgoconfig/countdownfillconfig.h
    app_state/led/ledalgoconfig/countdownfillconfig.cpp
    app_state/led/ledalgoconfig/cylonconfig.h
    app_state/led/ledalgoconfig/cylonconfig.cpp
    app_state/led/ledalgoconfig/rampupconfig.h
    app_state/led/ledalgoconfig/rampupconfig.cpp
    app_state/led/ledalgoconfig/solidcolorconfig.h
    app_state/led/ledalgoconfig/solidcolorconfig.cpp


    # Screens directory used for managing individual screen widgets
    screens/configuration/ledcontrolwidget.h
    screens/configuration/ledcontrolwidget.cpp
    screens/configuration/ledcontrolwidget.ui
    screens/configuration/interpolationselectorwidget.h
    screens/configuration/interpolationselectorwidget.cpp
    screens/configuration/interpolationselectorwidget.ui
    screens/configuration/idleledconfigurationwidget.h
    screens/configuration/idleledconfigurationwidget.cpp
    screens/configuration/idleledconfigurationwidget.ui
    screens/configuration/generalledconfigurationwidget.h
    screens/configuration/generalledconfigurationwidget.cpp
    screens/configuration/generalledconfigurationwidget.ui
    screens/configuration/colorselectionwidget.h
    screens/configuration/colorselectionwidget.cpp
    screens/configuration/colorselectionwidget.ui
    screens/configuration/blinkconfigwidget.h
    screens/configuration/blinkconfigwidget.cpp
    screens/configuration/blinkconfigwidget.ui
    screens/configuration/breathconfigwidget.h
    screens/configuration/breathconfigwidget.cpp
    screens/configuration/breathconfigwidget.ui
    screens/configuration/countdownconfigwidget.h
    screens/configuration/countdownconfigwidget.cpp
    screens/configuration/countdownconfigwidget.ui
    screens/configuration/cylonconfigwidget.h
    screens/configuration/cylonconfigwidget.cpp
    screens/configuration/cylonconfigwidget.ui
    screens/configuration/rampupconfigwidget.h
    screens/configuration/rampupconfigwidget.cpp
    screens/configuration/rampupconfigwidget.ui
    screens/configuration/offconfigwidget.h
    screens/configuration/offconfigwidget.cpp
    screens/configuration/offconfigwidget.ui
    screens/configuration/solidcolorconfigwidget.h
    screens/configuration/solidcolorconfigwidget.cpp
    screens/configuration/solidcolorconfigwidget.ui
    screens/configuration/cycledurationconfigwidget.h
    screens/configuration/cycledurationconfigwidget.cpp
    screens/configuration/cycledurationconfigwidget.ui
    screens/configuration/unifiedcheckbox.h
    screens/configuration/unifiedcheckbox.cpp
    screens/configuration/unifiedcheckbox.ui

    # other custom widgets
    widgets/RangeSlider.h
    widgets/RangeSlider.cpp
    widgets/brightnessrangeslider.h
    widgets/brightnessrangeslider.cpp
    widgets/brightnessselectionwidget.h
    widgets/brightnessselectionwidget.cpp
    widgets/brightnessselectionwidget.ui
    widgets/algorithmdropdown.h
    widgets/algorithmdropdown.cpp
    widgets/algorithmdropdown.ui


    defaultrestorable.h
    defaultrestorable.cpp

    integerobject.h
    integerobject.cpp

    interpolationcurveobject.h
    interpolationcurveobject.cpp
    colorobject.h
    colorobject.cpp
    booleanobject.h
    booleanobject.cpp
    qrealobject.h
    qrealobject.cpp

    algokindobject.h
    algokindobject.cpp

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

        qmlproject/confetti/main.qml
        qmlproject/confetti/Wall.qml
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

add_compile_definitions(RESOURCE_LOCATION="${CMAKE_SOURCE_DIR}/resources" BOX2DQML_ROOT="${BOX2DQML_ROOT}")

install(TARGETS BattleBox
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(BattleBox)
endif()


