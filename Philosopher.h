#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

#include <memory>
#include <random>
#include <thread>
#include <iostream>
#include "Table.h"

class Philosopher {
private:
    shared_ptr<Table> table; // the table where the philosophers are seated
    int seatNr; // the number of the seat where the philosopher is seated
    int platesLeft; // how many remaining plates to eat are there?
    timed_mutex *leftFork; // the left fork
    timed_mutex *rightFork; // the right fork

    // a random number generator used in different functions
    random_device rd;
    mt19937 generator;
    uniform_int_distribution<int> distribution_think;
    uniform_int_distribution<int> distribution_eat;
    uniform_int_distribution<int> distribution_threadLock;

public:
    /**
     * Constructor
     * @param aTable - pointer to the table where the philosopher is seated
     * @param aSeatNr - the seat where the philosopher is seated
     * @param plates - the number of plates that the philosopher shall consume
     */
    Philosopher(shared_ptr<Table> aTable, int aSeatNr, int plates);

    /**
     * The philosopher thinks (sleeps) for a random ammount of time
     */
    void thinking();

    /**
     * The philosopher eats for a random amount of time
     */
    void eating();

    /**
     * The philosopher consumer all plates and thinks between each plate
     */
    void startDinner() {
        while (platesLeft > 0) {
           thinking();
           eating();
        }
    }
};


#endif //PHILOSOPHER_H
