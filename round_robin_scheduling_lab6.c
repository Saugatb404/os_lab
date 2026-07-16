#include <stdio.h>

/*
    Structure representing one process.
*/
struct Process
{
    int pid;             // Process ID
    int burstTime;       // Original Burst Time
    int remainingTime;   // Remaining Burst Time
    int waitingTime;     // Waiting Time
    int turnaroundTime;  // Turnaround Time
};

int main()
{
    int n;
    int timeQuantum;

    printf("=====================================\n");
    printf(" Round Robin Scheduling Algorithm\n");
    printf("=====================================\n\n");

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process process[n];

    //----------------------------------------
    // Input Burst Times
    //----------------------------------------

    for (int i = 0; i < n; i++)
    {
        process[i].pid = i + 1;

        printf("Enter Burst Time for Process %d: ",
               process[i].pid);

        scanf("%d", &process[i].burstTime);

        process[i].remainingTime = process[i].burstTime;
        process[i].waitingTime = 0;
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &timeQuantum);

    //----------------------------------------
    // Round Robin Scheduling
    //----------------------------------------

    int currentTime = 0;
    int completed = 0;

    while (completed < n)
    {
        int executed = 0;

        for (int i = 0; i < n; i++)
        {
            if (process[i].remainingTime > 0)
            {
                executed = 1;

                if (process[i].remainingTime <= timeQuantum)
                {
                    currentTime += process[i].remainingTime;

                    process[i].remainingTime = 0;

                    process[i].turnaroundTime = currentTime;

                    process[i].waitingTime =
                        process[i].turnaroundTime -
                        process[i].burstTime;

                    completed++;
                }
                else
                {
                    currentTime += timeQuantum;
                    process[i].remainingTime -= timeQuantum;
                }
            }
        }

        if (!executed)
            break;
    }

    //----------------------------------------
    // Calculate Totals
    //----------------------------------------

    int totalWaitingTime = 0;
    int totalTurnaroundTime = 0;

    for (int i = 0; i < n; i++)
    {
        totalWaitingTime += process[i].waitingTime;
        totalTurnaroundTime += process[i].turnaroundTime;
    }

    double averageWaitingTime =
        (double)totalWaitingTime / n;

    double averageTurnaroundTime =
        (double)totalTurnaroundTime / n;

    //----------------------------------------
    // Display Result
    //----------------------------------------

    printf("\n-----------------------------------------------------------\n");
    printf("PID\tBurst\tWaiting\tTurnaround\n");
    printf("-----------------------------------------------------------\n");

    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\n",
               process[i].pid,
               process[i].burstTime,
               process[i].waitingTime,
               process[i].turnaroundTime);
    }

    printf("-----------------------------------------------------------\n");

    printf("Average Waiting Time    : %.2f\n",
           averageWaitingTime);

    printf("Average Turnaround Time : %.2f\n",
           averageTurnaroundTime);

    return 0;
}