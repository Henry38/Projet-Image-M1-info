
#include "FusionDialog.h"

FusionDialog::FusionDialog(QImage *img) : AbstractDialog() {
    imgSource = img;
    imgOpen = new QImage(img->width(), img->height(), QImage::Format_ARGB32);
    apercu = new QImage(img->width(), img->height(), QImage::Format_ARGB32);

    textBrowser = new QLineEdit(this);
    textBrowser->move(20, 291);
    textBrowser->resize(260, 30);
    textBrowser->setReadOnly(true);

    openButton = new QPushButton("Ouvrir", this);
    openButton->move(280, 291);
    openButton->resize(120, 30);

    slider = new QSlider(Qt::Horizontal, this);
    slider->move(20, 320);
    slider->resize(120, 30);
    slider->setMaximum(255);
    slider->setSliderPosition(slider->minimum());

    label = new QLabel(this);
    label->move(160, 325);
    label->resize(120, 20);

    QObject::connect(openButton, SIGNAL(clicked()), this, SLOT(openFilename()));
    QObject::connect(slider, SIGNAL(valueChanged(int)), this, SLOT(writeOpacity(int)));

    writeOpacity(slider->value());
    updateViewer();
}

FusionDialog::~FusionDialog() {
    delete imgOpen;
    delete apercu;
    delete textBrowser;
    delete openButton;
    delete slider;
    delete label;
}

void FusionDialog::updateViewer()
{
    double q;
    if (textBrowser->text() != "") {
        q = ((float) slider->value()) / ((float) slider->maximum());
    } else {
        q = 0.0;
    }
    //double alpha;
    QRgb pixelSource, pixelOpen, color;
    for (int i = 0; i < imgSource->width(); i++)
    {
        for (int j = 0; j < imgSource->height(); j++)
        {
            pixelSource = imgSource->pixel(i, j);
            if (matchImage(i, j)) {
                pixelOpen = imgOpen->pixel(i-imgOpen_x, j-imgOpen_y);
            } else {
                pixelOpen = qRgba(0, 0, 0, 0);
            }
            //alpha = ((float) qAlpha(pixelOpen)) / 255.0;
            color = qRgba((1-q)*qRed(pixelSource) + q*qRed(pixelOpen),
                          (1-q)*qGreen(pixelSource) + q*qGreen(pixelOpen),
                          (1-q)*qBlue(pixelSource) + q*qBlue(pixelOpen),
                          (1-q)*qAlpha(pixelSource) + q*qAlpha(pixelOpen));
            apercu->setPixel(i, j, color);
        }
    }
    display(apercu);
}

void FusionDialog::acceptDialog()
{
    if (textBrowser->text() != "") {
        imgSource->swap(*apercu);
    }
}

void FusionDialog::openFilename()
{
    QString filename = QFileDialog::getOpenFileName(this,
        "Ouvrir une image", QDir::currentPath() + "/../Projet-Image-M1-info/ressources", "Image Files (*.png *.jpg)");
    if (filename != "")
    {
        textBrowser->setText(filename);
        imgOpen->load(filename);
        // Ces deux variables servent a positionner
        // l'imgOpen sur l'imgSource
        imgOpen_x = 0;
        imgOpen_y = 0;
        updateViewer();
    }
}

void FusionDialog::writeOpacity(int value) {
    label->setText("Opacité : " + QString::number(value));
    updateViewer();
}

bool FusionDialog::matchImage(int x, int y) {
    if (textBrowser->text() == "") {
        return false;
    }
    return (x >= imgOpen_x && x < imgOpen_x+imgOpen->width() && y >= imgOpen_y && y < imgOpen_y+imgOpen->height());
}
