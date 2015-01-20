
SOURCES += \
    main.cpp \
    myWindow.cpp \
    BlurDialog.cpp \
    MyGraphicsView.cpp \
    Convolution.cpp \
    Matrix.cpp \
    AbstractDialog.cpp \
    FusionDialog.cpp \
    Histogramme.cpp \
    FiltreDialog.cpp \
    ScaleDialog.cpp \
    HistoDialog.cpp \
    HistoRGB.cpp \
    HistoYUV.cpp

HEADERS += \
    myWindow.h \
    BlurDialog.h \
    MyGraphicsView.h \
    Convolution.h \
    Matrix.h \
    AbstractDialog.h \
    FusionDialog.h \
    Histogramme.h \
    FiltreDialog.h \
    ScaleDialog.h \
    HistoDialog.h \
    HistoRGB.h \
    HistoYUV.h

QT += widgets

CONFIG += c++11

FORMS += \
    myWindow.ui\
    AbstractDialog.ui

RESOURCES = Images.qrc
