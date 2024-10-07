
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "functions.h"

#define NUM_SENSORS (GRID_SIZE * GRID_SIZE)

char floresta_area[GRID_SIZE][GRID_SIZE];
SensorNode sensors[GRID_SIZE][GRID_SIZE];

void init_floresta() {
    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            floresta_area[i][j] = '-';
            sensores[i][j].x = i;
            sensores[i][j].y = j;
            sensores[i][j].state = 0;
            pthread_mutex_init(&sensors[i][j].lock, NULL);
            pthread_cond_init(&sensors[i][j].cond, NULL);
        }
    }
}

void* sensor_thread(void* arg) {
    SensorNode* node = (SensorNode*)arg;
    while (1) {
        pthread_mutex_lock(&node->lock);
        pthread_cond_wait(&node->cond, &node->lock);
        pthread_mutex_unlock(&node->lock);
    }
}

void* incendio_init_thread(void* arg) {
    while (1) {
        sleep(3);
        int x = rand() % GRID_SIZE;
        int y = rand() % GRID_SIZE;

        pthread_mutex_lock(&sensors[x][y].lock);
        if (forest[x][y] == '-') {
            forest[x][y] = '@';
            printf("Localição de incendio: (%d, %d)\n", x, y);
        }
        pthread_mutex_unlock(&sensors[x][y].lock);
    }
}

void* control_center_thread(void* arg) {
    while (1) {
        sleep(1);
    }
}

int main() {
    srand(time(NULL));
   init_floresta();
    pthread_t sensor_threads[NUM_SENSORS];
    pthread_t fire_thread, control_thread;
    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            pthread_create(&sensor_threads[i * GRID_SIZE + j], NULL, sensor_thread, &sensors[i][j]);
        }
    }
    pthread_create(&fire_thread, NULL, incendio_init_thread, NULL);
    pthread_create(&control_thread, NULL, control_center_thread, NULL);
    pthread_join(fire_thread, NULL);
    pthread_join(control_thread, NULL);
    for (int i = 0; i < NUM_SENSORS; ++i) {
        pthread_join(sensor_threads[i], NULL);
    }
    return 0;
}
