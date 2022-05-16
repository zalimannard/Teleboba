#include <iostream>

#include "account.h"
#include "content.h"
#include "date.h"

int main(int argc, char* argv[])
{
    Date date = Date::fromString("02.24.4002");
    Content anime("Наруто", "Описание", date, "", 4,  3);
    std::set<Content> eee;
    eee.insert(anime);
    Account account("aeou");
    account.setDisliked(eee);
    std::cout << anime.getName() << std::endl;
    std::cout << date.toString() << std::endl;
    std::cout << account << std::endl;
}
