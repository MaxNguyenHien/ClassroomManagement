#ifndef CHECK_INPUT
#define CHECK_INPUT
#include<QString>
#include<QRegularExpression>
class CheckInput{
public:
    static bool isAlpha(QString input){

        QRegularExpression regex("^[a-zA-Z\\s]+$");

        QRegularExpressionMatch match = regex.match(input);
        if (match.hasMatch()) {
            return true;
        } else {
            return false;
        }

    }
    static bool isValidString(const QString& str)
    {
        QRegularExpression regex("^[a-zA-Z0-9]+$");  // Biểu thức chính quy để kiểm tra chữ và số
        QRegularExpressionMatch match = regex.match(str);

        return match.hasMatch();
    }
    static bool areStringsSimilar(QString str1, QString str2) {
        // So sánh hai chuỗi theo quy tắc không phân biệt chữ hoa chữ thường
        if (str1.compare(str2, Qt::CaseInsensitive) == 0) {
            return true;
        }

        // Kiểm tra xem chuỗi str1 có chứa chuỗi str2 không
        if (str1.contains(str2, Qt::CaseInsensitive)) {
            return true;
        }

        // Kiểm tra xem chuỗi str2 có chứa chuỗi str1 không
        if (str2.contains(str1, Qt::CaseInsensitive)) {
            return true;
        }

        return false;
    }

    static bool isNumber(QString input){
        if(input.toInt() == 0){
            return false;
        }else{
            return true;
        }
    }


};

#endif
