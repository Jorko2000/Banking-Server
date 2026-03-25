#pragma once

class ClientHandler {
private:
    int client_socket;

public:
    ClientHandler(int socket);
    void handle();
};
