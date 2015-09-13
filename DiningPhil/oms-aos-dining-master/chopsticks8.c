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
if(phil_id == 1 ) {
        // right-handed
        // pick up right chopstick first
        while(!pthread_mutex_trylock(&chopstick[(phil_id+1) % 5])){
            pickup_right_chopstick(phil_id);
            fflush(stdout);
            printf("Philosopher %d picked up the right chopstick\n", phil_id);
            while(!pthread_mutex_trylock(&chopstick[(phil_id+4) % 5])){
                pickup_left_chopstick(phil_id);
                fflush(stdout);
                printf("Philosopher %d picked up the left chopstick and is eating\n", phil_id);
            }
            fflush(stdout);
            putdown_right_chopstick(phil_id);
            pthread_mutex_unlock(&chopstick[(phil_id+1) % 5]);                
            printf("Philosopher %d gave up, will try again\n", phil_id);   
        }

} //end of conditional if on Phil # 1
 
else {
        // left-handed
        // pickup left chopstick first
        while(!pthread_mutex_trylock(&chopstick[(phil_id+4) % 5])){
            pickup_left_chopstick(phil_id);
            fflush(stdout);
            printf("Philosopher %d picked up the left chopstick\n", phil_id);
            while(!pthread_mutex_trylock(&chopstick[(phil_id+1) % 5])){
                pickup_right_chopstick(phil_id);
                fflush(stdout);
                printf("Philosopher %d picked up the right chopstick and is eating\n", phil_id);
            }
            fflush(stdout);
            putdown_left_chopstick(phil_id);
            pthread_mutex_unlock(&chopstick[(phil_id+4) % 5]);
            printf("Philosopher %d gave up, will try again\n", phil_id);
        } //end of while
        
  
                
    } //end of else
} //endo of function


/*
 * Uses pickup_left_chopstick and pickup_right_chopstick
 * to pick up the chopsticks
 */   
void putdown_chopsticks(int phil_id){
    fflush(stdout);
    putdown_left_chopstick(phil_id);
    pthread_mutex_unlock(&chopstick[(phil_id+4) % 5]);
    putdown_right_chopstick(phil_id);
    pthread_mutex_unlock(&chopstick[(phil_id+1) % 5]);
}
