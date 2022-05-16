#include <iostream>
#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <tgbot/tgbot.h>
#include <tgbot/types/InlineKeyboardMarkup.h>
#include <tgbot/types/KeyboardButton.h>

#include "account.h"

using namespace std;
using namespace TgBot;

void createKeyboard(const vector<vector<string>>& buttonLayout, ReplyKeyboardMarkup::Ptr& kb)
{
    for (size_t i = 0; i < buttonLayout.size(); ++i) 
    {
        vector<KeyboardButton::Ptr> row;
        for (size_t j = 0; j < buttonLayout[i].size(); ++j) 
        {
            KeyboardButton::Ptr button(new KeyboardButton);
            button->text = buttonLayout[i][j];
            row.push_back(button);
        }
        kb->keyboard.push_back(row);
    }
}

set<Content> readContentBase()
{
    std::ifstream in("../contentbase");
    std::string str;
    getline(in, str);
    set<Content> films;
    int nFilm = stoi(str);
    for (int i = 0; i < nFilm; ++i)
    {
        Content film;
        in >> film;
        films.insert(film);
        films.insert(film);
    }
    return films;
}

Account readAccount(int64_t id)
{
    std::string strId = std::to_string(id);
    std::ifstream in("../accounts/" + strId);
    Account account(strId);
    in >> account;
    return account;
}

std::vector<std::string> split(std::string s, char delim)
{
    std::vector<std::string> elems;
    std::stringstream ss(s);
    std::string item;
    while(std::getline(ss, item, delim)) 
    {
        elems.push_back(item);
    }
    return elems;
}

int main(int argc, char* argv[])
{
    map<string, string> texts;
    texts["textUpcomingSubscriptions"] = "⏰ Ближайшие подписки";
    texts["textWhatToSee"] = "👀 Что посмотреть?";
    texts["textOther"] = "/Прочее";
    texts["textAddYourElement"] = "Добавить новый элемент";
    texts["textBack"] = "/Назад";
    texts["textLiked"] = "❤️ Понравившиеся";
    texts["textDisliked"] = "💩 Непонравившиеся";
    texts["textAdded"] = "Добавленные";

    Bot bot("5205547272:AAG13BXkVQHURrh9PvQfltDOuTgZe1jh9A0");
    set<Content> films = readContentBase();
    srand(time(NULL));

    ReplyKeyboardMarkup::Ptr keyboardOneCol(new ReplyKeyboardMarkup);
    createKeyboard({
            {texts["textUpcomingSubscriptions"]}, 
            {texts["textWhatToSee"]}, 
            {texts["textOther"]},
    }, keyboardOneCol);
    
    ReplyKeyboardMarkup::Ptr keyboardWithLayout(new ReplyKeyboardMarkup);
    createKeyboard({
        // {texts["textAddYourElement"], texts["textAdded"]},
        {texts["textLiked"], texts["textDisliked"]},
        {texts["textBack"]},
    }, keyboardWithLayout);

        


    bot.getEvents().onCommand("start", [&bot, &keyboardOneCol](Message::Ptr message) 
    {
        std::string id = std::to_string(message->chat->id);
        if (access(("peoples/" + id).c_str(), F_OK) == -1)
        {
            Account user(id);
            ofstream fout;
            fout.open("../accounts/" + user.getId());
            fout << user;
            fout.close();
        }
        bot.getApi().sendMessage(message->chat->id, "Добро пожаловать", false, 0, keyboardOneCol);
    });

    bot.getEvents().onCommand("Прочее", [&bot, &keyboardWithLayout](Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id, "Дополнительные опции", false, 0, keyboardWithLayout);
    });

    bot.getEvents().onCommand("Назад", [&bot, &keyboardOneCol](Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id, "Основной экран", false, 0, keyboardOneCol);
    });

    bot.getEvents().onCallbackQuery([&bot](CallbackQuery::Ptr query) {
        if (StringTools::startsWith(query->data, "Не нравится")) {
            string str = split(query->message->caption, ';')[0];
            bot.getApi().sendMessage(query->message->chat->id, "Добавлено в 'Не нравится'", false, 0);
            Account user = readAccount(query->message->chat->id);
            set<Content> liked = user.getLiked();
            Content toDelete;
            set<Content> films = readContentBase();
            for (Content film : films)
            {
                if (film.getName() == str)
                {
                    toDelete = film;
                }
            }
            liked.erase(toDelete);
            user.setLiked(liked);
            set<Content> disliked = readAccount(query->message->chat->id).getDisliked();
            disliked.insert(toDelete);
            user.setDisliked(disliked);

            ofstream fout;
            fout.open("../accounts/" + user.getId());
            fout << user;
            fout.close();
        }
    });

    bot.getEvents().onCallbackQuery([&bot](CallbackQuery::Ptr query) {
        if (StringTools::startsWith(query->data, "Нравится")) {
            string str = split(query->message->caption, ';')[0];
            bot.getApi().sendMessage(query->message->chat->id, "Добавлено в 'Нравится'", false, 0);
            Account user = readAccount(query->message->chat->id);
            set<Content> disliked = user.getDisliked();
            Content toDelete;
            set<Content> films = readContentBase();
            for (Content film : films)
            {
                if (film.getName() == str)
                {
                    toDelete = film;
                }
            }
            disliked.erase(toDelete);
            user.setDisliked(disliked);
            set<Content> liked = readAccount(query->message->chat->id).getLiked();
            liked.insert(toDelete);
            user.setLiked(liked);

            ofstream fout;
            fout.open("../accounts/" + user.getId());
            fout << user;
            fout.close();
        }
    });

    bot.getEvents().onCallbackQuery([&bot](CallbackQuery::Ptr query) {
        if (StringTools::startsWith(query->data, "Подписаться")) {
            string str = split(query->message->caption, ';')[0];
            bot.getApi().sendMessage(query->message->chat->id, "Вы подписаны", false, 0);
            Account user = readAccount(query->message->chat->id);
            Content toDelete;
            set<Content> films = readContentBase();
            for (Content film : films)
            {
                if (film.getName() == str)
                {
                    toDelete = film;
                }
            }
            set<Content> follow = readAccount(query->message->chat->id).getFollow();
            follow.insert(toDelete);
            user.setFollow(follow);

            ofstream fout;
            fout.open("../accounts/" + user.getId());
            fout << user;
            fout.close();
        }
    });

    bot.getEvents().onAnyMessage([&bot, &texts](Message::Ptr message) 
    {
        std::cout << "Пользователь ввёл: " << message->text << std::endl;
        std::string photoMimeType = "image/jpeg";
        set<Content> films = readContentBase();

        if (StringTools::startsWith(message->text, "/")) {
            return;
        }
        // else if (message->text == texts["textAddYourElement"])
        // {
        //     // insertCustomFilm = true;
        //     bot.getApi().sendMessage(message->chat->id, "Введите информацию в формате\nДД.ММ.ГГГГ *Название*");
        // }
        else if (message->text == texts["textLiked"])
        {
            InlineKeyboardMarkup::Ptr keyboard(new InlineKeyboardMarkup);
            vector<InlineKeyboardButton::Ptr> row0;
            InlineKeyboardButton::Ptr checkButton(new InlineKeyboardButton);
            checkButton->text = "Больше не нравится";
            checkButton->callbackData = "Не нравится";
            row0.push_back(checkButton);
            keyboard->inlineKeyboard.push_back(row0);

            Account user = readAccount(message->chat->id);
            if (user.getLiked().empty())
            {
                bot.getApi().sendMessage(message->chat->id, "Пока что нет понравившихся фильмов");
            }
            for (Content film : user.getLiked())
            {
                std::string text = film.getName() + ";\n" + 
                    film.getDescription() + "\n" + film.getDate().toString();
                if (film.getNumberEpisodes() > 1)
                {
                    text += "\nКоличество серий: " + to_string(film.getNumberEpisodes());
                }
                if (film.getInterval() > 1)
                {
                    text += "\nИнтервал выхода: " + to_string(film.getInterval()) + " дней";
                }
                bot.getApi().sendPhoto(message->chat->id,
                        InputFile::fromFile("../" + film.getImagePath(), photoMimeType),
                        text, 0, keyboard);
            }
        }
        else if (message->text == texts["textDisliked"])
        {
            InlineKeyboardMarkup::Ptr keyboard(new InlineKeyboardMarkup);
            vector<InlineKeyboardButton::Ptr> row0;
            InlineKeyboardButton::Ptr checkButton(new InlineKeyboardButton);
            checkButton->text = "Всё-таки нравится";
            checkButton->callbackData = "Нравится";
            row0.push_back(checkButton);
            keyboard->inlineKeyboard.push_back(row0);

            Account user = readAccount(message->chat->id);
            if (user.getDisliked().empty())
            {
                bot.getApi().sendMessage(message->chat->id, "Непонравившихся фильмов не найдено");
            }
            for (Content film : user.getDisliked())
            {
                std::string text = film.getName() + ";\n" + 
                    film.getDescription() + "\n" + film.getDate().toString();
                if (film.getNumberEpisodes() > 1)
                {
                    text += "\nКоличество серий: " + to_string(film.getNumberEpisodes());
                }
                if (film.getInterval() > 1)
                {
                    text += "\nИнтервал выхода: " + to_string(film.getInterval()) + " дней";
                }
                bot.getApi().sendPhoto(message->chat->id,
                        InputFile::fromFile("../" + film.getImagePath(), photoMimeType),
                        text, 0, keyboard);
            }
        }
        // else if (message->text == texts["textAdded"])
        // {
        //     Account user = readAccount(message->chat->id);
        //     if (user.getCustom().empty())
        //     {
        //         bot.getApi().sendMessage(message->chat->id, "Вы пока не добавили не один сторонний фильм");
        //     }
        //     for (Content film : user.getCustom())
        //     {
        //         std::string text = film.getName() + ";\n" + film.getDate().toString();
        //
        //         bot.getApi().sendMessage(message->chat->id, text);
        //     }
        // }
        else if (message->text == "⏰ Ближайшие подписки")
        {
            Account user = readAccount(message->chat->id);
            set<Content> answerList;
            set<Content> followList = user.getFollow();
            for (Content film : user.getCustom())
            {
                answerList.insert(film);
            }
            Content todayFilm("SYSTEM", "", Date::fromString("17.05.2022"));
            for (Content film : followList)
            {
                if (todayFilm < film)
                {
                    answerList.insert(film);
                }
            }
            if (answerList.empty())
            {
                bot.getApi().sendMessage(message->chat->id, "Нет подписок, которые скоро выходят");
            }
            else
            {
                std::vector<Content> copiedAnswer(answerList.size());
                std::copy(answerList.begin(), answerList.end(), copiedAnswer.begin());
                std::sort(copiedAnswer.begin(), copiedAnswer.end());
               
                for (int i = 0; i < min(3, (int)copiedAnswer.size()); ++i)
                {
                    if (copiedAnswer[i].getImagePath() != "")
                    {
                        std::string text = copiedAnswer[i].getName() + "\n" +
                            copiedAnswer[i].getDescription() + "\n" + copiedAnswer[i].getDate().toString();
                        if (copiedAnswer[i].getNumberEpisodes() > 1)
                        {
                            text += "\nКоличество серий: " + to_string(copiedAnswer[i].getNumberEpisodes());
                        }
                        if (copiedAnswer[i].getInterval() > 1)
                        {
                            text += "\nИнтервал выхода: " + to_string(copiedAnswer[i].getInterval()) + " дней";
                        }
                        bot.getApi().sendPhoto(message->chat->id,
                                InputFile::fromFile("../" + copiedAnswer[i].getImagePath(), photoMimeType),
                                text);
                    }
                    else
                    {
                        std::string text = copiedAnswer[i].getName() + "\n" + copiedAnswer[i].getDate().toString();
                        bot.getApi().sendMessage(message->chat->id, text);
                    }
                }
            }
        }
        else if (message->text == texts["textWhatToSee"])
        {
            InlineKeyboardMarkup::Ptr keyboard(new InlineKeyboardMarkup);
            vector<InlineKeyboardButton::Ptr> row0;
            InlineKeyboardButton::Ptr checkButton(new InlineKeyboardButton);
            InlineKeyboardButton::Ptr checkButton2(new InlineKeyboardButton);
            InlineKeyboardButton::Ptr checkButton3(new InlineKeyboardButton);
            checkButton->text = "👍🏻";
            checkButton->callbackData = "Нравится";
            checkButton2->text = "👎🏻";
            checkButton2->callbackData = "Не нравится";
            checkButton3->text = "Подписаться";
            checkButton3->callbackData = "Подписаться";
            row0.push_back(checkButton);
            row0.push_back(checkButton2);
            row0.push_back(checkButton3);
            keyboard->inlineKeyboard.push_back(row0);


            Account user = readAccount(message->chat->id);
            set<Content> answerList = films;
            for (Content film : user.getFollow())
            {
                answerList.erase(film);
            }
            for (Content film : user.getViewed())
            {
                answerList.erase(film);
            }
            for (Content film : user.getDisliked())
            {
                answerList.erase(film);
            }
            for (Content film : user.getLiked())
            {
                answerList.erase(film);
            }

            if (answerList.empty())
            {
                bot.getApi().sendMessage(message->chat->id, "Просмотрена вся база фильмов. Заходите позже, здесь появится много нового" + message->text);
            }
            else
            {
                std::vector<Content> copiedAnswer(answerList.size());
                std::copy(answerList.begin(), answerList.end(), copiedAnswer.begin());
                std::sort(copiedAnswer.begin(), copiedAnswer.end());
                Content filmToShow = copiedAnswer[rand() % copiedAnswer.size()];

                std::string text = filmToShow.getName() + ";\n" + 
                    filmToShow.getDescription() + "\n" + filmToShow.getDate().toString();
                if (filmToShow.getNumberEpisodes() > 1)
                {
                    text += "\nКоличество серий: " + to_string(filmToShow.getNumberEpisodes());
                }
                if (filmToShow.getInterval() > 1)
                {
                    text += "\nИнтервал выхода: " + to_string(filmToShow.getInterval()) + " дней";
                }
                bot.getApi().sendPhoto(message->chat->id,
                        InputFile::fromFile("../" + filmToShow.getImagePath(), photoMimeType),
                        text, 0, keyboard);
            }
        }
    });



    try 
    {
        bot.getApi().deleteWebhook();
        TgLongPoll longPoll(bot);
        while (true)
        {
            longPoll.start();
        }
    } 
    catch (exception& e) 
    {
    }

    return 0;
}

