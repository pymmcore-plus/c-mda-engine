#ifndef _MMRunner_H_
#define _MMRunner_H_

#ifdef _MSC_VER
// We use exception specifications to instruct SWIG to generate the correct
// exception specifications for Java. Turn off the warnings that VC++ issues by
// the mere use of exception specifications (which VC++ does not implement).
#pragma warning(disable : 4290)
#endif
#include "MDAEvent.h"
#include <vector>

#include "../MMCore.h"
#include "BaseEventNotifier.h"

class MDAEvent;
class CMMCore;

class CMMRunner
{
public:
    CMMRunner();
    ~CMMRunner();

    bool isRunning();
    bool isPaused();
    void cancel();
    void togglePause();
    void run(std::vector<MDAEvent> &events);
    void* runEvent(MDAEvent& event);
    bool waitUntilEvent(MDAEvent& event);
    void setupEvent(MDAEvent& event);
    void* execEvent(MDAEvent& event);
    // event related 
    EventState getEventState(int event_id);
    
    // void teardownEvent(MDAEvent& event);
    void resetTimer();
    double timeElapsed();
    bool checkCanceled();
    void finishRun();
    void prepareToRun();
    double getCurrentTime();
    // engine related
    void setEventPosition(MDAEvent& event);
    void setEventZ(MDAEvent& event);
    void setEventExposure(MDAEvent& event);
    void setEventChannel(MDAEvent& event);
    void setEventAutoshutter(MDAEvent& event);
    void loadSystemConfiguration(std::string config_file="MMConfig_demo.cfg");

    // from mmcore
    unsigned getImageWidth() { return core_->getImageWidth(); };
    unsigned getImageHeight() { return core_->getImageHeight(); };
    unsigned getBytesPerPixel() { return core_->getBytesPerPixel(); };
    unsigned getImageBitDepth() { return core_->getImageBitDepth(); };

private:
    CMMCore* core_;
    bool running_;
    bool paused_; 
    double pausedTime_;
    double pausedInterval_;
    bool cancelled_; 
    double startTime_;
    BaseEventNotifier* notifier_;
};

#endif //_MMRunner_H_
