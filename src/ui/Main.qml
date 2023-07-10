import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs
import Qt.labs.platform
import IpCalculator 1.0

import "./components"

ApplicationWindow {
    id: app
    width: 450
    height: 700
    visible: true
    title: qsTr("Ip Tools")

    header: ToolBar {

        ToolButton {
            text: "\u2261" // => ≡
            onClicked: drawer.open()
        }

        Text {
            text: qsTr("Ip Tools")
            color: "#ffffff"
            elide: Label.ElideRight
            verticalAlignment: Qt.AlignVCenter
            horizontalAlignment: Qt.AlignHCenter
            anchors.fill: parent
        }

    }

    AppDrawer {
        id: drawer
        app: app
        onAboutBtnClicked: {
            drawer.close()
            aboutDialog.open()
            console.log("About Clicked")
        }
        onMediaButtonClicked: function(url) {
            console.log("Media Button Clicked")
            Qt.openUrlExternally(url)
        }
        onSettingsBtnClicked: function() {
            drawer.close()
            settingDialog.open()
        }
    }

    AboutDialog {
        id: aboutDialog
        width: 300
        height: 200
        aboutText: qsTr("Developped by @Danofred\nMinSdkVersion 23 (android 6)\nTargetSdkVersion 33 (android 11 R)\nVersion 1.0")
    }

    SettingDialog {
        id: settingDialog
        onAccepted: {
            console.log("[+] After restart, lang should be ", choosedLanguage)
            Utils.saveSetting("LANG", choosedLanguage)
            messageDialog.open()
        }

    }

    MessageDialog{
        id: messageDialog
        title: qsTr("Settings")
        buttons: MessageDialog.Ok
        text: qsTr("Changes will be applies after rebooting the app.")
    }

    IpCalculator { id: calculator }

    // content
    // the tabBar
    ColumnLayout {
        anchors.fill: parent
        TabBar {
            id: tabBarNav
            Layout.fillWidth: true
            TabButton {
                text: qsTr("Basic Mode")
                onClicked: {
                    stackView.pop(basicScreen)
                    stackView.push(basicScreen)
                }
            }
            TabButton {
                text: qsTr("Subnet Model")
                onClicked: {
                    stackView.pop(subnetScreen)
                    stackView.push(subnetScreen)
                }
            }
        }
        // The View to show the bar
        StackView {
            id: stackView
            Layout.fillHeight: true
            Layout.fillWidth: true

            Component.onCompleted: function(){
                stackView.push(subnetScreen)
                stackView.push(basicScreen)
            }
        }
    }

    BasicScreen {
        id: basicScreen
        onCalculateBtnClicked: function(){

            const ip = basicScreen.ipText
            // if ip is not valid
            if(!calculator.isValidIpv4(ip)) {
                basicScreen.resultText = qsTr("Your input is not a valid Ip address")
                return;
            }
            // if ip is valid
            const map = calculator.calculBasic(ip)
            var txt = "\n"
            Object.entries(map).forEach( (entry) => {
                const [key, value] = entry
                txt += "" + String(key).toUpperCase() + " = " + String(value).toUpperCase() + "\n"
            })
            basicScreen.resultText = txt
        }
    }

    SubnetScreen {
        id: subnetScreen
        onCalculateBtnClicked: function(){

            const ip = subnetScreen.ipText
            // if ip is not a network ip
            if(!calculator.isValidNetWorkIpv4(ip)) {
                subnetScreen.error = qsTr("Your entry is not a network ipv4 address")
                return;
            }

            // if ip is valid
            const map = calculator.calculSubnets(ip);

            // update view
            subnetScreen.subnetStr = map["netmask"]
            subnetScreen.basenetStr = map["base"]
            subnetScreen.typeStr = map["type"]
            subnetScreen.classStr = String(map["class"])
            subnetScreen.hexStr = String(map["hex"])
            subnetScreen.decimalStr = String(map["decimal"])
            subnetScreen.hostPerSubnetStr = String(map["hosts"])
            subnetScreen.subnetCountStr = map["subnetcount"]
            // update subnet list
            subnetScreen.subnetList = map["subnetlist"]
        }

    }
}
