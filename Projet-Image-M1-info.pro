
SOURCES += \
    main.cpp \
    myWindow.cpp \
    Viewer.cpp \
    BlurDialog.cpp \
    Convolution.cpp \
    Matrix.cpp \
    AbstractDialog.cpp \
    FusionDialog.cpp \
    ResizeTool.cpp

HEADERS += \
    myWindow.h \
    Viewer.h \
    BlurDialog.h \
    Convolution.h \
    Matrix.h \
    AbstractDialog.h \
    FusionDialog.h \
    ResizeTool.h

QT += widgets

CONFIG += c++11

FORMS += \
    AbstractDialog.ui
