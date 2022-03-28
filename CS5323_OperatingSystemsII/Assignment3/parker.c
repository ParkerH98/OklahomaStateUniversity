// Usage Instructions:
// make p && ./p

//CSX USAGE
//gcc parker.c -o p -pthread -lrt -w
//./p

// Parker Hague

#include <stdio.h>     // printf()
#include <string.h>    //strlen()
#include <ctype.h>     // toLower()
#include <pthread.h>   // threads
#include <semaphore.h> // semaphores
#include <assert.h>    // assert()
#include <stdlib.h>    // malloc()
#include <sys/ipc.h>

void relax_and_wait();
void *reader_thread();
void *writer_thread();

sem_t in_cs;
sem_t reader_sem;
pthread_mutex_t reader_count_mutex;
static int read_count = 0;
static int counter = 0;
int *readers_allowed_ptr;
int *read_count_ptr;
int num_readers;

int main()
{
    // gets thread # input and forces a specific range
    printf("Enter the number of readers between [1 - 14].\n");
    scanf("%d", &num_readers);
    assert(num_readers >= 1 && num_readers <= 14);

    // gets value of half the readers
    int k = (int)(num_readers / 2);
    if (k == 0)
    {
        // handles case where num_readers = 1
        k = 1;
    }

    // this is how many readers will be allowed to execute their thread before the writer is given focus
    int readers_allowed = k;
    if (readers_allowed != 1)
    {
        // all the cases where num_readers > 2
        readers_allowed++;
    }

    // reader/writer threads
    pthread_t readers[num_readers];
    pthread_t writer;

    // allows the k value to be read globally
    readers_allowed_ptr = malloc(readers_allowed * sizeof(int));
    *readers_allowed_ptr = readers_allowed;

    // inits in_cs semaphore and sets value to 1 so the writer is given initial priority
    sem_init(&in_cs, 0, 1);
    // inits reader_sem semaphore and sets value to readers_allowed
    sem_init(&reader_sem, 0, readers_allowed);

    // first half of the readers
    for (int i = 0; i < k; i++)
    {
        pthread_create(&readers[i], NULL, reader_thread, (void *)(unsigned long long)(i));
    }

    pthread_create(&writer, NULL, writer_thread, NULL);

    // second half of the readers
    for (int i = k; i < num_readers; i++)
        pthread_create(&readers[i], NULL, reader_thread, (void *)(unsigned long long)(i));

    // waits for all of the threads to finish executing
    pthread_exit(NULL);

    free(readers_allowed_ptr);
    free(read_count_ptr);
    return 0;
}

/*
This is the primary function that each reader will execute.
The readers will be able to freely execute this function
until blocked by the reader_sem. The reader_sem will allow
approximately half the readers to enter before blocking
them and signaling the writer to do some work. Once most
of the readers have left, the reader_sem is signaled to
allow another to enter.

@Params: int i
Return: void
*/
void *reader_thread(int i)
{
    // allows the readers to enter until readers_allowed has been reached
    sem_wait(&reader_sem);

    /* ------------------------- start critical section ------------------------- */
    // locks critical section for read_count
    pthread_mutex_lock(&reader_count_mutex);

    // incremented for each reader so we know when the first reader has arrived so we can stop the writer
    read_count++;
    read_count_ptr = read_count;

    // if it's the first reader then block the writer (if count not reached)
    if (read_count == 1)
    {
        if (counter != 25000)
        {
            // printf("Blocking Writer!\n");
            sem_wait(&in_cs);
        }
    }
    // unlocks critical section for read_count
    pthread_mutex_unlock(&reader_count_mutex);
    /* -------------------------- end critical section -------------------------- */

    // gets current values of semaphores to check if mutual exclusion is upheld
    int in_cs_val;
    int mom_val;
    sem_getvalue(&in_cs, &in_cs_val);
    sem_getvalue(&reader_sem, &mom_val);
    if (in_cs_val > 1 && mom_val > 0)
    {
        printf("WRITER ALREADY IN CRITICAL SECTION\n\n");
    }

    // psuedo read operation
    relax_and_wait();

    // if max num of allowed readers is reached then signal the writer to start
    if (read_count == *readers_allowed_ptr && counter != 25000)
    {
        // printf("Max Readers! Allowing Writer!\n");
        sem_post(&in_cs);
    }

    /* ------------------------- start critical section ------------------------- */
    // locks critical section for read_count
    pthread_mutex_lock(&reader_count_mutex);

    // decrements the read count so we know when the last reader is leaving and we can start the writer again
    read_count--;
    read_count_ptr = read_count;

    // allows the writer to write each time a reader leaves
    sem_post(&in_cs);
    sem_post(&reader_sem);

    // if the last reader is leaving then allow the writer to start and allow readers to ask for lock again
    if (read_count == 1)
    {
        // printf("Allowing Writer\n");
        if (counter == 25000)
        {
            sem_post(&reader_sem);
        }
        else
        {
            sem_post(&in_cs);
            sem_post(&reader_sem);
        }
    }

    // unlocks critical section for read_count
    pthread_mutex_unlock(&reader_count_mutex);
    /* -------------------------- end critical section -------------------------- */

    printf("Reader %d done. Read cnt as %d\n", i, counter);
    return NULL;
}

/*
This is the primary function that the writer will execute.
The writer will constantly loop and ask for the lock to be
able to write. Once the writer gets the lock it loops once
and gives up the lock. The writer will acquire the lock again
if a reader is not asking for it.

@Params: none
Return: void
*/
void *writer_thread()
{
    while (1)
    {
        // stops writer until signaled by the reader
        sem_wait(&in_cs);

        if (counter != 25000)
            counter++;
        else
        {
            // allows another reader to enter reader_thread() and then exits
            printf("Writer done. Count %d\n", counter);
            sem_post(&reader_sem);
            pthread_exit(NULL);
        }

        // the writer will signal the in_cs semaphore every time until one the conditions is met.
        // this block is primarily responsible for force stopping the writer and allowing a reader to do work
        // if (!(counter % 3000 == 0) || (read_count_ptr == *readers_allowed_ptr) || read_count_ptr == 0 || read_count_ptr == 1)
        // {
        //     sem_post(&in_cs);
        // }

        if (!(counter % 2000 == 0) || read_count_ptr == 0)
        {
            sem_post(&in_cs);
        }
    }
}

/*
Function to simulate reading.

@Params: none
Return: void
*/
void relax_and_wait()
{
    int i;
    int j;
    for (i = 0; i < 250000000; i++)
        i = i;
    j = counter;
}
