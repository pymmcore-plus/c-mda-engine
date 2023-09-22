#ifndef _MDAEvent_H_
#define _MDAEvent_H_

#ifdef _MSC_VER
// We use exception specifications to instruct SWIG to generate the correct
// exception specifications for Java. Turn off the warnings that VC++ issues by
// the mere use of exception specifications (which VC++ does not implement).
#pragma warning(disable : 4290)
#endif
#include <map>
#include "MDAPosition.h"

enum Action {AcquireImage}; 
enum EventState {Start, Paused, Canceled, Finished, FrameReady};

class Position; 

class Channel{
    public:
        Channel(std::string config, std::string group);
        std::string config_;
        std::string group_;
};

class PropertyTuple{
public:
    PropertyTuple(std::string device_name, std::string property_name, float value);

private:
    std::string deviceName_;
    std::string propertyName_;
    float value_;
};


class MDAEvent{
public:
    MDAEvent(std::map<std::string, int> index, Channel channel, float exposure,
    float min_start_time, Position position, Action action, int global_index, bool keep_shutter_open);
    float getMinStartTime();
    float getExposure();
    float getZ();
    float getX();
    float getY();
    void setZ(float z);
    void setX(float x);
    void setY(float y);
    bool isXSet();
    bool isYSet();
    bool isZSet();
    bool isExposureSet();
    bool isChannelSet();
    bool isAutoshutterSet();
    bool KeepShutterOpen();
    int getGlobalIndex() {return globalIndex_;};
    Action getAction() {return action_;};
private:
    std::map<std::string, int> index_;
    Channel channel_;
    float exposure_;
    float minStartTime_;
    Position position_;
    int globalIndex_;
    bool xSet_;
    bool ySet_;
    bool zSet_;
    bool keepShutterOpen_;
    Action action_;
    std::map<std::string, float> metadata_;


};

#endif // _MDAEvent_H_