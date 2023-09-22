#include "EventDataManager.h"
#include <stdexcept>
#include <iostream>
using namespace std;

EventMetaData::EventMetaData(int event_id, EventState state){
    eventId_ = event_id;
    state_ = state;
}

void EventMetaData::updateState(EventState state){
    state_ = state;
}

EventDataManager::EventDataManager(){
}

void EventDataManager::notifyStart(MDAEvent& event){
    EventMetaData* eventMetaData = new EventMetaData(event.getGlobalIndex(), Start);
    if (eventsState_.find(event.getGlobalIndex()) != eventsState_.end())
    {
        throw std::runtime_error("Event already exists");
    }
    eventsState_.insert(std::pair<int, EventMetaData&>(event.getGlobalIndex(), *eventMetaData));
}

void EventDataManager::notifyPauseToggled(MDAEvent& event, bool paused){
    if (eventsState_.find(event.getGlobalIndex()) == eventsState_.end())
    {
        throw std::runtime_error("Event does not exist");
    }
    EventMetaData& eventMetaData = eventsState_.at(event.getGlobalIndex());
    if (paused){
        eventMetaData.updateState(Paused);
    }
    else{
        eventMetaData.updateState(Start);
    }
}

void EventDataManager::notifyCanceled(MDAEvent& event){
    if (eventsState_.find(event.getGlobalIndex()) == eventsState_.end())
    {
        throw std::runtime_error("Event does not exist");
    }
    EventMetaData& eventMetaData = eventsState_.at(event.getGlobalIndex());
    eventMetaData.updateState(Canceled);
}

void EventDataManager::notifyFinished(MDAEvent& event){
    if (eventsState_.find(event.getGlobalIndex()) == eventsState_.end())
    {
        throw std::runtime_error("Event does not exist");
    }
    EventMetaData& eventMetaData = eventsState_.at(event.getGlobalIndex());
    eventMetaData.updateState(Finished);
}

void EventDataManager::notifyFrameReady(MDAEvent& event, std::map<std::string, std::string> &metadata, void* image){
    auto idx_globalindex =event.getGlobalIndex(); 
    if (eventsState_.find(idx_globalindex) == eventsState_.end())
    {
        throw std::runtime_error("Event does not exist");
    }
    EventMetaData& eventMetaData = eventsState_.at(idx_globalindex);
    eventMetaData.updateState(FrameReady);
}

EventState EventDataManager::getState(int event_id){
    if (eventsState_.find(event_id) == eventsState_.end())
    {
        throw std::runtime_error("Event does not exist");
    }
    EventMetaData& eventMetaData = eventsState_.at(event_id);
    return eventMetaData.getState();
}

// int main(){
//     EventDataManager eventDataManager = EventDataManager();
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
//     bool keep_shutter_open = false;
//     Action action = AcquireImage;
//     auto event0 = MDAEvent(index, channel, exposure, min_start_time, position, action, 0, keep_shutter_open);
//     auto event1 = MDAEvent(index, channel, exposure, min_start_time, position, action, 1, keep_shutter_open);

//     eventDataManager.notifyStart(event0);
//     eventDataManager.notifyStart(event1);
//     std::cout << eventDataManager.getState(0) << " " << eventDataManager.getState(1) << std::endl;
//     eventDataManager.notifyPauseToggled(event0, true);
//     std::cout << eventDataManager.getState(0) << " " << eventDataManager.getState(1) << std::endl;
    
//     eventDataManager.notifyPauseToggled(event0, false);

//     eventDataManager.notifyFinished(event1);
//     std::cout << eventDataManager.getState(0) << " " << eventDataManager.getState(1) << std::endl;
//     return 0;
// }