#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QMainWindow>
#include <QMessageBox>

namespace Ui {
class LoginForm;
}

class LoginForm : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginForm(QWidget *parent = nullptr);
    ~LoginForm();

private:
    Ui::LoginForm *ui;

    QString filePath;

    void on_pushButtonl_clicked();
    void on_pushButton_cancel_clicked();
    bool CheckExistingUser(QString, QString);
};

#endif // LOGINFORM_H
