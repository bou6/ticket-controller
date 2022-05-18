#include "Display.hpp"
#include <iostream>
#include <ctime>

Display::Display():
    m_image_index(0)
{
    time_t current_time;

    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    IMG_Init(IMG_INIT_JPG);

    // stores the start time
    time(&current_time);
    start_time = current_time;

    // SDL initialization
    m_window = SDL_CreateWindow("Display", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
    m_renderer = SDL_CreateRenderer(m_window, -1, 0);
    m_font = TTF_OpenFont("OpenSans-Italic.ttf", 25);
    color = { 255, 255, 255 };
    m_texture = IMG_LoadTexture(m_renderer, images_array[m_image_index]);
}

void Display::update()
{
    bool quit = false;
    SDL_Event event;
    time_t start_time;
    time_t current_time;
    time_t timeout=5;

    if (!quit)
    {
        SDL_WaitEventTimeout(&event,100);
        switch (event.type)
        {
            case SDL_QUIT:
                quit = true;
                break;
        }

        time(&current_time);
        std::cout << "current_time ="<<current_time<<"start_time ="<<start_time <<"timeout = "<<timeout<<std::endl;
        if (current_time - start_time > timeout)
        {
            start_time = current_time;
            m_image_index = (m_image_index+1)%images_array_size;
            std::cout << "change next image index = " << m_image_index <<std::endl;
            m_texture = IMG_LoadTexture(m_renderer, images_array[m_image_index]);
        }
        
        SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);

        // print the text 
        {
            char text[3];
            sprintf(text, "%d", m_image_index);

            SDL_Surface * surface = TTF_RenderText_Solid(m_font, text, color);
            SDL_Texture * nr_texture = SDL_CreateTextureFromSurface(m_renderer, surface);
            int texW = 100;
            int texH = 0;
            SDL_QueryTexture(nr_texture, NULL, NULL, &texW, &texH);
            SDL_Rect dstrect = { 0, 0, texW, texH };
            /* render the text */
            SDL_RenderCopy(m_renderer, nr_texture, NULL, &dstrect);
        }
        SDL_RenderPresent(m_renderer);
    }
 }

 Display::~Display()
 {
    SDL_DestroyTexture(m_texture);
    TTF_CloseFont(m_font);
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
 }