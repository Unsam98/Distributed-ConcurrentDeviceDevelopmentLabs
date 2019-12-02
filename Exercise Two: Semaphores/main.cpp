/*
 *Author: Samuel Orekoya 
 *License: MIT
 *Description:labs on  concurrency.
 */

/*! \mainpage Lab 2 CDD
 *
 * \section Semaphores
 *
 *This lab shows how semaphores by mutual exclusion
 *
 */

#include "Semaphore.h"
#include <iostream>
#include <thread>
#include <unistd.h>

/*! \fn void taskOne(std::shared_ptr<Semaphore> theSemaphore, int delay)
    \brief Description TaskOne functionality
    \param theSemaphore semaphore used to create mutual exclusion between two threads
    \param delay used for sleep() function
    \details This task runs first
*/

void taskOne(std::shared_ptr<Semaphore> theSemaphore, int delay){
  sleep(delay);
  std::cout <<"I ";
  std::cout << "must ";
  std::cout << "print ";
  std::cout << "first"<<std::endl;
  theSemaphore->Signal();
  
}

/*! \fn void taskTwo(std::shared_ptr<Semaphore> theSemaphore)
    \brief Description TaskTwo functionality
    \param theSemaphore semaphore used to create mutual exclusion between two threads
    \details This task runs second following the first being complete
*/


void taskTwo(std::shared_ptr<Semaphore> theSemaphore){
  theSemaphore->Wait();
  std::cout <<"This ";
  std::cout << "will ";
  std::cout << "appear ";
  std::cout << "second"<<std::endl;
}
/*! \fn int main(void)
    \brief Description of main functionality
    \details This is the main function of a semaphore
*/

int main(void){
  std::thread threadOne, threadTwo;
  std::shared_ptr<Semaphore> sem( new Semaphore);
  /**< Launch the threads  */
  int taskOneDelay=3;
  threadOne=std::thread(taskTwo,sem);
  threadTwo=std::thread(taskOne,sem,taskOneDelay);
  std::cout << "Launched from the main\n";
   /**< Wait for the threads to finish */
  threadOne.join();
  threadTwo.join();
  return 0;
}
