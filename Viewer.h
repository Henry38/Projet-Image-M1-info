#ifndef VIEWER_H
#define VIEWER_H

#include <QWidget>
#include <QImage>
#include <QLabel>
#include <QScrollArea>

class Viewer : public QWidget {

public:
    Viewer(int x, int y, int width, int height, QImage &img, QWidget *parent);
    ~Viewer();

private:
    QLabel *m_label;
    QScrollArea *m_scrollArea;

};

#endif // VIEWER_H
