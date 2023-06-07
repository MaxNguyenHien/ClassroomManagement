#ifndef Student_CPP
#define Student_CPP
#include<QDate>
#include "Score.cpp"
class Student {
private:
    QString id;
    QString name;
    Score score;
    QString gender;
    QDate date;
    QString homeTown;

public:
    // constructor
    Student(QString id,  QString name, Score score,  QString gender,  QDate date,  QString homeTown) {
        this->id = id;
        this->name = formatString(name);
        this->score = score;
        this->gender = gender;
        this->date = date;
        this->homeTown = homeTown;
    }

    // getters
    QString getId()  { return id; }
    QString getName()  { return name;}
    Score getScore() { return score;}
    QString getGender()  { return gender; }
    QDate getDate()  { return date; }
    QString getHomeTown()  { return homeTown; }




    // setters
    void setId(QString id) { this->id = id; }
    void setScore(Score score) {this->score = score;}
    void setName(QString name) { this->name = formatString(name); }
    void setGender(QString gender) { this->gender = gender; }
    void setDate(QDate date) { this->date = date; }
    void setHomeTown(QString homeTown) { this->homeTown = homeTown; }

    QString formatString(QString input) {

        std::string s = input.toStdString();

        for(unsigned long long int i = 0; i < s.length(); i++){
            if(i == 0){
                s[i] = toupper(s[i]);
            }
            else if(s[i-1] == ' '){
                s[i] = toupper(s[i]);
            }else {
                s[i] = tolower(s[i]);
            }
        }

        for(unsigned long long int i = 0; i < s.length(); i++){
            if(s[i] == ' ' && s[i-1] == ' '){
                s.erase(i, 1);
                i--;
            }
        }

        return QString::fromStdString(s);
    }
};

#endif
