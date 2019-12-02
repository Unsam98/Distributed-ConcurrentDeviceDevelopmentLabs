 /*
 *Author: Samuel Orekoya 
 *License: MIT
 *Description:labs on  concurrency.
 */

/*! \mainpage Barriers Class
 *
 * \section Barriers
 *
 * This class is used to create a Barrier instance
 */

// Code:
#include "Semaphore.h"
#include "Barrier.h"
#include <iostream>
Barrier::~Barrier() {}

Barrier::Barrier(int numThreads) :numThreads(numThreads),
s1(std::shared_ptr<Semaphore>(new Semaphore(0))),
s2(std::shared_ptr<Semaphore>(new Semaphore(1))),
mutex1(std::shared_ptr<Semaphore>(new Semaphore(1))){
}


void Barrier::wait() {

    mutex1->Wait();
    i++;

    if(i == numThreads){
        s2->Wait();
        s1->Signal();
    }
    mutex1->Signal();


    s1->Wait();
    s1->Signal();

    mutex1->Wait();

    i--;

    if (i == 0){
        s1->Wait();
        s2->Signal();
    }

    mutex1->Signal();

    s2->Wait();
    s2->Signal();

}
// Barrier.cpp ends here

 

