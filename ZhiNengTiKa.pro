TEMPLATE = subdirs

SUBDIRS += \
    ZhiNengTiKaCore \
    ZhiNengTiKaQML

ZhiNengTiKaQML.depends = ZhiNengTiKaCore

!android {
    SUBDIRS += ZhiNengTiKaWidgets
    ZhiNengTiKaWidgets.depends = ZhiNengTiKaCore
}
