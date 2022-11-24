#pragma once

#include <string>
#include <string.h>
#include <cstdlib>

static const int LOGINLENGTH {10};

class Chat {
    public:
        Chat();
        void reg(std::string login, std::string pass);
        bool login(std::string login, std::string pass);
        ~Chat();
    private:
        enum Status
        {
            free,
            deleted,
            engaged
        };

        struct AuthData 
        {
            AuthData();
            ~AuthData(){}
            AuthData(std::string login, int pass_hash);
            AuthData& operator= (const AuthData& other);           
            std::string m_login;
            int m_pass_hash;
            Status m_status;
        };
        AuthData* data;
        int mem_size;
        int data_count;
        int hash_pass(std::string password);
        int hash_func(std::string login, int offset);
        void resize();
        void delete_user(std::string login);
};