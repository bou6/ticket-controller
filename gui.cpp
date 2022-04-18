#include <SDL2/SDL.h>        
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <ctime>

constexpr int images_array_size= 3;

char* images_array[3]= {
    "146.jpg",
    "147.jpg",
    "148.jpg"
};
 
int main(int argc, char ** argv)
{
    bool quit = false;
    SDL_Event event;
    time_t start_time;
    time_t current_time;
    time_t timeout=5;
    int image_index=0;

    SDL_Init(SDL_INIT_VIDEO);

    TTF_Init();

    IMG_Init(IMG_INIT_JPG);

    SDL_Window * window = SDL_CreateWindow("SDL2 Displaying Image",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);

    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);

    TTF_Font * font = TTF_OpenFont("OpenSans-Italic.ttf", 25);
    SDL_Color color = { 255, 255, 255 };

    SDL_Texture * texture = IMG_LoadTexture(renderer, images_array[image_index]);
 
    // stores time in current_time
    time(&current_time);
    start_time = current_time;
    while (!quit)
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
            image_index = (image_index+1)%images_array_size;
            std::cout << "change next image index = " << image_index <<std::endl;
            texture = IMG_LoadTexture(renderer, images_array[image_index]);
        }
        
        SDL_RenderCopy(renderer, texture, NULL, NULL);

        // print the text 
        {
            char text[3];
            sprintf(text, "%d", image_index);

            SDL_Surface * surface = TTF_RenderText_Solid(font, text, color);
            SDL_Texture * nr_texture = SDL_CreateTextureFromSurface(renderer, surface);
            int texW = 100;
            int texH = 0;
            SDL_QueryTexture(nr_texture, NULL, NULL, &texW, &texH);
            SDL_Rect dstrect = { 0, 0, texW, texH };
            /* render the text */
            SDL_RenderCopy(renderer, nr_texture, NULL, &dstrect);
        }

        SDL_RenderPresent(renderer);
    }
 
    // here need to destroy the number texture and in general the number ressoures
    //SDL_DestroyTexture(nr_texture);
    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
 
    return 0;
}