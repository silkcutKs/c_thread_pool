# c language thread pool

## use
build your executable file with `worker_pool.c -lpthread`

first step, create worker pool with worker num, which will effect your concurrence.

```c
worker_pool *wp =  create_worker_pool(worker_num);
```

second, add task which you want to execute async.

```c
add_task(wp, execute_func, data);  
```

finally, destroy your worker_pool.

```c
destroy_worker_pool(wp);
```

extra, monitor run status.

```c
dump_worker_pool_status(worker_pool *wp);
```

## test

```shell
gcc -std=gnu99 -o main test.c worker_pool.c -lpthread
./main
```

output:

```shell
start worker 1
start worker 2
end worker 2
start worker 1
start worker 2
end worker 2
start worker 1
start worker 2
```

## advantage 

some action use `pthread_barrier_*` functions to sync data without lock.

## next
- use lock free struct to release lock time wait.
- destroy with wait.
- execute more fast.
