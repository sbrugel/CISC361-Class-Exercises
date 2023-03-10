#include <stdio.h>
#include <stdbool.h>

bool allTrue(bool *arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (!arr[i])
        {
            return false;
        }
    }
    return true;
}

int main()
{
    // Initialize variables
    int i = 0, num_processes = 0, total_time = 0, x, output_flag = 0, time_quantum = 0;
    int wait_time = 0, turnaround_time = 0, arrival_time[10], burst_time[10], temp[10];
    int wait_times[num_processes], turnaround_times[num_processes]; // new line by Simon
    float average_wait_time = 0, average_turnaround_time = 0;
    bool round_robin_algorithm = true;
    for (i = 0; i < 10; i++)
    {
        arrival_time[i] = 0;
        burst_time[i] = 0;
        temp[i] = 0;
    }

    // Define Number of Processes
    while (num_processes < 1 || num_processes > 10)
    {
        printf("\nEnter Total Number of Processes (1 - 10):\t");
        scanf("%d", &num_processes);
        if (num_processes < 1 || num_processes > 10)
        {
            printf("Incorrect Value Entered");
        }
    }
    // Define Process Details
    x = num_processes;
    for (i = 0; i < num_processes; i++)
    {
        printf("\nEnter Details of Process[%d]\n", i + 1);
        printf("Arrival Time (>-1):\t");
        scanf("%d", &arrival_time[i]);

        printf("Burst Time (>0):\t");
        scanf("%d", &burst_time[i]);
        temp[i] = burst_time[i];

        if (arrival_time[i] < 0 && burst_time[i] < 1)
        {
            printf("Incorrect Values Entered");
            i--;
        }
    }

    // Define Quantum
    if (round_robin_algorithm)
    {
        while (time_quantum < 1)
        {
            printf("\nEnter Time Quantum (>0):\t");
            scanf("%d", &time_quantum);
            if (time_quantum < 1)
            {
                printf("Incorrect Value Entered");
            }
        }
    }

    // Prepare Output
    printf("\nProcess ID\t\tArrival Time\t\tBurst Time\tTurnaround Time\tWaiting Time\n");

    // Perform Scheduling Calculations
    average_wait_time = 0;
    average_turnaround_time = 0;

    if (!round_robin_algorithm)
    {
        // first come, first serve
        int burstSum = 0;

        for (i = 0; i < num_processes; i++)
        {
            // TODO: sort processes by arrival time

            int wait_time = burstSum - arrival_time[i];
            average_wait_time += wait_time;
            int turnaround_time = burst_time[i] + wait_time;
            average_turnaround_time += turnaround_time;
            printf("%d\t\t\t%d\t\t\t%d\t\t%d\t\t%d\n", i + 1, arrival_time[i], burst_time[i], turnaround_time, wait_time);
            burstSum += burst_time[i];
        }
    }
    else
    {
        // round robin
        int remaining[num_processes];
        int wait_times[num_processes], turnaround_times[num_processes];
        bool complete[num_processes];
        int elapsed_time = 0;

        for (i = 0; i < num_processes; i++)
        {
            // TODO: sort processes by something

            for (int j = 0; j < num_processes; j++) // set initial values of the above arrays
            {
                remaining[j] = burst_time[j];
                complete[j] = false;
            }
        }

        // run the scheduler
        while (!allTrue(&complete, num_processes))
        {
            int flag = 0; // indicate if a process was executed in the current quantum
            for (i = 0; i < num_processes; i++)
            {
                // TODO: fix infinite loop here
                printf("process %d with %d left\n", i, remaining[i]);
                // has it arrived? does it have any time left?
                if (arrival_time[i] <= elapsed_time && remaining[i] > 0)
                {
                    // execute process
                    if (remaining[i] <= time_quantum)
                    {
                        elapsed_time += remaining[i]; // finish up this process
                        remaining[i] = 0;             // no more time left
                        flag = 1;                     // we ran a process
                    }
                }
                else
                {
                    elapsed_time += time_quantum;
                    remaining[i] -= time_quantum;
                }

                // update wait/turnaround for this process
                wait_times[i] = elapsed_time - burst_time[i] - arrival_time[i];
                turnaround_times[i] = elapsed_time - arrival_time[i];

                // update completed processes
                if (remaining[i] == 0)
                {
                    complete[i] = true;
                }
            }
        }

        // results
        for (i = 0; i < num_processes; i++)
        {
            printf("%d\t\t\t%d\t\t\t%d\t\t%d\t\t%d\n", i + 1, arrival_time[i], burst_time[i], turnaround_times[i], wait_times[i]);
        }
    }
    // Calculate & Print Average Wait and Turnaround Times
    average_turnaround_time /= num_processes;
    average_wait_time /= num_processes;
    printf("\n\nAverage Waiting Time:\t%f", average_wait_time);
    printf("\nAvg Turnaround Time:\t%f\n", average_turnaround_time);
    return 0;
}