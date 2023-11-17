import QtQuick



Rectangle{
    id:resizableRect
    property int length : 0
    property int leftX: 0
    property bool canDragLeft: false
    property bool canDragRight: false
    property bool draging: false
    property int srcX: 0
    radius: 6
    color: "#7fe2c6"
    width: length
    border.color: "#7f12c6"
    border.width: 2

    MouseArea {
        id: leftResizeArea
        width: 2
        height: parent.height
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        cursorShape: Qt.SizeHorCursor
//        hoverEnabled: true
        onPressed: {
            dragging = true
            leftResizeArea.mouseXWhenPressed = mapToGlobal(Qt.point(0, 0)).x ;
            leftResizeArea.widthWhenPressed = resizableRect.width;
            console.log(mouseXWhenPressed,widthWhenPressed);
        }
        onMouseXChanged: {
            if(dragging)
            {

                resizableRect.width = widthWhenPressed - ((mapToGlobal(Qt.point(Math.floor(mouseX), 0)).x) - mouseXWhenPressed)
                resizableRect.x = mapToItem(resizableRect.parent,Qt.point(Math.floor(mouseX), 0)).x
                resizableRect.width = widthWhenPressed - (resizableRect.parent.mapToGlobal(Qt.point(resizableRect.x,0)).x - leftResizeArea.mouseXWhenPressed)

                console.log("draging",resizableRect.width,resizableRect.x,mouseX)
            }
            else
            {
                console.log("not drag")
            }


        }
        onReleased:
        {
            dragging = false;
            console.log("release")
        }

        property int mouseXWhenPressed : 0
        property int widthWhenPressed: 0
        property bool dragging: false
    }

    MouseArea {
        id: rightResizeArea
        width: 2
        height: parent.height
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        cursorShape: Qt.SizeHorCursor
//        hoverEnabled: true
        onPressed: {
            dragging = true
            rightResizeArea.mouseXWhenPressed = mapToGlobal(Qt.point(mouseX, 0)).x ;
            rightResizeArea.widthWhenPressed = resizableRect.width;
            console.log(mouseXWhenPressed,widthWhenPressed);
        }
        onMouseXChanged: {
            if(dragging)
            {
                resizableRect.width = mapToGlobal(Qt.point(mouseX, 0)).x - mouseXWhenPressed + widthWhenPressed
//                console.log("draging")
            }
            else
            {
                console.log("not drag")
            }


        }
        onReleased:
        {
            dragging = false;
            console.log("release")
        }

        property int mouseXWhenPressed : 0
        property int widthWhenPressed: 0
        property bool dragging: false
    }

    MouseArea {
        id: centerResizeArea
        height: parent.height
        anchors.left: parent.left
        anchors.leftMargin: 2
        anchors.right: parent.right
        anchors.rightMargin: 2
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        cursorShape: Qt.OpenHandCursor
//        hoverEnabled: true
        onPressed: {
            dragging = true
            centerResizeArea.mouseXWhenPressed = mapToGlobal(Qt.point(mouseX, 0)).x ;
            centerResizeArea.xWhenPressed = parent.x  ;
            console.log(mouseXWhenPressed,xWhenPressed);
        }
        onMouseXChanged: {
            if(dragging)
            {
                resizableRect.x = xWhenPressed + mapToGlobal(Qt.point(mouseX, 0)).x - mouseXWhenPressed
//                console.log("draging")
            }
            else
            {
                console.log("not drag")
            }


        }
        onReleased:
        {
            dragging = false;
            console.log("release")
        }
        property int mouseXWhenPressed : 0
        property int xWhenPressed: 0
        property bool dragging: false
    }

}

