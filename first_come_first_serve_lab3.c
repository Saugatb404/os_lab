#include <stdio.h>
#include <stdlib.h>

struct Process
{
    int pid;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int waitingTime;
    int turnaroundTime;
};

void sortByArrivalTime(struct Process p[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (p[j].arrivalTime > p[j + 1].arrivalTime)
            {
                struct Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

void displayGanttChart(struct Process p[], int n)
{
    printf("\n\nGANTT CHART\n");

    printf(" ");

    for (int i = 0; i < n; i++)
    {
        printf("--------");
    }

    printf("\n|");

    for (int i = 0; i < n; i++)
    {
        printf("  P%d    |", p[i].pid);
    }

    printf("\n ");

    for (int i = 0; i < n; i++)
    {
        printf("--------");
    }

    printf("\n");

    printf("%d", p[0].arrivalTime);

    for (int i = 0; i < n; i++)
    {
        printf("%8d", p[i].completionTime);
    }

    printf("\n");
}

int main()
{
    int n;

    printf("=============================================\n");
    printf("       FCFS CPU SCHEDULING ALGORITHM\n");
    printf("=============================================\n");

    printf("\nEnter number of processes: ");
    scanf("%d", &n);

    if (n <= 0)
    {
        printf("Invalid number of processes.\n");
        return 1;
    }

    struct Process p[n];

    // Input
    printf("\nEnter process details:\n");

    for (int i = 0; i < n; i++)
    {
        p[i].pid = i + 1;

        printf("\nProcess P%d\n", p[i].pid);

        printf("Arrival Time : ");
        scanf("%d", &p[i].arrivalTime);

        printf("Burst Time   : ");
        scanf("%d", &p[i].burstTime);

        if (p[i].arrivalTime < 0 || p[i].burstTime <= 0)
        {
            printf("Invalid input.\n");
            return 1;
        }
    }

    // Sort according to arrival time
    sortByArrivalTime(p, n);

    // Calculate scheduling times
    int currentTime = 0;

    for (int i = 0; i < n; i++)
    {
        // CPU remains idle if next process has not arrived
        if (currentTime < p[i].arrivalTime)
        {
            currentTime = p[i].arrivalTime;
        }

        p[i].waitingTime = currentTime - p[i].arrivalTime;

        currentTime += p[i].burstTime;

        p[i].completionTime = currentTime;

        p[i].turnaroundTime =
            p[i].completionTime - p[i].arrivalTime;
    }

    // Calculate averages
    int totalWaitingTime = 0;
    int totalTurnaroundTime = 0;

    for (int i = 0; i < n; i++)
    {
        totalWaitingTime += p[i].waitingTime;
        totalTurnaroundTime += p[i].turnaroundTime;
    }

    double averageWaitingTime =
        (double)totalWaitingTime / n;

    double averageTurnaroundTime =
        (double)totalTurnaroundTime / n;

    // Display process table
    printf("\n\nPROCESS TABLE\n");

    printf("---------------------------------------------------------------\n");

    printf("PID\tAT\tBT\tCT\tWT\tTAT\n");

    printf("---------------------------------------------------------------\n");

    for (int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid,
               p[i].arrivalTime,
               p[i].burstTime,
               p[i].completionTime,
               p[i].waitingTime,
               p[i].turnaroundTime);
    }

    printf("---------------------------------------------------------------\n");

    printf("\nAverage Waiting Time    : %.2f", averageWaitingTime);
    printf("\nAverage Turnaround Time : %.2f\n",
           averageTurnaroundTime);

    // Display Gantt chart
    displayGanttChart(p, n);

    return 0;
}