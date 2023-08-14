#ifndef _MDAPosition_H_
#define _MDAPosition_H_

#ifdef _MSC_VER
// We use exception specifications to instruct SWIG to generate the correct
// exception specifications for Java. Turn off the warnings that VC++ issues by
// the mere use of exception specifications (which VC++ does not implement).
#pragma warning(disable : 4290)
#endif

#include <map>
#include <vector>
#include <string>
#include <climits>
#include <string>

#define MaxNameLength  256
#define MaxConfigLength 2560
#define UnsetPosition  (float)INT_MIN

enum Indices {TIME, POSITION, GRID, CHANNEL, Z};
enum GridPlans {GridFromEdges, GridRelative, NoGrid};


class Position {
public:
    Position();
    void setX(float x);
    void setY(float y);
    void setZ(float z);
    void setName(std::string name);
    float getX();
    float getY();
    float getZ();
    std::string getName();

private:
    float x_;
    float y_;
    float z_;
    std::string name_;
    // TODO: sequence?

};

// class Channel
// {
// public:
//     char[MaxConfigLength] name;
//     std::string group;
//     float exposure;
//     bool doStack;
//     float zOffset;
//     uint acquireEvery;
//     std::string Camera;

//     void setName(char[MaxConfigLength] name);
//     // {
//     //     strcpy(this->name, name);
//     // }
//     void setGroup(std::string group);
//     // {
//     //     strcpy(this->group, group);
//     // }
//     void setExposure(float exposure);
//     // {
//     //     this->exposure = exposure;
//     // }
//     void setDoStack(bool doStack);
//     // {
//     //     this->doStack = doStack;
//     // }
//     void setZOffset(float zOffset);
//     // {
//     //     this->zOffset = zOffset;
//     // }
//     void setAcquireEvery(uint acquireEvery);
//     // {
//     //     this->acquireEvery = acquireEvery;
//     // }
//     void setCamera(std::string Camera);
//     // {
//     //     strcpy(this->Camera, Camera);
//     // }
// };

// vector<Indices> DefaultAxisOrder = {TIME, POSITION, GRID, CHANNEL, Z};


#endif //_MDAPosition_H_
