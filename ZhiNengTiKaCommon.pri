VERSION = 4.0.0
DEFINES += APP_VERSION=\\\"$$VERSION\\\"
ANDROID_VERSION_NAME = $$VERSION
ANDROID_VERSION_CODE = 1

DEFINES += DATABASE_DOMAIN=\\\"https://gitee.com/LFWQSP2641/zhinengtika_database/raw/master/\\\"

DEFINES *= QT_USE_QSTRINGBUILDER

CONFIG += c++17 skip_target_version_ext

win32{

RC_ICONS = $$PWD/ZhiNengTiKaCore/Resource/img/xinjiaoyuico.ico

QMAKE_TARGET_PRODUCT = "ZhiNengTiKa"

QMAKE_TARGET_COPYRIGHT = "Copyright © 2022 - 2023 LFWQSP2641.All Rights Reserved."

RC_LANG = 0x0004

}
