#include <stdio.h>
#include "worker_pool.h"
#define UNUSED(d) ((void*)d)

int status = 0;

void worker_1(void *data) {
    fprintf(stdout, "start worker 1\n");
    (int *)data;
    status--;
    sleep(1);
    fprintf(stdout, "end worker 1\n");
    fflush(stdout);
}

void worker_2(void *data) {
    fprintf(stdout, "start worker 2\n");
    (int *)data;
    status +=2;
    fprintf(stdout, "end worker 2\n");
    fflush(stdout);
}

int main() {
    worker_pool *wp =  create_worker_pool(5);
    for(int i=0; i< 20; i++) {
        if (i%2) {
            add_task(wp, worker_1, NULL);  
        } else {
            add_task(wp, worker_2, NULL);  
        }
    }
    sleep(10);
    destroy_worker_pool(wp);
}
