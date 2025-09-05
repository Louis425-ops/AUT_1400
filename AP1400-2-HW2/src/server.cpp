#include "server.h"
#include "crypto.h"
#include "client.h"
#include <random>
#include <stdexcept>

std::vector<std::string> pending_trxs;

Server::Server(){

}

void  Server::show_wallets(const Server& server)
{
	std::cout << std::string(20, '*') << std::endl;
	for(const auto& client : clients)
		std::cout << client.first->get_id() <<  " : "  << client.second << std::endl;
	std::cout << std::string(20, '*') << std::endl;
}

std::shared_ptr<Client> Server::add_client(std::string id){
    std::string final_id = id;
    while(get_client(final_id) != nullptr){
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1000, 9999);

        final_id = id + std::to_string(dis(gen));
    }

    std::shared_ptr<Client> new_client = std::make_shared<Client>(final_id, *this);
    clients[new_client] = 5.0;
    return new_client;
}

std::shared_ptr<Client> Server::get_client(std::string id) const
{
    for (const auto& pair : clients){
        std::shared_ptr<Client> client_ptr = pair.first;
        if(client_ptr->get_id() == id){
            return client_ptr;
        }  
    }
    return nullptr;
}

double Server::get_wallet(std::string id){
    std::shared_ptr<Client> client_ptr = get_client(id);
    if(client_ptr != nullptr){
        return clients[client_ptr];
    }
    else{
        throw std::logic_error("this id doesn't exist");
    }
}

bool Server::parse_trx(std::string trx, std::string& sender, std::string& receiver, double& value){
    // use three function: find(), substr(), stod()
    size_t first_place = trx.find('-');
    size_t second_place = trx.find('-', first_place + 1);

    if(first_place == std::string::npos || second_place == std::string::npos){
        throw std::runtime_error("Invalid transaction format");
    }

    sender = trx.substr(0, first_place);
    receiver = trx.substr(first_place + 1, second_place - first_place - 1);

    value = std::stod(trx.substr(second_place + 1));

    return true;
}

bool Server::add_pending_trx(std::string trx, std::string signature){
    std::string sender, receiver;
    double value;
    if(parse_trx(trx, sender, receiver, value)){
        std::shared_ptr client_sender = get_client(sender);
        if(client_sender == nullptr){
            return false;
        }
        if(value > get_wallet(sender)){
            return false;
        }
        else{
            if(crypto::verifySignature(client_sender->get_publickey(), trx, signature)){
                pending_trxs.push_back(trx);
                return true;
            }
            else{
                return false;
            }
        }
    }
    else{
        return false;
    }
}

size_t Server::mine(){
    bool find = false;
    std::string mempool = "";
    for(const auto& trx : pending_trxs){
        mempool += trx;
    } // get the mempool
    int i = 1;
    while(!find){
        std::string sender, receiver;
        double value;

        i = i % pending_trxs.size();
        
        parse_trx(pending_trxs[i-1], sender, receiver, value);
        std::shared_ptr<Client> sender_ptr = get_client(sender);
        std::shared_ptr<Client> receiver_ptr = get_client(receiver);

        size_t nonce_sender = sender_ptr->generate_nonce();
        std::string result = mempool + std::to_string(nonce_sender);
        std::string hash = crypto::sha256(result);

        std::string digits_only = "";
        for(char c : hash){
            if(std::isdigit(c)){
                digits_only += c;
                if(digits_only.length() >= 10){
                    break;
                }
            }
        }

        for(int j = 0; j <= 7; j++){
            if(digits_only.substr(j, 3) == "000"){
                for(const auto& trx : pending_trxs){
                    std::string send, receive;
                    double money;
                    parse_trx(trx, send, receive, money);
                    std::shared_ptr<Client> send_ptr;
                    std::shared_ptr<Client> receive_ptr;
                    send_ptr = get_client(send);
                    receive_ptr = get_client(receive);
                    clients[send_ptr] -= money;
                    clients[receive_ptr] += money;
                }
                pending_trxs.clear();
                clients[sender_ptr] += 6.25;
                std::cout << sender << std::endl;
                find = true;
                return nonce_sender;
            }
            else{
                continue;
            }
        }

        i++;

        if(find){
            break;
        }

        //if(!find){
        //    size_t
        //}
    }
}