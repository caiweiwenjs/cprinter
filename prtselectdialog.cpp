#include "prtselectdialog.h"
#include "ui_prtselectdialog.h"
#include "sqlhelper.h"

PrtSelectDialog::PrtSelectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PrtSelectDialog)
{
    ui->setupUi(this);

    SqlHelper *sqlHelper = SqlHelper::GetInstance();
    QVector<QVector<QVariant> > res = sqlHelper->exec("select printer_name from user_printer;", 1);
    for (auto i : res) {
        ui->listWidget->addItem(i[0].toString());
        //ui->listWidget->addItem(i[1].toString());
    }
}

PrtSelectDialog::~PrtSelectDialog()
{
    delete ui;
}

QString PrtSelectDialog::getPtrName() {
    return prt_name;
}

void PrtSelectDialog::on_buttonBox_clicked(QAbstractButton *button)
{
    //qDebug() << "132";
    QList <QListWidgetItem *> ql = ui->listWidget->selectedItems();
    if (ql.size() <= 0) {
        QDialog *dialog = new QDialog();
        dialog->setWindowTitle("select one");
        dialog->exec();
        delete dialog;
        return ;
    }
    //qDebug() << "132";
    //qDebug() << ql[0]->text();

    if (ui->buttonBox->button(QDialogButtonBox::Ok) == (QPushButton *)button) {
        prt_name = ql[0]->text();
    } else if (ui->buttonBox->button(QDialogButtonBox::Cancel) == (QPushButton *)button) {
        prt_name = "";
    } else {
        qDebug() << "error";
    }
}
