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
    
    // void teardownEvent(MDAEvent& event);
    void resetTimer();
    float timeElapsed();
    bool checkCanceled();
    void finishRun();
    void prepareToRun();
    float getCurrentTime();
    // engine related
    void setEventPosition(MDAEvent& event);
    void setEventZ(MDAEvent& event);
    void setEventExposure(MDAEvent& event);
    void setEventChannel(MDAEvent& event);
    void setEventAutoshutter(MDAEvent& event);

    // from mmcore
    unsigned getImageWidth() { return core_->getImageWidth(); };
    unsigned getImageHeight() { return core_->getImageHeight(); };
    unsigned getBytesPerPixel() { return core_->getBytesPerPixel(); };
    unsigned getImageBitDepth() { return core_->getImageBitDepth(); };

private:
    CMMCore* core_;
    bool running_;
    bool paused_; 
    float pausedTime_;
    float pausedInterval_;
    bool cancelled_; 
    float startTime_;
};

#endif //_MMRunner_H_
