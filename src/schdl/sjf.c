#include <stdio.h>
#include "process.h"

/* ============================================================
 * Student implementation area
 * ============================================================ */
void sjf_schedule(Process p[], int n)
{
    (void)p;
    (void)n;
    /* TODO: Implement SJF scheduling algorithm here */
    int time = 0;
    int posicion = 0;
    for (posicion = 0; posicion < n; posicion++){
        int shortest_job = -1;
        int shortest_burst = 99999;
        for (int i = posicion; i < n; i++){
            if(p[i].arrival_time <= time && p[i].burst_time < shortest_burst){
                shortest_burst = p[i].burst_time;
                shortest_job = i;
            }

        }
        if (shortest_job == -1){
            posicion--;
            int shortest_arrival = 99999;
            for(int j = posicion; j < n; j++){
                if(p[j].arrival_time < shortest_arrival){
                    shortest_arrival = p[j].arrival_time;

                }

            }
            time = shortest_arrival;
            continue;
        }
        if(shortest_job != posicion){
            Process temp = p[shortest_job];
            p[shortest_job] = p[posicion];
            p[posicion] = temp;


        }
        time += p[posicion].burst_time;
        p[posicion].turnaround_time = time - p[posicion].arrival_time;
        p[posicion].waiting_time = p[posicion].turnaround_time - p[posicion].burst_time;
        p[posicion].completed = 1;

    }
}

/* ============================================================
 * DO NOT MODIFY MAIN
 * ============================================================ */
#ifndef UNIT_TEST
int main(void)
{
    int n;
    printf("Número de procesos: ");
    scanf("%d", &n);

    Process p[n];
    read_processes(p, n);
    init_processes(p, n);

    sjf_schedule(p, n);

    print_results(p, n, "SJF Scheduling");
    return 0;
}
#endif