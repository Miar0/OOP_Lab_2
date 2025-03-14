#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <vector>
#include <cmath>
#include <format>
#include <iostream>
#include <Windows.h>
#include <sstream>

using namespace std;

struct Point {
    double x, y;
};

double distance(const Point &p1, const Point &p2);

struct Triangle {
    Point a, b, c;

    double area();
    bool is_zero_area();
    bool contains(const Point &p);
    vector<double> is_point_inside(Point p);
};

double heronArea(const Triangle &t);
bool check_triangle_side(double det);
void clear_buffer();
bool check_to_fail();
void print_menu();

#endif
