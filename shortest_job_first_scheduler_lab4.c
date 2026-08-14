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

    int completed;
};

int main()
{
    int n;

    printf("=============================================\n");
    printf("       SHORTEST JOB FIRST SCHEDULING\n");
    printf("          NON-PREEMPTIVE SJF\n");
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
        p[i].completed = 0;

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

    int currentTime = 0;
    int completedProcesses = 0;



    
    int order[n];
    int orderCount = 0;

    // SJF scheduling
    while (completedProcesses < n)
    {
        int shortest = -1;

        /*
            Find the shortest process that has already arrived
            and has not been executed.
        */
        for (int i = 0; i < n; i++)
        {
            if (!p[i].completed &&
                p[i].arrivalTime <= currentTime)
            {
                if (shortest == -1 ||
                    p[i].burstTime < p[shortest].burstTime)
                {
                    shortest = i;
                }
            }
        }

        /*
            No process has arrived yet.
            CPU remains idle.
        */
        if (shortest == -1)
        {
            currentTime++;

            continue;
        }

        // Store execution order
        order[orderCount++] = shortest;

        // Waiting Time
        p[shortest].waitingTime =
            currentTime - p[shortest].arrivalTime;

        // Execute process
        currentTime += p[shortest].burstTime;

        // Completion Time
        p[shortest].completionTime = currentTime;

        // Turnaround Time
        p[shortest].turnaroundTime =
            p[shortest].completionTime -
            p[shortest].arrivalTime;

        p[shortest].completed = 1;

        completedProcesses++;
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

    // Display table
    printf("\n\nPROCESS TABLE\n");

    printf("-----------------------------------------------------------------\n");

    printf("PID\tAT\tBT\tCT\tWT\tTAT\n");

    printf("-----------------------------------------------------------------\n");

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

    printf("-----------------------------------------------------------------\n");

    printf("\nAverage Waiting Time    : %.2f",
           averageWaitingTime);

    printf("\nAverage Turnaround Time : %.2f\n",
           averageTurnaroundTime);

    // Gantt Chart
    printf("\n\nGANTT CHART\n");

    printf(" ");

    for (int i = 0; i < orderCount; i++)
    {
        printf("--------");
    }

    printf("\n|");

    for (int i = 0; i < orderCount; i++)
    {
        int index = order[i];

        printf("  P%d    |", p[index].pid);
    }

    printf("\n ");

    for (int i = 0; i < orderCount; i++)
    {
        printf("--------");
    }

    printf("\n");

    /*
        Display timeline.
        For the first process, its start time is:

            completionTime - burstTime
    */

    int first = order[0];

    printf("%d",
           p[first].completionTime -
           p[first].burstTime);

    for (int i = 0; i < orderCount; i++)
    {
        int index = order[i];

        printf("%8d",
               p[index].completionTime);
    }

    printf("\n");

    return 0;
}