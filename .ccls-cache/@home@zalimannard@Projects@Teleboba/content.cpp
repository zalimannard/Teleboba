#include "content.h"

#include <iostream>
#include <string>

Content::Content()
{

}

Content::Content(const std::string &name, const std::string &description,
        const Date &date, const std::string &imagePath, const int &interval,
        const int &numberEpisodes)
{
    setName(name);
    setDescription(description);
    setDate(date);
    setImagePath(imagePath);
    setInterval(interval);
    setNumberEpisodes(numberEpisodes);
}

std::string Content::getName() const
{
    return name_;
}

std::string Content::getDescription() const
{
    return description_;
}

Date Content::getDate() const
{
    return date_;
}

std::string Content::getImagePath() const
{
    return imagePath_;
}

int Content::getInterval() const
{
    return interval_;
}

int Content::getNumberEpisodes() const
{
    return numberEpisodes_;
}

std::ostream& operator<< (std::ostream &out, const Content &content)
{
    out << content.getName() << std::endl;
    out << content.getDescription() << std::endl;
    out << content.getDate().toString() << std::endl;
    out << content.getImagePath() << std::endl;
    out << content.getInterval() << std::endl;
    out << content.getNumberEpisodes() << std::endl;

    return out; 
}

std::istream& operator>> (std::istream &in, Content &content)
{
    std::string name;
    std::string description;
    std::string date;
    std::string imagePath;
    std::string interval;
    std::string numberEpisodes;
    getline(in, name);
    getline(in, description);
    getline(in, date);
    getline(in, imagePath);
    getline(in, interval);
    getline(in, numberEpisodes);
    content.setName(name);
    content.setDescription(description);
    content.setDate(Date::fromString(date));
    content.setImagePath(imagePath);
    content.setInterval(std::stoi(interval));
    content.setNumberEpisodes(std::stoi(numberEpisodes));
    return in;
}

bool operator< (const Content &c1, const Content &c2)
{
    return c1.getDate() < c2.getDate();
}

void Content::setName(const std::string &value)
{
    name_ = value;
}

void Content::setDescription(const std::string &value)
{
    description_ = value;
}

void Content::setDate(const Date &value)
{
    date_ = value;
}

void Content::setImagePath(const std::string &value)
{
    imagePath_ = value;
}

void Content::setInterval(const int &value)
{
    interval_ = value;
}

void Content::setNumberEpisodes(const int &value)
{
    numberEpisodes_ = value;
}

