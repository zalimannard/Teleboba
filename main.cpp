#include <iostream>

#include "content.h"
#include "date.h"

int main(int argc, char* argv[])
{
    Date date(13, 3, 333);
    Content anime("Наруто", "Описание", date, "", 4,  3);
    std::cout << anime.getName() << std::endl;
}
