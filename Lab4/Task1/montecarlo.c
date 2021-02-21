#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

void *compute_pi(void *);

#define NUM_THREADS 32

int sample_points_per_thread = 10000;


void *compute_pi(void *s){
    unsigned int seed, i, *hit_pointer;
    double x_coord, y_coord;
    double local_hits;
    hit_pointer = (unsigned int*) s;
    seed = *hit_pointer;
    local_hits = 0;
    srand(time(NULL));
    for(int k = 0; k < sample_points_per_thread;k++){
        x_coord = (double)(rand_r(&seed))/(RAND_MAX) - 0.5;
        //printf("Estimated x Value: %f\n",x_coord);
        y_coord = (double)(rand_r(&seed))/(RAND_MAX) - 0.5;
        //printf("Estimated y Value: %f\n",y_coord);
        if((x_coord * x_coord + y_coord * y_coord < 0.25)){
            local_hits++;
            //printf("Estimated localhits Value: %f\n",local_hits);
        }
    }
    *hit_pointer = local_hits;
    pthread_exit(0);
}

int main(){
    int hits[NUM_THREADS];
    double pi;
    double total_hits;
    pthread_t p_threads[NUM_THREADS];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    for(int i = 0; i < NUM_THREADS;i++){
        hits[i] = i;
        pthread_create(&p_threads[i], &attr, compute_pi, (void*) &hits[i]);
    }

    for(int j = 0; j < NUM_THREADS;j++){
        pthread_join(p_threads[j], NULL);
        total_hits += hits[j];
        printf("Estimated totalhits Value: %f\n",total_hits);
    }

    pi = 4.0 * (total_hits)/(NUM_THREADS * sample_points_per_thread);

    printf("Estimated Pi Value: %f\n",pi);


}