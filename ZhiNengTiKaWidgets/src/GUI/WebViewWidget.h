#ifndef WEBVIEWWIDGET_H
#define WEBVIEWWIDGET_H

#include "src/Logic/ImageProvider.h"
#include "src/Logic/TemplateAnalysis.h"

class WebView : public QTextBrowser
{
    Q_OBJECT

public:
    explicit WebView(QWidget *parent = nullptr)
        : QTextBrowser{ parent }
    {
        QPalette palette;
        palette.setColor(QPalette::Window, Qt::white);
        this->setPalette(QPalette());
        connect(&imageProvider, &ImageProvider::progress, this, &WebView::reload);
        connect(&imageProvider, &ImageProvider::progress, this, &WebView::progress);
    }
    void setHtml(const QString &html)
    {
        this->html = html;
        this->processedHtml = imageProvider.loadHtml(this->html);
        this->QTextBrowser::setHtml(processedHtml);
    }
    QString getHtml() const
    {
        return this->html;
    }

protected:
    QString html;
    QString processedHtml;
    ImageProvider imageProvider;
protected slots:
    void reload() override
    {
        qDebug() << Q_FUNC_INFO;
        const auto horizontalScrollBarValue(this->horizontalScrollBar()->value());
        const auto verticalScrollBarValue(this->verticalScrollBar()->value());
        this->setHtml(processedHtml);
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
