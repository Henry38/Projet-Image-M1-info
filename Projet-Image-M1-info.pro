
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

INCLUDEPATH += "usr\include\opencv"

LIBS += -L"usr\lib" \
    -lopencv_core \
    -lopencv_highgui \
    -lopencv_imgproc \
    -lopencv_features2d \
    -lopencv_calib3d \
    -lopencv_objdetect \
    -lopencv_ml
