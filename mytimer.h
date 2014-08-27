#ifndef PARALLEL_TIMER_H
#define PARALLEL_TIMER_H

#include <stdint.h>
#include <string.h>
#include <stdio.h>

typedef uint64_t mytime_t; 

__inline__ mytime_t _rdtsc() {
    unsigned long int lo, hi;
    __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
    return (mytime_t)hi << 32 | lo;
}

class myTimer
{
    public: 
        myTimer(): _start(0), _end(0), _cpuMHz(0) {}; 
        ~myTimer() {}; 
        void init(); 
        void start() { _start = _rdtsc(); _end = 0; };
        void stop() { _end = _rdtsc(); };
        void reset() { _start = 0; _end = 0; };
        mytime_t get_ticks() const { return (_end-_start); }
        mytime_t get_time() const; 

    private:
        mytime_t _start; 
        mytime_t _end; 
        double _cpuMHz; 
}; 

inline void myTimer::init()
{
    FILE* cpuinfo; 
    char s[100]; 
    cpuinfo = fopen("/proc/cpuinfo","r");
    while(fgets(s, 100, cpuinfo) != NULL){
        char cmp_str[8]; 
        strncpy(cmp_str, s, 7);
        cmp_str[7] = '\0'; 
        if(strcmp(cmp_str, "cpu MHz") == 0) {
            sscanf(s, "cpu MHz : %lf", &_cpuMHz);
            break; 
        }
    }
    fclose(cpuinfo); 
    reset(); 
}

inline mytime_t myTimer::get_time() const
{
    if (_cpuMHz < 0.001){
        return 0; 
    }
    return (mytime_t)((double)get_ticks()/(_cpuMHz*1000.0));
}

#endif
