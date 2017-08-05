#-------------------------------------------------
#
# Project created by QtCreator 2016-10-01T00:01:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = IPpng
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    PngProc.cpp \
    handler.cpp \
    dialog.cpp \
    noize.cpp \
    convolutiondialog.cpp \
    addnoizedialog.cpp \
    globcontrastdialog.cpp \
    impulsenoizedialog.cpp \
    bindialog.cpp \
    nlmeansdialog.cpp

HEADERS  += mainwindow.h \
    PngProc.h \
    includ/crc32.h \
    includ/deflate.h \
    includ/inffast.h \
    includ/inffixed.h \
    includ/inflate.h \
    includ/inftrees.h \
    includ/png.h \
    includ/pngconf.h \
    includ/pngdebug.h \
    includ/pnginfo.h \
    includ/pnglibconf.h \
    includ/pngpriv.h \
    includ/pngstruct.h \
    includ/trees.h \
    includ/zconf.h \
    includ/zlib.h \
    includ/zutil.h \
    handler.h \
    dialog.h \
    noize.h \
    convolutiondialog.h \
    addnoizedialog.h \
    globcontrastdialog.h \
    impulsenoizedialog.h \
    bindialog.h \
    nlmeansdialog.h




FORMS    += mainwindow.ui \
    dialog.ui \
    convolutiondialog.ui \
    addnoizedialog.ui \
    globcontrastdialog.ui \
    impulsenoizedialog.ui \
    bindialog.ui \
    nlmeansdialog.ui



INCLUDEPATH += "C:/QtProjects/IPf_png/IPpng/includ"

LIBS+=-L"C:/QtProjects/IPf_png/IPpng/lib/" -lLibPNG1


CONFIG(debug, debug|release) {
    LIBS += -lLibPNG1
}
CONFIG(release, debug|release) {
    LIBS += -lLibPNG1
}

RESOURCES += \
    images.qrc


