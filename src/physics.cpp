#include "physics.h"
#include <iostream>
#include <vector>
#include <random>
#include<string>

void goToXY(int row, int col)
{
    std::cout << "\033[" << row << ";" << col << "H";
}

float y_boundary(float& y,  float vy)
{
    if (y < 0)
    {
        y = 0;
        vy = -vy * 0.8f;
        return vy;
    }
    else
    {
        y = 29;
        vy = -vy * 0.8f;
        return vy;
    }
}
float x_boundary(float& x,  float vx)
{
    if (x >= 29)
    {
        x = 29;
        vx = -vx * 0.8f;
        return vx;
    }
    else
    {
        x = 0;
        vx = -vx * 0.8f;
        return vx;
    }
}
void grid_print(void)
{
    std::vector<std::string>grid(30 * 30, ". ");
        for (int i = 0; i < 30; ++i)
        {
            for (int j = 0; j < 30; ++j)
            {
                std::cout << grid[(30 * i) + j];
            }
            std::cout << '\n';
        }
}
int ran_num(void)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distrib(0, 29);
    return distrib(gen);
}
float ran_num_2(void)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distrib(10.0f, 35.0f);
    return distrib(gen);
}
float ran_num_3(void)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distrib(0.0f, 360.0f);
    return distrib(gen);
}