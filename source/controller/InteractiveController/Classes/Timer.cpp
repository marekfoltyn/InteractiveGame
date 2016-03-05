#ifndef Timer_h
#define Timer_h

#include <chrono>

/**
 * Helper classes and methods used in the game.
 */
namespace Util{
    
/**
 * Time-tracking class. Works like a stopwatch:
 * reset() starts the timing and elapsed() gets
 * the elapsed time since the reset() was called
 */
class Timer {
    typedef std::chrono::high_resolution_clock high_resolution_clock;
    typedef std::chrono::milliseconds milliseconds;
public:

    /**
     * create a Tieme
     * @param run when true, the timing will start immediately
     */
    explicit Timer(bool run = false)
    {
        if (run)
            reset();
    }
    
    /**
     * start a new timing from now
     */
    void reset()
    {
        _start = high_resolution_clock::now();
    }
    
    /**
     * get elapsed time since the reset() or Timer(true) was called
     */
    milliseconds elapsed() const
    {
        return std::chrono::duration_cast<milliseconds>(high_resolution_clock::now() - _start);
    }
    
private:
    high_resolution_clock::time_point _start;
};
    
}

#endif
