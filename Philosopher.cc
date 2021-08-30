#include "Philosopher.h"

Philosopher::Philosopher(shared_ptr<Table> aTable, int aSeatNr, int plates) : table(aTable), seatNr(aSeatNr), platesLeft(plates) {
    leftFork = table->getLeftForkPtr(seatNr).get();
    rightFork = table->getRightForkPtr(seatNr).get();

    // random generator
    generator = mt19937(rd());
    distribution_think = uniform_int_distribution<int>(1, 5);
    distribution_eat = uniform_int_distribution<int>(1, 5);
    distribution_threadLock = uniform_int_distribution<int>(100, 1000); // milliseconds to try to pick up right fork
}

void Philosopher::thinking() {
    table->thinking(seatNr);
    this_thread::sleep_for(chrono::seconds(distribution_think(generator)));
}

void Philosopher::eating() {
    // locks for the mutex's. defer_lock == don't lock yet
    unique_lock<timed_mutex> leftLock(*leftFork, defer_lock);
    unique_lock<timed_mutex> rightLock(*rightFork, defer_lock);

    /*
     * Using lock to lock both lock while preventing deadlock works better than the code following it
     * but that won't allow monitoring of the philosopher as it picks up/puts down the fork
     */
    // lock(leftLock, rightLock);
    bool plateFinished = false; // true when both locks are acquired
    while (!plateFinished) {
        // pick up the left fork, block until successful
        try {
            leftLock.lock();
        } catch (exception &e) {
            throw e;
        }
        table->holdLeftFork(seatNr);

        /*
         * try to pick up right fork, block for a random amount of time if not successful
         * time to block can be tweaked in constructor
         */
        try {
            if (rightLock.try_lock_for(chrono::milliseconds(distribution_threadLock(generator)))) {
                table->holdRightFork(seatNr);
                table->eating(seatNr);
                this_thread::sleep_for(chrono::seconds(distribution_eat(generator)));
                plateFinished = true; // both locks are acquired, quit the while-loop
                platesLeft--;
                table->finishedEating(seatNr);
                rightLock.unlock();
                table->releaseRightFork(seatNr);
            }
        } catch (exception &e) {
            throw e;
        }
        leftLock.unlock();
        table->releaseLeftFork(seatNr);
    }

    /*
     * The code below can be used if both locks are locked at once using lock()
     */
    /*
    table->eating(seatNr);
    int secondsToSleep = distribution(generator);
    this_thread::sleep_for(chrono::seconds(secondsToSleep));

    platesLeft--;

    table->finishedEating(seatNr);
    leftLock.unlock();
    rightLock.unlock();
    */
}
