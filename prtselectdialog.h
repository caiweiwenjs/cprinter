#ifndef PRTSELECTDIALOG_H
#define PRTSELECTDIALOG_H

#include <QDialog>
#include <QString>
#include <QAbstractButton>

namespace Ui {
class PrtSelectDialog;
}

class PrtSelectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PrtSelectDialog(QWidget *parent = 0);
    ~PrtSelectDialog();
    QString getPtrName();

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::PrtSelectDialog *ui;
    QString prt_name;
};

#endif // PRTSELECTDIALOG_H
