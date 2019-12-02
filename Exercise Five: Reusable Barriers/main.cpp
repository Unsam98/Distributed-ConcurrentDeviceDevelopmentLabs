 /*
 *Author: Samuel Orekoya 
 *License: MIT
 *Description:labs on  concurrency.
 */

/*! \mainpage Lab 5 CDD
 *
 * \section Barriers
 *
 * This lab will show how reusable barriers can be used to
 * to help concurrency by making one section of a threads run first then the second.
 * 
 *Output will be all the A's being printed first with an int beside it,
 * then all the B's with the int beside it, the loop then incremenets and the same continues to happen
 * again with a new integer.
 */


#include "Barrier.h"
#include <iostream>
#include <thread>
#include <vector>


static const int num_threads = 100;
int sharedVariable=0;


/*! \fn void barrierTask(std::shared_ptr<Barrier> theBarrier, int numLoops)
    \brief This function a passed in Barrier and an integer variable is used to control the amount of interation occurs.
    \param theBarrier is the implementation of the barrier class which which will control the output of the threads
    \param numLoops used to decide with the loop how many times it will increment
    \details This function shows how you can use a barrier to control the output of multiple threads in stages.
*/

void barrierTask(std::shared_ptr<Barrier> theBarrier, int numLoops){

  for(int i=0;i<numLoops;++i){
    theBarrier->wait();
    std::cout << "A"<< i;
    //Barrier
    theBarrier->wait();
    std::cout<< "B" << i;
  }
  

}


int main(void){
  std::vector<std::thread> vt(num_threads);
  std::shared_ptr<Barrier> aBarrier( new Barrier(num_threads));
  
  /**< Launch the threads  */
  
  int i=0;
  for(std::thread& t: vt){
    t=std::thread(barrierTask,aBarrier,10);
  }
  
  /**< Join the threads with the main thread */
  
  for (auto& v :vt){
      v.join();
  }
  std::cout << sharedVariable << std::endl;
  return 0;
}
