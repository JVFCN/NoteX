import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    width: 800
    height: 600
    visible: true
    id: settingUI

    header: TabBar {
        id: tabBar
        currentIndex: stackLayout.currentIndex
        TabButton {
            text: "界面设置"
        }
        TabButton {
            text: "Page 2"
        }
        TabButton {
            text: "Page 3"
        }
        TabButton {
            text: "Page 4"
        }
    }
    StackLayout {
        id: stackLayout
        anchors.fill: parent
        currentIndex: tabBar.currentIndex
        Item {
            id: uiSettings
            RowLayout {
                Text {
                    text: qsTr("字体大小:")
                }
                Slider {
                    id: slider_fontSize
                    from: 5
                    value: 12
                    to: 30
                    live: true
                    stepSize: 1
                }

                Text {
                    text: slider_fontSize.value
                }
            }
        }

        Item {
            id: page2
            Rectangle {
                anchors.fill: parent
                Switch {
                    text: "Switch 2"
                    anchors.centerIn: parent
                }
            }
        }
        Item {
            id: page3
            Rectangle {
                anchors.fill: parent
                Text {
                    text: qsTr("text")
                }
            }
        }
    }
}
