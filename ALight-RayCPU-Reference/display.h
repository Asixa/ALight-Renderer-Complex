#ifndef DISPLAY_H
#define DISPLAY_H

#include <iostream>
#include <SDL2/SDL.h>
#include "config.h"
#include "math.h"
#include "vec3.h"

using namespace math;

class Display
{
public:
    Display(const char *title, int width, int height, int scale);
    ~Display();

    int init();
    void render();

    void clear(const Uint32 &color)
    {
        for (int i = 0; i < m_width * m_height; i++)
            m_pixels[i] = color;
    }

    void setPixel(int x, int y, const Uint32 &color)
    {
        if (x < 0 || x >= m_width || y < 0 || y >= m_height)
            return;

        m_pixels[x + y * m_width] = color;
    }

    void setPixel(int x, int y, vec3 &v)
    {
        if (x < 0 || x >= m_width || y < 0 || y >= m_height)
            return;

        v = math::pow(v, 1.0f / GAMMA);
        v = math::clamp(v, 0.0f, 1.0f);

        auto r = static_cast<Uint32>(v.x * 255.0f);
        auto g = static_cast<Uint32>(v.y * 255.0f);
        auto b = static_cast<Uint32>(v.z * 255.0f);
        auto hex = ((r << 16) | (g << 8) | b);

        m_pixels[x + y * m_width] = hex;
    }

    void setTitle(const char *title);

    int getWidth() const
    {
        return m_width;
    }
    int getHeight() const
    {
        return m_height;
    }
    float getAspectRatio() const
    {
        return static_cast<float>(m_width) / m_height;
    }
    SDL_Window *getWindow() const
    {
        return m_window;
    }
    SDL_Renderer *getRenderer() const
    {
        return m_renderer;
    }
    SDL_Texture *getTexture() const
    {
        return m_texture;
    }
private:
    const char *m_title;
    int m_width;
    int m_height;
    int m_scale;
    Uint32 *m_pixels;
    SDL_Window *m_window;
    SDL_Renderer *m_renderer;
    SDL_Texture *m_texture;
};

#endif
