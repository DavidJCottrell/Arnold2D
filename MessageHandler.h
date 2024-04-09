#ifndef ARNOLD_MESSAGEHANDLER_H
#define ARNOLD_MESSAGEHANDLER_H

#include <zmq.hpp>
#include <iostream>
#include <string>

#define SERVER_ADDR "tcp://localhost:5001"

class MessageHandler {
public:
    static MessageHandler &getInstance() {
        static MessageHandler instance;
        return instance;
    }

    void SendMsg(const std::string &msg);

private:
    MessageHandler();

    ~MessageHandler();

    zmq::context_t zmq_context;
    zmq::socket_t zmq_send_socket;
};


#endif //ARNOLD_MESSAGEHANDLER_H
