/* Copyright <c> 2017 Manoel Vilela & HackerRank */

#include <iostream>

using namespace std;

/*
 * Create classes Rectangle and RectangleArea
 */

class Rectangle {
protected:
    int width;
    int height;
public:
    void display() {
        cout << width << " " << height << endl;
    }
};

class RectangleArea: public Rectangle {
public:
    void read_input() {
        cin >> width >> height;
    }

    void display() {
         cout << width * height << endl;;
    }
};

int main(void) {
    RectangleArea r_area;
    r_area.read_input();
    r_area.Rectangle::display();
    r_area.display();
    return 0;
}
