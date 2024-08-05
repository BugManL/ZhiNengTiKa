#ifndef WEBVIEWWIDGET_H
#define WEBVIEWWIDGET_H

#include "src/Logic/ImageProviderMultiThreading.h"
#include "src/Logic/TemplateAnalysis.h"

class WebView : public QTextBrowser
{
    Q_OBJECT

public:
    explicit WebView(QWidget *parent = nullptr)
        : QTextBrowser{ parent }
    {
        imageProvider.setPlaceholder(true);
        connect(&imageProvider, &ImageProviderMultiThreading::textUpdated, this, &WebView::onTextUpdated);
        connect(&imageProvider, &ImageProviderMultiThreading::progress, this, &WebView::progress);
    }
    void setHtml(const QString &html)
    {
        this->html = html;
        imageProvider.loadHtml(html);
    }
    QString getHtml() const
    {
        return this->html;
    }

protected:
    QString html;
    ImageProviderMultiThreading imageProvider;
protected slots:
    void onTextUpdated(const QString &str)
    {
        const auto horizontalScrollBarValue(this->horizontalScrollBar()->value());
        const auto verticalScrollBarValue(this->verticalScrollBar()->value());
        this->QTextBrowser::setHtml(str);
        this->horizontalScrollBar()->setValue(horizontalScrollBarValue);
        this->verticalScrollBar()->setValue(verticalScrollBarValue);
    }

signals:
    void progress(int finished, int total);
};

class WebViewWidget : public QWidget
{
    Q_OBJECT

public:
    explicit WebViewWidget(const TemplateAnalysis &templateAnalysis, QWidget *parent = nullptr);
    virtual QString getAnalyzedHtml(const qsizetype index = -1) = 0;

    const TemplateAnalysis &getTemplateAnalysis() const;
    void setTemplateAnalysis(const TemplateAnalysis &newTemplateAnalysis);

protected:
    QGridLayout *mainLayout;
    WebView *webView;
    QListWidget *pagesSwitch;

    QProgressBar *progressBar;

    QPushButton *openBrowserButton;

    qsizetype currentPageIndex = -1;
    QHash<QString, qsizetype> pageHash;

    bool templateAnalysisStateChanged = false;

    TemplateAnalysis templateAnalysis;
    void showEvent(QShowEvent *event) override;

    void keyPressEvent(QKeyEvent *event) override;

public slots:
    void saveToFile(const QString &pathName);

protected slots:
    void analysis();
    void switchPage(QListWidgetItem *item);

    void openByBrowser();

    void onWebViewProgress(int finished, int total);

signals:

    void templateAnalysisChanged();

private:
    Q_PROPERTY(TemplateAnalysis templateAnalysis READ getTemplateAnalysis WRITE setTemplateAnalysis NOTIFY templateAnalysisChanged FINAL)
};

#endif // WEBVIEWWIDGET_H
