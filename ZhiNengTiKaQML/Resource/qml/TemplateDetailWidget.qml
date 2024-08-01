import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import ImageProvider

Item {
    property var templateAnalysisPointer: null
    property bool initFinish: false

    ImageProvider {
        id: imageProvider
        placeholder: true
        onProgress: function(finished, total) {
            progressLayout.visible = (finished !== total)
            progressBar.to = total
            progressBar.value = finished
            progressText.text = finished + "/" + total
        }
        onTextUpdated: function(html) {
            templateDetailText.setHtmlDirectly(html)
        }
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
                Layout.preferredWidth: textMetrics.width
                horizontalAlignment: Text.AlignHCenter
                visible: questionsCountsListView.currentIndex !== -1
                text: "All"
                MouseArea {
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked: questionsCountsListView.currentIndex = -1
                }
                TextMetrics {
                    id: textMetrics
                    font: switchAllButton.font
                    text: switchAllButton.text
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
                FontMetrics {
                    id: fm
                    font: Qt.application.font
                }
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

                property var processedHtml

                Rectangle {
                    z: parent.z - 1
                    anchors.fill: parent
                    color: "white"
                }

                function setHtmlAndFlickToTop(html) {
                    templateDetailText.processedHtml = imageProvider.loadHtml(html)
                    reload()
                }

                function setHtmlDirectly(html) {
                    templateDetailText.text = ""
                    templateDetailText.text = html
                }

                function reload() {
                    templateDetailText.text = ""
                    templateDetailText.text = templateDetailText.processedHtml
                }
            }
        }

        RowLayout {
            id: progressLayout
            Layout.fillWidth: true
            visible: false
            ProgressBar {
                id: progressBar
                Layout.fillWidth: true
            }
            Text {
                id: progressText
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
            templateDetailText.setHtmlAndFlickToTop("<h1>error</h1>")
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
            templateDetailText.setHtmlAndFlickToTop(templateAnalysisPointer.getAnswerAndAnalysisHtml(questionsCountsListView.currentIndex))
        }
        else if(tabBar.currentIndex === 1)
        {
            templateDetailText.setHtmlAndFlickToTop(templateAnalysisPointer.getAnswerHtml(questionsCountsListView.currentIndex))
        }
        else if(tabBar.currentIndex === 2)
        {
            templateDetailText.setHtmlAndFlickToTop(templateAnalysisPointer.getQuestionHtml(questionsCountsListView.currentIndex))
        }
    }
}
