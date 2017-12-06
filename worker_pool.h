#ifndef THREAD_POOL_H
#define THREAD_POOL_H

/* all abi is depend on posix thread api */
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>

#include "atomic.h"

#define WP_SUCCESS  0
#define WP_FAIL     -1

#define smalloc malloc
#define sfree   free

typedef void worker_executor(void *data);
typedef struct worker_pool  worker_pool;
typedef struct task         task;

/* todo add task id */
struct task{
    worker_executor *exec;
    void *data;
    task *prev; 
};
 
/* todo use lock free */
/* abb and memory barrier */
/* task queue */
typedef struct {
    uint64_t processed;
    uint64_t len;
    task    head;
    task    *tail; 
    
    // notify
    pthread_mutex_t lock;
    pthread_cond_t cond;
}task_queue;

/* worker */
typedef struct {
    uint32_t    worker_id;
    uint64_t    all_execute_time;   /* us(microsecond) */
    pthread_t   tid;
    worker_pool *wp;
}worker;

/* worker pool */
struct worker_pool{
    worker              *ws;
    pthread_barrier_t   pb;                 /* use for sync, use begin and end barrier */
    uint32_t            all_worker_num;     /* can use volidate keyword, or use atomic func */
    uint32_t            working_num;
    int                 running;
    task_queue          tq;
};

/* inline func */
static inline long get_current_usec() {
    struct timeval time;
    gettimeofday(&time, NULL);
    return time.tv_sec * 1000 * 1000 + time.tv_usec;
}

worker_pool* create_worker_pool(int worker_num);
void destroy_worker_pool(worker_pool *wp);
void add_task(worker_pool *wp, worker_executor exec, void *data);
void dump_worker_pool_status(worker_pool *wp);
#endif
