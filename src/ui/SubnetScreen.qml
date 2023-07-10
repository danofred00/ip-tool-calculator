import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs
import Qt.labs.platform

import IpTableModel 1.0

import "components"

Frame {

    id: subnetScreen

    property string ipText: "0.0.0.0/0"
    property string error: ""
    property string subnetStr: ""
    property string basenetStr: ""
    property string hexStr: ""
    property string decimalStr: ""
    property string classStr: ""
    property string subnetCountStr: ""
    property string typeStr: ""
    property string hostPerSubnetStr: ""

    property var subnetList: undefined


    signal calculateBtnClicked()

    FileDialog {
        id: fileDialog
        folder: StandardPaths.writableLocation(StandardPaths.DocumentsLocation)
        nameFilters: ["Text Files (*.txt)", "All Files (*.*)"]
        fileMode: FileDialog.SaveFile
        onAccepted: function() {
            // code to save the file

        }
    }

    ColumnLayout {

        anchors.fill: parent
        // input network ip
        ColumnLayout{

            spacing: 1.0

            RowLayout {
                Label{ text: qsTr("Network IP : ")}
                TextField {
                    id: networkInput
                    Layout.fillWidth: true
                    horizontalAlignment: Qt.AlignHCenter
                    placeholderText: qsTr("Enter a Network Ip. Default = 0.0.0.0/0")
                    onTextChanged: function(){
                        ipText = networkInput.text
                        // console.log("Subnet - ", ipText, " - ", networkInput.text)
                    }
                }
            }
            Text {
                id: errorText
                Layout.fillWidth: true
                text: error
                horizontalAlignment: Qt.AlignHCenter
                font.weight: Font.Bold
                color: "#ff0000"
            }
        }
        // buttons
        RowLayout {
            // calculate Button
            Button {
                id: calculateBtn
                Layout.fillWidth: true
                text: qsTr("Calculate")
                onClicked: {
                    error = ""
                    if(Utils.validateIp(ipText)) {

                        subnetList = undefined
                        calculateBtnClicked()
                        // we check if the value of list is valid
                        if(subnetList !== undefined) {
                            // empty the view
                            const rows = ipTableModel.rowCount();
                            ipTableModel.removeRows(1, rows-1);
                            // appends some values
                            subnetList.forEach(function(value, index) {
                                const map = JSON.parse(Utils.mapToString(value))
                                const lastRow = ipTableModel.rowCount();
                                // insert row
                                ipTableModel.insertRow(lastRow)
                                // get indexes
                                const indexNetwork = ipTableModel.index(lastRow, 1)
                                const indexNetmask = ipTableModel.index(lastRow, 2);
                                const indexBroadcast = ipTableModel.index(lastRow, 3);
                                // update data
                                ipTableModel.setData(indexNetwork, map["network"], Qt.EditRole)
                                ipTableModel.setData(indexNetmask, map["netmask"], Qt.EditRole)
                                ipTableModel.setData(indexBroadcast, map["broadcast"], Qt.EditRole)
                            })

                        }
                    } else {
                        error = qsTr("Your input is not a valid network ip address")
                    }
                }
            }
            // Save Button
            Button {
                id: saveBtn
                Layout.fillWidth: true
                text: qsTr("Save")
                onClicked: {
                    console.log("Frame2 : Save Button Clicked")
                }
            }
        }
        // some result
        ColumnLayout {
            spacing: 2.0
            SubnetFormComponent {
                id: subnet
                label: qsTr("Subnet Mask")
                value: subnetStr
            }
            SubnetFormComponent {
                id: basenet
                label: qsTr("Base Network")
                value: basenetStr
            }
            SubnetFormComponent {
                id: hex
                label: qsTr("Hex")
                value: hexStr
            }
            SubnetFormComponent {
                id: decimal
                label: qsTr("Decimal")
                value: decimalStr
            }
            SubnetFormComponent {
                id: classAddr
                label: qsTr("Class Address")
                value: classStr
            }
            SubnetFormComponent {
                id: typeAddr
                label: qsTr("Type")
                value: typeStr
            }
            SubnetFormComponent {
                id: subnetCount
                label: qsTr("Subnet Count")
                value: subnetCountStr
            }
            SubnetFormComponent {
                id: hostPerSubnets
                label: qsTr("Hosts/Subnet")
                value: hostPerSubnetStr
            }
        }

        Item {

            Layout.topMargin: 10
            Layout.fillWidth: true
            Layout.fillHeight: true

            Rectangle{
                anchors.fill: parent
                color: "#181818"
            }

            TableView {
                id: tableView
                anchors.fill: parent
                columnWidthProvider: function(column) {

                    const firstColumnWidth = 30

                    return column === 0 ? firstColumnWidth : (tableView.width-firstColumnWidth)/(tableView.columns-1);
                }
                model: IpTableModel {
                    id: ipTableModel
                    onDataChanged: {
                        // console.log("Some thing changed in model ", ipTableModel.rowCount())
                    }
                }
                clip: true
                delegate: Rectangle {
                    property bool heading : model.heading
                    border.width: 1
                    color: heading ? "#181818" : "#fff"
                    Text {
                        text: model.data
                        color:  heading === true ? "#ffffff" : "#000000"
                        anchors.centerIn: parent
                    }
                }
            }
        }
    }

    Component.onCompleted: { }

}
