#include "../cs225/catch/catch.hpp"
#include "../graph.h"
#include "../route.h"
#include "../airport.h"
#include "../cs225/PNG.h"
#include "../cs225/HSLAPixel.h"
#include <iostream>
using cs225::HSLAPixel;
using cs225::PNG;
using namespace std;
TEST_CASE("Graph::testdrawing", "[weight=2]") {
    const HSLAPixel BLUE(240, 1.0, 0.6, 1.0);

    pair<double, double> position1(300, 300);
    pair<double, double> position0(600, 600);
    PNG a;
    a.readFromFile("data/white.png");
    double k = (position1.second - position0.second)/(position1.first - position0.first); // y = kx + b
    double b = position1.second - k * position1.first;
    const double num = 1000;
    double interval = (position1.first - position0.first) / num;
    for (int i = 1; i <= num; i++) {
        double new_x = position0.first + i * interval;
        HSLAPixel & pixel = a.getPixel(new_x, k * new_x + b);
        pixel.h = 240;
        for (int j = 0; j < 6; j++) {
            HSLAPixel & pixeltop = a.getPixel(new_x, (k * new_x + b)-j);
            HSLAPixel & pixeldown = a.getPixel(new_x, (k * new_x + b)+j);
            HSLAPixel & pixelleft = a.getPixel((new_x)-j, k * new_x + b);
            HSLAPixel & pixelright = a.getPixel((new_x)+j, k * new_x + b);
        
            pixeltop = BLUE;
            pixeldown = BLUE;
            pixelleft = BLUE;
            pixelright = BLUE;
        }
    }
    a.writeToFile("outputWhite.png");
    //cout << "finished draw'" << endl;
}