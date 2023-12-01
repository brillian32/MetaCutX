import QtQuick
import QtQuick.Controls
import Qt.labs.animation
import QtQuick.Particles
import QtCharts 2.4
import Qt.labs.platform
import QtWebEngine
import QtDataVisualization 1.4


Rectangle {
    id: tools



    Rectangle {
        id: tool1
        anchors.horizontalCenter: tools.horizontalCenter
        anchors.top: tools.top
        anchors.topMargin: 20
        color: "#00ffff"
        height: 40
        radius: 10
        width: 120
    }
    Rectangle {
        id: tool2
        anchors.horizontalCenter: tools.horizontalCenter
        anchors.top: tool1.bottom
        anchors.topMargin: 30
        color: "#00ffff"
        height: 40
        radius: 10
        width: 120
    }
}

