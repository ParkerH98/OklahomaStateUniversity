#include "header.h"
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

void printTrain(int day);

void reserveSeats(struct Customer *customer, int client_socket, int *port)
{
    struct Customer a;
    a = *customer;

    if (!(a.receipt_id >= 2000 && a.receipt_id < 3000))
    {
        a.receipt_id = receipt_num;
        receipt_num++;
    }

    // ==================
    // RECEIPT OPERATIONS
    // ==================
    // saves receipt id into a string for appending
    char receipt_id_str[20];
    sprintf(receipt_id_str, "%d", a.receipt_id);

    // creates file name and appends receipt id num
    char receipt_filename[15];
    strcat(receipt_id_str, "_r.txt");
    strcpy(receipt_filename, receipt_id_str);

    // ======================================================
    //              BEGINNING CRITICAL SECTION
    // ======================================================

    // gives lock to writer
    sem_wait(wrt);

/* ------------------------- ticket receipt printing ------------------------ */
    // opens file,  writes, and closes file 
    FILE *receipt_fp = fopen(receipt_filename, "w");
    fprintf(receipt_fp, "%s\n", a.name);
    fprintf(receipt_fp, "%d\n", a.govt_id);
    fprintf(receipt_fp, "%d\n", a.travel_date);
    fprintf(receipt_fp, "%d\n", a.num_traveler);
    for (int i = 0; i < NUM_SEATS; i++)
    {
        fprintf(receipt_fp, "%d", a.seats[i]);
    }
    fprintf(receipt_fp, "\n");
    fclose(receipt_fp);

/* -------------------------- summary file printing ------------------------- */
    // opens file,  writes, and closes file
    FILE *summary_fp = fopen("summary.txt", "a");
    if (a.receipt_id >= 2000)
    {
        fprintf(summary_fp, "**MODIFIED**\n");
    }
    fprintf(summary_fp, "Server ID: %d\n", *port);
    fprintf(summary_fp, "Receipt ID: %d\n", a.receipt_id);
    fprintf(summary_fp, "Name: %s\n", a.name);
    fprintf(summary_fp, "DOB: %d\n", a.dob);
    fprintf(summary_fp, "Government ID: %d\n", a.govt_id);
    fprintf(summary_fp, "Travel Day: %d\n", a.travel_date);

    fprintf(summary_fp, "Number of Travelers: %d\n", a.num_traveler);
    fprintf(summary_fp, "Seats Selected: \n");

    fprintf(summary_fp, "===================");
    for (int i = 0; i < NUM_SEATS - 1; i++)
    {
        if (i % 10 == 0)
            fprintf(summary_fp, "\n");
        fprintf(summary_fp, "%d ", a.seats[i]);
    }
    fprintf(summary_fp, "\n===================");
    fprintf(summary_fp, "\n\n");
    fclose(summary_fp);

/* --------------------------- trainfile printing --------------------------- */
    char train_filename[32];

    char travel_date_string[10];
    sprintf(travel_date_string, "%d", a.travel_date);

    strcpy(train_filename, "train_day");
    strcat(train_filename, travel_date_string);
    strcat(train_filename, ".txt");

    // opens, reads, and closes file
    FILE *train_fp;
    train_fp = fopen(train_filename, "r");

    char seats_now[33];
    fscanf(train_fp, "%s", seats_now);
    fclose(train_fp);

    // opens, writes, and closes file
    train_fp = fopen(train_filename, "w");
    for(int i=0; i<30; i++)
    {
        if( a.seats[i] == 1 ) seats_now[i] = '1';
    }
    fprintf(train_fp, "%s", seats_now);

    // closes file & writes gives up the lock
    fclose(train_fp);
    sem_post(wrt);
}

void inquiry(int ticket, int client_socket)
{
    // Reader acquire the lock before modifying read_count
    pthread_mutex_lock(&mutex);
    read_count++;

    // If this is the first reader, then it will block the writer
    if (read_count == 1)
    {
        sem_wait(wrt);
    }
    pthread_mutex_unlock(&mutex);

    char receipt_filename[32];
    char temp[10];

    sprintf(temp, "%d", ticket);
    strcpy(receipt_filename, temp);
    strcat(receipt_filename, "_r.txt");

    if (fopen(receipt_filename, "r"))
    {
        printf("Inquiry Received: Found ticket [%d] in our database.\n", ticket);

        FILE *fp1;
        fp1 = fopen(receipt_filename, "r");

        char temp[50];
        int temp2, temp3, temp4;
        char temp5[35];
        fscanf(fp1, "%[^\n]%d%d%d%s", temp, &temp2, &temp3, &temp4, temp5);


        char inquiry_msg[1024];
        char selected_seats[256];

        for (int i = 0; i < NUM_SEATS - 1; i++)
        {
            if (i % 10 == 0)
                strcat(selected_seats, "\n");
            char temp[50];
            sprintf(temp, "%c ", temp5[i]);
            strcat(selected_seats, temp);
        }

        // for (int i = 0; i < NUM_SEATS - 1; i++)
        // {
        //     if (i % 10 == 0)
        //         strcat(selected_seats, "\n");
            

        //     sprintf(temp, "%d ", temp5[i]);
        //     strcat(selected_seats, temp);
        // }

        sprintf(inquiry_msg, "\n\n===================Inquiry Results===================\nName: %s\nDOB: %d\nGovernment ID: %d\nNumber of Travelers: %d\nSeats Selected: \n===================%s\n===================\n\n",
                temp, temp2, temp3, temp4, selected_seats);

        send(client_socket, inquiry_msg, sizeof(inquiry_msg), 0);

                // printf("Name: %s\n", temp);
        // printf("Date of Birth: %d\n", temp2);
        // printf("Govt. ID: %d\n", temp3);
        // printf("Number of seats: %d\n", temp4);

        // for (int i = 0; i < 30; i++)
        // {
        //     if (temp5[i] == '1')
        //         printf("%d ", i + 1);
        // }
        // printf("\n");

        fclose(fp1);

        // Reader acquire the lock before modifying read_count
        pthread_mutex_lock(&mutex);
        read_count--;

        // if this is the last reader, it will signal the writer
        if (read_count == 0)
        {
            sem_post(wrt);
        }
        pthread_mutex_unlock(&mutex);
    }
    else
    {
        printf("Ticket not found.\n");
    }
}


void modify(int ticket, int client_socket, int *port)
{
    // int ticket = a.receipt_id;
    char receipt_filename[32];
    char temp[10];

    sprintf(temp, "%d", ticket);
    strcpy(receipt_filename, temp);
    strcat(receipt_filename, "_r.txt");

    // ======================================================
    //              BEGINNING CRITICAL SECTION
    // ======================================================

    // gives lock to writer
    sem_wait(wrt);
    if (fopen(receipt_filename, "r"))
    {
        char modification_message[512];

        sprintf(modification_message, "\nFound ticket [%d] in our database. Now modifying ticket.\n", ticket);
        send(client_socket, modification_message, sizeof(modification_message), 0);

        FILE *fp1;
        fp1 = fopen(receipt_filename, "r");

        char _name[50];
        int _govt, _day, _traveler;
        char _seats[35];

        fscanf(fp1, "%[^\n]%d%d%d%s", _name, &_govt, &_day, &_traveler, _seats);
        fclose(fp1);

        char train_filename[32];
        char Day[5];
        sprintf(Day, "%d", _day);

        strcpy(train_filename, "train_day");
        strcat(train_filename, Day);
        strcat(train_filename, ".txt");

        fp1 = fopen(train_filename, "r");
        
        char seats_now[31];
        fscanf(fp1, "%s", seats_now);
        fclose(fp1);

        fp1 = fopen(train_filename, "w");
        for(int i=0; i<30; i++)
        {
            if(_seats[i] == '1') seats_now[i] = '0';
        }

        fprintf(fp1, "%s", seats_now);

        // closes file & writes gives up the lock
        fclose(fp1);
        sem_post(wrt);

        struct Customer modified_cust;
        struct Customer *modified_cust_ptr = &modified_cust;

        // receives modified customer struct from the client
        recv(client_socket, modified_cust_ptr, sizeof(struct Customer), 0);

        ticket = ticket + 1000;
        modified_cust.receipt_id = ticket;

        reserveSeats(modified_cust_ptr, client_socket, port);
        remove(receipt_filename);
    }
    else
    {
        printf("Ticket not found.\n");
    }
}

void cancellation(int *ticket_ptr, int client_socket)
{
    int ticket = *ticket_ptr;
    char receipt_filename[11];
    char temp[10];

    sprintf(temp, "%d", ticket);
    strcpy(receipt_filename, temp);
    strcat(receipt_filename, "_r.txt");

    printf("%s\n", receipt_filename);

    // ======================================================
    //              BEGINNING CRITICAL SECTION
    // ======================================================

    // gives lock to writer
    sem_wait(wrt);

    if (fopen(receipt_filename, "r"))
    {
        char confirmation_msg[1024];
        sprintf(confirmation_msg, "Ticket [%d] was found.\nAre you sure you want to cancel the reservation (Y or N)?\n", ticket);

        FILE *fp1;
        fp1 = fopen(receipt_filename, "r");

        char _name[50];
        int _govt, _day, _traveler;
        char _seats[35];

        fscanf(fp1, "%[^\n]%d%d%d%s", _name, &_govt, &_day, &_traveler, _seats);
        fclose(fp1);

        char train_filename[32];
        char Day[5];
        sprintf(Day, "%d", _day);

        strcpy(train_filename, "train_day");
        strcat(train_filename, Day);
        strcat(train_filename, ".txt");

        fp1 = fopen(train_filename, "r");
        
        char seats_now[31];
        fscanf(fp1, "%s", seats_now);

        fclose(fp1);

        fp1 = fopen(train_filename, "w");
        for(int i=0; i<30; i++)
        {
            if(_seats[i] == '1') seats_now[i] = '0';
        }

        fprintf(fp1, "%s", seats_now);

        // closes file & writes gives up the lock
        fclose(fp1);
        sem_post(wrt);

        // sends confirmation message to the client
        send(client_socket, confirmation_msg, sizeof(confirmation_msg), 0);

        // receives cancellation confirmation answer from client
        char answer[2];
        recv(client_socket, answer, sizeof(answer), 0);

        if ((strcmp(answer, "Y") == 0) || (strcmp(answer, "y") == 0))
        {
            printf("Reservation for ticket %d is cancelled.\n", ticket);
            remove(receipt_filename);
        }
    }
    else
    {
        printf("The ticket doesn't exist.\n");
    }
}

struct Customer getInformationFromUser()
{
    struct Customer a;

    printf("Please enter your credentials as prompted.\n\n");
    printf("Name: ");
    char Name[50];
    scanf(" %s", Name);
    strcpy(a.name , Name);
    printf("Date of Birth(YYYYMMDD): ");
    scanf("%d", &a.dob);
    printf("Gender (M or F): ");
    scanf(" %c", &a.gender);
    printf("Government ID: ");
    scanf("%d", &a.govt_id);
    while(1)
    {
        printf("Available dates of travel: [1] 05062021 [2] 05072021\nSelect One: ");
        scanf("%d", &a.travel_date);
        
        if(a.travel_date> 2)
        {
            printf("Choose a valid date.\n");
            continue;
        }
        break;
    }

    
    char train_filename[32];
    char Day[5];
    sprintf(Day, "%d", a.travel_date);

    strcpy(train_filename, "train_day");
    strcat(train_filename, Day);
    strcat(train_filename, ".txt");
    FILE *train_fp;
    train_fp = fopen(train_filename, "r");
    char seats_counter[33];
    fscanf(train_fp, "%s", seats_counter);
    fclose(train_fp);
    int counter = 0; 
    int len = strlen(seats_counter);
    for(int i = 0; i<len; i++)
    {
        if(seats_counter[i] == '0') counter++;
    }

    printf("Number of Travelers: ");
    scanf("%d", &a.num_traveler);

    while(a.num_traveler>counter)
    {
        printf("We don't have that many seats left. Select a number between 1-%d: ", counter);
        scanf("%d", &a.num_traveler);
    } 


    // Sets all the values of the seats[] to be 0. This fixes a bug where unexpected values were present in the array.
    for (int i = 0; i < NUM_SEATS; i++)
    {
        a.seats[i] = 0;
    }

    printTrain(a.travel_date);

    printf("Enter your desired seats to reserve:\n");

    // sets the desired customer's seats' indices to be 1
    for (int i = 0; i < a.num_traveler;)
    {
        printf("Choose seat for ticket %d/%d: ", i + 1, a.num_traveler);
        while(1)
        {
            int temp;
            scanf("%d", &temp);
            if(seats_counter[temp-1] == '1')
            {
                printf("Seat not availalble. Select a valid seat.\n");
                continue;
            }
            a.seats[temp - 1] = 1;
            break;
        }
        i++;
    }
    printf("\n");

    return a;
}


struct Customer printReceipt(struct Customer a, int choice)
{
    printf("\n\n_____________________________________\n");
    printf("Your Hogwards express ticket is ready\n");
    printf("_____________________________________\n");

    if (choice == 1)
        receipt_num++;
    if (choice < 4)
    {
        // previously no values have been assigned
        a.receipt_id = choice * 1000 + receipt_num; //1000 for reservation, 2000 for modification, 3000 for cancelation
    }

    printf("Your receipt number (store for future use): %d\n", a.receipt_id);
    printf("==============================================\n");
    printf("Customer Name: %s\n", a.name);
    printf("Customer ID: %d\n", a.govt_id);
    printf("Date of Travel (YYYYMMDD): %d\n", a.travel_date);

    printf("Seats Booked: %d\n", a.num_traveler);
    for (int i = 1; i <= 30; i++)
    {
        if (a.seats[i])
            printf("%d ", i);
    }
    printf("\n");
    //printf("Total number of seats = %d\n", cnt);

    printf("Have a great travel to Hogwarts. Dumbeldore awaits\n");
    printf("__________________________________________________\n\n");

    sleep(3);
    return a;
}


void printTrain(int day)
{
    char train_filename[32];
    char temp[10];

    sprintf(temp, "%d", day);

    strcpy(train_filename, "train_day");
    strcat(train_filename, temp);
    strcat(train_filename, ".txt");

    FILE *fp1;
    fp1 = fopen(train_filename, "r");

    char train_seats[32];
    fscanf(fp1, "%[^\n]", train_seats);

    printf("Available seats at the moment:\n");
    printf("======================================");
    for (int i = 0; i < NUM_SEATS - 1; i++)
    {
        if (i % 10 == 0)
            printf("\n");

        if (train_seats[i] == '0')
            printf("%-3d ", i + 1);
        else
            printf("%-3c ", 'B');
    }
    printf("\n======================================\n\n");
    fclose(fp1);
}

void createTrainFiles()
{
    FILE *f, *f2;
    f = fopen("train_day1.txt", "w");
    f2 = fopen("train_day2.txt", "w");

    char t[30];
    for (int i = 0; i < 30; i++)
    {
        t[i] = '0';
    }

    fprintf(f, "%s", t);
    fprintf(f2, "%s", t);

    fclose(f);
    fclose(f2);
}