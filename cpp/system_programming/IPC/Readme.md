## Interprocess Communication (IPC)

This module introduces the Inter Process Communication concepts in C++ 11, 14 with basics and then with ways the processes communicate to avoid race conditions, deadlocks and condition variables for processes to be in synchronisation. There is an examples to show and solve race condition issues using mutex, lock, unique_lock concepts. Example for showing synchronisation between processes using producer-consumer problem and stack implemetation.   

Then the concept of promise & future is introduced for thread communication with simple example and then for exception handling for threads and finally to synchronize between threads\(one-shot event signalling\). It is like a high-level implementation of mutex-condition variable when object state to be reflected across the threads.  

Order of files to go through  
├── mutex_1.cpp  
├── mutex_2.cpp  
├── mutex_3.cpp  
├── atomic_1.cpp  
├── deadlock_mutex.cpp  
├── race\_condition.cpp  
├── sync\_condvar.cpp  
├── sync\_stack.cpp  
├── promise\_future_1.cpp  
├── promise\_future_2.cpp  
├── promise\_future_3.cpp  


Reference/Courtesy: KPIT Ecode-Kaizen web platform
