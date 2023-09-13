#ifndef _MDAPosition_H_
#define _MDAPosition_H_

#ifdef _MSC_VER
// We use exception specifications to instruct SWIG to generate the correct
// exception specifications for Java. Turn off the warnings that VC++ issues by
// the mere use of exception specifications (which VC++ does not implement).
#pragma warning(disable : 4290)
#endif

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


#endif //_MDAPosition_H_
