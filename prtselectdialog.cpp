#include "prtselectdialog.h"
#include "ui_prtselectdialog.h"
#include "sqlhelper.h"
#include "unixutil.h"

PrtSelectDialog::PrtSelectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PrtSelectDialog)
{
    ui->setupUi(this);

    SqlHelper *sqlHelper = SqlHelper::GetInstance();
    QVector<UserPrinter> userPrinters = sqlHelper->getUserPrinterByUserName(UnixUtil::getUserName());
    //QVector<QVector<QVariant> > res = sqlHelper->exec("select printer_name from user_printer;", 1);
    for (auto i : userPrinters) {
        ui->listWidget->addItem(i.getPrinterName());
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
    QList <QListWidgetItem *> ql = ui->listWidget->selectedItems();
    if (ql.size() <= 0) {
        QDialog *dialog = new QDialog();
        dialog->setWindowTitle("select one");
        dialog->exec();
        delete dialog;
        return ;
    }

    if (ui->buttonBox->button(QDialogButtonBox::Ok) == (QPushButton *)button) {
        prt_name = ql[0]->text();
    } else if (ui->buttonBox->button(QDialogButtonBox::Cancel) == (QPushButton *)button) {
        prt_name = "";
    } else {
        qDebug() << "error";
    }
}
