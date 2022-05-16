#include "content.h"

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

