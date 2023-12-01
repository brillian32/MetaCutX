import  QtQuick

Window{

    id:rootWind;
    width:480;
    height:480
    visible:true;
    title:qsTr("resourseView")
    color:"#000000"


    Rectangle{
        id:libriry
        anchors.left:rootWind.left
        width:rootWind.width
        height:60
        color:"#141a22"

        Image{
            id:Media
            width:25
            height:25
            anchors.left:libriry.left
            anchors.leftMargin:15
            anchors.verticalCenter:libriry.verticalCenter
            source:"qrc:img/Media.png"
            opacity:1
            MouseArea{
                anchors.fill: parent
                onPressed:{
                    parent.opacity=0.5
                    parent.scale=1.2
                }
                onReleased:{
                    parent.opacity=1
                    parent.scale=1
                    //
                    // do something
                }

            }


        }


        Image{
            id:Audio
            width:25
            height:25
            anchors.left:Media.right
            anchors.leftMargin:15
            anchors.verticalCenter:libriry.verticalCenter
            source:"qrc:img/Audio.png"
            opacity:1
            MouseArea{
                anchors.fill: parent
                onPressed:{
                    parent.opacity=0.5
                    parent.scale=1.2
                }
                onReleased:{
                    parent.opacity=1
                    parent.scale=1
                    //
                    // do something
                }

            }


        }



        Image{
            id:Effects
            width:25
            height:25
            anchors.left:Audio.right
            anchors.leftMargin:15
            anchors.verticalCenter:libriry.verticalCenter
            source:"qrc:img/Effects.png"
            opacity:1
            MouseArea{
                anchors.fill: parent
                onPressed:{
                    parent.opacity=0.5
                    parent.scale=1.2
                }
                onReleased:{
                    parent.opacity=1
                    parent.scale=1
                    //
                    // do something
                }

            }


        }


    }






}