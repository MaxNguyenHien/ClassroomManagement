#include "registerform.h"
#include "loginform.h"
#include "ui_registerform.h"
#include "ui_loginform.h"
#include "xlsxdocument.h"
#include "CheckInput.cpp"
#include <QMessageBox>

RegisterForm::RegisterForm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RegisterForm)
{
    ui->setupUi(this);

    setFixedSize(318, 344);

    filePath = "D://PROJECT C++//Student_Management_System//StudentManagement//data.xlsx";

    connect(ui->pushButtonRegisterR, &QPushButton::clicked, this, &RegisterForm::onButtonRegisterClicked);
    connect(ui->pushButtonCancel, &QPushButton::clicked, this, &RegisterForm::onCancelButtonClicked);


    ui->lineEdit_usernameR->setPlaceholderText("Username");
    ui->lineEdit_passwordR->setPlaceholderText("Password");
    ui->lineEdit_passwordR2->setPlaceholderText("Confirm password");
}

void RegisterForm::onButtonRegisterClicked(){

    QString username = ui->lineEdit_usernameR->text();
    QString password = ui->lineEdit_passwordR->text();
    QString password2 = ui->lineEdit_passwordR2->text();

    if(password != password2){
        QMessageBox::critical(this, "Error", "Password not match!");
            return;
    }
    if(username == "" || password == ""){
            QMessageBox::critical(this, "Error", "Invalid Username or Password!");
            return;
    }
    if (isAccountExists(username)) {
            // Tài khoản đã tồn tại, hiển thị thông báo lỗi
            QMessageBox::critical(this, "Error", "Account already exists.");
            return;
    }
    if(!CheckInput::isValidString(username)){
            QMessageBox::critical(this, "Error", "Invalid Username or Password!");
            return;
    }
    if(password.contains(QRegularExpression("\\s"))){
            QMessageBox::critical(this, "Error", "Invalid Username or Password!");
            return;
    }
    QXlsx::Document xlsx(filePath);
    int lastRow = xlsx.dimension().lastRow();
        xlsx.write(lastRow+1, 1, username);
        xlsx.write(lastRow+1, 2, password);


    if (xlsx.save()) {
        QMessageBox::information(this, "Success", "Register successfully.");
        ui->lineEdit_usernameR->setText("");
        ui->lineEdit_passwordR->setText("");
        ui->lineEdit_passwordR2->setText("");
    } else {
        QMessageBox::critical(this, "Error", "Failed register.");
    }
}

bool RegisterForm::isAccountExists(QString username) {
    QXlsx::Document xlsx(filePath);

    // Lấy số dòng cuối cùng trong file Excel
    int lastRow = xlsx.dimension().lastRow();

    // Đọc dữ liệu từ cột A (cột 1) và kiểm tra xem tài khoản đã tồn tại hay chưa
    for (int row = 1; row <= lastRow; row++) {
        QString existingUsername = xlsx.read(row, 1).toString();
        if (existingUsername.compare(username, Qt::CaseInsensitive) == 0) {
            return true;  // Tài khoản đã tồn tại
        }
    }

    return false;  // Tài khoản không tồn tại
}

void RegisterForm::onCancelButtonClicked(){

    this->close();
    LoginForm *lf = new LoginForm;
    lf->show();
}

RegisterForm::~RegisterForm()
{
    delete ui;
}
