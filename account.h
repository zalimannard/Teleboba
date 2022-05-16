#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <set>

#include "content.h"

class Account
{
public:
    Account(const std::string &id);
    
    std::string getId() const;
    std::set<Content> getViewed() const;
    void setViewed(const std::set<Content> &value);
    std::set<Content> getLiked() const;
    void setLiked(const std::set<Content> &value);
    std::set<Content> getDisliked() const;
    void setDisliked(const std::set<Content> &value);
    std::set<Content> getCustom() const;
    void setCustom(const std::set<Content> &value);
    std::set<Content> getFollow() const;
    void setFollow(const std::set<Content> &value);

    friend std::ostream& operator<< (std::ostream &out, const Account &user);
    friend std::istream& operator>> (std::istream &in, Account &user);

private:
    std::string id_;
    std::set<Content> viewed_;
    std::set<Content> liked_;
    std::set<Content> disliked_;
    std::set<Content> custom_;
    std::set<Content> follow_;
};

#endif
