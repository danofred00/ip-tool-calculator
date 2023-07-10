import QtQuick 2.15
import QtQuick.Controls
import QtQuick.Layouts

Item {

    id: subnetFormComponent

    property string bgcolor: "#1a1b1c"
    property string fgcolor: "#ffffff"

    Layout.fillWidth: true
    height: 30

    required property string label
    property string value

    RowLayout {
        anchors.fill: parent
        Label {
            Layout.preferredWidth: 100
            text: label
        }

        TextField {
            id: input
            Layout.fillWidth: true
            text: value
            color: fgcolor
            readOnly: true
            leftPadding: 10.0
            background: Rectangle {
                color: bgcolor
            }
        }
    }

}

