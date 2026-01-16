#include <stdio.h>
#include "process.h"

int main() {
    int n;
    printf("Número de procesos: ");
    scanf("%d", &n);

    Process p[n];
    read_processes(p, n);
    init_processes(p, n);

    // TODO: Aquí va la lógica del scheduler
    int time = 0;
    int quantum = 1;
    int completed = 0;

    while (!completed) {
        int i = 0;
        for (i; i < n; i++) {
            if (time < p[i].arrival_time) {
            time = p[i].arrival_time;
        }
        p[i].remaining_time -= quantum;
        time += quantum;
        if (p[i].remaining_time == 0){
            p[i].completed = 1;
        }


        }

    }
    
    print_results(p, n, "RR Scheduling");
    return 0;
}