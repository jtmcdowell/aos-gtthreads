#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <inttypes.h>
#include <pthread.h>

#include "philosopher.h"

int i;
int servings = 100000;
pthread_mutex_t chopstick[5];
int delay = 30; /*delay in seconds for picking up the chopstick*/

/*
 * Performs necessary initialization of mutexes.
 */
void chopsticks_init(){
    for (i = 0; i < 5; i++)
        pthread_mutex_init(&chopstick[i], NULL);
}

/*
 * Cleans up mutex resources.
 */
void chopsticks_destroy(){
    for(i = 0; i < 5; i++)
        pthread_mutex_destroy(&chopstick[i]);
}

/*
 * Uses pickup_left_chopstick and pickup_right_chopstick
 * to pick up the chopsticks
 */ 
void pickup_chopsticks(int phil_id){
if(phil_id == 1) {
        // right-handed
        // pick up right chopstick
        pthread_mutex_trylock(&chopstick[(phil_id + 1) % 5]);
        pickup_right_chopstick(phil_id);
        fflush(stdout);
        printf("Philosopher %d picked up the RIGHT chopstick\n", phil_id);       

        // pickup left chopstick
        if(pthread_mutex_trylock(&chopstick[(phil_id) % 5])) {
            // sleep(delay);
            pickup_left_chopstick(phil_id);
            fflush(stdout);
            printf("Philosopher %d picked up the LEFT chopstick\n", phil_id);
        }
        else{
        fflush(stdout);
        putdown_right_chopstick(phil_id);
        pthread_mutex_unlock(&chopstick[(phil_id + 1) % 5]);
        printf("Philosopher %d put down the RIGHT chopstick\n", phil_id);
        }

}

else {
    // left-handed
    // pickup left chopstick
    pthread_mutex_trylock(&chopstick[(phil_id) % 5]);
    pickup_left_chopstick(phil_id);
    fflush(stdout);
    printf("Philosopher %d picked up the LEFT chopstick\n", phil_id); 
         
    // pick up right chopstick
    if(pthread_mutex_trylock(&chopstick[(phil_id + 1) % 5])){
        pickup_right_chopstick(phil_id);
        fflush(stdout);
        printf("Philosopher %d picked up the RIGHT chopstick\n", phil_id);
    }
    else{

    fflush(stdout);
    putdown_left_chopstick(phil_id);
    pthread_mutex_unlock(&chopstick[(phil_id) % 5]);
    printf("Philosopher %d put down the LEFT chopstick\n", phil_id);
    }
}

}

/*
 * Uses pickup_left_chopstick and pickup_right_chopstick
 * to pick up the chopsticks
 */   
void putdown_chopsticks(int phil_id){
    if(phil_id == 1){
    fflush(stdout);
    putdown_right_chopstick(phil_id);
    pthread_mutex_unlock(&chopstick[(phil_id + 1) % 5]);
    printf("PUTDOWN CALL **** Philosopher %d put down RIGHT chopstick\n", phil_id);
    putdown_left_chopstick(phil_id);
    pthread_mutex_unlock(&chopstick[(phil_id) % 5]);
    printf("PUTDOWN CALL **** Philosopher %d put down LEFT chopstick\n", phil_id);
    }
    else{
    fflush(stdout);
    putdown_left_chopstick(phil_id);
    pthread_mutex_unlock(&chopstick[(phil_id) % 5]);
    printf("PUTDOWN CALL **** Philosopher %d put down LEFT chopstick\n", phil_id);
    putdown_right_chopstick(phil_id);
    pthread_mutex_unlock(&chopstick[(phil_id + 1) % 5]);
    printf("PUTDOWN CALL **** Philosopher %d put down RIGHT chopstick\n", phil_id);
    }
    
}
