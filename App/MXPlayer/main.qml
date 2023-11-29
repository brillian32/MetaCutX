import QtQuick
import QtQuick.Controls
import QtMultimedia
//import FrameProvider 1.0



Window {
    id:rootWind
    width: 640
    height: 480
    visible: true
    title: qsTr("Player")
    color: "#000000"

    PlayerSlider{
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10
        width: parent.width - 20
    }

    VideoOutput {
        id: videoContainer
        anchors.fill: parent
        fillMode: VideoOutput.PreserveAspectFit
    }

//    FrameProvider{
//        id:frameProvider
//        videoSink:videoContainer.videoSink
//    }

    Component.onCompleted: {
        frameProvider.debug();
        frameProvider.videoSink = videoContainer.videoSink
    }
}
