#include "account.h"

Account::Account(const std::string &id)
{
    id_ = id;
}

std::ostream& operator<< (std::ostream &out, const Account &user)
{
    out << user.getViewed().size() << std::endl;
    for (Content film : user.getViewed())
    {
        out << film;
    }
    out << user.getLiked().size() << std::endl;
    for (Content film : user.getLiked())
    {
        out << film;
    }
    out << user.getDisliked().size() << std::endl;
    for (Content film : user.getDisliked())
    {
        out << film;
    }
    out << user.getCustom().size() << std::endl;
    for (Content film : user.getCustom())
    {
        out << film;
    }
    out << user.getFollow().size() << std::endl;
    for (Content film : user.getFollow())
    {
        out << film;
    }
    return out; 
}

std::istream& operator>> (std::istream &in, Account &user)
{
    std::set<Content> viewed;
    std::set<Content> liked;
    std::set<Content> disliked;
    std::set<Content> custom;
    std::set<Content> follow;
    
    std::string str;
    int nFilm;

    getline(in, str);
    nFilm = stoi(str);
    for (int i = 0; i < nFilm; ++i)
    {
        Content f;
        in >> f;
        viewed.insert(f);
    }
    getline(in, str);
    nFilm = stoi(str);
    for (int i = 0; i < nFilm; ++i)
    {
        Content f;
        in >> f;
        liked.insert(f);
    }
    getline(in, str);
    nFilm = stoi(str);
    for (int i = 0; i < nFilm; ++i)
    {
        Content f;
        in >> f;
        disliked.insert(f);
    }
    getline(in, str);
    nFilm = stoi(str);
    for (int i = 0; i < nFilm; ++i)
    {
        Content f;
        in >> f;
        custom.insert(f);
    }
    getline(in, str);
    nFilm = stoi(str);
    for (int i = 0; i < nFilm; ++i)
    {
        Content f;
        in >> f;
        follow.insert(f);
    }

    user.setViewed(viewed);
    user.setLiked(liked);
    user.setDisliked(disliked);
    user.setCustom(custom);
    user.setFollow(follow);

    return in;
}

std::string Account::getId() const
{
    return id_;
}

std::set<Content> Account::getViewed() const
{
    return viewed_;
}

void Account::setViewed(const std::set<Content> &value)
{
    viewed_ = value;
}

std::set<Content> Account::getLiked() const
{
    return liked_;
}

void Account::setLiked(const std::set<Content> &value)
{
    liked_ = value;
}

std::set<Content> Account::getDisliked() const
{
    return disliked_;
}

void Account::setDisliked(const std::set<Content> &value)
{
    disliked_ = value;
}

std::set<Content> Account::getCustom() const
{
    return custom_;
}

void Account::setCustom(const std::set<Content> &value)
{
    custom_ = value;
}

std::set<Content> Account::getFollow() const
{
    return follow_;
}

void Account::setFollow(const std::set<Content> &value)
{
    follow_ = value;
}

