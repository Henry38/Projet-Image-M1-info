
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
    HistoRGB.cpp \
    HistoYUV.cpp \
    MyGraphicsScene.cpp \
    Calcul.cpp \
    HistoDialog.cpp

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
    HistoRGB.h \
    HistoYUV.h \
    MyGraphicsScene.h \
    Calcul.h \
    HistoDialog.h

QT += widgets

CONFIG += c++11

FORMS += \
    myWindow.ui\
    AbstractDialog.ui

RESOURCES = Images.qrc

INCLUDEPATH += "C:\opencv\build\include\opencv"
INCLUDEPATH += "C:\opencv\build\include\opencv2"
