// Usage Instructions:
// make p && ./p

#include <stdio.h>   // printf()
#include <string.h>  //strlen()
#include <ctype.h>   // toLower()
#include <pthread.h> // threads
#include <assert.h>  // assert()
#include <stdlib.h>  // malloc()
#include <math.h>

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
    if (strcmp(argv[3], "fifo") == 0)
        fifo_replacement(argv);

    if (strcmp(argv[3], "lru") == 0)
        lru_replacement(argv);

    return 0;
}

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
        if (frame_ptr == *num_frames)
            frame_ptr = 0;

        char *memory_addr = strtok(line, " ");
        char frame_number[FRAME_NUM_LEN + 1];
        strncpy(frame_number, memory_addr, FRAME_NUM_LEN);

        char *rw_operation = strtok(NULL, " ");
        strtok(rw_operation, "\n");

        int hit = check_page_hit(frame_number);
        if (hit)
            continue;

        if (!hit)
        {
            strcpy(frames[frame_ptr], frame_number);
            frame_ptr++;
            page_fault++;
            increment_rw(rw_operation);
        }
    }

    summary_printout();
}

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
        read_index++;
        char *memory_addr = strtok(line, " ");
        char frame_number[FRAME_NUM_LEN + 1];
        strncpy(frame_number, memory_addr, FRAME_NUM_LEN);

        char *rw_operation = strtok(NULL, " ");
        strtok(rw_operation, "\n");

        int hit = lru_check_page_hit(frame_number, indices);
        if (hit)
            continue;

        if (!hit)
        {
            page_fault++;
            increment_rw(rw_operation);

            // set not full - no need to find victim
            if (arr_size < *num_frames)
            {
                strcpy(frames[arr_size], frame_number);
                indices[arr_size] = read_index;
                arr_size++;
                continue;
            }

            int victim = lru_find_victim();
            strcpy(frames[victim], frame_number);
            indices[victim] = read_index;
        }
    }

    summary_printout();
}

int check_page_hit(char *frame_number)
{
    int hit = 0;
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

void increment_rw(char *rw_operation)
{
    if (strcmp(rw_operation, "R") == 0)
        num_reads++;

    if (strcmp(rw_operation, "W") == 0)
        num_writes++;
}

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
    printf("------------------------------\n");
}

void user_input_printout(char *argv[])
{
    printf("------------------------------\n");
    printf("Trace File: %s\n", argv[1]);
    printf("Number of Frames: %s\n", argv[2]);
    printf("Replacement Algorithm: %s\n", argv[3]);
    printf("------------------------------\n");
}

int lru_check_page_hit(char *frame_number, int *indices)
{
    int hit = 0;
    for (int i = 0; i < *num_frames; i++)
    {
        if (strcmp(frames[i], frame_number) == 0)
        {
            hit = 1;
            lru_update_index(i, indices);
            break;
        }
    }
    return hit;
}

int lru_find_victim()
{
    int lru = INT32_MAX;
    int victim = -1;
    for (int i = 0; i < *num_frames; i++)
    {
        if (indices[i] < lru)
        {
            lru = indices[i];
            victim = i;
        }
    }

    return victim;
}

void lru_update_index(int index_to_update, int *indices_arr)
{
    indices_arr[index_to_update] = read_index;
}
