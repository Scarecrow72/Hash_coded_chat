#include "chat.h"
#include <iostream>

//Конструктор
Chat::Chat()
{
    mem_size = 10;
    data_count = 0;
    data = new AuthData [mem_size];
}

//Деструктор
Chat::~Chat() 
{
    delete[] data;
}

//Хеш-функция для преобразования пароля
int Chat::hash_pass(std::string password)
{
    int val {0};
    double k {0.7};
    for(int i = 0; i < password.length(); ++i)
        val += password[i];
    return static_cast<int>(mem_size * (val * k - static_cast<int>(val * k)));
}

//Хеш-функция для хеш-таблицы
int Chat::hash_func(std::string login, int offset)
{
    int val {0};
    for(int i = 0; i < login.length(); ++i)
    {
        val += login[i];
    }
    return (val % mem_size + offset * offset) % mem_size;
}

//Конструктор по умолчанию для ячейки таблицы
Chat::AuthData::AuthData(): m_login(""), m_pass_hash(0), m_status(Status::free)
{}
            
//Параметризированный конструктор для ячейки таблицы
Chat::AuthData::AuthData(std::string login, int pass_hash) 
{
    m_login = login;
    m_pass_hash = pass_hash;
    m_status = engaged;
}

//Конструктор присваивания
Chat::AuthData& Chat::AuthData::operator= (const AuthData& other)
{
    m_login = other.m_login;
    m_pass_hash = other.m_pass_hash;
    m_status = other.m_status;
    return *this;
}            

//Функция регистрации нового пользователя
void Chat::reg(std::string login, std::string pass) 
{
    /*if(count == mem_size)
        resize();*/
    int index {-1};
    int i {0};
    for(int i = 0; i < mem_size; ++i)
        if(data[i].m_login == login)
        {
            std::cout << "Aborted" << std::endl;
            return;
        }
    for(; i < mem_size; ++i)
    {
        index = hash_func(login, i);
        if(data[index].m_status != engaged)
            break;
    }
    if(i >= mem_size)
        return;
    data[index] = AuthData(login, hash_pass(pass));
    ++data_count;
    std::cout << "Your registration is sucsessful" << std::endl;
}

//функция авторизации пользователя
bool Chat::login(std::string login, std::string pass)
{
    int index {-1};
    int i {0};
    for(; i < mem_size; ++i)
    {
        index = hash_func(login, i);
        if(data[index].m_login == login && data[index].m_status == engaged)
        {
            if(data[index].m_pass_hash == hash_pass(pass))
                return true;
        }
    }
    return false;
}

//Функция удаления пользователя
void Chat::delete_user(std::string login)
{
    int index {-1};
    for(int i = 0; i < mem_size; ++i)
    {
        index = hash_func(login, i);
        if(data[index].m_login == login)
            data[index].m_status = deleted;
    }
}

//Функция изменения размера хеш-таблицы
void Chat::resize()
{
    AuthData *old_data = data;
    int old_size = mem_size;
    mem_size *= 2;
    data_count = 0;
    data = new AuthData [mem_size];
    int index {-1};
    for(int i = 0; i < old_size; ++i)
    {
        if(old_data[i].m_status == engaged)
        {
            for(int j = 0; j < mem_size; ++i)
            {
                index = hash_func(old_data[i].m_login, j);
                if(data[index].m_status != engaged)
                {
                    data[index] = old_data[i];
                    ++data_count;
                }
            }
        }
    }
}