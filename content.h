#ifndef FILM_H
#define FILM_H

#include <iostream>

#include "date.h"

class Content
{
public:
    Content(const std::string &name, const std::string &description,
            const Date &date, const std::string &imagePath, const int &interval,
            const int &numberEpisodes);

    std::string getName() const;
    std::string getDescription() const;
    Date getDate() const;
    std::string getImagePath() const;
    int getInterval() const;
    int getNumberEpisodes() const;

private:
    std::string name_;
    std::string description_;
    Date date_;
    std::string imagePath_;
    int interval_;
    int numberEpisodes_;

    void setName(const std::string &value);
    void setDescription(const std::string &value);
    void setDate(const Date &value);
    void setImagePath(const std::string &value);
    void setInterval(const int &value);
    void setNumberEpisodes(const int &value);
};

#endif
