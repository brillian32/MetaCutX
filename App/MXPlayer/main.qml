import QtQuick
import QtQuick.Controls
import QtMultimedia
//import FrameProvider 1.0
import MXPlayController 1.0

Window {
    id: rootWind
    color: "#000000"
    height: 480
    title: qsTr("Player")
    visible: true
    width: 640

    //    FrameProvider{
    //        id:frameProvider
    //        videoSink:videoContainer.videoSink
    //    }
    Component.onCompleted: {
        frameProvider.debug();
        frameProvider.videoSink = videoContainer.videoSink;
    }

    PlayerSlider {
        id: slider
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 50
        anchors.left: parent.left
        anchors.leftMargin: 10
        width: parent.width - 20
        Component.onCompleted: {
            slider.value = 0;
            slider.from = 0;
            slider.to = playController.getFrameCount();
            console.log("slider.to = " + slider.to);
        }
    }
    PlayerToolBox {
        anchors.top: slider.bottom
        anchors.bottomMargin: 6
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10
        height: 30
    }
    VideoOutput {
        id: videoContainer
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 70
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.top: parent.top
        anchors.topMargin: 10
        fillMode: VideoOutput.PreserveAspectFit
    }
    PlayController {
        id: playController
    }
}
