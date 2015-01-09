
SOURCES += \
    main.cpp \
    myWindow.cpp \
    Viewer.cpp \
    BlurDialog.cpp \
    MyGraphicsView.cpp \
    MyGraphicsScene.cpp \
    Convolution.cpp \
    Matrix.cpp \
    AbstractDialog.cpp \
    FusionDialog.cpp

HEADERS += \
    myWindow.h \
    Viewer.h \
    BlurDialog.h \
    MyGraphicsView.h \
    MyGraphicsScene.h \
    Convolution.h \
    Matrix.h \
    AbstractDialog.h \
    FusionDialog.h

QT += widgets

CONFIG += c++11

FORMS += \
    myWindow.ui\
    AbstractDialog.ui
