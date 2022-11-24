#include <iostream>
#include "chat.h"

int main()
{
    Chat chat;
    bool is_chat_work {true};
    while(is_chat_work)
    {
        std::cout << "Enter\n1 - for registration\n2 - for authorisation\n0 - for exit" << std::endl;
        int key;
        while(true)
        {
            std::cin >> key;
            if(std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(32787, '\n');
            }
            else
                break;
        }
        switch (key)
        {
            case 0:
                {
                    is_chat_work = false;
                    break;
                }
            case 1:
                {
                    std::cout << "Create your login: ";
                    std::string new_login;
                    while(new_login.empty())
                        std::getline(std::cin, new_login);
                    std::cout << "Create your password: ";
                    std::string new_password;
                    while(new_password.empty())
                        std::getline(std::cin, new_password);
                    chat.reg(new_login,new_password);
                    break;
                }
            case 2:
                {
                    std::cout << "Enter your login: ";
                    std::string new_login;
                    while(new_login.empty())
                        std::getline(std::cin, new_login);
                    std::cout << "Enter your password: ";
                    std::string new_password;
                    while(new_password.empty())
                        std::getline(std::cin, new_password);
                    std::cout << std::boolalpha;
                    std::cout << chat.login(new_login,new_password) << std::endl;
                    break;
                }
        }
    }
    
    return 0;
}