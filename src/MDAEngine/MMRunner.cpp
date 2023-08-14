#include "MMRunner.h"

#include <algorithm>
#include <cassert>
#include <chrono>
#include <cstring>
#include <fstream>
#include <set>
#include <sstream>
#include <vector>
#include <iostream>
#include <thread>


#ifndef _WINDOWS
// Needed on Unix for getcwd() and gethostname()
#include <pwd.h>
#include <sys/types.h>
#include <unistd.h>
#else
// for _getcwd
#include <direct.h>
#endif

using namespace std;

CMMRunner::CMMRunner():
running_(false),
paused_(false),
pausedTime_(0),
pausedInterval_(0.1),
cancelled_(false)
{
    // core_ = new CMMCore();
    ofstream MyFile("test123.txt");
    MyFile << "Files can be tricky, but it is fun enough!";
    // get current time in seconds
    resetTimer();
}

float CMMRunner::getCurrentTime()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()).count()/1000.0;
}
void sleep_for(float milliseconds)
{
    long long int microsec = (long long int)(milliseconds*1000.0);
    std::this_thread::sleep_for(std::chrono::microseconds(microsec));
}

void CMMRunner::resetTimer()
{
    startTime_ = getCurrentTime();
}

CMMRunner::~CMMRunner()
{
    try
    {
        // reset();
    }
    catch (...)
    {
        // LOG_ERROR(coreLogger_) << "Exception caught in CMMRunner desructor.";
    }
    // Not sure if we should delete the sequence_ or not. It is so because it is getting passed from 
    // outside and so should be deleted outside as well ?
    // delete sequence_;
}

float CMMRunner::timeElapsed()
{
    return getCurrentTime() -startTime_;
}
bool CMMRunner::isRunning()
{
    return running_;
}

bool CMMRunner::isPaused()
{
    return paused_;
}

void CMMRunner::cancel()
{
    cancelled_ = true;
    pausedTime_ = 0;
}
void CMMRunner::togglePause()
{
    if (isRunning()){
        paused_ = !paused_;
    }
}


bool CMMRunner::checkCanceled()
{
    // TODO: more logic. For now, just check the flag. in pymcoreplus, it is reset to false. 
    auto cancelled = cancelled_;
    cancelled_ = false;
    return cancelled;
}

/**
Wait until the event's min start time, checking for pauses cancellations.
Parameters
----------
event : MDAEvent The event to wait for.

Returns
-------
bool
    Whether the MDA was cancelled while waiting.
*/
bool CMMRunner::waitUntilEvent(MDAEvent& event)
{
    if (!isRunning())
        return false;
    else if (checkCanceled())
        return true;
    while (isPaused() && (!cancelled_))
    {
        pausedTime_ += pausedInterval_;
        // now, sleep for pausedInterval_ seconds
        sleep_for(pausedInterval_*1000);
        if (checkCanceled())
        {
            return true;
        }

    }
    if (event.getMinStartTime())
    {
        auto go_at = event.getMinStartTime() + pausedTime_;
    // We need to enter a loop here checking paused and canceled.
    // otherwise you'll potentially wait a long time to cancel
        auto to_go = go_at - timeElapsed();
        while (to_go > 0)
        {
            while (paused_ &&  !cancelled_)
            {
                pausedTime_ += pausedInterval_;  // fixme: be more precise
                to_go += pausedInterval_;
                // now, sleep for pausedInterval_ seconds
                sleep_for(pausedInterval_*1000);
            }
            if (cancelled_)
                break;
            
            // sleep for minimum of 0.5 seconds and to_go
            auto sleepdur =min(to_go*1000, (float)(500.0));
            sleep_for(sleepdur);

            to_go = go_at - timeElapsed();

            
        }
    }
    
// check canceled again in case it was canceled
// during the waiting loop
return checkCanceled();
}
void CMMRunner::prepareToRun()
{
    running_ = true;
    paused_ = false;
    pausedTime_ = 0;
    resetTimer();
}

void CMMRunner::run(std::vector<MDAEvent>& events)
{
    prepareToRun();
    for (int i = 0; i < events.size(); i++)
    {
        runEvent(events[i]);
    }
   
finishRun();
}

/**
* Run a single event.
* Parameters
* ----------
* event : MDAEvent
* The event to run.
* Returns
* -------
* bool
* Whether the MDA was cancelled while running.
*/
bool CMMRunner::runEvent(MDAEvent& event)
{
    if (waitUntilEvent(event)||  !running_)
    {
        return true;
    }
    setupEvent(event);
    auto output = execEvent(event);
    return false;
}
unsigned char* CMMRunner::execEvent(MDAEvent& event)
{
    unsigned char* output;
    return output;
}
void CMMRunner::setupEvent(MDAEvent& event)
{
        // if event.keep_shutter_open:
        //         ...
    auto x_pos = event.getX();
    auto y_pos = event.getY();
    if (event.isXSet() || event.isYSet())
    {
        setEventPosition(event);
    }
    if (event.isZSet())
    {
        setEventZ(event);
    }
    if (event.isChannelSet())
    {
        setEventChannel(event);
    }
    if (event.isExposureSet())
    {
        setEventExposure(event);
    }
    if (event.isAutoshutterSet())
    {
        setEventAutoshutter(event);
    }

}

void CMMRunner::finishRun()
{
    running_ = false;
    cancelled_ = false;
}

// engine related
void CMMRunner::setEventZ(MDAEvent& event)
{
    ;
}
void CMMRunner::setEventChannel(MDAEvent& event)
{
    ;
}
void CMMRunner::setEventExposure(MDAEvent& event)
{
    ;
}
void CMMRunner::setEventAutoshutter(MDAEvent& event)
{
    ;
}
void CMMRunner::setEventPosition(MDAEvent& event)
{
    float x_pos;
    float y_pos;
    if (event.isXSet())
    {
        x_pos = event.getX();
    }
    else{
        // TODO: call mmcore to get current position
        x_pos = 0.0;
    }

    if (event.isYSet())
    {
        y_pos = event.getY();
    }
    else{
        // TODO: call mmcore to get current position
        y_pos = 0.0;
    
    }
    // TODO: call mmcore to set position
    // self._mmc.setXYPosition(x_pos, y_pos);
}

// int main(int argc, char **argv)
// {
// //  auto var = CMMRunner();
// }
