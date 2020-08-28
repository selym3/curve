#include <iostream>
#include "src/curve.hpp"

#include <SDL2/SDL.h>

#include <memory>

#include <cmath>

#define WIDTH (600)
#define HEIGHT (600)

#define T_STEP (0.01)
#define GRADIENT_STEP T_STEP//(0.01)

class curve_tracker
{

private:
    mp::curve<2> &target;

    const mp::vec2 *v_ptr;

    int i;

    void Update()
    {
        v_ptr = &(target.points[i]);
    }

public:
    curve_tracker(mp::curve<2> &target) : target(target)
    {
        i = 0;

        Update();
    }

    ~curve_tracker()
    {
        // deconstructor
    }

    void Next()
    {
        i++;

        i %= target.points.size();

        Update();
    }

    void Prev()
    {
        i--;

        i += target.points.size() * (i < 0);

        Update();
    }

    const mp::vec2 &Get() const
    {
        return *v_ptr;
    }

    mp::curve<2> &Curve() const
    {
        return target;
    }

    void Set(const mp::curve<2> &target)
    {
        this->target = target;
    }
};

int main(void)
{
    if (SDL_Init(SDL_INIT_VIDEO))
    {
        std::cout << "Couldn't initialize sdl video: " << SDL_GetError() << "\n";
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("curve", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);

    if (!window)
    {
        std::cout << "Couldn't create sdl window: " << SDL_GetError() << "\n";
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!renderer)
    {
        std::cout << "Couldn't create sdl renderer: " << SDL_GetError() << "\n";
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    bool running = true;

    const Uint8 *keys = SDL_GetKeyboardState(NULL);
    SDL_Event event;

    SDL_Rect to_draw = {0, 0, 10, 10};

    mp::line<2> curve({{0,0}}, {{WIDTH, HEIGHT}});

    // mp::quadratic_bezier<2> curve(
    //     {{0,0}},
    //     {{ WIDTH * 0.75, HEIGHT / 2}},
    //     {{0,HEIGHT}}
    // );

    /*
    mp::catmull_rom<2> curve(
        {{0, 100}},
        {{25, 100}},
        {{50, 100}},
        {{75, 100}});
    */

    curve_tracker tracker(curve);

    auto SetRect = [&](SDL_Rect &rect, mp::vec<2> &src) {
        rect.x = src[0] - rect.w / 2.0;
        rect.y = src[1] - rect.h / 2.0;
    };

    auto RotatePoint = [&](double rads, mp::vec<2> &src) {
        double sd = std::sin(rads);
        double cd = std::cos(rads);

        double x = src[0] * cd - src[1] * sd;
        double y = src[0] * sd + src[1] * cd;

        return mp::vec2({x, y});
    };

    double current_t = 0.0;

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_KEYDOWN:
            case SDL_KEYUP:
                keys = SDL_GetKeyboardState(NULL);

                if (keys[SDL_SCANCODE_ESCAPE])
                {
                    running = false;
                    break;
                }

                if (keys[SDL_SCANCODE_LEFT])
                {
                    tracker.Prev();
                }

                if (keys[SDL_SCANCODE_RIGHT])
                {
                    tracker.Next();
                }

                if (keys[SDL_SCANCODE_X])
                {
                    current_t += (GRADIENT_STEP);
                }

                if (keys[SDL_SCANCODE_Z])
                {
                    current_t -= (GRADIENT_STEP);
                }

                if (current_t < 0)
                    current_t = 0;
                else if (current_t > 1)
                    current_t = 1;

                break;
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

        mp::vec2 last = tracker.Curve()(0);

        for (double t = 0; t < 1 + T_STEP; t += (T_STEP))
        {
            mp::vec2 current = tracker.Curve()(t);

            SetRect(to_draw, current);

            SDL_RenderFillRect(renderer, &to_draw);

            SDL_RenderDrawLine(renderer, last[0], last[1], current[0], current[1]);

            last = current;
        }

        SDL_SetRenderDrawColor(renderer, 0, 255, 255, 0);

        for (auto &p : tracker.Curve().points)
        {
            SDL_SetRenderDrawColor(renderer, 0, 255 * (&p == &tracker.Get()), 255, 0);

            mp::vec2 speed({(double)(10 * (-keys[SDL_SCANCODE_A] + keys[SDL_SCANCODE_D]) * (&p == &tracker.Get())),
                            (double)(10 * (-keys[SDL_SCANCODE_W] + keys[SDL_SCANCODE_S]) * (&p == &tracker.Get()))});

            p += speed;

            SetRect(to_draw, p);

            SDL_RenderFillRect(renderer, &to_draw);
        }

        // Draw Midpoint
        mp::vec2 midpoint = tracker.Curve()(0.5);

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);

        SetRect(to_draw, midpoint);
        SDL_RenderFillRect(renderer, &to_draw);

        // Draw Angle
        mp::vec2 point = tracker.Curve()(current_t);
        mp::vec2 gradient = tracker.Curve()[current_t];
        double angle = std::atan2(gradient[1], gradient[0]);

        // std::cout << angle << "\n";

        mp::vec2 dir({25, 0});
        dir = RotatePoint(angle, dir);

        std::cout << current_t << ": " << point << " + " << dir << "\n";

        dir += point;

        SDL_RenderDrawLine(renderer, point[0], point[1], dir[0], dir[1]);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    return 0;
}