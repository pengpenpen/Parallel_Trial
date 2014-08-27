#include <iostream>
#include <stdlib.h>

#include "mytimer.h"

int main()
{
    myTimer t; 
    t.init(); 
    t.start(); 
    long int tmp = 0; 
    for(int i = 0; i < 100000; ++ i)
        tmp += rand();  
    t.stop(); 
    std::cout << "Total time is " << t.get_time() << "ns" << std::endl; 

    return 0; 
}
