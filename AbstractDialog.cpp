
#include "AbstractDialog.h"
#include "ui_AbstractDialog.h"

AbstractDialog::AbstractDialog() : QDialog(0), ui(new Ui::AbstractDialog) {
    ui->setupUi(this);

    QObject::connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(updateViewer()));
    QObject::connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    QObject::connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    QObject::connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(acceptDialog()));
}

AbstractDialog::~AbstractDialog() {
    delete ui;
}

QScrollArea* AbstractDialog::getViewer() {
    return ui->scrollArea;
}
