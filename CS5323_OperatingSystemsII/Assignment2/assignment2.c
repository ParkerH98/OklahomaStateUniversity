// Usage Instructions:
// make p && ./p

#include <stdio.h>   // printf()
#include <string.h>  //strlen()
#include <ctype.h>   // toLower()
#include <pthread.h> // threads
#include <assert.h>  // assert()
#include <stdlib.h>  // malloc()

// struct that will serve as a dictionary for each histogram
typedef struct CharDictionary
{
    int key;
    int value;
} CharDictionary;

typedef struct Histogram
{
    CharDictionary histogramList[26];
} Histogram;

void readFile();
void convertToLowerCase(char *string);
void initializeHistogram();
void printHistogram();
void *threadTask();
void populateHistogram(char line[]);

FILE *f;
pthread_mutex_t histogram_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t print_mutex = PTHREAD_MUTEX_INITIALIZER;

Histogram histogram;

int *remaining_threads;

int main()
{



    char filePath[512] = "file.txt";
    int numThreads = 3;



    // char filePath[512];
    // int numThreads = 0;

    // printf("Please enter a filepath to read from.\n");
    // fgets(filePath, sizeof(filePath), stdin);
    // filePath[strlen(filePath) - 1] = '\0';

    // // gets thread # input and forces a specific range
    // printf("Please specify the number of threads between 2 and 4 inclusive.\n");
    // scanf("%d", &numThreads);
    // assert(numThreads > 1 && numThreads <= 4);

    // printf("\n\n{%d} threads processing file at path: %s\n", numThreads, filePath);


    remaining_threads = malloc(numThreads * sizeof(int));
    *remaining_threads = numThreads;

    // open file for reading
    f = fopen(filePath, "r");

    initializeHistogram(&histogram);

    // an array of threads representing the thread pool
    pthread_t thread_pool[numThreads];

    // each created thread will run the threadTask() which will infinitely loop and try to get the histogram_mutex lock
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

Params: none
Return: void
*/
void *threadTask()
{
    char line[512];

    while (1)
    {
        // reads the line from the file
        if (fgets(line, 512, f) == NULL)
        {
            pthread_mutex_lock(&print_mutex);
            *remaining_threads = *remaining_threads - 1;
            pthread_mutex_unlock(&print_mutex);

            if (*remaining_threads == 0)
            {
                printHistogram();
            }
            return NULL;
        }

        // get rid of ending \n from fgets
        if (line[strlen(line) - 1] == '\n')
        {
            line[strlen(line) - 1] = '\0';
        }

        pthread_mutex_lock(&histogram_mutex);

        convertToLowerCase(line);
        populateHistogram(line);

        pthread_mutex_unlock(&histogram_mutex);
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
void populateHistogram(char line[])
{
    int i = 0;
    while (line[i])
    {
        char c = line[i];
        if (!isalpha(c))
        {
            i++;
            continue;
        }
        histogram.histogramList[c - 97].value++;
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
void initializeHistogram()
{
    for (int i = 97; i < 123; i++)
    {
        histogram.histogramList[i - 97].key = i;
        histogram.histogramList[i - 97].value = 0;
    }
}

/*
---------------------------------------------------------

Params: Histogram * & char[]
Return: void
*/
void printHistogram()
{
    printf("{");

    for (int i = 0; i < 26; i++)
    {
        if (i == 25)
        {
            printf("'%c': %d}", histogram.histogramList[i].key, histogram.histogramList[i].value);
            continue;
        }

        printf("'%c': %d, ", histogram.histogramList[i].key, histogram.histogramList[i].value);
    }
    printf("\n\n");
}
