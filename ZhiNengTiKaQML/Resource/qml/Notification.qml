import QtQuick
import QtQuick.Controls

Popup {
    id: notification
    width: messageText.width
    height: messageText.height + 20
    opacity: 0
    property alias message: messageText.text
    property int displayDuration: 3000 // 显示持续时间，单位为毫秒
    property int maxWidth // 最大宽度

    signal notificationClosed

    Rectangle {
        anchors.centerIn: parent
        width: notification.width
        height: notification.height
        color: "gray"
        Text {
            id: messageText
            anchors.centerIn: parent
            wrapMode: Text.Wrap
            text: ""
        }

        TextMetrics {
            id: textMetrics
            font: messageText.font
            text: messageText.text
        }

        SequentialAnimation {
            id: fadeAnimation
            ScriptAction { script: { console.log("start") } }
            PropertyAction { target: notification; property: "visible"; value: true }
            NumberAnimation { target: notification; property: "opacity"; to: 1; duration: 500 }
            PauseAnimation { duration: notification.displayDuration }
            NumberAnimation { target: notification; property: "opacity"; to: 0; duration: 500 }
            PropertyAction { target: notification; property: "visible"; value: false }
            ScriptAction { script: { notification.notificationClosed() } }
        }
    }

    function show(message) {
        messageText.text = message
        messageText.width = textMetrics
        if (messageText.width > notification.maxWidth)
        {
            messageText.width = notification.maxWidth
        }
        fadeAnimation.restart()
    }
}
