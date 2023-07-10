import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs
import Qt.labs.platform

Frame {

    id: basicScreen

    property string resultText: qsTr("No Thing here for the moment")
    property string ipText: "0.0.0.0/0"

    signal calculateBtnClicked()

    FileDialog {
        id: fileDialog
        folder: StandardPaths.writableLocation(StandardPaths.DocumentsLocation)
        nameFilters: ["Text Files (*.txt)", "All Files (*.*)"]
        fileMode: FileDialog.SaveFile
        onAccepted: function() {
            Utils.saveFileContent(fileDialog.currentFile.toString(), resultText)
        }
    }

    ColumnLayout {

        anchors.fill: parent

        RowLayout {
            Label{ text: qsTr("Target IP : ")}
            TextField {
                id: hostInput
                Layout.fillWidth: true
                horizontalAlignment: Qt.AlignHCenter
                placeholderText: qsTr("Enter the target. Default = 0.0.0.0/0")
                onTextChanged: function(){
                    ipText = hostInput.text
                    // console.log(ipText, " ", hostInput.text)
                }
            }
        }
        // button Section
        RowLayout {
            // calculate Button
            Button {
                id: calculateBtn
                Layout.fillWidth: true
                text: qsTr("Calculate")
                onClicked: {
                    if(Utils.validateIp(ipText)) {
                        resultArea.color = "#fff"
                        calculateBtnClicked()
                        console.log("Frame1 : Caculate Button Clicked")
                    } else {
                        resultArea.color = "#f00"
                        resultText = qsTr("Your input is not a valid Ip address")
                    }
                }
            }
            // Save Button
            Button {
                id: saveBtn
                Layout.fillWidth: true
                text: qsTr("Save")
                onClicked: {
                    fileDialog.open()
                    console.log("Frame1 : Save Button Clicked")
                }
            }
        }

        ColumnLayout {

            width: basicScreen.width

            Label {
                Layout.fillWidth: true
                horizontalAlignment: Qt.AlignHCenter;
                text: qsTr("The result will be shown here") }
            TextArea {
                id: resultArea
                Layout.fillHeight: true
                Layout.fillWidth: true
                readOnly: true
                text: resultText
                font.weight: Font.Bold
                color: "#fff"
                padding: 2.0
                wrapMode: Text.WrapAnywhere
                onTextChanged: {
                    resultText = resultArea.text
                }
                background: Rectangle {
                    color: "#000"
                }
            }
        }
    }

}
