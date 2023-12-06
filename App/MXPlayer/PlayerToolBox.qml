import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: toolBox
    width: 200
    height: 200
    color: "#181c1f"
    radius: 0
    border.color: "red"
    border.width: 2

    RowLayout {
        id: toolBoxLayout
        anchors.fill: parent
        spacing: 10
        RowLayout {
            spacing: 10

            ToolButton {
                icon.source: "qrc:/img/pre.png"
                onClicked: {
                    playController.preFrame();
                    console.log("pre");
                }
            }
            ToolButton {
                icon.source: "qrc:/img/next.png"
                onClicked: {
                    playController.nextFrame();
                    console.log("next");
                }
            }
            ToolButton {
                icon.source: "qrc:/img/play.png"
                onClicked: {
                    if (playController.isPlaying()) {
                        icon.source = "qrc:/img/play.png"
                        playController.pause();
                    }
                    else{
                        playController.play();
                        icon.source = "qrc:/img/pause.png"
                        console.log("play");
                    }
                }
            }
        //     ToolButton {
        //         icon.source: "qrc:/img/pause.png"
        //         onClicked: {
        //             console.log("pause");
        //         }
        //     }
        }
    }
}
