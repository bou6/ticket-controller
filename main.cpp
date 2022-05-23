#include <thread>
#include <iostream>
#include <unistd.h>
#include "Controller.hpp"
#include "Display.hpp"

// TODO 
// the controller is blocked on the socket receiving this is why it stays blocked when the display is quit, need to add a timeout to the socket listenning
// The display update, if you move or do an event in the winodw then the frequencey of diplaying the pictures will change

Controller* ctrl_ptr;
Display* disp_ptr;

void displayTask()
{
    while (!disp_ptr->quit())
    {
        disp_ptr->update();
    }
    std::cout << "Quiting display Task" <<std::endl;
    disp_ptr->~Display();
}

void controllerTask()
{
    while(!ctrl_ptr->m_quit)
    {
        ctrl_ptr->update();
    }
    std::cout <<"Quitting the controller task"<<std::endl;
    ctrl_ptr->~Controller();
}

int main()
{
    disp_ptr = new Display();
    ctrl_ptr = new Controller(disp_ptr);
    
    std::thread controllerThread(controllerTask);
    std::thread displayThread(displayTask);

    controllerThread.join();
    displayThread.join();

    return 0;
}