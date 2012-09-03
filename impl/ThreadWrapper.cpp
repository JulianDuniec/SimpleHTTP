#include "../headers/ThreadWrapper.h"

ThreadWrapper::ThreadWrapper() {/* empty */}
ThreadWrapper::~ThreadWrapper() {/* empty */}

/** Returns true if the thread was successfully started, false if there was an error starting the thread */
bool ThreadWrapper::StartInternalThread()
{
   return (pthread_create(&_thread, NULL, InternalThreadEntryFunc, this) == 0);
}

/** Will not return until the internal thread has exited. */
void ThreadWrapper::WaitForInternalThreadToExit()
{
   (void) pthread_join(_thread, NULL);
}

/** Implement this method in your subclass with the code you want your thread to run. */
void ThreadWrapper::InternalThreadEntry() {

}

void * ThreadWrapper::InternalThreadEntryFunc(void * This) {
   ((ThreadWrapper *)This)->InternalThreadEntry(); 
   return NULL;
}
