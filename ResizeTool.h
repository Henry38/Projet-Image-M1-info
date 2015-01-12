#ifndef RESIZETOOL_H
#define RESIZETOOL_H

#include <QPaintEvent>

class ResizeTool : QWidget {

    Q_OBJECT

public:
    ResizeTool();
    ~ResizeTool();
    paintEvent(QPaintEvent*);
};

#endif // RESIZETOOL_H
