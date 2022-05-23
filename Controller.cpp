#include "Controller.hpp"
#include <iostream>
#include <SDL2/SDL.h>     
#include <unistd.h>
#include <string.h>
#include <fcntl.h>


#define PORT 8080

Controller::Controller(Display* disp_ptr):
m_counters(10,0),
m_disp_ptr(disp_ptr),
m_quit(false)
{
    int opt = 1;
    int addrlen = sizeof(address);

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM , 0))
        == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET,
                    SO_REUSEADDR | SO_REUSEPORT, &opt,
                    sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr*)&address,
                sizeof(address))
        < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
}

void Controller::update()
{
    int new_socket, valread;
    int addrlen = sizeof(address);
    char buffer[1024] = { 0 };
    char* hello = "Hello from server";

    if (m_disp_ptr->quit())
    {
        m_quit = true;
        std::cout<< "quitting the Controller" <<std::endl;
        return;
    }
    std::cout <<"1"<<std::endl;

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    std::cout <<"2"<<std::endl;
    if ((new_socket
         = accept(server_fd, (struct sockaddr*)&address,
                  (socklen_t*)&addrlen))
        < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    std::cout <<"3"<<std::endl;
    valread = read(new_socket, buffer, 1024);
    int ret = handleRxData(buffer, 1024);
    if (ret<0)
    {
        char* response= "command not recognised";
        send(new_socket, response, strlen(response), 0);
    }
    else
    {
        char* response= "command executed";
        send(new_socket, response, strlen(response), 0);
    }
    return;
}

int Controller::handleRxData(char* buffer, int cnt)
{
    if (memcmp(buffer, "up",strlen("up"))==0)
    {
        std::cout << "up event received"<<std::endl;
        std::cout << "window ="<<buffer[Controller::UP_WINDOW_NB_POS]<<std::endl;
    }
    else if (memcmp(buffer, "down",strlen("down"))==0)
    {
        std::cout << "down event received"<<std::endl;
        std::cout << "window ="<<buffer[Controller::DOWN_WINDOW_NB_POS]<<std::endl;
    }
    else if (memcmp(buffer, "val",strlen("val"))==0)
    {
        //take the number and output it directly
        std::cout << "val event received"<<std::endl;
        std::cout << "window ="<<buffer[Controller::VAL_WINDOW_NB_POS]<<std::endl;
        std::cout << "value ="<<buffer[Controller::VAL_VALUE_POS]<<std::endl;

        // convert the windw index and value
        char windowNb_array[m_windowNbSize + 1];
        char value_array[m_windowValueSize + 1];
        memcpy(windowNb_array, &buffer[Controller::VAL_WINDOW_NB_POS],m_windowNbSize);
        windowNb_array[m_windowNbSize] = '\0';
        int windowNb = atoi(windowNb_array);

        memcpy(value_array, &buffer[Controller::VAL_VALUE_POS], m_windowValueSize);
        value_array[m_windowValueSize] = '\0';
        int windowValue = atoi(value_array);

        std::cout << "window Nb :"<< windowNb<< " window value : " << windowValue <<std::endl;

        // update the window value
        m_counters[windowNb]=windowValue;

        for (std::vector<int>::iterator it = m_counters.begin(); it!=m_counters.end(); it++)
        {
            std::cout << "--- value ---: "<<*it<<std::endl;
        }

    }
    else
    {
        // command not supported !
        std::cout << "event not recognised"<<std::endl;
        return -1;
    }
    return 0;
}