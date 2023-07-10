import QtQuick 2.15
import QtQuick.Controls
import QtQuick.Layouts

Drawer {

    id: drawer

    required property ApplicationWindow app

    signal aboutBtnClicked()
    signal settingsBtnClicked()
    signal mediaButtonClicked(url: string)

    width: app.width > 500 ? 350 : app.width * 0.7
    height: app.height

    function str_endwith(str, end) {

        const end_size = end.length
        const str_size = str.length
        for(var i = str_size - end_size, j=0; i<str_size; i++, j++)
            if(str[i] !== end[j])
                return false
        return true
    }


    ColumnLayout {

        anchors.fill: parent

        Rectangle {
            id: logoContainer
            Layout.fillWidth: true
            height: 200

            Rectangle {
                anchors.centerIn: parent
                width: 128
                height: 128
                color: "#fff"
                border.width: 2
                border.color: "#000"
                radius: 100

                Image {
                    id: logo
                    width: 118
                    anchors.centerIn: parent
                    fillMode: Image.PreserveAspectFit
                    source: "qrc:/ui/assets/logo/logo.jpg"

                }
            }
        }

        Component {
            id: sectionHeading
            Rectangle {
                width: drawer.width
                height: 2
                color: "#000"
            }
        }
        ListView {

            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true
            model: drawerListModel
            delegate: ItemDelegate {
                width: parent.width
                text: model.label
                icon.source: model.iconUrl
                icon.color: str_endwith(model.iconUrl, ".svg") ? "#000" : icon.color
                onClicked: model.onClicked()
            }
            section.property: "type"
            section.criteria: ViewSection.FullString
            section.delegate: sectionHeading
        }
        // footer
        Rectangle {
            Layout.fillWidth: true
            color: "#000"
            height: 20

            Text {
                anchors.fill: parent
                text: qsTr("By @Danofred0")
                horizontalAlignment: Qt.AlignHCenter
                font.weight: Font.Bold
                elide: Text.ElideRight
                color: "#fff"
            }
        }
    }

    ListModel {
        id: drawerListModel
        ListElement { type:"Application"; label: "About"; iconUrl: "qrc:/ui/assets/icons/svg/alert-circle.svg"; onClicked: ()=>{ drawer.aboutBtnClicked() } }
        ListElement { type:"Application"; label: "Settings"; iconUrl: "qrc:/ui/assets/icons/svg/alert-circle.svg"; onClicked: ()=>{ drawer.settingsBtnClicked() } }
        ListElement { type:"Author"; label: "Github"; iconUrl: "qrc:/ui/assets/icons/png/github-logo.png"; onClicked: ()=>{ drawer.mediaButtonClicked("https://github.com/danofred00") } }
        ListElement { type:"Author"; label: "Facebook"; iconUrl: "qrc:/ui/assets/icons/png/facebook.png"; onClicked: ()=>{ drawer.mediaButtonClicked("https://m.facebook.com/danofred00") } }
        ListElement { type:"Author"; label: "Youtube"; iconUrl: "qrc:/ui/assets/icons/png/youtube.png"; onClicked: ()=>{ drawer.mediaButtonClicked("https://m.youtube.com/@HarpTutos") } }
        ListElement { type:"Author"; label: "Telegram"; iconUrl: "qrc:/ui/assets/icons/png/telegram.png"; onClicked: ()=>{ drawer.mediaButtonClicked("https://t.me/HarpTutos") } }
    }

}
