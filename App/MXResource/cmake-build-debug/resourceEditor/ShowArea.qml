import QtQuick
import QtQuick.Controls
import Qt.labs.animation
import QtQuick.Particles
import QtCharts 2.4
import Qt.labs.platform
import QtWebEngine
import QtDataVisualization 1.4

Rectangle {
    id: showArea
    color: "black"

    Rectangle {
        id: video
        color: "#a9a9a9"
        height: 65
        width: 90
        x: 30
        y: 30
        radius:10

        MouseArea {
            anchors.fill: parent
            drag.target: parent
            drag.axis:Drag.XAxis|Drag.YAxis;
            drag.minimumX:5
            // drag.maximumX:showArea.width-video.width
            drag.minimumY:5
            // drag.maximumY:showArea.height-video.height
        }
    }
}
