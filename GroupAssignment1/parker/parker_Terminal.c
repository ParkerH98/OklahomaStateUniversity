#include "header.h"

void printToTerminal(struct EmployeeStructure *employeePtr)
{
    system("gnome-terminal --  bash -c \"tty; exec bash\""); // opens a new terminal

    int file = open("/dev/pts/2", O_WRONLY); // sets the gnome-terminal as a file to write to
    int stdoutDescriptor = dup(1);           // copies the file descriptor for stdout

    dup2(file, 1);                              // writes the stdout file descriptor to that of the new gnome-terminal

    printf("Id: %d\n", employeePtr->id);
    printf("Employee Name: %s\n", employeePtr->employeeName);
    printf("Job Title: %s\n", employeePtr->jobTitle);
    printf("Base Pay: %f\n", employeePtr->basePay);
    printf("Overtime Pay: %f\n", employeePtr->overtimePay);
    printf("Benefit: %f\n", employeePtr->benefit);
    printf("Status: %s\n", employeePtr->status);
    printf("Satisfaction Level: %f\n", employeePtr->satisfactionLevel);
    printf("Number of Projects: %d\n", employeePtr->numberProject);
    printf("Average Monthly Hours: %d\n", employeePtr->averageMonthlyHours);
    printf("Company Time (Years): %d\n", employeePtr->yearsInCompany);
    printf("Work Accident: %d\n", employeePtr->workAccident);
    printf("Promotion in Last 5 Years: %d\n", employeePtr->promotionsLast5Years);
    printf("Should display in a new window\n"); // tests that stdout prints to new terminal
    printf("===================================================\n\n");

    dup2(stdoutDescriptor, 1);            // sets the stdout file descriptor back thereby undoing the change
    printf("Should display in vscode\n"); // tests the stdout prints back in original location
}