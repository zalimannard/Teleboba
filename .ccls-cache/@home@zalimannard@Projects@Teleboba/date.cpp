#include "date.h"

Date::Date(const int &day, const int &month, const int &year)
{
    set(day, month, year);
}

int Date::getDay() const
{
    return day_;
}

int Date::getMonth() const
{
    return month_;
}

int Date::getYear() const
{
    return year_;
}

std::string Date::toString() const
{
    std::string answer = "";
    if (getDay() < 10)
    {
        answer += "0";
    }
    answer += std::to_string(getDay()) + ".";
    if (getMonth() < 10)
    {
        answer += "0";
    }
    answer += std::to_string(getMonth()) + ".";
    answer += std::to_string(getYear());
    return answer;
}

void Date::set(const int &day, const int &month, const int &year)
{   
    year_ = 2000;
    if ((year < 9999) && (year > 999))
    {
        year_ = year;
    }
    month_ = 1;
    if ((month < 13) && (month > 0))
    {
        month_ = month;
    }
    day_ = 1;
    if (day > 0)
    {
        switch (month)
        {
            case 1:
                if (day < 31)
                {
                    day_ = day;
                }
                break;
            case 2:
                if (year % 400 == 0)
                {
                    if (day < 30)
                    {
                        day_ = day;
                    }
                }
                else if (year % 100 == 0)
                {
                    if (day < 29)
                    {
                        day_ = day;
                    }
                }
                else if (year % 4 == 0)
                {
                    if (day < 30)
                    {
                        day_ = day;
                    }
                }
                else 
                {
                    if (day < 29)
                    {
                        day_ = day;
                    }
                }
                break;
            case 3:
                if (day < 31)
                {
                    day_ = day;
                }
                break;
            case 4:
                if (day < 30)
                {
                    day_ = day;
                }
                break;
            case 5:
                if (day < 31)
                {
                    day_ = day;
                }
                break;
            case 6:
                if (day < 30)
                {
                    day_ = day;
                }
                break;
            case 7:
                if (day < 31)
                {
                    day_ = day;
                }
                break;
            case 8:
                if (day < 31)
                {
                    day_ = day;
                }
                break;
            case 9:
                if (day < 30)
                {
                    day_ = day;
                }
                break;
            case 10:
                if (day < 31)
                {
                    day_ = day;
                }
                break;
            case 11:
                if (day < 30)
                {
                    day_ = day;
                }
                break;
            case 12:
                if (day < 31)
                {
                    day_ = day;
                }
                break;
        }
    }
    
}

bool operator== (const Date &date1, const Date &date2)
{
    return ((date1.getYear() == date2.getYear()) &&
            (date1.getMonth() == date2.getMonth()) &&
            (date1.getDay() == date2.getDay()));
}

bool operator!= (const Date &date1, const Date &date2)
{
    return !(date1 == date2);
}

bool operator< (const Date &date1, const Date &date2)
{
    if (date1.getYear() < date2.getYear())
    {
        return true;
    }
    if (date1.getMonth() < date2.getMonth())
    {
        return true;
    }
    if (date1.getDay() < date2.getDay())
    {
        return true;
    }
    return false;
}

bool operator> (const Date &date1, const Date &date2)
{
    if (date1.getYear() > date2.getYear())
    {
        return true;
    }
    if (date1.getMonth() > date2.getMonth())
    {
        return true;
    }
    if (date1.getDay() > date2.getDay())
    {
        return true;
    }
    return false;
}

bool operator>= (const Date &date1, const Date &date2)
{
    return ((date1 > date2) || (date1 == date2));
}

bool operator<= (const Date &date1, const Date &date2)
{
    return ((date1 < date2) || (date1 == date2));
}

