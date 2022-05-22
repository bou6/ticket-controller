#ifndef DISPLAY_HPP
#define DISPLAY_HPP
#include <ctime>
#include <SDL2/SDL.h>        
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

class Display
{
    private:
    SDL_Window * m_window;
    SDL_Renderer * m_renderer;
    TTF_Font * m_font;
    SDL_Color color;
    SDL_Texture * m_texture;
    time_t start_time;

    static constexpr int images_array_size= 3;
    char* images_array[3]= {
        "146.jpg",
        "147.jpg",
        "148.jpg"
    };

    // index of the image to be displayed
    int m_image_index;

    public:
    bool m_quit;
    Display();
    ~Display();
    void update();
};

 #endif 