import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import ImageProvider

Item {
    property var templateAnalysisPointer: null
    property bool initFinish: false

    ImageProvider {
        id: imageProvider
        cacheMode: true
    }

    ColumnLayout {
        id: mainColumnLayout
        height: parent.height
        width: parent.width
        TabBar {
            id: tabBar
            Layout.fillWidth: true

            TabButton {
                text: "答案和解析"
            }
            TabButton {
                text: "答案"
            }
            TabButton {
                text: "原题"
            }
            onCurrentIndexChanged: getHtml()
        }
        RowLayout {
            Layout.fillWidth: true
            Text {
                id: switchAllButton
                Layout.preferredWidth: 60
                horizontalAlignment: Text.AlignHCenter
                visible: questionsCountsListView.currentIndex !== -1
                text: "All"
                MouseArea {
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked: questionsCountsListView.currentIndex = -1
                }
            }

            ListView {
                id: questionsCountsListView
                height: Math.max(fm.ascent, 20)
                Layout.fillWidth: true
                orientation: Qt.Horizontal
                clip: true
                delegate: ItemDelegate {
                    height: questionsCountsListView.height
                    text: modelData
                    highlighted: ListView.isCurrentItem
                    onClicked: {
                        questionsCountsListView.currentIndex = index
                    }
                }
                onCurrentItemChanged: getHtml()
            }
            FontMetrics {
                id: fm
                font: Qt.application.font
            }
        }

        Flickable {
            id: flick
            Layout.fillHeight: true
            Layout.fillWidth: true
            contentHeight: templateDetailText.height
            clip: true
            Text {
                id: templateDetailText
                width: parent.width
                wrapMode: Text.Wrap

                Rectangle {
                    z: parent.z - 1
                    anchors.fill: parent
                    color: "white"
                }

                function setHtml(html) {
                    templateDetailText.text = imageProvider.loadHtml(html)
                    flick.contentY = 0
                }
            }
        }
    }

    Component.onCompleted: {
        if(templateAnalysisPointer !== null)
        {
            setTemplateRawDataQML(templateAnalysisPointer)
        }
        else
        {
            templateDetailText.text = "<h1>error</h1>"
        }
    }
    Component.onDestruction: {
    }

    function setTemplateRawDataQML(newTemplateAnalysisPointer){
        initFinish = false
        questionsCountsListView.model = newTemplateAnalysisPointer.getQuestionsCountsStrListModel()
        initFinish = true
        questionsCountsListView.currentIndex = -1
    }
    function getHtml() {
        if(!initFinish)
        {
            return
        }

        if(tabBar.currentIndex === 0)
        {
            templateDetailText.text = templateAnalysisPointer.getAnswerAndAnalysisHtml(questionsCountsListView.currentIndex)
        }
        else if(tabBar.currentIndex === 1)
        {
            templateDetailText.text = templateAnalysisPointer.getAnswerHtml(questionsCountsListView.currentIndex)
        }
        else if(tabBar.currentIndex === 2)
        {
            templateDetailText.text = templateAnalysisPointer.getQuestionHtml(questionsCountsListView.currentIndex)
        }
    }
}
