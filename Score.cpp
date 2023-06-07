#ifndef SCORE_CPP
#define SCORE_CPP
#include<QString>
#include<QRegularExpression>
class Score {
private:
    double GPA;
    QString grade;
public:
    Score(){

    }
    Score(double GPA){
        this->GPA = GPA;
        if(GPA<=4 && GPA >= 3.65){
            this->grade = "A";
        }else if(GPA<3.65 && GPA>=2.65){
            this->grade = "B";
        }else if(GPA<2.65 && GPA>=1.65){
            this->grade = "C";
        }else if(GPA<1.65 && GPA>=1){
            this->grade = "D";
        }else{
            this->grade = "F";
        }
    }

    double getGPA() { return GPA;}
    QString getGrade()  { return grade; }

    void setGPA(double GPA) {this->GPA = GPA;}
    void setGrade(QString grade) { this->grade = grade; }
};

#endif
