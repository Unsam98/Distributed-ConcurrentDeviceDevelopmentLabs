/*
 *Author: Samuel Orekoya C00215885
 *License: MIT
 *Description:labs on  concurrency.
 */


/*! \mainpage Barriers Header
 *
 * \section Barriers
 *
 * Used to create a Barrier instance throught the uses of semaphores to control
 * the output of threads.
 */

/* Code: */
#include "Semaphore.h"
#pragma once
class Barrier{
    int numThreads;

    std::shared_ptr<Semaphore> s1 ;
    std::shared_ptr<Semaphore> s2 ;
    std::shared_ptr<Semaphore> mutex1 ;

  int i=0;
 public:
  Barrier(int numThreads);
  virtual ~Barrier();
  void wait();  
};


/* Barrier.h ends here */
