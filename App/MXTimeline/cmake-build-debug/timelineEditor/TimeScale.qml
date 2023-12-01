import QtQuick
import Qt.labs.animation

Rectangle {

    id:time_sacle
    z:10
    width: parent.width
    height: 40
    visible: true

    color: "#141a22"
    focus: true

    Component.onCompleted:{
            creatModel(200);

    }

    ListModel{
        id:modelList
    }

    Component{
        id:child_com

            Rectangle{
                id:rect
                width: 1.5
                height: (index%10)===0 ? 22 : 15
                radius: 1
                color: "#bdbfc1"

                Text {
                    id: txt
                    color: "#bdbfc1"
                    anchors.horizontalCenter: rect.horizontalCenter
                    anchors.top:rect.bottom
                    font.pointSize: 10
                    text:(index%10)===0 ?modelList.get(index).idx : ""

                    MouseArea{
                        anchors.fill: parent
                        propagateComposedEvents:true
                        onClicked: {
                            console.log(index)
                        }
                }

                }
            }




        }

    Row{
        id: row
        spacing: 4
        //设定范围
        BoundaryRule on spacing {
            id: minMaxRule
            minimum: 2
            maximum: 10
        }
        Repeater{
            id:repeat
            model: modelList
            delegate: child_com
            }

        }

    MouseArea{
        id:mouseArea
        anchors.fill: parent
        //drag.target:parent
        property bool isPressed: false
        property double pressedX: 0
        property double pressedDragX: 0
        propagateComposedEvents:true
        hoverEnabled : true

        onClicked: {
            console.log("clicked")

        }
        onEntered: {
            cursorShape = Qt.SizeHorCursor

        }
        onExited: {
            //isPressed = false
        }

        onPressed:(event)=>{
            isPressed = true
            pressedX = event.x
        }

        onReleased: {
            isPressed = false
        }

        onPositionChanged:(event)=> {
                if(isPressed){
                       pressedDragX = event.x - pressedX
                       console.log(event.x - pressedX)
                                  row.spacing = row.spacing + (event.x - pressedX)/50
                                  pressedX = event.x
                  }

        }
    }

     function  creatModel(nums){
        modelList.clear()
        for(var i=0;i<nums;i++){
            var data = {'idx': i.toString()};
            modelList.append(data)
        }


    }



}
