#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define POP_SIZE 20
#define SURVIVORS 5
#define GENE_POOL 26

typedef struct {
    char value;     // gene character
    int fitness;    // score
} Gene;

char gene_types[GENE_POOL] = {
    'a','b','c','d','e','f','g','h','i','j',
    'k','l','m','n','o','p','q','r','s','t',
    'u','v','w','x','y','z'
};

Gene population[POP_SIZE];


// random gene generator
char random_gene() {
    return gene_types[rand() % GENE_POOL];
}


// fitness function
// earlier letters are stronger: a > z
int fitness(char g) {
    return 'z' - g;
}


// initialize population
void generate_population() {
    for (int i = 0; i < POP_SIZE; i++) {
        population[i].value = random_gene();
        population[i].fitness = fitness(population[i].value);
    }
}


// bubble sort by fitness
void bubble_sort() {
    for (int i = 0; i < POP_SIZE - 1; i++) {
        for (int j = 0; j < POP_SIZE - i - 1; j++) {

            if (population[j].fitness < population[j + 1].fitness) {

                Gene temp = population[j];
                population[j] = population[j + 1];
                population[j + 1] = temp;
            }
        }
    }
}


// create child from two parents
char breed(char a, char b) {

    // average character position
    int posA = a - 'a';
    int posB = b - 'a';

    int childPos = (posA + posB) / 2;

    // mutation chance
    if (rand() % 100 < 20) {
        childPos = rand() % 26;
    }

    return 'a' + childPos;
}


// next generation
void evolve() {

    // strongest survive
    for (int i = SURVIVORS; i < POP_SIZE; i++) {

        int p1 = rand() % SURVIVORS;
        int p2 = rand() % SURVIVORS;

        char child = breed(
            population[p1].value,
            population[p2].value
        );

        population[i].value = child;
        population[i].fitness = fitness(child);
    }
}


void print_population() {

    for (int i = 0; i < POP_SIZE; i++) {
        printf("%c (%d)\n",
            population[i].value,
            population[i].fitness
        );
    }

    printf("\n");
}


int main() {

    srand(time(NULL));

    generate_population();

    for (int generation = 0; generation < 10; generation++) {

        bubble_sort();

        printf("Generation %d\n", generation);
        print_population();

        evolve();
    }

    return 0;
}
