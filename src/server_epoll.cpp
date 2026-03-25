#include "server_epoll.h"
#include "thread_pool.h"
#include "client_handler.h"
#include "logger.h"

#include <sys/epoll.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>

#define MAX_EVENTS 10

Server::Server(int port) : port(port) {}

void Server::start() {
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;

    bind(server_fd, (sockaddr*)&addr, sizeof(addr));
    listen(server_fd, SOMAXCONN);

    epoll_fd = epoll_create1(0);

    epoll_event ev{};
    ev.events = EPOLLIN;
    ev.data.fd = server_fd;

    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, server_fd, &ev);

    ThreadPool pool(4);

    epoll_event events[MAX_EVENTS];

    Logger::log("Server started on port 8080");

    while (true) {
        int nfds = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);

        for (int i = 0; i < nfds; ++i) {
            if (events[i].data.fd == server_fd) {
                int client = accept(server_fd, nullptr, nullptr);

                epoll_event client_ev{};
                client_ev.events = EPOLLIN;
                client_ev.data.fd = client;

                epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client, &client_ev);

                Logger::log("New client connected");
            } else {
                int client_fd = events[i].data.fd;

                pool.enqueue([client_fd]() {
                    ClientHandler handler(client_fd);
                    handler.handle();
                });
            }
        }
    }
}
