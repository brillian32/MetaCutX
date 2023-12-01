import  QtQuick

Window{

    id:rootWind;
    width:480;
    height:480
    visible:true;
    title:qsTr("resourceView")
    color:"#000000"


    Rectangle{
        id:libriry
        anchors.left:rootWind.left
        width:rootWind.width
        height:60
        color:"#141a22"

        Image{
            id:media
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
            id:audio
            width:25
            height:25
            anchors.left:media.right
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
            id:effects
            width:25
            height:25
            anchors.left:audio.right
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