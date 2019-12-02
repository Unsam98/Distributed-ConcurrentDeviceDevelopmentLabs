/*
 *Author: Samuel Orekoya 
 *License: MIT
 *Description:labs on  concurrency.
 */

/*! \mainpage Lab 3 CDD
 *
 * \section Rendezvous
 *
 *This lab shows how rendezvous work this is done when two threads sync at a certain point
 *
 */


#include "Semaphore.h"
#include <iostream>
#include <thread>
#include <chrono>

/*! \fn void taskOne(std::shared_ptr<Semaphore> firstSem, std::shared_ptr<Semaphore> secondSem, int delay)
    \brief This function the "semB" will signal the first 
    \param "SemA" the first initialisation of a semaphore
    \param "SemB" the second initialisation of a semaphore
    \param delay used for sleep() function
    \details This task runs first
*/


void taskOne(std::shared_ptr<Semaphore> semA,std::shared_ptr<Semaphore>  semB, int delay){
  std::this_thread::sleep_for(std::chrono::seconds(delay));
  std::cout <<"Task One has arrived! "<< std::endl;
  
  //This is the R point !
  semB-> Signal();
  semA-> Wait();
  //THIS IS THE RENDEZVOUS POINT!
  
  std::cout << "Task One has left!"<<std::endl;
}

/*! \fn void taskTwo(std::shared_ptr<Semaphore> firstSem, std::shared_ptr<Semaphore> secondSem, int delay)
    \brief This function the "semA" will signal the second 
    \param "SemA" the first initialisation of a semaphore
    \param "SemB" the second initialisation of a semaphore
    \param delay used for sleep() function
    \details This task runs first
*/


void taskTwo(std::shared_ptr<Semaphore> semA, std::shared_ptr<Semaphore> semB, int delay){
  std::this_thread::sleep_for(std::chrono::seconds(delay));
  std::cout <<"Task Two has arrived "<<std::endl;
  //THIS IS THE RENDEZVOUS POINT!
  
  semA-> Signal();
  semB-> Wait();
  
  std::cout << "Task Two has left "<<std::endl;
}


/*! \fn int main(void)
    \brief Description of main functionality
    \details This is the main function of a semaphore, it creates two threads and two semaphores and the runs the two threads
*/

int main(void){
  std::thread threadOne, threadTwo;
  std::shared_ptr<Semaphore> sem1( new Semaphore);
  std::shared_ptr<Semaphore> sem2( new Semaphore);
  int taskOneDelay=5;
  int taskTwoDelay=1;
  /**< Launch the threads  */
  threadOne=std::thread(taskTwo,sem1,sem2,taskTwoDelay);
  threadTwo=std::thread(taskOne,sem1,sem2,taskOneDelay);
  std::cout << "Launched from the main\n";
  threadOne.join();
  threadTwo.join();
  return 0;
}
