import QtQuick
import QtQml 2.15
//import Box2D 2.0

import QtQuick.Window 2.1;
import QtQuick.Layouts 1.1

Item {
    id: secondPane
    Layout.preferredWidth: 800
    Layout.fillHeight: true

    Loader {
        id: sceneLoader
        width: parent.width
        height: parent.height
        source: mainWidget.source
        focus: true
        Connections{
            target: mainWidget
            function onSourceChanged(s) {
                sceneLoader.setSource(s);
            }
        }
    }
}

