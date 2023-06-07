#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Student.cpp"
#include <QStandardItemModel>
#include <QButtonGroup>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



private:
    Ui::MainWindow *ui;
    enum Province {
        AnGiang,
        BaRiaVungTau,
        BacLieu,
        // ...
        YenBai
    };
    void ShowList(QList<Student>);
    void Clear();
    void getInformation(int);
    void pushInformation(int);
    bool checkUniqueId(QString);
    QString filePathSystem;
    bool checkUpdate;
    QList<Student> students;
    QList<Student> studentsSearch;
    QButtonGroup *buttonGroup;


private slots:
    void onAddButtonClicked();
    void onDeleteButtonClicked();
    void onUpdateButtonClicked();
    void onCancelButtonClicked();
    void onSearchButtonClicked();
    void onCancelSearchButtonClicked();
    void onNewStudentListClicked();
    void setUpdateProcessingOn();
    void setUpdateProcessingOff();
    void onStatisticButtonClicked();


    void on_actionOpen_triggered();
    void on_actionSave_Save_As_triggered();
    void saveStudentsToExcel(QList<Student>, QString);
    void on_actionLogout_triggered();
    void on_actionAbout_this_App_triggered();

};
#endif // MAINWINDOW_H
