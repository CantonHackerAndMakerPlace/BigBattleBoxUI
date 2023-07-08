import QtQuick 2.2
import QtQuick.Controls 2.2
import QtQuick.Layouts
import Box2D 2.0
import QtMultimedia
import QtQml 2.15
import "../shared"

Rectangle {
    id: confettiPage
    width: 320; height: 480
    color: "lightgray"
    World { id: physicsWorld }
    property list<Item> confetti:[];
    Connections {
        target: mainWidget
        onWinnerChanged: function(text) {
            winningPlayerName.text = "Player " + text + "\nWINS!";
        }
    }
    Connections {
        target: mainWidget
        onRestartConfetti: function () {
            restartConfetti();
        }
    }


    Text {
        id: winningPlayerName
        text: qsTr("waffles")
        font.bold: true
        font.family: "Helvetica"
        font.pixelSize: 75
        onTextChanged: function textChanged(text) {
                winningPlayerName.y = secondPane.height/3 - (winningPlayerName.height/2)
                winningPlayerName.x = secondPane.width/2 - (winningPlayerName.width/2)
            }
        y: winningPlayerName.y = secondPane.height/3 - (winningPlayerName.height/2)
        x: winningPlayerName.x = secondPane.width/2 - (winningPlayerName.width/2)
        z: 4
        onWidthChanged: confettiPage.widthChanged()
        onHeightChanged: confettiPage.heightChanged()
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    Component {
        id: confetti
        RectangleBoxBody {
            id: rect
            width: 20
            height: 20

            world: physicsWorld
            bodyType: Body.Dynamic

            property variant colors : [
                "#FF0000","#FF8000","#FFFF00","#00FF00",
                "#0080FF","#0000FF","#FF00FF","#FFFFFF"
            ]
            property int colorIndex : 0
            property bool animateDeletion: false

            property bool isBall: true
            density: 0.5
            friction: 1
            restitution: 0.2

            border.color: "#999"
            color: colors[colorIndex]
            radius: 3

            PropertyAnimation {
                target: rect
                property: "opacity"
                duration: 1000
                to: 0
                easing.type: Easing.InCubic
                running: animateDeletion
                onRunningChanged: {
                    if (!running)
                        rect.destroy();
                }
            }
        }

    }

    Item {
        id: physicsRoot
        anchors.fill: parent

        Item {
            id: topWall
            height: 10
            y: -10
            anchors.left: parent.left
            anchors.right: parent.right
            BoxBody {
                target: topWall
                world: physicsWorld
                width: topWall.width
                height: topWall.height
            }
        }

        Wall {
            id: leftWall
            width: 40
            anchors {
                left: parent.left
                top: parent.top
                bottom: parent.bottom
                bottomMargin: 40
            }
        }

        Wall {
            id: rightWall
            width: 40
            anchors {
                right: parent.right
                top: parent.top
                bottom: parent.bottom
                bottomMargin: 40
            }
        }

        PhysicsItem {
            id: ground
            height: 40
            world: physicsWorld
            anchors {
                left: parent.left
                right: parent.right
                bottom: parent.bottom
            }
            fixtures: Box {
                id: groundFixture
                width: ground.width
                height: ground.height
                friction: 1
                density: 1
            }
            Rectangle {
                anchors.fill: parent
                color: "#DEDEDE"
            }
        }

        Rectangle {
            id: debugButton
            x: 50
            y: 10
            width: 120
            height: 30
            Text {
                text: debugDraw.visible ? "Debug view: on" : "Debug view: off"
                anchors.centerIn: parent
            }
            color: "#DEDEDE"
            border.color: "#999"
            radius: 5
            MouseArea {
                anchors.fill: parent
                onClicked: debugDraw.visible = !debugDraw.visible;
            }
        }
        Item {
            id:lTimer
            property int fireCount: 0

            Timer {
                id: leftSideConfettiTimer
                interval: 25
                running: true
                repeat: true
                triggeredOnStart: true
                onTriggered: {
                    if (lTimer.fireCount < 200) {
                        lTimer.fireCount += 1;
                        fireConfetti(ground.x + 100, ground.y - 100, 1, -1);
                    } else {
                        leftSideConfettiTimer.stop();
                    }
                }
            }

        }
        Item {
            id:rTimer
            property int fireCount: 0

            Timer {
                id: rightSideConfettiTimer
                interval: 25
                running: true
                repeat: true
                triggeredOnStart: true
                onTriggered: {
                    if (rTimer.fireCount < 200) {
                        rTimer.fireCount += 1;
                        fireConfetti(ground.x + ground.width - (100 + leftWall.width), ground.y - 100, -1, -1);
                    } else {
                        rightSideConfettiTimer.stop();
                    }
                }
            }
        }

        DebugDraw {
            id: debugDraw
            anchors.fill: parent
            world: physicsWorld
            opacity: 0.7
            visible: false
        }
    }

    function fireConfetti(posX, posY, transformX, transformY) {
        var initalAngle = (Math.random() * (70 - 20));
        var angle = (initalAngle + 20);
        var newBox = confetti.createObject(physicsRoot);
        newBox.x = posX;
        newBox.y = posY;
        var impulse = (Math.random() * 10) + 1;
        var impulseX = impulse * Math.cos(angle * Math.PI / 180);
        var impulseY = impulse * Math.sin(angle * Math.PI / 180);
        newBox.colorIndex = (Math.random() * 100) % newBox.colors.length;
        newBox.body.applyLinearImpulse(Qt.point(transformX*impulseX, transformY*impulseY), newBox.body.getWorldCenter());
        confettiPage.confetti.push(newBox);
    }

    function restartConfetti() {
        for (var i = 0; i < confettiPage.confetti.length; i++) {
            confettiPage.confetti[i].destroy();
        }
        confettiPage.confetti = [];
        rTimer.fireCount = 0;
        rightSideConfettiTimer.start();
        lTimer.fireCount = 0;
        leftSideConfettiTimer.start();
    }
}
