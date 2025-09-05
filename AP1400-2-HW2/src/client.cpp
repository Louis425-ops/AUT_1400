#include "client.h"
#include "crypto.h"
#include "server.h"
#include <stdexcept>
#include <random>


Client::Client(std::string id, Server& server): id(id), server(&server)
{
    crypto::generate_key(public_key, private_key);
}

std::string Client::get_id(){
    return this->id;
}

std::string Client::get_publickey() const {
    return this->public_key;
}

double Client::get_wallet(){
    return server->get_wallet(id);
}

std::string Client::sign(std::string txt) const {
    return crypto::signMessage(private_key, txt);
}

bool Client::transfer_money(std::string receiver, double value){
    std::shared_ptr<Client> receiver_ptr = server->get_client(receiver);
    if(receiver_ptr == nullptr){
        return false;
    }
    std::string final_trx = id + '-' + receiver + '-' + std::to_string(value);
    std::string sign_trx = sign(final_trx);
    if(value > get_wallet()){
        return false;
    }
    else{
        return server->add_pending_trx(final_trx, sign_trx);
    }
}

size_t Client::generate_nonce(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> dis(0, SIZE_MAX);

    return dis(gen);
}