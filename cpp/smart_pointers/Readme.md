smart_pointers scripts explains the use of shared_ptr using MyWidget class which has a label and parent, child ptrs to connect between widget objects.  
There is one-way where only parent side traversal is possible.  
There is a two-way where both parent and child way traversal is possible. This causes a cyclic redundancy issue with using shared_ptr for both.  
To solve above problem, we use weak_ptr in final script which assigns weak_ptr for child.  
The above scripts are validated with valgrind for memory leak checks.  


Reference/Courtesy: KPIT Ecode-Kaizen web platform  
