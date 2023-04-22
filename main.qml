import QtQuick
import QtQuick.Window
import QtQuick.Dialogs
import QtQuick.Controls
import Qt.labs.platform
import QtQuick.Layouts
import MyCppFunc

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
                property bool window_ExitOrShow: false
                onClicked: {
                    if (window_ExitOrShow === false) {
                        var component = Qt.createComponent("QML_SettingUI.qml")
                        var win = component.createObject()
                        win.closing.connect(function () {
//                            console.log('关闭')
                            window_ExitOrShow = false
                        })
                        win.show()
                        window_ExitOrShow = true
                    }
                }
            }
        }
    }

    FileDialog {
        id: saveFileDialog
        fileMode: FileDialog.SaveFile

        onAccepted: {
//            console.log("保存")
        }
        onRejected: {
//            console.log("取消")
        }
    }

    onClosing: function (closeevent) {
        closeevent.accepted = false
        main.visible = false
    }

    Rectangle {
        width: 100
        height: 50
        color: "lightgreen"
        id: saveOK
        visible: false
        z: 100
        x: parent.width / 2 - 100
        radius: 10

        Text {
            text: qsTr("保存成功")
            x: parent.width / 2 - 30
            y: parent.height / 2 - 10
            font.pixelSize: 15
        }

        NumberAnimation on y {
            id: saveFileAnimation
            from: 0
            to: 50
            duration: 300
            running: false
            onFinished: {
                saveFileAnimation_opactiy.start()
            }
        }
        NumberAnimation {
            id: saveFileAnimation_opactiy
            target: saveOK // 目标对象是长方体
            property: "opacity" // 改变的属性是不透明度
            to: 0
            duration: 1000 // 持续时间是
            easing.type: Easing.InOutQuad
            running: false
        }
    }

    MessageDialog {
        id: msg_quit_yesorno
        title: "警告"
        text: "文件未保存, 是否退出?"
        buttons: MessageDialog.Discard | MessageDialog.Save

        onDiscardClicked: {
//            console.log("丢弃")
            Qt.quit()
        }

        onSaveClicked: {
//            console.log("保存")
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
        x: parent.width / 2 - 100
        y: parent.height / 2

        Text {
            id: textOpenFile
            color: "#94A7B0"
            font.pointSize: 12
            text: qsTr("打开文件夹...")
            MouseArea {
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
    FileDialog {
        id: fileDialog
        onAccepted: {
            filePath = fileDialog.file
//            console.log("File:", filePath)

            textOpenFile.visible = false
            textOpenFolder.visible = false
            noteX_title.visible = false
            textAreaMain.visible = true
            slView_textArea.visible = true
//            toolbar_main.visible = true
            menuBar_file.visible = true

            fileData = tdor.readFile(filePath)
//            console.log(fileData)
            fileName = tdor.getFileName(filePath)
//            console.log(fileName)
            main.title = "NoteX  " + fileName
            textAreaMain.text = fileData
        }
        onRejected: {
//            console.log("取消")
            return
        }
    }

    TextEditor {
        id: tdor
    }

    FolderDialog {
        id: folderDialog
        onAccepted: {
//            console.log("Folder:", folderDialog.folder)
            textOpenFile.destroy()
            textOpenFolder.destroy()
            noteX_title.destroy()
            textAreaMain.visible = true
            slView_textArea.visible = true
        }
        onRejected: {
//            console.log("取消")
        }
    }

    MenuBar {
        Menu {
            id: menuBar_file
            title: qsTr("文件")
            visible: false
            MenuItem {
                text: qsTr("打开文件")
                onTriggered: fileDialog.open()
            }
            MenuItem {
                text: qsTr("打开文件夹")
                onTriggered: folderDialog.open()
            }
            MenuItem {
                id: saveFileMenu
                text: qsTr("保存文件")
                onTriggered: tdor.saveFile(filePath, textAreaMain.text)
            }
            MenuItem {
                text: qsTr("另存为")
                onTriggered: saveFileDialog.open()
            }
            MenuItem {
                id: autoSave
                text: qsTr("自动保存")
                checkable: true
            }
        }
        Menu {
            title: qsTr("查看")
        }

        Menu {
            title: qsTr("帮助")
            MenuItem {
                text: "官网"
                onTriggered: {
                    Qt.openUrlExternally("https://jvfcn.github.io/NoteX.io/")
                }
            }
            MenuItem {
                text: "GitHub仓库"
                onTriggered: {
                    Qt.openUrlExternally("https://github.com/JVFCN/NoteX")
                }
            }
            MenuItem {
                text: "作者GitHub主页"
                onTriggered: {
                    Qt.openUrlExternally("https://github.com/JVFCN")
                }
            }
        }
    }

    ScrollView {
        id: slView_textArea
        anchors.fill: parent
        visible: false

        TextArea {
            id: textAreaMain
            focus: true
            visible: false
            font.pointSize: 12

            onTextChanged: {
                main.title = "NoteX  " + fileName + "*"
                if (autoSave.checked === true) {
                    tdor.saveFile(filePath, textAreaMain.text)
                    main.title = "NoteX" + fileName
                }
            }


            Shortcut {
                sequence: "Ctrl+S"
                onActivated: {
                    if (main.title !== "NoteX") {
                        saveOK.visible = true
                        if (saveFileAnimation.running === false && saveFileAnimation_opactiy.running === false ) {
                            saveFileAnimation.start()
                            saveOK.opacity = 1
                        }

                        tdor.saveFile(filePath, textAreaMain.text)
                        main.title = "NoteX  " + fileName
                    }
                }
            }
        }
    }
}
