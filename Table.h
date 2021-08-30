/**
 * @desc The table at which the philosophers dine
 */

#ifndef TABLE_H
#define TABLE_H

#include <mutex>
#include <vector>
#include <memory>
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

class Table {
private:
    int seats; // the number of philosophers seated at the table
    vector<shared_ptr<timed_mutex>> forks; // each fork is a timed mutex
    mutex logMutex; // lock logging functions
    chrono::system_clock::time_point startTime; // to measure time in log function
    string filename;
    fstream fs;

    /**
     * @desc Logs to screen and file
     * @param msg - the message to log
     */
    void log(string msg);
public:
    /**
     * constructor
     * @param iSeats - how many seats/philosophers are there at the table
     */
    explicit Table(int iSeats, string aFilename);

    ~Table();

    /**
     * returns a pointer to the left fork for a seat/philosopher
     * @param seatNr - the philosophers seatNr
     * @return - pointer to the left fork
     */
    shared_ptr<timed_mutex> getLeftForkPtr(int seatNr) { return forks[seatNr]; }

    /**
     * returns a pointer to the right fork for a seat/philosopher
     * @param seatNr - the philosophers seatNr
     * @return - pointer to the right fork
     */
    shared_ptr<timed_mutex> getRightForkPtr(int seatNr) { return forks[(seatNr + 1) % seats]; }

    /*
     * The following functions creates log entries for the philosophers different actions
     */
    void holdLeftFork(int seatNr);
    void releaseLeftFork(int seatNr);
    void holdRightFork(int seatNr);
    void releaseRightFork(int seatNr);
    void eating(int seatNr);
    void finishedEating(int seatNr);
    void thinking(int seatNr);
};
#endif //TABLE_H
