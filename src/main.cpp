#include "physics.h"
#include <cmath>
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <numbers>
#include <numbers>

int main(void)
{
    int mode{};
    std::cout << "Enter 1: Ball simulator\nEnter 2: Ball interceptor\nEnter 3: Multiple Ball Simulator\n";
    std::cin >> mode;
    if (mode == 1)
    {
        std::cout << "Enter the initial x coordinate (0 to 29): ";
        int x_start{};
        std::cin >> x_start;
        x_start = std::clamp(x_start, 0, 29);
        std::cout << "Enter the initial y coordinate (0 to 29): ";
        int y_start{};
        std::cin >> y_start;
        y_start = std::clamp(y_start, 0, 29);
        std::cout << "Enter the velocity you want to hit it with the wall: ";
        float vel{};
        std::cin >> vel;
        std::cout << "Enter the angle between initial velocity and the x-axis: ";
        float angle{};
        std::cin >> angle;
        std::cout << "\033[2J\033[H";
        double cos = std::cos(angle * (std::numbers::pi / 180));
        double sin = std::sin(angle * (std::numbers::pi / 180));
        grid_print();
        int iteration{};
        float x_previous{};
        float y_previous{};
        float x = x_start;
        float y = y_start;
        float vx = vel * cos;
        float vy = vel * sin;
        float dt = 0.1f;
        while (true)
        {
            x_previous = x;
            y_previous = y;
            vy = vy - (9.8f * dt);
            x = x + (vx * dt);
            y = y + (vy * dt);
            if (x < 0 || x >= 29)
            {
                vx = x_boundary(x, vx);
            }
            if (y < 0 || y >= 29)
            {
                vy = y_boundary(y, vy);
            }
            if (iteration != 0)
            {
                goToXY(30 - (int)y_previous, (2 * (int)x_previous) + 1);
                std::cout << ". ";
            }
            goToXY(30 - (int)y, (2 * (int)x) + 1);
            std::cout << "+ ";

            std::cout << std::flush;
            std::this_thread::sleep_for(std::chrono::milliseconds(16));
            iteration++;
        }
    }
    else if (mode == 2)
    {
        Ball interceptor{};
        Ball target{};
        std::cout << "Enter the x coordinate of your target (0 to 29): ";
        std::cin >> target.x;
        target.x = std::clamp(target.x, 0.0f, 29.0f);
        std::cout << "Enter the y coordinate of your target (0 to 29): ";
        std::cin >> target.y;
        target.y = std::clamp(target.y, 0.0f, 29.0f);
        std::cout << "Enter the initial velocity of your target: ";
        float vel{};
        std::cin >> vel;
        std::cout << "Enter the angle between initial velocity and the x axis: ";
        float angle{};
        std::cin >> angle;
        std::cout << "Enter the x coordinate of your interceptor (0 to 29): ";
        std::cin >> interceptor.x;
        interceptor.x = std::clamp(interceptor.x, 0.0f, 29.0f);
        std::cout << "Enter the y coordinate of your interceptor (0 to 29): ";
        std::cin >> interceptor.y;
        interceptor.y = std::clamp(interceptor.y, 0.0f, 29.0f);
        std::cout << "\033[2J\033[H";
        double cos = std::cos(angle * (std::numbers::pi / 180));
        double sin = std::sin(angle * (std::numbers::pi / 180));
        grid_print();
        float t_hit = 0.8f;
        int iteration{};
        target.vx = vel * cos;
        target.vy = vel * sin;
        float dt =  0.1f;
        interceptor.vx = ((target.x - interceptor.x) / t_hit) + target.vx;
        interceptor.vy = ((target.y - interceptor.y) / t_hit) + target.vy;
        while (true)
        {
            interceptor.x_previous = interceptor.x;
            interceptor.y_previous = interceptor.y;
            target.x_previous = target.x;
            target.y_previous = target.y;
            target.vy = target.vy - (9.8f * dt);
            target.x = target.x + (target.vx * dt);
            target.y = target.y + (target.vy * dt);
            interceptor.vy = interceptor.vy - (9.8f * dt);
            interceptor.x = interceptor.x + (interceptor.vx * dt);
            interceptor.y = interceptor.y + (interceptor.vy * dt);
            if (target.x >= 29 || target.x < 0)
            {
                target.vx = x_boundary(target.x, target.vx);
            }
            if (target.y >= 29 || target.y < 0)
            {
                target.vy = y_boundary(target.y, target.vy);
            }
            if (interceptor.x >= 29 || interceptor.x < 0)
            {
                interceptor.vx = x_boundary(interceptor.x, interceptor.vx);
            }
            if (interceptor.y >= 29 || interceptor.y < 0)
            {
                interceptor.vy = y_boundary(interceptor.y, interceptor.vy);
            }
            if (iteration != 0)
            {
                goToXY(30 - (int)target.y_previous, (2 * (int)target.x_previous) + 1);
                std::cout << ". ";
                goToXY(30 - (int)interceptor.y_previous, (2 * (int)interceptor.x_previous) + 1);
                std::cout << ". ";
            }
            goToXY(30 - int(target.y), (2 * (int)target.x) + 1);
            std::cout << "+ ";
            goToXY(30 - int(interceptor.y), (2 * (int)interceptor.x) + 1);
            std::cout << "@ ";
            std::cout << std::flush;
            std::this_thread::sleep_for(std::chrono::milliseconds(16));
            if (((int)target.x == (int)interceptor.x) && ((int)target.y == (int)interceptor.y))
            {
                goToXY(32, 1);
                std::cout << "BOOM! Target intercepted mid-air!\n";
                break;
            }
            iteration++;
        }
    }
    else if (mode == 3)
    {
    int total_balls{};
    std::cout << "How many balls you want to bounce at once: ";
    std::cin >> total_balls;
    total_balls = std::clamp(total_balls, 1, 200);
    std::cout << "\033[2J\033[H";
    grid_print();
    std::vector<Ball> balls(total_balls);
    for (int  i = 0; i < total_balls; ++i)
    {
        
    int x_start{ran_num()};
    
    int y_start{ran_num()};
    
    float vel{ran_num_2()};
   
    float angle{ran_num_3()};
   
    double cos = std::cos(angle * (std::numbers::pi / 180));
    double sin = std::sin(angle * (std::numbers::pi / 180));
    balls[i].x = x_start;
    balls[i].y = y_start;
    balls[i].vx = vel * cos;
    balls[i].vy = vel * sin;
    balls[i].x_previous = {};
    balls[i].y_previous = {};
    }
    int iteration{};
    float dt = 0.1f;
    while (true)
    {
        for (int i = 0; i < total_balls; ++i)
        {
            balls[i].x_previous = balls[i].x;
        balls[i].y_previous = balls[i].y;
        balls[i].vy = balls[i].vy - (9.8f * dt);
        balls[i].x = balls[i].x + (balls[i].vx * dt);
        balls[i].y = balls[i].y + (balls[i].vy * dt);
        if (balls[i].x < 0 || balls[i].x >= 29)
        {
            balls[i].vx = x_boundary(balls[i].x, balls[i].vx);
        }
        if (balls[i].y < 0 || balls[i].y >= 29)
        {
            balls[i].vy = y_boundary(balls[i].y, balls[i].vy);
        }
        if (iteration != 0)
        {
            goToXY(30 - (int)balls[i].y_previous, (2 * (int)balls[i].x_previous) + 1);
            std::cout << ". ";
        }
        goToXY(30 - (int)balls[i].y, (2 * (int)balls[i].x) + 1);
        std::cout << "+ ";
        }
        std::cout << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
        iteration++;
        
    }
    }
}