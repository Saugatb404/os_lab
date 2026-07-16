#include <stdio.h>

/*
    Structure representing one process.
*/
struct Process
{
    int pid;             // Process ID
    int burstTime;       // CPU Burst Time
    int waitingTime;     // Waiting Time
    int turnaroundTime;  // Turnaround Time
};

int main()
{
    int n;

    printf("=====================================\n");
    printf(" Shortest Job First Scheduling (SJF)\n");
    printf("=====================================\n\n");

    printf("Enter number of processes: ");
    scanf("%d", &n);

    // Variable Length Array (C99)
    struct Process process[n];
    struct Process temp;

   
    // Input Burst Times
  

    for (int i = 0; i < n; i++)
    {
        process[i].pid = i + 1;

        printf("Enter Burst Time for Process %d: ", process[i].pid);
        scanf("%d", &process[i].burstTime);
    }

   
    // Sort Processes by Burst Time
    // (Bubble Sort)


    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (process[i].burstTime > process[j].burstTime)
            {
                // Swap complete process structures
                temp = process[i];
                process[i] = process[j];
                process[j] = temp;
            }
        }
    }

    // Calculate Waiting Time
  

    process[0].waitingTime = 0;

    for (int i = 1; i < n; i++)
    {
        process[i].waitingTime =
            process[i - 1].waitingTime +
            process[i - 1].burstTime;
    }

    
    // Calculate Turnaround Time
   
    for (int i = 0; i < n; i++)
    {
        process[i].turnaroundTime =
            process[i].waitingTime +
            process[i].burstTime;
    }

    // Calculate Totals


    int totalWaitingTime = 0;
    int totalTurnaroundTime = 0;

    for (int i = 0; i < n; i++)
    {
        totalWaitingTime += process[i].waitingTime;
        totalTurnaroundTime += process[i].turnaroundTime;
    }

   
    // Calculate Average

    double averageWaitingTime =
        (double)totalWaitingTime / n;

    double averageTurnaroundTime =
        (double)totalTurnaroundTime / n;

  
    // Display Result
    

    printf("\n-------------------------------------------------------------\n");
    printf("PID\tBurst Time\tWaiting Time\tTurnaround Time\n");
    printf("-------------------------------------------------------------\n");

    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t\t%d\t\t%d\n",
               process[i].pid,
               process[i].burstTime,
               process[i].waitingTime,
               process[i].turnaroundTime);
    }

    printf("-------------------------------------------------------------\n");

    printf("Average Waiting Time    : %.2f\n", averageWaitingTime);
    printf("Average Turnaround Time : %.2f\n", averageTurnaroundTime);

    return 0;
}