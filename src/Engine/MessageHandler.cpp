#include "../include/MessageHandler.h"

MessageHandler::MessageHandler() {
    zmq_context = zmq::context_t();
    zmq_send_socket = zmq::socket_t(zmq_context, ZMQ_PUSH);
    zmq_send_socket.bind(SERVER_ADDR);
}

void MessageHandler::SendMsg(const std::string &msg) {
    zmq::message_t send_message(msg);
    std::cout << "Now sending -> " << send_message << std::endl;
    zmq_send_socket.send(send_message, zmq::send_flags::dontwait);
}

MessageHandler::~MessageHandler() {
    zmq_ctx_destroy(&zmq_context);
}


