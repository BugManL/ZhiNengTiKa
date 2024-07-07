#include "ResourceFileWidget.h"
#include "../Logic/ResourceFileFetcher.h"

ResourceFileWidget::ResourceFileWidget(QWidget *parent)
    : QWidget{ parent },
      resourceFileFetcher(new ResourceFileFetcher(this)),
      mainLayout(new QVBoxLayout(this)),
      subjectsTabBar(new QTabBar(this)),
      editionTabBar(new QTabBar(this)),
      moduleTabBar(new QTabBar(this)),
      resourceFileListView(new QListView(this)),
      nextPage(new QPushButton(QStringLiteral("下一页"), this))
{
    const auto fakeTabIndex1 = subjectsTabBar->addTab(QString());
    subjectsTabBar->setTabVisible(fakeTabIndex1, false);
    const auto fakeTabIndex2 = editionTabBar->addTab(QString());
    editionTabBar->setTabVisible(fakeTabIndex2, false);
    const auto fakeTabIndex3 = moduleTabBar->addTab(QString());
    moduleTabBar->setTabVisible(fakeTabIndex3, false);
    nextPage->setVisible(false);
    resourceFileListView->setModel(resourceFileFetcher->getModel());
    mainLayout->addWidget(subjectsTabBar);
    mainLayout->addWidget(editionTabBar);
    mainLayout->addWidget(moduleTabBar);
    mainLayout->addWidget(resourceFileListView);
    mainLayout->addWidget(nextPage);
    connect(resourceFileFetcher, &ResourceFileFetcher::initFinished, this, &ResourceFileWidget::onResourceFileFetcherInitFinished);
    connect(subjectsTabBar, &QTabBar::tabBarClicked, this, &ResourceFileWidget::onSubjectsTabBarTabBarClicked);
    connect(editionTabBar, &QTabBar::tabBarClicked, this, &ResourceFileWidget::onEditionTabBarTabBarClicked);
    connect(moduleTabBar, &QTabBar::tabBarClicked, this, &ResourceFileWidget::onModuleTabBarTabBarClicked);
    connect(resourceFileListView, &QListView::clicked, this, &ResourceFileWidget::onResourceFileListViewClicked);
    connect(nextPage, &QPushButton::clicked, this, &ResourceFileWidget::onNextButtonClicked);
    connect(resourceFileFetcher, &ResourceFileFetcher::continueLoadModelFinished, this, &ResourceFileWidget::onResourceFileFetcherContinueLoadModelFinished);
    connect(resourceFileFetcher, &ResourceFileFetcher::downloadResourceFileFinished, this, &ResourceFileWidget::onResourceFileFetcherDownloadFinished);
}

void ResourceFileWidget::init()
{
    if(inited)
        return;
    inited = true;
    this->setEnabled(false);
    resourceFileFetcher->init();
}

void ResourceFileWidget::onResourceFileFetcherInitFinished()
{
    const auto list(resourceFileFetcher->getSubjectList());
    for(const auto &i : list)
    {
        subjectsTabBar->addTab(i);
    }
    this->setEnabled(true);
}

void ResourceFileWidget::onSubjectsTabBarTabBarClicked(int index)
{
    if(index == -1)
        return;
    for(auto i(1); i < editionTabBar->count(); ++i)
        editionTabBar->removeTab(i);
    const auto list(resourceFileFetcher->getEditionList(subjectsTabBar->tabText(index)));
    for(const auto &i : list)
    {
        editionTabBar->addTab(i);
    }
}

void ResourceFileWidget::onEditionTabBarTabBarClicked(int index)
{
    if(index == -1)
        return;
    for(auto i(1); i < moduleTabBar->count(); ++i)
        moduleTabBar->removeTab(i);
    const auto list(resourceFileFetcher->getModuleList(subjectsTabBar->tabText(subjectsTabBar->currentIndex()), editionTabBar->tabText(index)));
    for(const auto &i : list)
    {
        moduleTabBar->addTab(i);
    }
}

void ResourceFileWidget::onModuleTabBarTabBarClicked(int index)
{
    if(index == -1)
        return;
    this->setEnabled(false);
    resourceFileFetcher->resetModel(subjectsTabBar->tabText(subjectsTabBar->currentIndex()),
                                    editionTabBar->tabText(editionTabBar->currentIndex()),
                                    moduleTabBar->tabText(moduleTabBar->currentIndex()));
}

void ResourceFileWidget::onResourceFileFetcherResetModelFinished()
{
    nextPage->setVisible(resourceFileFetcher->haveNextPage());
    QScrollBar *pVerticalScrollBar = resourceFileListView->verticalScrollBar();
    pVerticalScrollBar->setValue(0);
    this->setEnabled(true);
}

void ResourceFileWidget::onResourceFileListViewClicked(const QModelIndex &index)
{
    if(!index.isValid())
        return;
    this->setEnabled(false);
    resourceFileFetcher->downloadResourceFile(index.row(),
                                              subjectsTabBar->tabText(subjectsTabBar->currentIndex()),
                                              editionTabBar->tabText(editionTabBar->currentIndex()),
                                              moduleTabBar->tabText(moduleTabBar->currentIndex()));
}

void ResourceFileWidget::onNextButtonClicked()
{
    nextPage->setVisible(false);
    resourceFileFetcher->continueLoadModel();
}

void ResourceFileWidget::onResourceFileFetcherContinueLoadModelFinished()
{
    nextPage->setVisible(resourceFileFetcher->haveNextPage());
}

void ResourceFileWidget::onResourceFileFetcherDownloadFinished(const QString &path)
{
    QDesktopServices::openUrl(QUrl::fromLocalFile(path));
}

void ResourceFileWidget::onResourceFileFetcherError(const QString &msg)
{
    this->setEnabled(true);
    QMessageBox::warning(this, {}, msg);
}
