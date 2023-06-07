#ifndef REGISTERFORM_H
#define REGISTERFORM_H

#include <QMainWindow>

namespace Ui {
class RegisterForm;
}

class RegisterForm : public QMainWindow
{
    Q_OBJECT

public:
    explicit RegisterForm(QWidget *parent = nullptr);
    ~RegisterForm();

private:
    Ui::RegisterForm *ui;

    QString filePath;

    void onButtonRegisterClicked();
    void onCancelButtonClicked();
    bool isAccountExists(QString);
};

#endif // REGISTERFORM_H
