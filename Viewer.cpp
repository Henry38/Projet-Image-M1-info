
#include "Viewer.h"

Viewer::Viewer(int x, int y, int width, int height, QImage *img, QWidget *parent = 0) : QWidget(parent) {
    move(x, y);
    setFixedSize(width, height);

    m_label = new QLabel();

    m_scrollArea = new QScrollArea(this);
    m_scrollArea->move(0, 0);
    m_scrollArea->resize(width, height);
    m_scrollArea->setWidgetResizable(true);

    setImage(img);
}

Viewer::~Viewer() {
    delete m_label;
    delete m_scrollArea;
}

void Viewer::setImage(QImage *img) {
    m_label->setPixmap(QPixmap::fromImage(*img));
    m_scrollArea->setWidget(m_label);
    repaint();
}
