#include <stdio.h>
#include "process.h"

/* ============================================================
 * Student implementation area
 * ============================================================ */
void sort_by_arrival(Process p[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].arrival_time > p[j + 1].arrival_time) {
                Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

 void fcfs_schedule(Process p[], int n)
{
    (void)p;
    (void)n;
    // Ordenar por arrival_time
    sort_by_arrival(p, n);
    
    int time = 0;
    for (int i = 0; i < n; i++) {
        // Si CPU está idle, avanzar al siguiente arrival
        if (time < p[i].arrival_time) {
            time = p[i].arrival_time;
        }
        // Calcular tiempos
        p[i].waiting_time = time - p[i].arrival_time;
        time += p[i].burst_time;
        p[i].turnaround_time = p[i].waiting_time + p[i].burst_time;
        p[i].completed = 1;
        
        printf("   -> P%d terminó en tiempo %d\n", p[i].id, time);
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
    
    fcfs_schedule(p, n);

    print_results(p, n, "FCFS Scheduling");
    return 0;
}
#endif