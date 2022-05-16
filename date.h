#ifndef DATE_H
#define DATE_H

class Date
{
public:
    Date(int day = 0, int month = 0, int year = 0);

    int getDay() const;
    int getMonth() const;
    int getYear() const;
    
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

    void setDay(int value);
    void setMonth(int value);
    void setYear(int value);

};

#endif
