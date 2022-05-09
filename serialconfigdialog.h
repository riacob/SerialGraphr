/*
 *
 * @Author Riccardo Iacob
 * @File serialconfigdialog.h
 * @Date 09/05/2022
 *
 * @Description this dialog window allows the user to safely configure all the properties held in the SerialConfig class
 *
*/

#ifndef SERIALCONFIGDIALOG_H
#define SERIALCONFIGDIALOG_H

#include <QDialog>

#include "serialconfig.h"
#include "logger.h"

namespace Ui {
class SerialConfigDialog;
}

class SerialConfigDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SerialConfigDialog(QWidget *parent = nullptr);
    ~SerialConfigDialog();
    SerialConfig* getSerialConfig();

private slots:
    void on_pushButtonRefreshDevices_clicked();

    void on_pushButtonExitOk_clicked();

    void on_pushButtonExitCancel_clicked();

private:
    SerialConfig* serialConfig = NULL;
    Logger* logger;
    Ui::SerialConfigDialog *ui;
    void saveConfig();
    bool validateConfig();
    void refreshDevices();
};

#endif // SERIALCONFIGDIALOG_H
