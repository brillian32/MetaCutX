import QtQuick
import QtQuick.Controls
import Qt.labs.animation
import QtQuick.Particles
import QtCharts 2.4
import Qt.labs.platform
import QtWebEngine
import QtDataVisualization 1.4

Window {
    id: rootWind
    height: 400
    title: qsTr("resourceView")
    visible: true
    width: 480

    Libriry {
        id: libriry
        anchors.left: rootWind.left
        width: rootWind.width
    }


    Tools{
        id:tools
        anchors.fill: parent
        anchors.rightMargin: 320
        anchors.topMargin: 60
    }


    SearchLine{
        id:searchLine
        anchors.bottomMargin: 280
        // anchors.left:tools.right
        // anchors.right:rootWind.right
        // anchors.top:libriry.bottom
        // height:40
        anchors.fill: parent
        anchors.leftMargin: 160
        anchors.topMargin: 60
    }



    ShowArea{
        id:showArea
        anchors.bottom: rootWind.bottom
        anchors.left: tools.right
        anchors.right: rootWind.right
        anchors.top: searchLine.bottom
    }


}
