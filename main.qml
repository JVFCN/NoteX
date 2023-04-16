import QtQuick
import QtQuick.Window
import QtQuick.Dialogs
import QtQuick.Controls
import Qt.labs.platform
import QtQuick.Layouts
import MyCppFunc
//import QtQml
ApplicationWindow {
    id: main
    visible: true
    width: 1400
    height: 900
    color: "#FAFAFA"
    title: "NoteX"

    footer: ToolBar {
        RowLayout {
            anchors.fill: parent
            ToolButton {
                text: "设置"
                onClicked: menu
            }
        }
    }

    onClosing: function(closeevent){
        closeevent.accepted = false
        main.visible = false
   }

    MessageDialog {
        id: msg_quit_yesorno
        title: "警告"
        text: "文件未保存, 是否退出?"
        buttons: MessageDialog.Discard | MessageDialog.Save

        onDiscardClicked: {
            console.log("丢弃")
            Qt.quit()
        }

        onSaveClicked: {
            console.log("保存")
        }
    }

    SystemTrayIcon {
        visible: true
        id: systemTrayIcon
        tooltip: "NoteX"
        icon.source: "qrc:/res/File.png"
        menu: Menu {
            MenuItem {
                text: "官网"
                onTriggered: {
                    Qt.openUrlExternally("https://jvfcn.github.io/NoteX.io/")
                }
            }
            MenuSeparator {}
            MenuItem {
                text: qsTr("退出")
                onTriggered: {
                    Qt.quit()
                }
            }
        }
    }
    Connections {
        target: systemTrayIcon
        function onActivated(systemTrayIcon) {
            // 在这里处理系统图标被点击的逻辑
            main.visibility = Window.Windowed
            main.raise()
        }
    }


    minimumHeight: 500
    minimumWidth: 700

    Label {
        id: noteX_title
        text: "NoteX：文本编辑解决方案"
        color: "#989898"
        font.pixelSize: 40
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.topMargin: 150
        anchors.leftMargin: 100
    }

    Column {
        anchors.centerIn: parent

        Text {
            id: textOpenFile
            color: "#94A7B0"
            font.pointSize: 12
            text: qsTr("打开文件夹...")
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    folderDialog.open()
                }
            }
        }

        Text {
            id: textOpenFolder
            color: "#94A7B0"
            font.pointSize: 12
            text: qsTr("打开文件...")
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    fileDialog.open()
                }
            }
        }
    }

    property string fileName
    property string filePath
    property string fileData
    FileDialog{
        id: fileDialog
        onAccepted: {
            filePath = fileDialog.file
            console.log("File:", filePath)

            textOpenFile.visible = false
            textOpenFolder.visible = false
            noteX_title.visible = false
            textAreaMain.visible = true
            slView_textArea.visible = true

            fileData = tdor.readFile(filePath);
            console.log(fileData)
            fileName = tdor.getFileName(filePath);
            console.log(fileName)
            main.title = "NoteX  " + fileName
            textAreaMain.text = fileData
        }
        onRejected: {
         console.log("取消")
            return
        }
    }

    TextEditor {
        id: tdor
    }

    FolderDialog {
        id: folderDialog
        onAccepted: {
            console.log("Folder:", folderDialog.folder)
            textOpenFile.destroy()
            textOpenFolder.destroy()
            noteX_title.destroy()
            textAreaMain.visible = true
            slView_textArea.visible = true
        }
        onRejected: {
            console.log("取消")
        }
    }

    MenuBar {
        Menu {
            title: qsTr("文件")
            MenuItem {
               text: qsTr("打开文件")
               onTriggered: fileDialog.open()
            }
            MenuItem {
                text: qsTr("打开文件夹")
                onTriggered: folderDialog.open()
            }
            MenuItem {
                text: qsTr("保存文件")
            }
            MenuItem {
                text: qsTr("另存为")
            }
            MenuItem {
                text: qsTr("自动保存")
                checkable: true
//                checked: true
            }
        }
        Menu {
            title: qsTr("查看")
        }

        Menu {
            title: qsTr("帮助")
        }
    }

    ScrollView{
        id: slView_textArea
        anchors.fill: parent
        visible: false
        TextArea {
            id: textAreaMain
            focus: true
            visible: false
            onTextChanged: {
                main.title = "NoteX  " + fileName + "*"
            }

            Shortcut {
                sequence: "Ctrl+S"
                onActivated: {
                    if (main.title !== "NoteX")
                    {
                        console.log("CS")
                        tdor.saveFile(filePath, textAreaMain.text)
                        main.title = "NoteX  " + fileName
                    }
                }
            }
        }
    }
}
