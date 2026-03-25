#include "client_handler.h"
#include "database.h"
#include "logger.h"

#include <unistd.h>
#include <cstring>

ClientHandler::ClientHandler(int socket) : client_socket(socket) {}

void ClientHandler::handle() {
    char buffer[1024] = {0};

    int bytes = read(client_socket, buffer, sizeof(buffer));

    if (bytes <= 0) {
        close(client_socket);
        return;
    }

    std::string request(buffer);
    Logger::log("Request: " + request);

    std::string response = Database::getInstance().process(request);

    send(client_socket, response.c_str(), response.size(), 0);

    memset(buffer, 0, sizeof(buffer));
}
