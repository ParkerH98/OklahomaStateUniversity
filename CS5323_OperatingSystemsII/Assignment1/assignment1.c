// Usage Instructions:
// make p && ./p

#include <stdio.h> // printf()
#include <string.h> //strlen()
#include <ctype.h> // toLower()
#include <pthread.h> // threads
#include <assert.h>  // assert()

// struct that will serve as a dictionary for each histogram
typedef struct CharDictionary
{
    int key;
    int value;
} CharDictionary;

// Struct that will be the carried around by each thread. Contains a 
// copy of a dictionary that will serve as the histogram for each line.
// The struct also has an id that will be used to control the printing order.
typedef struct Histogram
{
    CharDictionary histogramList[26];
    int id;
} Histogram;

void readFile();
void convertToLowerCase(char *string);
void initializeHistogram();
void printHistogram(Histogram *histogram, char line[]);
void *threadTask();
void populateHistogram(Histogram *histogram, char line[]);

FILE *f;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// keeps track of which line is read on the file
int readCount = 1;
// keeps track of which line has been printed on the console
int printCount = 1;

int main()
{
    char filePath[512];
    int numThreads = 0;

    printf("Please enter a filepath to read from.\n");
    fgets(filePath, sizeof(filePath), stdin);
    filePath[strlen(filePath) - 1] = '\0';

    // gets thread # input and forces a specific range
    printf("Please specify the number of threads between 2 and 4 inclusive.\n");
    scanf("%d", &numThreads);
    assert(numThreads > 1 && numThreads <= 4);

    printf("\n\n{%d} threads processing file at path: %s\n", numThreads, filePath);

    // open file for reading
    f = fopen(filePath, "r");

    // an array of threads representing the thread pool
    pthread_t thread_pool[numThreads];

    // each created thread will run the threadTask() which will infinitely loop and try to get the mutex lock
    for (int i = 0; i < numThreads; i++)
    {
        pthread_create(&thread_pool[i], NULL, threadTask, NULL);
    }

    // waits for all of the threads to finish executing
    pthread_exit(NULL);
    return 0;
}


/*
---------------------------------------------------------
This is the main thread function that is ran by the threads
in the thread pool. In this function each thread will enter
the loop and initialize its Histogram. Then it will read the 
next available line in the file if it exists. Then the thead
will enter a secondary waiting loop where it will only get the
mutex and print to console if it is its turn. The printing
order is based off of the order that the lines were read
from the input file. After the thread has printed, it will
give up its mutex and the next thread will grab it and print.
This process will continue until each line in the text file 
has been processed.

Params: none
Return: void
*/
void *threadTask()
{
    char line[512];
    Histogram histogram;

    while (1)
    {
        // sets up the initial/restarted histogram each iteration
        initializeHistogram(&histogram);

        // reads the line from the file
        if (fgets(line, 512, f) != NULL)
        {
            // saves the currently read line as the hostogram's id so that priority can be used for printing the histograms
            histogram.id = readCount;
            readCount++;
        }
        else
        {
            // if there's no line to read then the thread gives up the mutex lock and exits
            pthread_mutex_unlock(&mutex);
            return NULL;
        }

        // get rid of ending \n from fgets
        if (line[strlen(line) - 1] == '\n')
        {
            line[strlen(line) - 1] = '\0';
        }

        convertToLowerCase(line);

        // evalutes the line read and creates the histogram from it
        populateHistogram(&histogram, line);

        // Once a line has been read and a thread has finished creating its histogram it will sit and wait in this
        // loop until its turn to print the histogram. The priint order is based on the histogram's id that's given at
        // the time of reading the line
        while (1)
        {
            if (histogram.id == printCount)
            {
                // mutex is locked during the printing process
                pthread_mutex_lock(&mutex);

                // printf("ThreadID: %d\n", pthread_self());

                printHistogram(&histogram, line);
                printCount++;

                // after the printing, the mutex is returned
                pthread_mutex_unlock(&mutex);
                break;
            }
        }
    }
    return NULL;
}

/*
---------------------------------------------------------
Populates the passed Histogram with the occurrances of the 
characters in the passed char[] 'line'.

Params: pointer to char[]
Return: void
*/
void populateHistogram(Histogram *histogram, char line[])
{
    int i = 0;
    while (line[i])
    {
        char c = line[i];
        histogram->histogramList[c - 97].value++;
        i++;
    }
}

/*
---------------------------------------------------------
Converts each char of the the passed char[] from an uppercase
character to lowercase. Doing this allows the dictionary to
be able to maintain only lowercase values opposed to both 
upper and lower. 

Params: pointer to char[]
Return: void
*/
void convertToLowerCase(char *string)
{
    int i = 0;
    char c;

    while (string[i])
    {
        string[i] = tolower(string[i]);
        i++;
    }
}

/*
---------------------------------------------------------
Fills the passed Histogram with the English alphabet as keys
and initializes each value to be 0, the number of occurrances.

Params: Histogram *
Return: void
*/
void initializeHistogram(Histogram *histogram)
{
    for (int i = 97; i < 123; i++)
    {
        histogram->histogramList[i - 97].key = i;
        histogram->histogramList[i - 97].value = 0;
    }
}

/*
---------------------------------------------------------
Prints the histogram that's passed to the function.

Params: Histogram * & char[]
Return: void
*/
void printHistogram(Histogram *histogram, char line[])
{
    // prints line number that the line belongs to from the read file
    printf("%d %s\n", printCount, line);

    printf("{");

    for (int i = 0; i < 26; i++)
    {
        if (i == 25)
        {
            printf("'%c': %d}", histogram->histogramList[i].key, histogram->histogramList[i].value);
            continue;
        }

        printf("'%c': %d, ", histogram->histogramList[i].key, histogram->histogramList[i].value);
    }
    printf("\n\n");
}
