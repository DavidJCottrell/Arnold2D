#ifndef ARNOLD_MESSAGEHANDLER_H
#define ARNOLD_MESSAGEHANDLER_H

#include <zmq.hpp>
#include <string>
#include <iostream>

//192.168.7.186:

#define SERVER_ADDR "tcp://192.168.7.186:5001"

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

#endif // ARNOLD_MESSAGEHANDLER_H
