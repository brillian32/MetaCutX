import QtQuick 2.0
import QtQuick.Particles
import QtQuick.Controls

Item {

    id:trackHead
    width:parent.width

    Component.onCompleted:{
            creatTrackModel(4);

    }

    function addTrack()
    {
        console.debug("listView.count",listView.count)
        if(listView.count%2==0)
        {
            model_data.append({"idx":listView.count+1 ,"visable":true,"colorIn":"#141a22"})
        }else{
            model_data.append({"idx":listView.count+1 ,"visable":true,"colorIn":"#1b222a"})
        }
        listView.update()
        //listView.height = (listView.count+1)*60


    }

    function creatTrackModel(trackNums)
    {
        model_data.clear()
        for(var i = 0;i<trackNums;i++)
        {

           if  (i%2 == 0)
           {
                model_data.append({"idx":i ,"visable":true,"colorIn":"#141a22"})
           }else{
                model_data.append({"idx":i ,"visable":true,"colorIn":"#1b222a"})
           }
        }
        outside_border.height = trackNums*60
        listView.height = trackNums*60
    }




    Rectangle{
        id:outside_border
        z:2
        //parent: listView
        anchors.left: trackHead.left
        anchors.top: trackHead.top
        width: 100
        height: 180
        color: "#00000000"
        border.color: "#343434"
        border.width: 1
    }

    Component{
        id:track_com
        //轨道
        Rectangle{
            id:rect_child
            property bool choose: false
            width: trackHead.width
            height:60
            color: listView.currentIndex===index? "#111213":colorIn

            //diable mask
            Image {
                id:disable_mask
                x: outside_border.x + outside_border.width
                visible: visable===false
                antialiasing: true
                smooth: true
                source: "qrc:img/disableMask.png"
                opacity: 0.5
                width: rect_child.width
                height : rect_child.height
            }

            //粒子效果
            Rectangle {
                id: mask_emitter
                z:3
                anchors.fill: parent
                color: "#00000000"
                ParticleSystem {
                    id: particles
                }
                Emitter {
                    id: emitter
                    anchors.centerIn: parent
                    width: parent.width; height:  parent.height
                    system: particles
                    emitRate: 8
                    lifeSpan: 1500
                    lifeSpanVariation: 500
                    size: 1
                    endSize: 2
                }
                ItemParticle {
                    system: particles
                    delegate: Rectangle {
                        id: rect
                        width: 2
                        height: 2
                        color: "#7fe2c6"
                        radius: 1
                    }
                }
            }
            Image {
                id: img_lock
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 8
                width: 12
                height: 12
                source: visable?"qrc:img/lockTrack.png":"qrc:img/unlockTrack.png"

            }
            Text {
                id: text_track

                anchors.horizontalCenter: img_lock.horizontalCenter
                anchors.top: img_lock.bottom
                anchors.topMargin: 2
                font.pointSize: 10
                color: "#dbdbdb"
                text: index.toString()
            }

            MouseArea{
                anchors.fill: rect_child
                propagateComposedEvents:true
                onClicked: (mouse)=>{
                    listView.currentIndex = index
                    console.log(index)
                }
            }

            //剪辑片段
            Clip{
                id:clip
                length: 40
                anchors.top: parent.top
                anchors.topMargin: 1
                anchors.bottom: parent.bottom
                x: outside_border.width
                anchors.bottomMargin: 1
            }

            MouseArea{
                propagateComposedEvents:true
                anchors.fill: img_lock
                parent:img_lock
                onClicked: {
                    visable = !visable
                    console.log("visable ",visable)
                    mouse.accepted = false;
                }
                onPressed:
                {
                    mouse.accepted = false; //忽略点击事件，传递给下一层处理
                }
            }

        }
    }

    ListModel{
        id:model_data
    }

    ScrollView {

        id:scrollView
        contentWidth: 1
        ScrollBar.vertical: ScrollBar {
            parent: scrollView
            x: scrollView.mirrored ? 0 : scrollView.width - width
            //y: scrollView.topPadding
             anchors.top: scrollView.top
            height: listView.height
            active: scrollView.ScrollBar.horizontal.active
            policy: ScrollBar.AlwaysOn
            background:  Rectangle{
                color: "#40464c"
                radius: 2
            }

        }


        ScrollBar.horizontal.policy: ScrollBar.AlwaysOff

        width: parent.width
        height: listView.height

     ListView{
         id:listView

         verticalLayoutDirection:"BottomToTop"
         model: model_data
         delegate: track_com

         highlight: Rectangle{
             color: "lightblue"
         }

         onCurrentItemChanged: {
             console.debug("onCurrentIndexChanged");
         }

         }

}
     Rectangle{
         id:drag_rect
         x: outside_border.x
         y: outside_border.y+outside_border.height
         width: parent.width
         height: 200
         color:"#191f25"

         Component{
             id:drag_com
             Rectangle{
                 id:drag_item
                 property bool canResize: false
                 property bool isPressed: false
                 property int  pressedX: 0
                 width: 80
                 height: 40
                 color: "#66b3ab"
                 border.color: "#7fe2c6"
                 border.width: 2
                 radius:8
                 MouseArea {
                     property bool enterIn: false
                     anchors.fill: drag_item

                     drag.target: drag_item
                     hoverEnabled : true
                    // drag.axis: Drag.XAndYAxis
                   drag.minimumX: outside_border.width
                    drag.maximumX: trackHead.width
                    drag.minimumY: -outside_border.height
                    drag.maximumY: 0

                    onEntered:(event)=> {
                        cursorShape = Qt.CrossCursor
                                  enterIn = true
//                        onMouseXChanged:(mouseX) =>{
//                                      console.log("move1")


//                                  }

                    }
                    onMouseXChanged:(mouseX) =>{
                                        drag_item.canResize = false
                        console.log("move",mouseX.x)
                                        console.log("move2",drag_item.width);
                                       if(-3<(mouseX.x - drag_item.width)&(mouseX.x - drag_item.width)<0)
                                                                              {
                                        cursorShape = Qt.SizeHorCursor
                                            drag_item.canResize = true
                                                                              }
                                        else{
                                            cursorShape = Qt.SizeAllCursor
                                            if(0<(mouseX.x )&(mouseX.x )<3)
                                                                                   {
                                             cursorShape = Qt.SizeHorCursor
                                                drag_item.canResize = true
                                                                                   }
                                             else{
                                                 cursorShape = Qt.SizeAllCursor
                                             }
                                        }


                    }

                    onPressed:(event)=>{
                        drag_item.isPressed = true
                        drag_item.pressedX = event.x
                    }

                    onReleased: {
                        drag_item.isPressed = false
                    }

                    onPositionChanged:(event)=> {
                            if(drag_item.isPressed){

                                   console.log(event.x - drag_item.pressedX,"drag xVallue")
                                              drag_item.width = drag_item.width + event.x - drag_item.pressedX

                              }

                    }
                 }

             }
         }

         Row{
            id:row
            spacing:5
            Repeater{
                model: 2
                delegate: drag_com

            }
         }

     }
}



