/*
 *Author: Samuel Orekoya 
 *License: MIT
 *Description:labs on  concurrency.
 */

/*! \mainpage Lab 4 CDD
 *
 * \section Mutual Exclusion
 *
 *This lab demonstrates mutual exclusion in concurrency using semaphores.
 *We also use the clean function in the make file.
 */

#include "Semaphore.h"
#include <iostream>
#include <thread>
#include <vector>


static const int num_threads = 100;
int sharedVariable=0;


/*! \fn void updateTasks(std::shared_ptr<Semaphore> firstSem, int numUpdates)
    \brief The implementation of this fuction is to use a passed in semaphore and int to change a shared var
    \param firstSem the initialisation of a semaphore
    \param numUpdates used to decide with the loop how many times the shared variable will be updated
    \details This function safely updates a shared variable using mutual exclusion with multiple threads.
*/

void updateTask(std::shared_ptr<Semaphore> firstSem, int numUpdates){


   firstSem->Wait();
  std::cout << sharedVariable << std::endl;
  for(int i=0;i<numUpdates;i++){
    //UPDATE SHARED VARIABLE HERE!
    sharedVariable++;
  }
  firstSem->Signal(); 


}


int main(void){
  std::vector<std::thread> vt(num_threads);
  std::shared_ptr<Semaphore> aSemaphore( new Semaphore(1));
  /**< Launch the threads  */
  int i=0;
  for(std::thread& t: vt){
    t=std::thread(updateTask,aSemaphore,1000);
  }
  std::cout << "Launched from the main\n";
  /**< Join the threads with the main thread */
  for (auto& v :vt){
      v.join();
  }
  std::cout << sharedVariable << std::endl;
  return 0;
}
