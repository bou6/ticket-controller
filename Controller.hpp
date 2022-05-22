#ifndef INPUT_MANAGER_HPP
#define INPUT_MANAGER_HPP
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include<vector>
#include "Display.hpp"

class Controller
{
private:
    static constexpr int m_windowValueSize = 4; /* size of the window value in the request */
    static constexpr int m_windowNbSize = 1; /*size of the window number in the request*/
    std::vector<int> m_counters;
    int server_fd;
    struct sockaddr_in address;
    Display* m_disp_ptr;

    enum{
        UP_START_POS =0,
        UP_WINDOW_NB_POS = UP_START_POS + strlen("up"),
    }UP_CMD_POS_IN_ARRAY;

    enum{
        DOWN_START_POS =0,
        DOWN_WINDOW_NB_POS = DOWN_START_POS + strlen("down"),
    }DOWN_CMD_POS_IN_ARRAY;

    enum{
        VAL_START_POS =0,
        VAL_WINDOW_NB_POS= VAL_START_POS + strlen("val"),
        VAL_VALUE_POS= VAL_WINDOW_NB_POS + m_windowNbSize, /**#### Here we suppose that only numbers with 4 digits are given */
    }VAL_CMD_POS_IN_ARRAY;

public:
    Controller(Display* disp_ptr);
    bool m_quit;
    void update();
    int handleRxData(char* buffer, int cnt);
    int getCounter();
};

#endif