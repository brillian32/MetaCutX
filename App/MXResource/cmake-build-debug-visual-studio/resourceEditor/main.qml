import  QtQuick
import  QtQuick.Controls

Window{

    id:rootWind
    width:480
    height:400
    visible:true
    title:qsTr("resourceView")
    color:"#000000"


    Rectangle{
        z:10
        id:libriry
        anchors.left:rootWind.left
        width:rootWind.width
        height:60
        color:"#141a22"

        Image{
            id:media
            width:30
            height:30
            anchors.left:libriry.left
            anchors.leftMargin:30
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
            id:audio
            width:30
            height:30
            anchors.left:media.right
            anchors.leftMargin:30
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
            id:effects
            width:30
            height:30
            anchors.left:audio.right
            anchors.leftMargin:30
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


    Rectangle{
        id:tools
        width:160
        anchors.left:rootWind.left
        anchors.bottom:rootWind.bottom
        anchors.top:libriry.bottom


        Item{
            id:tool1
            width:120
            height:50
            anchors.left:tools.left
            anchors.leftMargin:20


        }


        Item{
            id:tool2
            width:120
            height:50
            anchors.top:tool1.bottom
            anchors.topMargin:30
            anchors.left:tools.left
            anchors.leftMargin:20


        }

    }



    Rectangle{
        id:searchLine
        anchors.left:tools.right
        anchors.right:rootWind.right
        anchors.top:libriry.bottom
        height:40

        TextField{
            id:textField
            width:120
            height:30
            anchors.left:searchLine.left
            anchors.leftMargin:10
            anchors.top:searchLine.top
            anchors.topMargin:5

            placeholderText:qsTt("Search something")



        }

    }


    Rectangle{
        id:showArea
        anchors.left:tools.right
        anchors.right:rootWind.right
        anchors.top:searchLine.bottom
        anchors.bottom:rootWind.bottom
        color:"#000000"
    }



}