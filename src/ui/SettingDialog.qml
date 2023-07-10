import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs
import QtQuick.Layouts

Dialog {
    id: settingDialog
    title: qsTr("Settings")
    anchors.centerIn: parent

    property string choosedLanguage: "ENGLISH"

    ColumnLayout {
        anchors.fill: parent

        RowLayout {

            Layout.fillWidth: true

            Label{ text: qsTr("Choose Language") }

            ComboBox {
                id: languageChooser
                model: ["English", "French"]
                onActivated: function(index){
                    if(index === 1)
                        choosedLanguage = String(currentText).toUpperCase()
                    else
                        choosedLanguage = String(textAt(0)).toUpperCase()
                }
            }
        }

        RowLayout {
            Button { text: qsTr("Save"); onClicked: { settingDialog.accept() } }
            Button { text: qsTr("Cancel"); onClicked: { settingDialog.reject() } }
        }

    }

}
