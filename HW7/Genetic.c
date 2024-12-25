/*
    File Name : Genetic.c
    Description : 알고리즘 HW7 과제 중 1. Genetic 구현

    Input: 강의자료 Chapter 8-1, 11p의 점 A, B, C, D, E, F, G, H

    - 시작 점은 A로 고정

    - A=(0,3), B=(7,5), C=(6,0), D=(4,3), E=(1,0), F=(5,3), H=(4,1), G=(2,2)
    
    Output: 이동 순서, 이동 거리
*/

/* Heading Comments
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#define NUM_CITIES 8
#define POP_SIZE 5040 // (7!)
#define MUTATION_RATE 0.01
#define CROSSOVER_RATE 1.0
#define MAX_GENERATIONS 1000

//Struct Set
typedef struct {
    int path[NUM_CITIES];
    double fitness;
} Set;

double cities[NUM_CITIES][2] = {
    {0, 3}, {7, 5}, {6, 0}, {4, 3}, {1, 0}, {5, 3}, {4, 1}, {2, 2}
};

char city_names[NUM_CITIES] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};

Set gen[POP_SIZE];
int gen_count = 0;

// distance calculation
double distance(int a, int b) {
    return sqrt(pow(cities[a][0] - cities[b][0], 2) + pow(cities[a][1] - cities[b][1], 2));
}

// Total distance
double calculate_fitness(int path[]) {
    double total = 0.0;
    for (int i = 0; i < NUM_CITIES - 1; i++) {
        total += distance(path[i], path[i + 1]);
    }
    total += distance(path[NUM_CITIES - 1], path[0]);
    return 1 / total; // Fitness 
}

// Create all possible set
void create_set(int *path, int left, int right) {
    if (left == right) {
        Set ind;
        ind.path[0] = 0; // Starting Point
        for (int i = 0; i < right + 1; i++) {
            ind.path[i + 1] = path[i];
        }
        ind.fitness = calculate_fitness(ind.path);
        gen[gen_count++] = ind;
    } else {
        for (int i = left; i <= right; i++) {
            int temp = path[left];
            path[left] = path[i];
            path[i] = temp;

            create_set(path, left + 1, right);

            temp = path[left];
            path[left] = path[i];
            path[i] = temp; 
        }
    }
}

// Create an initial candidate solution set
void init_set() {
    int path[NUM_CITIES - 1];
    for (int i = 1; i < NUM_CITIES; i++) {
        path[i - 1] = i; // cities except the starting city
    }
    create_set(path, 0, NUM_CITIES - 2); // Create all possible set
}

// Cycle Crossover 
void cycle_crossover(Set *parent1, Set *parent2, Set *child1, Set *child2) {
    if (((double)rand() / RAND_MAX) <= CROSSOVER_RATE) {
        int visited[NUM_CITIES] = {0};
        int index = 1;      
        int start = parent1->path[index]; 

        memset(child1->path, -1, sizeof(child1->path));
        memset(child2->path, -1, sizeof(child2->path));

        while (!visited[index]) {
            child1->path[index] = parent1->path[index];
            child2->path[index] = parent2->path[index];
            visited[index] = 1;  

            int next_city = parent1->path[index];
            for (int i = 1; i < NUM_CITIES; i++) {
                if (parent2->path[i] == next_city) {
                    index = i; 
                    break;
                }
            }
        }

        for (int i = 1; i < NUM_CITIES; i++) {
            if (child1->path[i] == -1) {
                child1->path[i] = parent2->path[i];
            }
            if (child2->path[i] == -1) {
                child2->path[i] = parent1->path[i];
            }
        }


        child1->path[0] = 0;
        child2->path[0] = 0;
    } else {
        // Crossover rate X
        *child1 = *parent1;
        *child2 = *parent2;
    }
}


// Mutate 
void mutate(Set *ind) {
    for (int i = 1; i < NUM_CITIES; i++) {
        if (((double)rand() / RAND_MAX) < MUTATION_RATE) {
            int b = rand() % (NUM_CITIES - 1) + 1;
            int temp = ind->path[i];
            ind->path[i] = ind->path[b];
            ind->path[b] = temp;
        }
    }
}

// Evolve Gen.
void evolve() {
    Set new_gen[POP_SIZE];
    int new_gen_count = 0;

    while (new_gen_count < POP_SIZE) {
        Set parent1 = gen[rand() % gen_count];
        Set parent2 = gen[rand() % gen_count];

        Set child1, child2;
        cycle_crossover(&parent1, &parent2, &child1, &child2);
        mutate(&child1);
        mutate(&child2);
        child1.fitness = calculate_fitness(child1.path);
        child2.fitness = calculate_fitness(child2.path);

        new_gen[new_gen_count++] = child1;
        if (new_gen_count < POP_SIZE) {
            new_gen[new_gen_count++] = child2;
        }
    }

    for (int i = 0; i < POP_SIZE; i++) {
        gen[i] = new_gen[i];
    }
}

void print_best_solution() {
    double best_fitness = 0.0;
    int best_idx = 0;
    for (int i = 0; i < gen_count; i++) {
        if (gen[i].fitness > best_fitness) {
            best_fitness = gen[i].fitness;
            best_idx = i;
        }
    }
    printf("Route: ");
    for (int i = 0; i < NUM_CITIES; i++) {
        printf("%c ", city_names[gen[best_idx].path[i]]);
    }
    printf("%c\n", city_names[gen[best_idx].path[0]]); 
    printf("Distance: %.2f\n", 1 / best_fitness);
}

// Main
int main() {
    srand(time(NULL)); // for random number
    init_set(); // Create an initial candidate solution set

    for (int gen = 0; gen < MAX_GENERATIONS; gen++) {
        evolve();
    }

    print_best_solution(); // Print
    return 0;
}
