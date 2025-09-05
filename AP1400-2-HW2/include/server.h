#ifndef SERVER_H
#define SERVER_H

#include<string>
#include<iostream>
#include<map>

#include<memory>
#include<vector>

class Client;

extern std::vector<std::string> pending_trxs;

class Server{
    public:
        Server();
        void show_wallets(const Server& server);
        std::shared_ptr<Client> add_client(std::string id);
        std::shared_ptr<Client> get_client(std::string id) const;
        double get_wallet(std::string id);
        bool parse_trx(std::string trx, std::string& sender, std::string& receiver, double& value);
        bool add_pending_trx(std::string trx, std::string signature);
        size_t mine();
    private:
        std::map<std::shared_ptr<Client>, double> clients;
};

#endif //SERVER_H