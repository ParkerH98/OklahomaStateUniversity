// Usage Instructions:
// make test

#include <stdio.h>   // printf()
#include <string.h>  //strlen()
#include <ctype.h>   // toLower()
#include <pthread.h> // threads
#include <assert.h>  // assert()
#include <stdlib.h>  // malloc()
#include <stdint.h> //MAXINT32

#define FRAME_NUM_LEN 5

void fifo_replacement(char *argv[]);
void lru_replacement(char *argv[]);
void user_input_printout(char *argv[]);
char **frame_table_init();
void increment_rw(char *rw_operation);
int check_page_hit(char *frame_number);
int lru_check_page_hit(char *frame_number, int *indices);
void summary_printout();
int lru_find_victim();
void lru_update_index(int index_to_update, int *indices);

int num_reads = 0;
int num_writes = 0;
int read_index = -1;
int page_fault = 0;
char **frames;
int *indices;
int *num_frames;

int main(int argc, char *argv[])
{

    // will run either the fifo or lru replacement algorithm depending
    // on the passed command line argument

    if (strcmp(argv[3], "fifo") == 0)
        fifo_replacement(argv);

    if (strcmp(argv[3], "lru") == 0)
        lru_replacement(argv);

    return 0;
}

/**
 * The FIFO page replacement algorithm. Replaces the frames in the working
 * set in a circular queue fashion while serving first come first serve.
 * @param argv  The array of command line arguments passed when executing the program.
 */
void fifo_replacement(char *argv[])
{
    user_input_printout(argv);

    // allocating variable size int for num_frames
    num_frames = malloc(atoi(argv[2]) * sizeof(int));
    *num_frames = atoi(argv[2]);

    // allocating variable size arrays
    frames = frame_table_init();

    // open file for reading
    FILE *f;
    f = fopen(argv[1], "r");

    char line[64];
    int frame_ptr = 0;

    while (fgets(line, 512, f) != NULL)
    {
        // this resets the pointer when it reaches the end of the array
        // thus making it like a circular queue
        if (frame_ptr == *num_frames)
            frame_ptr = 0;

        // copies the first 5 hex numbers of the memory address to represent the page frame
        char *memory_addr = strtok(line, " ");
        char frame_number[FRAME_NUM_LEN + 1];
        strncpy(frame_number, memory_addr, FRAME_NUM_LEN);

        // gets the operation at the memory address (R or W)
        char *rw_operation = strtok(NULL, " ");
        strtok(rw_operation, "\n");

        // checks to see if the frame is in the working set
        int hit = check_page_hit(frame_number);

        // if the frame is in the working set then we can continue onto the next instruction
        if (hit)
            continue;

        // if the frame is not in the working set then we have a page fault (miss)
        if (!hit)
        {
            // copy the new frame into the working set
            strcpy(frames[frame_ptr], frame_number);

            // increment the frame pointer to the next location in the working set & add to num read/writes
            frame_ptr++;
            page_fault++;
            increment_rw(rw_operation);
        }
    }

    summary_printout();

    // frees dynamically allocated memory
    free(num_frames);
    free(frames);
}


/**
 * The LRU page replacement algorithm. Replaces the frame in the working
 * set that was accessed least recently. This is a more efficient way of deciding
 * which should be the victim frame.
 * @param argv The array of command line arguments passed when executing the program.
 */
void lru_replacement(char *argv[])
{
    user_input_printout(argv);

    // allocating variable size int for num_frames
    num_frames = malloc(atoi(argv[2]) * sizeof(int));
    *num_frames = atoi(argv[2]);

    // allocating variable size arrays
    frames = frame_table_init();
    indices = malloc(sizeof(int) * *num_frames);

    // open file for reading
    FILE *f;
    f = fopen(argv[1], "r");

    char line[64];
    int arr_size = 0;

    while (fgets(line, 512, f) != NULL)
    {
        // read_index is used to keep track of the memory address that was accessed least recently
        read_index++;

        // copies the first 5 hex numbers of the memory address to represent the page frame
        char *memory_addr = strtok(line, " ");
        char frame_number[FRAME_NUM_LEN + 1];
        strncpy(frame_number, memory_addr, FRAME_NUM_LEN);

        // gets the operation at the memory address (R or W)
        char *rw_operation = strtok(NULL, " ");
        strtok(rw_operation, "\n");

        // checks to see if the frame is in the working set
        int hit = lru_check_page_hit(frame_number, indices);

        // if the frame is in the working set then we can continue onto the next instruction
        if (hit)
            continue;

        // if the frame is not in the working set then we have a page fault (miss)
        if (!hit)
        {
            // increments the page fault for a miss & also increments the read/write count
            page_fault++;
            increment_rw(rw_operation);

            // set not full - no need to find victim (this happens to the first n frames in the working set)
            if (arr_size < *num_frames)
            {
                // copies frame into working set and updates the new frame's read index
                strcpy(frames[arr_size], frame_number);
                indices[arr_size] = read_index;

                // arr_size only used to keep track of the first n frames in the working set
                arr_size++;
                continue;
            }

            // returns the index of the least recently used memory address in the working set
            int victim = lru_find_victim();

            // replaces the least recently used frame
            strcpy(frames[victim], frame_number);

            // sets the read index for the new frame so we know how recently it was used
            indices[victim] = read_index;
        }
    }

    summary_printout();

    // frees dynamically allocated memory
    free(num_frames);
    free(frames);
    free(indices);
}

/**
 * Checks each frame in the working set to determine if a page hit or miss occurred. 
 * @param frame_number The hex representation of the frame number
 * @return 1 for page hit and 0 for page miss
 */
int check_page_hit(char *frame_number)
{
    int hit = 0;

    // if a page hit is found, the hit is set to 1 and the loop breaks
    for (int i = 0; i < *num_frames; i++)
    {
        if (strcmp(frames[i], frame_number) == 0)
        {
            hit = 1;
            break;
        }
    }
    return hit;
}

/**
 * Increments the read and write counts depending on what operation is passed to the function.
 * @param rw_operation The operation that occurred at the memory address in the trace file.
 */
void increment_rw(char *rw_operation)
{
    // read operations increment the read count
    if (strcmp(rw_operation, "R") == 0)
        num_reads++;

    // when a write operation occurs the write count is incremented, but the read is too because the
    // instruction has to be read before it can be written to
    if (strcmp(rw_operation, "W") == 0)
    {
        num_writes++;
        num_reads++;
    }
}

/**
 * Dynamically allocates an array that will be used as the working set for this program.
 * @return A double pointer to the newly created 2d char array.
 */
char **frame_table_init()
{
    // allocates an array for each row (frame)
    char **arr = malloc(sizeof(char *) * *num_frames);

    for (int i = 0; i < *num_frames; i++)
    {
        // allocates column elements for the length of each memory address
        arr[i] = malloc(sizeof(char) * (FRAME_NUM_LEN + 1));
    }
    return arr;
}

/**
 * Prints out the number of reads, writes, page faults, and the contents of the working set.
 */
void summary_printout()
{
    printf("Contents of page frames\n");

    for (int i = 0; i < *num_frames; i++)
    {
        printf("%s ", frames[i]);
    }

    printf("\nNumber of Reads: %d\n", num_reads);
    printf("Number of Writes: %d\n", num_writes);
    printf("Number of Page Faults: %d\n", page_fault);
    printf("----------------------------------\n");
}

/**
 * Prints out a summary of the passed command line arguments.
 */
void user_input_printout(char *argv[])
{
    printf("----------------------------------\n");
    printf("Trace File: %s\n", argv[1]);
    printf("Number of Frames: %s\n", argv[2]);
    printf("Replacement Algorithm: %s\n", argv[3]);
    printf("----------------------------------\n");
}

/**
 * Checks each frame in the working set to determine if a page hit or miss occurred. 
 * @param frame_number The hex representation of the frame number
 * @param indices A pointer to the indices array that stores each read index
 * @return 1 for page hit and 0 for page miss
 */
int lru_check_page_hit(char *frame_number, int *indices)
{
    int hit = 0;

    // if a page hit is found, the hit is set to 1 and the loop breaks
    for (int i = 0; i < *num_frames; i++)
    {
        if (strcmp(frames[i], frame_number) == 0)
        {
            hit = 1;
            // updates the read index so the program knows the frame was recently used
            lru_update_index(i, indices);
            break;
        }
    }
    return hit;
}

/**
 * Checks each frame in the wokring set to find the one that was use the longest ago.
 * For this implementation, it will be the frame with the minimum read index. 
 * @return The index of the victim frame that was least recently used
 */
int lru_find_victim()
{
    int lru = INT32_MAX;
    int victim = -1;
    for (int i = 0; i < *num_frames; i++)
    {
        // compares each read index to see if it's the new minimum
        if (indices[i] < lru)
        {
            lru = indices[i];
            victim = i;
        }
    }

    return victim;
}

/**
 * Updates the read index in the indices array to allow the program to keep track of when a frame was recently used.
 * @param index_to_update The index of the idices array to update
 * @param indices_arr The array of read indices 
 */
void lru_update_index(int index_to_update, int *indices_arr)
{
    indices_arr[index_to_update] = read_index;
}
