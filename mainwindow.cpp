#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "Student.cpp"
#include "CheckInput.cpp"
#include <QTableWidget>
#include <QMessageBox>
#include <string>
#include <QIcon>
#include <QFileDialog>
#include "loginform.h"
#include "xlsxdocument.h"
#include <QtCharts>
#include <QVBoxLayout>
#include <QtGlobal>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(1000, 700);

    checkUpdate = false;
    filePathSystem = "";


    //settings combobox
    QStringList listProvince =(QStringList()<<"An Giang"
                                              <<"Ba Ria – Vung Tau"
                                              <<"Bac Lieu"
                                              <<"Bac Giang"
                                              <<"Bac Kan"
                                              <<"Bac Ninh"
                                              <<"Ben Tre"
                                              <<"Binh Duong"
                                              <<"Binh Dinh"
                                              <<"Binh Phuoc"
                                              <<"Binh Thuan"
                                              <<"Ca Mau"
                                              <<"Cao Bang"
                                              <<"Can Tho"
                                              <<"Da Nang"
                                              <<"Dak Lak"
                                              <<"Dak Nong"
                                              <<"Dien Bien"
                                              <<"Dong Nai"
                                              <<"Dong Thap"
                                              <<"Gia Lai"
                                              <<"Ha Giang"
                                              <<"Ha Nam"
                                              <<"Hanoi"
                                              <<"Ha Tinh"
                                              <<"Hai Duong"
                                              <<"Hai Phong"
                                              <<"Hau Giang"
                                              <<"Hoa Binh"
                                              <<"Hung Yen"
                                              <<"Khanh Hoa"
                                              <<"Kien Giang"
                                              <<"Kon Tum"
                                              <<"Lai Chau"
                                              <<"Lang Son"
                                              <<"Lao Cai"
                                              <<"Lam Dong"
                                              <<"Long An"
                                              <<"Nam Dinh"
                                              <<"Nghe An"
                                              <<"Ninh Binh"
                                              <<"Ninh Thuan"
                                              <<"Phu Tho"
                                              <<"Phu Yen"
                                              <<"Quang Binh"
                                              <<"Quang Nam"
                                              <<"Quang Ngai"
                                              <<"Quang Ninh"
                                              <<"Quang Tri"
                                              <<"Soc Trang"
                                              <<"Son La"
                                              <<"Tay Ninh"
                                              <<"Thai Binh"
                                              <<"Thai Nguyen"
                                              <<"Thanh Hoa"
                                              <<"Ho Chi Minh city"
                                              <<"Thua Thien Hue"
                                              <<"Tien Giang"
                                              <<"Tra Vinh"
                                              <<"Tuyen Quang"
                                              <<"Vinh Long"
                                              <<"Vinh Phuc"
                                              <<"Yen Bai");
    ui->comboBox->addItems(listProvince);


    connect(ui->pushButtonAdd, &QPushButton::clicked, this, &MainWindow::onAddButtonClicked);
    connect(ui->pushButtonDelete, &QPushButton::clicked, this, &MainWindow::onDeleteButtonClicked);
    connect(ui->pushButtonUpdate, &QPushButton::clicked, this, &MainWindow::onUpdateButtonClicked);
    connect(ui->pushButtonCancel, &QPushButton::clicked, this, &MainWindow::onCancelButtonClicked);
    connect(ui->pushButtonSearch, &QPushButton::clicked, this, &MainWindow::onSearchButtonClicked);
    connect(ui->pushButtonCancelSearch, &QPushButton::clicked, this, &MainWindow::onCancelSearchButtonClicked);
    connect(ui->pushButtonNewStudentList, &QPushButton::clicked, this, &MainWindow::onNewStudentListClicked);
    connect(ui->pushButtonStatistic, &QPushButton::clicked, this, &MainWindow::onStatisticButtonClicked);

    ui->pushButtonCancel->hide();
    ui->label_Updating->hide();
    ui->label_Processing->hide();


    buttonGroup = new QButtonGroup(this);
    buttonGroup->addButton(ui->radioButtonMale);
    ui->radioButtonMale->setChecked(true);
    buttonGroup->addButton(ui->radioButtonFemale);
    buttonGroup->setExclusive(true);


}

void MainWindow::onAddButtonClicked()
{
    QString id = ui->lineEditID->text();
    QString name = ui->lineEditName->text();
    Score score(ui->doubleSpinBoxGPA->value());
    QAbstractButton *selectedButton = buttonGroup->checkedButton();
    QString gender = selectedButton->text();
    QDate date = ui->dateEdit->date();
    QString hometown = ui->comboBox->currentText();


    if (id.isEmpty() || name.isEmpty()) {
        QMessageBox::critical(this, "Error", "Please enter all required information.");
        return;
    }
    if (!CheckInput::isNumber(id)) {
        QMessageBox::critical(this, "Error", "Please enter a valid ID. ID must be a number.");
        return;
    }
    if(id.toInt() <= 0){
        QMessageBox::critical(this, "Error", "Please enter a valid ID.");
        return;
    }
    if(!CheckInput::isAlpha(name)){
        QMessageBox::critical(this, "Error", "Invalid name. Name must be alphabetic.");
        return;
    }

    Student student(id, name, score, gender, date, hometown);
    if(checkUniqueId(id)){
        students.append(student);
    }else{
        QMessageBox::critical(this, "Error", "ID must be unique");
        return;
    }


    ShowList(this->students);
    Clear();
}

void MainWindow::onDeleteButtonClicked()
{
    // Lấy số hàng đang được chọn
    int currentRow = ui->tableWidget->currentRow();

    // If no row is selected, show an error message and return
    if (currentRow == -1) {
        QMessageBox::critical(this, "Error", "Please select a row to delete.");
        return;
    }

    // Ask the user to confirm the deletion
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Delete student", "Are you sure you want to delete this student?",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::No) {
        return;
    }

    // Lấy các phần tử trong hàng
    QTableWidgetItem *idItem = ui->tableWidget->item(currentRow, 0);
    QString deleteId = idItem->text();

    // Duyệt qua danh sách sinh viên
    for (int i = 0; i < students.count(); i++) {
        // Nếu sinh viên có id bằng với deleteId
        if (students[i].getId().compare(deleteId) == 0) {
            // Xóa sinh viên khỏi danh sách
            students.removeAt(i);
            break; // thoát khỏi vòng lặp sau khi đã xóa
        }
    }
    ShowList(this->students);
}


void MainWindow::onUpdateButtonClicked()
{
    int currentRow = ui->tableWidget->currentRow();
    if (currentRow == -1) {
        QMessageBox::critical(this, "Error", "Please select a row to update.");
        return;
    }
    if(checkUpdate == false){
        getInformation(currentRow);
        setUpdateProcessingOn();

    }else if(checkUpdate == true){
        // Ask the user to confirm the update
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Update", "Are you sure you want to update this row?",
                                      QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::No) {
            return;
        }
        pushInformation(currentRow);
    }
    ShowList(this->students);
}

void MainWindow::onCancelButtonClicked(){
    setUpdateProcessingOff();
}

void MainWindow::onSearchButtonClicked(){

    QString nameSearch = ui->lineEditNameSearch->text();
    if(nameSearch.isEmpty()){
        return;
    }

    QString name = ui->lineEditNameSearch->text();
    foreach (Student std, this->students) {
        if(CheckInput::areStringsSimilar(name, std.getName())){
            studentsSearch.append(std);
        }
    }

    ShowList(studentsSearch);
    studentsSearch.clear();
    ui->pushButtonAdd->setEnabled(false);
    ui->pushButtonUpdate->setEnabled(false);
    ui->pushButtonDelete->setEnabled(false);
}
void MainWindow::onCancelSearchButtonClicked(){
    ShowList(students);
    ui->pushButtonAdd->setEnabled(true);
    ui->pushButtonUpdate->setEnabled(true);
    ui->pushButtonDelete->setEnabled(true);
}

void MainWindow::onStatisticButtonClicked(){

    int countMale = 0;;
    int countFemale = 0;

    int countA = 0;
    int countB = 0;
    int countC = 0;
    int countD = 0;
    int countF = 0;

    foreach (Student std, students) {
        if(std.getGender() == "Male"){
            countMale++;
        }else{
            countFemale++;
        }
    }

    foreach (Student std, students) {
        if(std.getScore().getGrade() == "A"){
            countA++;
        }else if(std.getScore().getGrade() == "B"){
            countB++;
        }else if(std.getScore().getGrade() == "C"){
            countC++;
        }else if(std.getScore().getGrade() == "D"){
            countD++;
        }else {
            countF++;
        }
    }
    int maxValue = qMax(qMax(qMax(qMax(countA, countB), countC), countD), countF);

    // Tạo đối tượng QDialog
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("Statistics");

    // Tạo QVBoxLayout để chứa các QChartView
    QVBoxLayout *layout = new QVBoxLayout(dialog);

    // Tạo QPieSeries cho biểu đồ pie
    QPieSeries *pieSeries = new QPieSeries();
    pieSeries->append("Male", countMale);
    pieSeries->append("Female", countFemale);

    // Tạo QChart cho biểu đồ pie và thiết lập QPieSeries vào nó
    QChart *pieChart = new QChart();
    pieChart->addSeries(pieSeries);
    pieChart->setTitle("GENDER");
    pieChart->setAnimationOptions(QChart::AllAnimations);

    // Thiết lập hiển thị phần trăm và nhãn trên các phần của biểu đồ
    QPieSlice *sliceMale = pieSeries->slices().at(0);
    sliceMale->setLabel(QString("Male: %1").arg(sliceMale->value()));

    QPieSlice *sliceFemale = pieSeries->slices().at(1);
    sliceFemale->setLabel(QString("Female: %1").arg(sliceFemale->value()));
    //QColor colorMale(0, 238, 238); //Xanh
    QColor colorFemale(255, 110, 180); // Hồng
    //sliceMale->setBrush(colorMale);
    sliceFemale->setBrush(colorFemale);

    // Tạo QChartView cho biểu đồ pie và thiết lập QChart vào nó
    QChartView *pieChartView = new QChartView(pieChart);
    pieChartView->setRenderHint(QPainter::Antialiasing);
    layout->addWidget(pieChartView);


    //QColor colorBarChart("#A9A9A9");//Dark Gray
    // Tạo QBarSet cho biểu đồ cột
    QBarSet *barSet = new QBarSet("Grade");
    *barSet << countA << countB << countC << countD << countF;
    //barSet->setColor(colorBarChart);

    // Tạo QBarSeries cho biểu đồ cột và thiết lập QBarSet vào nó
    QBarSeries *barSeries = new QBarSeries();
    barSeries->append(barSet);



    // Tạo QChart cho biểu đồ cột và thiết lập QBarSeries vào nó
    QChart *barChart = new QChart();
    barChart->addSeries(barSeries);
    barChart->setTitle("SCORE");
    barChart->setAnimationOptions(QChart::SeriesAnimations);



    // Tạo QCategoryAxis cho trục x của biểu đồ cột
    QStringList categories;
    categories << "A" << "B" << "C" << "D" << "F";
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    barChart->addAxis(axisX, Qt::AlignBottom);
    barSeries->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0, maxValue);
    axisY->setLabelFormat("%i");
    axisY->setTickCount(maxValue + 1);
    barChart->addAxis(axisY, Qt::AlignLeft);
    barSeries->attachAxis(axisY);

    barChart->legend()->setVisible(true);
    barChart->legend()->setAlignment(Qt::AlignBottom);



    // Tạo QChartView cho biểu đồ cột và thiết lập QChart vào nó
    QChartView *barChartView = new QChartView(barChart);
    barChartView->setRenderHint(QPainter::Antialiasing);
    layout->addWidget(barChartView);

    dialog->setFixedSize(500, 650);
    // Hiển thị dialog
    dialog->exec();
}

void MainWindow::Clear(){
    ui->lineEditID->setText("");
    ui->lineEditName->setText("");
    ui->doubleSpinBoxGPA->setValue(0);
    ui->radioButtonMale->setChecked(true);
    QDate date = QDate::fromString("01/01/2000", "dd/MM/yyyy");
    ui->dateEdit->setDate(date);
    ui->comboBox->setCurrentIndex(0);
}

void MainWindow::getInformation(int currentRow){
    // Lấy các phần tử trong hàng
    QTableWidgetItem *idItem = ui->tableWidget->item(currentRow, 0);
    QString id = idItem->text();
    ui->lineEditID->setText(id);

    QTableWidgetItem *nameItem = ui->tableWidget->item(currentRow, 1);
    QString name = nameItem->text();
    ui->lineEditName->setText(name);

    QTableWidgetItem *genderItem = ui->tableWidget->item(currentRow, 2);
    QString gender = genderItem->text();
    if(gender.compare("Male")){
        ui->radioButtonFemale->setChecked(true);
    }else if(gender.compare("Female")){
        ui->radioButtonMale->setChecked(true);
    }

    QTableWidgetItem *dateItem = ui->tableWidget->item(currentRow, 3);
    QString dateString = dateItem->text();
    QDate date = QDate::fromString(dateString, "dd/MM/yyyy");
    ui->dateEdit->setDate(date);

    QTableWidgetItem *homeTownItem = ui->tableWidget->item(currentRow, 4);
    QString homeTown = homeTownItem->text();
    ui->comboBox->setCurrentText(homeTown);

    QTableWidgetItem *GPAItem = ui->tableWidget->item(currentRow, 5);
    QString GPAstr = GPAItem->text();
    double GPA = GPAstr.toDouble();
    ui->doubleSpinBoxGPA->setValue(GPA);
}


void MainWindow::pushInformation(int currentRow){

    QString id = ui->lineEditID->text();
    QString name = ui->lineEditName->text();
    QString GPAstr = ui->doubleSpinBoxGPA->text();
    double GPA = GPAstr.toDouble();
    QAbstractButton *selectedButton = buttonGroup->checkedButton();
    QString gender = selectedButton->text();
    QDate date = ui->dateEdit->date();
    QString hometown = ui->comboBox->currentText();

    if (id.isEmpty()|| name.isEmpty()) {
        QMessageBox::critical(this, "Error", "Please enter all required information.");
        return;
    }else if (!CheckInput::isNumber(id)) {
        QMessageBox::critical(this, "Error", "Please enter a valid ID. ID must be a number.");       
        return;
    }else if(id.toInt() <= 0){
        QMessageBox::critical(this, "Error", "Please enter a valid ID.");
        return;
    }else if(!CheckInput::isAlpha(name)){
        QMessageBox::critical(this, "Error", "Invalid name. Name must be alphabetic.");
        return;
    }else{
        Student student(id, name, GPA, gender, date, hometown);
        students.removeAt(currentRow);
        students.insert(currentRow, student);
        setUpdateProcessingOff();
    }
}

bool MainWindow::checkUniqueId(QString id){
    for(Student std : students){
        if(std.getId().compare(id) == 0){
            return false;
            break;
        }
    }
    return true;
}

void MainWindow::setUpdateProcessingOff(){
    ui->label_Updating->hide();
    ui->pushButtonCancel->hide();
    ui->label_Processing->hide();
    ui->pushButtonAdd->setEnabled(true);
    ui->pushButtonDelete->setEnabled(true);
    ui->pushButtonSearch->setEnabled(true);
    ui->pushButtonCancelSearch->setEnabled(true);
    ui->pushButtonNewStudentList->setEnabled(true);
    ui->actionOpen->setEnabled(true);
//    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
//    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setEnabled(true);
    ui->tableWidget->setCurrentItem(nullptr);
    checkUpdate = false;
    Clear();
}


void MainWindow::setUpdateProcessingOn(){
    ui->label_Updating->show();
    ui->pushButtonCancel->show();
    ui->label_Processing->show();
    ui->pushButtonAdd->setEnabled(false);
    ui->pushButtonDelete->setEnabled(false);
    ui->pushButtonSearch->setEnabled(false);
    ui->pushButtonCancelSearch->setEnabled(false);
    ui->pushButtonNewStudentList->setEnabled(false);
    ui->actionOpen->setEnabled(false);
    ui->tableWidget->setEnabled(false);
    checkUpdate = true;

}


void MainWindow::ShowList(QList<Student> students){

    // Lấy con trỏ đến QTableWidget đã thêm vào UI
    QTableWidget *tableWidget = ui->tableWidget;

    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

    // Đặt số lượng cột và dòng cho QTableWidget
    tableWidget->setColumnCount(7);
    tableWidget->setRowCount(students.count());

    // Đặt tên cho các cột
    tableWidget->setHorizontalHeaderLabels({"ID", "Name","Gender", "Date", "HomeTown", "GPA", "Grade"});

    // Thêm thông tin của sinh viên vào QTableWidget
    for (int i = 0; i < students.count(); i++) {
        QTableWidgetItem *idItem = new QTableWidgetItem(students[i].getId());
        QTableWidgetItem *nameItem = new QTableWidgetItem(students[i].getName());
        QTableWidgetItem *GPAItem = new QTableWidgetItem(QString::number(students[i].getScore().getGPA()));
        QTableWidgetItem *genderItem = new QTableWidgetItem(students[i].getGender());
        QTableWidgetItem *dateItem = new QTableWidgetItem(students[i].getDate().toString("dd/MM/yyyy"));
        QTableWidgetItem *homeTownItem = new QTableWidgetItem(students[i].getHomeTown());
        QTableWidgetItem *gradeItem = new QTableWidgetItem(students[i].getScore().getGrade());

        tableWidget->setItem(i, 0, idItem);
        tableWidget->setItem(i, 1, nameItem);
        tableWidget->setItem(i, 2, genderItem);
        tableWidget->setItem(i, 3, dateItem);
        tableWidget->setItem(i, 4, homeTownItem);
        tableWidget->setItem(i, 5, GPAItem);
        tableWidget->setItem(i, 6, gradeItem);
    }

    // Đặt kích thước cho các cột
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    tableWidget->horizontalHeader()->setStretchLastSection(true);
    tableWidget->setColumnWidth(0, 140);
    tableWidget->setColumnWidth(1, 250);
    tableWidget->setColumnWidth(2, 100);
    tableWidget->setColumnWidth(3, 140);
    tableWidget->setColumnWidth(4, 180);
    tableWidget->setColumnWidth(5, 50);
    tableWidget->setColumnWidth(6, 50);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    QString filePath = QFileDialog::getOpenFileName(nullptr, "Open Excel File", "D://PROJECT C++//Student_Management_System", "Excel Files (*.xlsx)");

    if (filePath.isEmpty()) {
        // Hủy việc chọn tệp tin
        return;
    }
    students.clear();

    QXlsx::Document xlsx(filePath);

    int row = 2; // Bắt đầu đọc từ hàng thứ 2 (hàng thứ nhất là tiêu đề)
    while (!xlsx.read(row, 1).isNull()) {
        QString id = xlsx.read(row, 1).toString();
        QString name = xlsx.read(row, 2).toString();
        QString gender = xlsx.read(row, 3).toString();
        QDate date = QDate::fromString(xlsx.read(row, 4).toString(), "dd/MM/yyyy");
        QString homeTown = xlsx.read(row, 5).toString();
        double gpa = xlsx.read(row, 6).toDouble();
        // Tạo đối tượng Student từ dữ liệu đọc được
        Student student(id, name, gpa, gender, date, homeTown);
        // Thêm student vào QList<Student>
        students.append(student);

        row++; // Tăng số hàng lên để đọc hàng tiếp theo
    }

    filePathSystem = filePath;
    QFileInfo fileInfor(filePathSystem);
    fileInfor.fileName();
    ui->labelFilePath->setText(fileInfor.fileName());
    ShowList(students);

}


void MainWindow::on_actionSave_Save_As_triggered()
{
    if(filePathSystem.isEmpty()){
        QString filePath = QFileDialog::getSaveFileName(this, "Save Excel File", "D://PROJECT C++//Student_Management_System", "Excel Files (*.xlsx)");
        saveStudentsToExcel(students, filePath);
    }else{
        saveStudentsToExcel(students, filePathSystem);
    }

}

void MainWindow::saveStudentsToExcel(QList<Student> students, QString filePath)
{


    if (filePath.isEmpty()) {
        // Hủy việc lưu tệp tin
        return;
    }

    QXlsx::Document xlsx;
    xlsx.deleteSheet("Sheet1"); // Xóa toàn bộ sheet trong tệp Excel
    xlsx.addSheet("Sheet1"); // Thêm sheet mới có tên là "Sheet1"

    xlsx.write("A1", "ID");
    xlsx.write("B1", "Name");
    xlsx.write("C1", "Gender");
    xlsx.write("D1", "Date");
    xlsx.write("E1", "HomeTown");
    xlsx.write("F1", "GPA");
    xlsx.write("G1", "Grade");

    for (int row = 0; row < students.size(); ++row) {
        Student student = students[row];
        xlsx.write(row + 2, 1, student.getId());
        xlsx.write(row + 2, 2, student.getName());
        xlsx.write(row + 2, 3, student.getGender());
        xlsx.write(row + 2, 4, student.getDate().toString("dd/MM/yyyy"));
        xlsx.write(row + 2, 5, student.getHomeTown());
        xlsx.write(row + 2, 6, student.getScore().getGPA());
        xlsx.write(row + 2, 7, student.getScore().getGrade());
    }

    if (xlsx.saveAs(filePath)) {
        QMessageBox::information(this, "Success", "Excel file saved successfully.");
    } else {
        QMessageBox::critical(this, "Error", "Failed to save Excel file.");
    }
}


void MainWindow::on_actionLogout_triggered()
{

    this->close();
    LoginForm *lg = new LoginForm();
    lg->show();

}


void MainWindow::on_actionAbout_this_App_triggered()
{
    QString appName = QApplication::applicationName();
    QString appVersion = "1.0.0";

    QMessageBox::information(this, "Application Information", "App Name: " + appName +"\n"
                                                              "Version: " + appVersion);
}

void MainWindow::onNewStudentListClicked(){
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Create New Student List", "Are you sure you want create new Student List?",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::No) {
        return;
    }else{
        students.clear();
        filePathSystem = "";
        QFileInfo fileInfor(filePathSystem);
        fileInfor.fileName();
        ui->labelFilePath->setText(fileInfor.fileName());
        ShowList(students);
    }

}




