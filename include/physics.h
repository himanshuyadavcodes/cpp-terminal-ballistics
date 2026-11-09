#pragma once

struct Ball
{
    float x{};
    float y{};
    float vx{};
    float vy{};
    float x_previous{};
    float y_previous{};
};

void goToXY(int row, int col);
float y_boundary(float& y,  float vy);
float x_boundary(float& x,  float vx);
void grid_print(void);
int ran_num(void);
float ran_num_2(void);
float ran_num_3(void);
