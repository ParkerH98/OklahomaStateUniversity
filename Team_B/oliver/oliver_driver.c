#include "oliver_linkedListExperiment.c"
#include "oliver_threads.c"

// This function runs two tests.

// Important note:  The EmployeeStructure and employeeStructure data-structures are the same.
//                  They are the same thing, just with different names so this Driver could be ready
//                  in time. Dynamic Memory Allocation doesn't like header files.
void main(){
    LLTest();
    printf("\n\n\n");
    SSThreadsTest();
}