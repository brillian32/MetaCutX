import QtQuick
import QtQuick.Controls
import Qt.labs.animation
import QtQuick.Particles
import QtCharts 2.4
import Qt.labs.platform
import QtWebEngine
import QtDataVisualization 1.4


Rectangle {
    id: searchLine



    TextField {
        id: textField
        anchors.left: searchLine.left
        anchors.leftMargin: 20
        anchors.verticalCenter: searchLine.verticalCenter
        height: 30
        width: 120
    }
}

