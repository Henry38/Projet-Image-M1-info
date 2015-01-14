
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
    scaledialog.cpp \
    FiltreDialog.cpp

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
    scaledialog.h \
    FiltreDialog.h

QT += widgets

CONFIG += c++11

FORMS += \
    myWindow.ui\
    AbstractDialog.ui
