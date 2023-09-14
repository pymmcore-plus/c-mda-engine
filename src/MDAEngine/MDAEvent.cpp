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

#include <iostream>
#include "MDAEvent.h"

using namespace std;

Channel::Channel(string config, string group):
    config_(config),
    group_(group)
{
    ;
}

PropertyTuple::PropertyTuple(string device_name, string property_name, float value):
    deviceName_(device_name),
    propertyName_(property_name),
    value_(value)
{
    ;
}

MDAEvent::MDAEvent(std::map<std::string, int> index, Channel channel, float exposure,
    float min_start_time, Position position, int global_index, bool keep_shutter_open):
    index_(index),
    channel_(channel),
    exposure_(exposure),
    minStartTime_(min_start_time),
    position_(position),
    globalIndex_(global_index),
    xSet_(false),
    ySet_(false),
    zSet_(false),
    keepShutterOpen_(keep_shutter_open)
    {
    ;
    }
bool MDAEvent::KeepShutterOpen(){
    return keepShutterOpen_;
}

float MDAEvent::getMinStartTime(){
    return minStartTime_;
}
float MDAEvent::getExposure(){
    return exposure_;
}
float MDAEvent::getZ(){
    return position_.getZ();
}
float MDAEvent::getX(){
    return position_.getX();
}
float MDAEvent::getY(){
    return position_.getY();
}
void MDAEvent::setZ(float z){
    position_.setZ(z);
    zSet_ = true;
}
void MDAEvent::setX(float x){
    position_.setX(x);
    xSet_ = true;
}
void MDAEvent::setY(float y){
    position_.setY(y);
    ySet_ = true;
}

bool MDAEvent::isXSet(){
    return xSet_;
}
bool MDAEvent::isYSet(){
    return ySet_;
}
bool MDAEvent::isZSet(){
    return zSet_;
}
bool MDAEvent::isExposureSet(){
    return exposure_ != 0;
}
bool MDAEvent::isChannelSet(){
    return channel_.config_ != "";
}
bool MDAEvent::isAutoshutterSet(){
    return false;
}

// int main(){
// // Here, we instantiate MDAEvent objects and print out their attributes.
// // We also instantiate Position and Channel objects and print out their attributes.
// // We also instantiate PropertyTuple objects and print out their attributes.
// auto index = std::map<std::string, int>();
// index["t"] = 4;
// index["c"] = 0;
// index["z"] = 5;
// Channel channel = Channel("DAPI", "channel");
// float exposure = 50;
// float min_start_time = 0;
// Position position = Position();
// position.setX(0);
// position.setY(0);
// position.setZ(0);
// position.setName("dummyPos");
// int global_index = 0;
// auto mdaevent = MDAEvent(index, channel, exposure, min_start_time, position, global_index);
// }