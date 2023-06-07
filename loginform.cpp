#include "loginform.h"
#include "mainwindow.h"
#include "registerform.h"
#include "ui_loginform.h"
#include "ui_mainwindow.h"
#include "ui_registerform.h"
#include "xlsxdocument.h"


LoginForm::LoginForm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginForm)
{
    ui->setupUi(this);

    setFixedSize(318, 344);

    filePath = "D://PROJECT C++//Student_Management_System//StudentManagement//data.xlsx";
    connect(ui->pushButtonLogin, &QPushButton::clicked, this, &LoginForm::on_pushButtonl_clicked);
    connect(ui->pushButtonRegister, &QPushButton::clicked, this, &LoginForm::on_pushButton_cancel_clicked);

    ui->lineEdit_username->setPlaceholderText("Username");

    ui->lineEdit_password->setPlaceholderText("Password");
}

void LoginForm::on_pushButtonl_clicked()
{
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();
    if(username == "" || password == ""){
        QMessageBox::critical(this, "Error", "Infor not match");
        return;
    }

    if(CheckExistingUser(username, password))
    {
        this->close();
        MainWindow *mw = new MainWindow;
        //ui->setupUi(mw);
        mw->show();
    }
    else
    {
        QMessageBox::critical(this,"Error","Infor not match");
    }
}

bool LoginForm::CheckExistingUser(QString username, QString password){
    QXlsx::Document xlsx(filePath);
    int lastRow = xlsx.dimension().lastRow();
    for(int row = 1; row <= lastRow; row++){
        QString existingUsername = xlsx.read(row, 1).toString();
        QString existingPassword = xlsx.read(row, 2).toString();
        if(username == existingUsername && password == existingPassword){
            return true;
        }
    }
    return false;
}


void LoginForm::on_pushButton_cancel_clicked()
{
    this->close();
    RegisterForm *rf = new RegisterForm;
    rf->show();
}

LoginForm::~LoginForm()
{
    delete ui;
}
