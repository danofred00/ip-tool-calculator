import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs
import QtQuick.Layouts

Dialog {
    id: aboutDialog
    modal: true
    title: qsTr("About")
    anchors.centerIn: parent

    required property string aboutText

    background: Rectangle {
        color: "#d5d5d5"
    }

    ColumnLayout {

        anchors.fill: parent
        spacing: 5.0

        Text {
            Layout.fillHeight: true
            Layout.fillWidth: true
            text: aboutText
            color: "#000"
        }

        Button {
            Layout.fillWidth: true
            text: qsTr("Close")
            onClicked: aboutDialog.accept()
        }

    }

}
