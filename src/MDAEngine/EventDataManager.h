#ifndef _event_data_manager_H
#define _event_data_manager_H
#ifdef _MSC_VER
// We use exception specifications to instruct SWIG to generate the correct
// exception specifications for Java. Turn off the warnings that VC++ issues by
// the mere use of exception specifications (which VC++ does not implement).
#pragma warning(disable : 4290)
#endif
#include "BaseEventNotifier.h"
#include "MDAEvent.h"
#include <map>

class MDAEvent;

class EventMetaData{
    public:
        EventMetaData(int event_id, EventState state);
        void updateState(EventState state);
        void updateImage(void* image);
        EventState getState(){return state_;};
        void* getImage(){return image_;};
    private:
        int eventId_;
        EventState state_;
        void* image_;
};

class EventDataManager : public BaseEventNotifier{
    public:
        EventDataManager();
        bool notifyStart(MDAEvent& event);
        bool notifyPauseToggled(MDAEvent& event, bool paused);
        bool notifyCanceled(MDAEvent& event);
        bool notifyFinished(MDAEvent& event);
        bool notifyFrameReady(MDAEvent& event, std::map<std::string, std::string> &metadata, void* image);

        // Fetching data from acquisition
        EventState getState(int event_id);
        void* getImage(int event_id);
        double secondsTaken();
    private:
    std::map<int, EventMetaData&> eventsState_;
};

#endif // _event_data_manager_H