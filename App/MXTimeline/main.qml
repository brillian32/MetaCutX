import QtQuick

Window {
    id:rootWind
    width: 640
    height: 480
    visible: true
    title: qsTr("timelineView")
color: "#000000"


    Rectangle{
         z:10
         id:addTrack
         anchors.left: rootWind.left
         width: 100
         height:40
         color:"#141a22"
        Image{
            width: 17
            height: 17
            anchors.left: addTrack.left
            anchors.leftMargin: 5
            anchors.verticalCenter:addTrack.verticalCenter
            source: "qrc:img/addTrack.png"
            opacity: 1
            MouseArea{
                anchors.fill:  parent
                onPressed: {
                    parent.opacity = 0.5
                    parent.scale = 1.2
                }
                onReleased: {
                    parent.opacity = 1
                    parent.scale = 1
                    track.addTrack();
                }
            }

        }
    }



    TimeScale{
        id:timeRuler
        anchors.left: addTrack.right
        anchors.top: rootWind.top

    }
    TrackHead{
        id:track
        anchors.top:timeRuler.bottom
        anchors.left: rootWind.left
    }
}
