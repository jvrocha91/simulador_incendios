
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "functions.h"
#ifndef FUNCTIONS_H
#define FUNCTIONS_H


extern char floresta_area[GRID_SIZE][GRID_SIZE];
extern SensorNode sensors[GRID_SIZE][GRID_SIZE];

void print_floresta() {
    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            printf("%c ", forest[i][j]);
        }
        printf("\n");
    }
}

void log_event(const char* event) {
    FILE* log_file = fopen("log.txt", "a");
    if (log_file != NULL) {
        fprintf(log_file, "%s\n", event);
        fclose(log_file);
    }
}

#define GRID_SIZE 30
typedef struct {
    int x, y;
    pthread_mutex_t lock;
    pthread_cond_t cond;
    int state;
} SensorNode;

void init_floresta();
void* sensor_thread(void* arg);
void* incendio_init_thread(void* arg);
void* control_center_thread(void* arg);
void print_floresta();
void log_event(const char* event);

#endif
