#ifndef DATE_H
#define DATE_H

#include <string>

class Date
{
public:
    Date(const int &day = 1, const int &month = 1, const int &year = 2000);

    int getDay() const;
    int getMonth() const;
    int getYear() const;

    std::string toString() const;
    static Date fromString(const std::string &str)
    {
        Date answer(1, 1, 2000);
        if (str.length() == 10)
        {
            if ((str[2] == '.') && (str[5] == '.') &&
                    (std::isdigit(str[0])) && (std::isdigit(str[1])) &&
                    (std::isdigit(str[3])) && (std::isdigit(str[4])) &&
                    (std::isdigit(str[6])) && (std::isdigit(str[7])) &&
                    (std::isdigit(str[8])) && (std::isdigit(str[9])))
            {
                answer.set(
                ((str[0] - '0') * 10 + (str[1] - '0')),
                ((str[3] - '0') * 10 + (str[4] - '0')),
                ((str[6] - '0') * 1000 + (str[7] - '0') * 100 +
                        (str[8] - '0') * 10 + (str[9] - '0'))
                );
            }
        }
        return answer;
    }
    
    friend bool operator== (const Date &date1, const Date &date2);
    friend bool operator!= (const Date &date1, const Date &date2);
    friend bool operator< (const Date &date1, const Date &date2);
    friend bool operator> (const Date &date1, const Date &date2);
    friend bool operator<= (const Date &date1, const Date &date2);
    friend bool operator>= (const Date &date1, const Date &date2);

private:
    int day_;
    int month_;
    int year_;

    void set(const int &day, const int &month, const int &year);

};

#endif
