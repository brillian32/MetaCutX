import QtQuick
import QtQuick.Controls
import Qt.labs.animation
import QtQuick.Particles
import QtCharts 2.4
import Qt.labs.platform
import QtWebEngine
import QtDataVisualization 1.4


Rectangle {
    id: libriry
    color: "#808080"
    height: 60


    Image {
        id: media
        anchors.left: libriry.left
        anchors.leftMargin: 30
        anchors.verticalCenter: libriry.verticalCenter
        height: 30
        opacity: 1
        source: "qrc:img/Media.png"
        width: 30

        MouseArea {
            anchors.fill: parent

            onPressed: {
                parent.opacity = 0.5;
                parent.scale = 1.2;
            }
            onReleased: {
                parent.opacity = 1;
                parent.scale =
                // do something
                1;
            }
        }
    }
    Image {
        id: audio
        anchors.left: media.right
        anchors.leftMargin: 30
        anchors.verticalCenter: libriry.verticalCenter
        height: 30
        opacity: 1
        source: "qrc:img/Audio.png"
        width: 30

        MouseArea {
            anchors.fill: parent

            onPressed: {
                parent.opacity = 0.5;
                parent.scale = 1.2;
            }
            onReleased: {
                parent.opacity = 1;
                parent.scale =
                // do something
                1;
            }
        }
    }
    Image {
        id: effects
        anchors.left: audio.right
        anchors.leftMargin: 30
        anchors.verticalCenter: libriry.verticalCenter
        height: 30
        opacity: 1
        source: "qrc:img/Effects.png"
        width: 30

        MouseArea {
            anchors.fill: parent

            onPressed: {
                parent.opacity = 0.5;
                parent.scale = 1.2;
            }
            onReleased: {
                parent.opacity = 1;
                parent.scale =
                // do something
                1;
            }
        }
    }
}

