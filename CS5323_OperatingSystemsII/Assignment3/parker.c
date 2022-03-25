// Usage Instructions:
// make p && ./p

#include <stdio.h>     // printf()
#include <string.h>    //strlen()
#include <ctype.h>     // toLower()
#include <pthread.h>   // threads
#include <semaphore.h> // semaphores
#include <assert.h>    // assert()
#include <stdlib.h>    // malloc()


#include <sys/ipc.h>




pthread_mutex_t reader_count_mutex;
static int read_count = 0;
static int counter = 0;

const int QUEUE_SIZE = 20;
int intArray[QUEUE_SIZE];
int head = 0;
int tail = -1;
int count = 0;

void relax_and_wait();
void *reader_thread();
void *writer_thread();

sem_t *in_cs;
sem_t *mom;

#define WRITE "/write"
sem_t *writer;

int main()
{

    sem_unlink(WRITE);

    writer = sem_open(WRITE, IPC_CREAT, 0660, 10);
    int value;

    // sem_init(&my_semaphore, 0, 10);
    sem_getvalue(writer, &value);
    printf("The initial value of the semaphore is %d\n", value);

    int num_readers = 10;
    int k = (int)(num_readers / 2);
    pthread_t readers[num_readers];
    pthread_t writer;

    for (int i = 0; i < k; i++)
    {
        pthread_create(&readers[i], NULL, reader_thread, i);
    }

    pthread_create(&writer, NULL, writer_thread, NULL);

    for (int i = k; i < num_readers; i++)
    {
        pthread_create(&readers[i], NULL, reader_thread, i);
    }

    // waits for all of the threads to finish executing
    pthread_exit(NULL);
    return 0;
}

void *reader_thread(int i)
{
    // Reader acquire the lock before modifying read_count
    pthread_mutex_lock(&reader_count_mutex);
    read_count++;

    // If this is the first reader, then it will block the writer
    if (read_count == 1)
    {
        // sem_wait(in_cs);
        // sem_wait(mom);
    }

    pthread_mutex_unlock(&reader_count_mutex);

    relax_and_wait();

    // Reader acquire the lock before modifying read_count
    pthread_mutex_lock(&reader_count_mutex);
    read_count--;

    // if this is the last reader, it will signal the writer
    if (read_count == 0)
    {
        // sem_post(in_cs);
    }

    pthread_mutex_unlock(&reader_count_mutex);

    printf("Reader %d done. Read cnt as %d\n", i, counter);

    return NULL;
}

void *writer_thread()
{
    while (1)
    {
        sem_wait(in_cs);
        if (counter != 25000)
        {
            counter++;
        }
        else
        {
            printf("Writer done. Count %d\n", counter);
            sem_post(in_cs);

            return NULL;
        }
        sem_post(in_cs);
    }
}

void relax_and_wait()
{
    int i;
    int j;
    for (i = 0; i < 250000000; i++)
        i = i;
    j = counter;
}


 // gets thread # input and forces a specific range
    // printf("Please specify the number of threads between 1 and 4.\n");
    // scanf("%d", &numThreads);
    // assert(numThreads >= 1 && numThreads <= 4);
    // printf("\n\n{%d} threads processing file: %s\n", numThreads, filePath);
