import QtQuick
import QtQuick.Controls

Slider {
        property bool blockSig: false
        property bool blockSig2: false
        width: parent.width
        height: 20
        id: control
        value: 10
        from: 0
        to:100

        background: Rectangle {
            x: control.leftPadding
            y: control.topPadding + control.availableHeight / 2 - height / 2
            implicitWidth: 200
            implicitHeight: 4
            width: control.availableWidth
            height: implicitHeight
            radius: 2
            color: "#353d46"

            Rectangle {
                width: control.visualPosition * parent.width
                height: parent.height
                color: "#44f1c6"
                radius: 2
            }
        }

        handle: Rectangle {
            x: control.leftPadding + control.visualPosition * (control.availableWidth - width)
            y: control.topPadding + control.availableHeight / 2 - height / 2
            width:  !control.hovered ?16:20
            height: !control.hovered ?16:20
            radius: !control.hovered ?8:10
            color: control.hovered ? "#4f575d" : "#4f575d"
            border.color:  control.hovered ? "#f0f8fe": "#c3cad0"
            border.width: 2
            MouseArea{
                anchors.fill: parent
                onPressed: {
                    control.blockSig2 = true
                }
                onReleased: {
                    control.blockSig2 = false
                }
            }
        }

        onValueChanged: {
            if (blockSig) {
                return;
            }
            console.log("value:",value,parseInt(value))
            playController.setCurrentFrame(parseInt(value))
        }
}
