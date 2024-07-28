CONFIG += precompile_header
PRECOMPILED_HEADER = $$PWD/pch.h
SOURCES += $$PWD/pch.h.cpp
INCLUDEPATH += $$PWD/../3rd
DEPENDPATH += $$PWD/../3rd
INCLUDEPATH += $$PWD/../3rd_build/src
DEPENDPATH += $$PWD/../3rd_build/src

INCLUDEPATH += $$PWD/../3rd/quazip/quazip
DEPENDPATH += $$PWD/../3rd/quazip/quazip
INCLUDEPATH += $$PWD/../3rd/zlib
DEPENDPATH += $$PWD/../3rd/zlib
