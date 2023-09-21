#include <iostream>
#include <vector>

#include "MDAEvent.h"
#include "StdoutEventNotifier.h"
using namespace std;

void StdoutEventNotifier::notifyStart(MDAEvent& event){
    std::cout << "Start event" << std::endl;
}

void StdoutEventNotifier::notifyPauseToggled(bool paused){
    std::cout << "PauseToggle event" << std::endl;
}

void StdoutEventNotifier::notifyCanceled(MDAEvent& event){
    std::cout << "Canceled event" << std::endl;
}

void StdoutEventNotifier::notifyFinished(MDAEvent& event){
    std::cout << "Finished event" << std::endl;
}

void StdoutEventNotifier::notifyFrameReady(MDAEvent& event, std::map<std::string, std::string> &metadata, void* image){
    std::cout << "frameReady event" << std::endl;
}


// int main()
// {
//     auto notifier = StdoutEventNotifier();
// // create an event. 
//     auto index = std::map<std::string, int>();
//     index["t"] = 4;
//     index["c"] = 0;
//     index["z"] = 5;
//     Channel channel = Channel("FITC", "channel");
//     float exposure = 50;
//     float min_start_time = 8;
//     Position position = Position();
//     position.setZ(2);
//     position.setName("dummyPos");
//     int global_index = 0;
//     bool keep_shutter_open = false;
//     Action action = AcquireImage;
//     auto event = MDAEvent(index, channel, exposure, min_start_time, position, action, global_index, keep_shutter_open);


// // 
//     notifier.notifyStart(event);
//     notifier.notifyPauseToggled(true);
//     notifier.notifyCanceled(event);
//     notifier.notifyFinished(event);
//     std::map<std::string, std::string> metadata;
//     void* pixels = nullptr;
//     notifier.notifyFrameReady(event, metadata, pixels);
// }