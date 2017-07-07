#include <sstream>
#include <cstdlib>
#include <iostream>

//Implement the class Box
//l,b,h are integers representing the dimensions of the box

// The class should have the following functions :

// Constructors:
// Box();
// Box(int,int,int);
// Box(Box);


// int getLength(); // Return box's length
// int getBreadth (); // Return box's breadth
// int getHeight ();  //Return box's height
// long long CalculateVolume(); // Return the volume of the box

//Overload operator < as specified
//bool operator<(Box& b)

//Overload operator << as specified
//ostream& operator<<(ostream& out, Box& B)

class Box {
private:
    int l, b, h;
public:
    Box();
    Box(int, int, int);
    Box(const Box& b);
    int getLength();
    int getBreadth();
    int getHeight();
    long long CalculateVolume();
    bool operator<(Box& b);
    friend std::ostream& operator<<(std::ostream& out, Box& b);
};

Box::Box(){
    Box::l = 0;
    Box::b = 0;
    Box::h = 0;
}
Box::Box(int l, int b, int h) {
    Box::l = l;
    Box::b = b;
    Box::h = h;
}

Box::Box(const Box& b) {
    //Box b = new Box();
    this->l = b.l;
    this->b = b.b;
    this->h = b.h;
}

int Box::getLength() {
    return Box::l;
}

int Box::getBreadth() {
    return Box::b;
}

int Box::getHeight() {
    return Box::h;
}


long long Box::CalculateVolume() {
    return (long long) Box::getLength() * Box::getBreadth() * Box::getHeight();
}

bool Box::operator<(Box& b) {
    if (Box::l < b.l) {
        return true;
    } else if (Box::b < b.b && Box::l == b.l) {
        return true;
    } else if (Box::h < b.h && Box::l == b.l && Box::b == b.b) {
        return true;
    } else {
        return false;
    }

}


std::ostream& operator<<(std::ostream& out, Box& B) {
    return out << B.l << " " << B.b << " " << B.h;
}

int main(int argc, char **argv) {
    return 0;
}
