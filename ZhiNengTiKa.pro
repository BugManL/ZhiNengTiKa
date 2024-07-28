TEMPLATE = subdirs

SUBDIRS += \
    3rd_build/Qt-AES \
    3rd_build/zxing-cpp \
    ZhiNengTiKaCore \
    ZhiNengTiKaWidgets \
    ZhiNengTiKaQML

ZhiNengTiKaCore.depends = 3rd_build/Qt-AES
ZhiNengTiKaCore.depends = 3rd_build/zxing-cpp
ZhiNengTiKaWidgets.depends = ZhiNengTiKaCore
ZhiNengTiKaQML.depends = ZhiNengTiKaCore
