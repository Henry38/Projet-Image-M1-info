
#include "AbstractDialog.h"
#include "ui_AbstractDialog.h"

AbstractDialog::AbstractDialog() : QDialog(0), ui(new Ui::AbstractDialog) {
    ui->setupUi(this);

    label = new QLabel();

    QObject::connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(updateViewer()));
    QObject::connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    QObject::connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    QObject::connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(acceptDialog()));
}

AbstractDialog::~AbstractDialog() {
    delete ui;
    delete label;
}

void AbstractDialog::display(QImage *img) {
    label->setPixmap(QPixmap::fromImage(*img));
    ui->scrollArea->setWidget(label);
}

/*QScrollArea* AbstractDialog::getViewer() {
    return ui->scrollArea;
}*/
