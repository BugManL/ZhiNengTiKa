#ifndef RESOURCEFILEWIDGET_H
#define RESOURCEFILEWIDGET_H

class ResourceFileFetcher;

class ResourceFileWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ResourceFileWidget(QWidget *parent = nullptr);

public:
    void init();

protected:
    ResourceFileFetcher *resourceFileFetcher;
    QVBoxLayout *mainLayout;
    QTabBar *subjectsTabBar;
    QTabBar *editionTabBar;
    QTabBar *moduleTabBar;
    QListView *resourceFileListView;
    QPushButton *nextPage;

    bool inited=false;

protected slots:
    void onResourceFileFetcherInitFinished();
    void onSubjectsTabBarTabBarClicked(int index);
    void onEditionTabBarTabBarClicked(int index);
    void onModuleTabBarTabBarClicked(int index);
    void onResourceFileFetcherResetModelFinished();
    void onResourceFileListViewClicked(const QModelIndex &index);
    void onNextButtonClicked();
    void onResourceFileFetcherContinueLoadModelFinished();
    void onResourceFileFetcherDownloadFinished(const QString &path);
    void onResourceFileFetcherError(const QString &msg);

signals:
};

#endif // RESOURCEFILEWIDGET_H
