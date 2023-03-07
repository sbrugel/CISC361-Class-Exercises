#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>
#define MAX_NO_OF_THREADS 10
#define MAX_NO_OF_ELEMENTS 100000000

typedef struct arg_data
{
    int thread_number;
} arg_data;

// shared data on which threads will work concurrently
// array which will be summed
static int arr[MAX_NO_OF_ELEMENTS];

// sum variable that will store the total sum
static long long int sum;

void *worker_sum(void *arg)
{
    arg_data *current_thread_data = (arg_data *)arg;
    printf("Current thread no is : %d\n", current_thread_data->thread_number);

    // Determine the bounds
    int thread_no = current_thread_data->thread_number - 1;
    long split_at = MAX_NO_OF_ELEMENTS / MAX_NO_OF_THREADS;

    int startpart = thread_no * split_at;
    int endpart = (thread_no + 1) * split_at;
    int current_thread_sum = 0;

    printf("Here we will sum %d to %d\n", arr[startpart], arr[endpart - 1]);

    // Generate the sum
    for (int i = arr[startpart] - 1; i < arr[endpart - 1] - 1; i++)
    {
        current_thread_sum += arr[i];
    }

    sum += current_thread_sum;
    return NULL;
}

int main()
{
    // let the array consists of first MAX_NO_OF_ELEMENTS integers,
    // 1 to MAX_NO_OF_ELEMENTS
    for (int i = 0; i < MAX_NO_OF_ELEMENTS; i++)
        arr[i] = i + 1;

    // pthread objects
    pthread_t id[MAX_NO_OF_THREADS];
    pthread_attr_t attr;

    // argument data to send in worker functions
    arg_data arg_arr[MAX_NO_OF_THREADS];

    // total number of threads we will create
    int no_of_threads = MAX_NO_OF_THREADS;
    printf("Creating %d number of threads...\n", no_of_threads);

    // Setup timing
    clock_t start, end;
    double cpu_time_taken;

    start = clock();

    int thread_no = 1;

    // creating the child threads
    for (int i = 0; i < no_of_threads; i++)
    {
        arg_arr[i].thread_number = thread_no;
        pthread_create(&id[thread_no - 1], NULL, worker_sum, &arg_arr[i]);
        thread_no++;
    }

    // joining the threads one by one
    for (int i = 0; i < no_of_threads; i++)
    {
        pthread_join(id[i], NULL);
    }

    end = clock();
    cpu_time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("All child threads has finished their works...\n");
    printf("Total sum: %lld\n", sum);
    printf("Time taken to sum all the numbers are %lf\n", cpu_time_taken);
    return 0;
}