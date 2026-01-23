#include <stdio.h>
#include "process.h"

void rr_schedule(Process p[], int n, int quantum) {
    int time = 0;
    int completed_count = 0;
    int queue[100];  // Cola de índices 
    int front = 0, rear = 0;
    int in_queue[n];  // Para rastrear si un proceso ya está en cola
    
    // Inicializar
    for (int i = 0; i < n; i++) {
        in_queue[i] = 0;
    }
    
    // Buscar el primer proceso que llega
    int first_arrival = p[0].arrival_time;
    for (int i = 1; i < n; i++) {
        if (p[i].arrival_time < first_arrival) {
            first_arrival = p[i].arrival_time;
        }
    }
    time = first_arrival;
    
    // Agregar procesos que llegan en time inicial
    for (int i = 0; i < n; i++) {
        if (p[i].arrival_time <= time) {
            queue[rear++] = i;
            in_queue[i] = 1;
        }
    }
    
    while (completed_count < n) {
        if (front == rear) {
            // La cola esta vacia, adelantarse al siguiete arrival de proceso
            time++;
            for (int i = 0; i < n; i++) {
                if (p[i].arrival_time <= time && !in_queue[i] && p[i].remaining_time > 0) {
                    queue[rear++] = i;
                    in_queue[i] = 1;
                }
            }
            continue;
        }
        
        // Sacar proceso de la cola
        int idx = queue[front++];
        
        // Ejecutar por duracion de quantum o hasta que acabe el proceso
        int exec_time = (p[idx].remaining_time > quantum) ? quantum : p[idx].remaining_time;
        p[idx].remaining_time -= exec_time;
        time += exec_time;
        
        // Agregar procesos que llegaron en la ejecuccion
        for (int i = 0; i < n; i++) {
            if (p[i].arrival_time <= time && !in_queue[i] && p[i].remaining_time > 0) {
                queue[rear++] = i;
                in_queue[i] = 1;
            }
        }
        
        // Si acabo el proceso
        if (p[idx].remaining_time == 0) {
            p[idx].completed = 1;
            p[idx].turnaround_time = time - p[idx].arrival_time;
            p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
            completed_count++;
        } else {
            // Volver a encolar si no acabo el proceso
            queue[rear++] = idx;
        }
    }
}
#ifndef UNIT_TEST
int main() {
    int n;
    printf("Número de procesos: ");
    scanf("%d", &n);

    Process p[n];
    read_processes(p, n);
    init_processes(p, n);

    // TODO: Aquí va la lógica del scheduler
    int quantum;
    printf("Quantum: ");       
    scanf("%d", &quantum);
    rr_schedule(p, n, quantum);
    
    print_results(p, n, "RR Scheduling");
    return 0;
}
#endif