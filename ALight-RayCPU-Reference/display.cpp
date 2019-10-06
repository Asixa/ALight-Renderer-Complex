#include "display.h"

Display::Display(const char *title, int width, int height, int scale)
{
    m_title = title;
    m_width = width;
    m_height = height;
    m_scale = scale;
    m_pixels = new Uint32[m_width * m_height];
    clear(0x00000000);

    if (init() != 0)
    {
        std::cout << "Failed to initialize a display... Exiting the program with error code 1." << std::endl;
        delete[] m_pixels;
        std::exit(1);
    }

    std::cout << "Initialized a new Display succesfully." << std::endl;
}

Display::~Display()
{
    delete[] m_pixels;

    SDL_DestroyTexture(m_texture);
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);

    std::cout << "Display object has been destroyed succesfully." << std::endl;
}

int Display::init()
{
    // Create a SDL_Window pointer and close the program with an error message if that fails
    m_window = SDL_CreateWindow(m_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_width * m_scale, m_height * m_scale, SDL_WINDOW_SHOWN);
    if (m_window == nullptr)
    {
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }
    else
    {
        std::cout << "SDL_Window has been succesfully created." << std::endl;
    }

    // Create a SDL_Renderer pointer and close the program with an error message if it fails
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED); // | SDL_RENDERER_PRESENTVSYNC
    if (m_renderer == nullptr)
    {
        SDL_DestroyWindow(m_window);
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }
    else
    {
        std::cout << "SDL_Renderer has been succesfully created." << std::endl;
    }

    // Create a SDL_Texture from the surface we previously loaded, destroy the surface and close the program if an error occurred
    m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, m_width, m_height);
    if (m_texture == nullptr)
    {
        SDL_DestroyRenderer(m_renderer);
        SDL_DestroyWindow(m_window);
        std::cout << "SDL_CreateTexture Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }
    else
    {
        std::cout << "SDL_Texture has been succesfully created." << std::endl;
    }

    // No errors!
    return 0;
}

void Display::render()
{
    SDL_UpdateTexture(m_texture, nullptr, m_pixels, m_width * sizeof(Uint32));
    SDL_RenderClear(m_renderer);
    SDL_RenderCopy(m_renderer, m_texture, nullptr, nullptr);
    SDL_RenderPresent(m_renderer);
}

void Display::setTitle(const char *title)
{
    m_title = title;
    SDL_SetWindowTitle(m_window, m_title);
}
