#include "date.h"

Date::Date(int day, int month, int year)
{
    setDay(day);
    setMonth(month);
    setYear(year);
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

void Date::setDay(int value)
{
    day_ = value;
}

void Date::setMonth(int value)
{
    month_ = value;
}

void Date::setYear(int value)
{
    year_ = value;
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

