#include <pthread.h>

class ThreadWrapper {
public:
	ThreadWrapper();
	virtual ~ThreadWrapper();
	bool StartInternalThread();
	void WaitForInternalThreadToExit();
protected:
	virtual void InternalThreadEntry();
private:
	static void * InternalThreadEntryFunc(void * This);
	pthread_t _thread;
};
