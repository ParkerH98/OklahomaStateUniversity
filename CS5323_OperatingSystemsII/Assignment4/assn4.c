// Usage Instructions:
// make p && ./p

#include <stdio.h>   // printf()
#include <string.h>  //strlen()
#include <ctype.h>   // toLower()
#include <pthread.h> // threads
#include <assert.h>  // assert()
#include <stdlib.h>  // malloc()
#include <math.h>    

void fifo_replacement(char *argv[]);
void lru_replacement(char *argv[]);
void user_input_printout(char *argv[]);
char **frame_table_init();
void increment_rw(char *operation);
int check_page_hit(char *location, int *indices);
void summary_printout();
int lru_find_victim();
void lru_update_index(int index_to_update, int *indices);

int num_reads = 0;
int num_writes = 0;
int read_index = 0;
int page_fault = 0;
char **frames;
int *indices;
int *num_frames;

// 784740
//  670356

int main(int argc, char *argv[])
{
    fifo_replacement(argv);
    // lru_replacement(argv);
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

        char *location = strtok(line, " ");
        char *operation = strtok(NULL, " ");
        strtok(operation, "\n");

        increment_rw(operation);

        int hit = check_page_hit(location, indices);
        if (hit == 0)
        {
            // todo bug right here
            // strcpy(frames[frame_ptr], location);
            frame_ptr++;
            page_fault++;
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
        char *location = strtok(line, " ");
        char *operation = strtok(NULL, " ");
        strtok(operation, "\n");

        increment_rw(operation);

        int hit = check_page_hit(location, indices);

        if (hit == 0 && arr_size < *num_frames)
        {
            strcpy(frames[arr_size], location);
            indices[arr_size] = read_index;
            arr_size++;
            read_index++;
            page_fault++;
            continue;
        }

        // MISS
        if (hit == 0)
        {

            int victim = lru_find_victim();

            strcpy(frames[victim], location);

            indices[victim] = read_index;

            page_fault++;
        }

        read_index++;
    }

    summary_printout();

}

int check_page_hit(char *location, int *indices)
{
    int hit = 0;
    for (int i = 0; i < *num_frames; i++)
    {

        if (strcmp(frames[i], location) == 0)
        {
            hit = 1;
            lru_update_index(i, indices);
            break;
        }
    }

    return hit;
}

void increment_rw(char *operation)
{
    if (strcmp(operation, "R") == 0)
        num_reads++;

    if (strcmp(operation, "W") == 0)
        num_writes++;
}

char **frame_table_init()
{
    int mem_addr_len = 8;

    // allocates an array for each row (frame)
    char **arr = malloc(sizeof(char *) * *num_frames);

    for (int i = 0; i < *num_frames; i++)
    {
        // allocates column elements for the length of each memory address
        arr[i] = malloc(sizeof(char) * (mem_addr_len + 1));
    }
    return arr;
}

void summary_printout()
{
    printf("\nContents of page frames\n");

    for (int i = 0; i < *num_frames; i++)
    {
        printf("%s ", frames[i]);
    }

    printf("\nNumber of Reads: %d\n", num_reads);
    printf("Number of Writes: %d\n", num_writes);
    printf("Number of Page Faults: %d\n\n", page_fault);
}

void user_input_printout(char *argv[])
{
    printf("\nTrace File: %s\n", argv[1]);
    printf("Number of Frames: %s\n", argv[2]);
    printf("Replacement Algorithm: %s\n\n", argv[3]);
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

void lru_update_index(int index_to_update, int *indices)
{
    indices[index_to_update] = read_index;
}
