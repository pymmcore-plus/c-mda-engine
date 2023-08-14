#include "MDAPosition.h"
#include <algorithm>
#include <cassert>
#include <chrono>
#include <cstring>
#include <fstream>
#include <set>
#include <sstream>
#include <vector>
#include <iostream>

#include <string>
#include <vector>
#include <map>

#ifndef _WINDOWS
// Needed on Unix for getcwd() and gethostname()
#include <pwd.h>
#include <sys/types.h>
#include <unistd.h>
#else
// for _getcwd
#include <direct.h>
#include <vector>
#endif

using namespace std;

Position::Position():
    x_(UnsetPosition),
    y_(UnsetPosition),
    z_(UnsetPosition)
{
; // empty constructor
}
void Position::setX(float x)
{
    x_ = x;
}
void Position::setY(float y)
{
    y_ = y;
}
void Position::setZ(float z)
{
    z_ = z;
}
void Position::setName(string name)
{
    name_ = name;
}
float Position::getX()
{
    return x_;
}
float Position::getY()
{
    return y_;
}
float Position::getZ()
{
    return z_;
}
string Position::getName()
{
    return name_;
}

// int main()
// {
// // initialize the position class with a dummy example
//     Position pos;
//     pos.setX(1.0);
//     pos.setY(2.0);
//     pos.setZ(3.0);
//     char name[MaxNameLength] = "test";
//     pos.setName(name);
//     std::cout << "Position name: " << pos.getName() << std::endl;
//     std::cout << "Position x: " << pos.getX() << std::endl;
//     std::cout << "Position y: " << pos.getY() << std::endl;
//     std::cout << "Position z: " << pos.getZ() << std::endl;
//     return 0;
// }
