
SOURCES += \
    main.cpp \
    myWindow.cpp \
    BlurDialog.cpp \
    MyGraphicsView.cpp \
    MyGraphicsScene.cpp \
    Convolution.cpp \
    Matrix.cpp \
    AbstractDialog.cpp \
    FusionDialog.cpp \
    Histogramme.cpp \
    FiltreDialog.cpp \
    ScaleDialog.cpp

HEADERS += \
    myWindow.h \
    BlurDialog.h \
    MyGraphicsView.h \
    MyGraphicsScene.h \
    Convolution.h \
    Matrix.h \
    AbstractDialog.h \
    FusionDialog.h \
    Histogramme.h \
    FiltreDialog.h \
    ScaleDialog.h

QT += widgets

CONFIG += c++11

FORMS += \
    myWindow.ui\
    AbstractDialog.ui
