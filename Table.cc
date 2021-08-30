#include "Table.h"

void Table::log(string msg) {
    auto timeStamp = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now() - startTime).count();
    lock_guard<mutex> lock(logMutex);
    cout << "time stamp(ms): " << timeStamp << " action: " << msg << endl;
    fs << "time stamp(ms): " << timeStamp << " action: " << msg << endl;
}

Table::Table(int iSeats, string aFilename) : seats(iSeats), filename(aFilename) {
    // create mutex:es pointers
    for (int i = 0; i < seats; i++) {
        forks.push_back(make_shared<timed_mutex>());
    }

    // open filestream
    fs.open(filename, fstream::out);

    // start timer
    startTime = chrono::system_clock::now();
}

Table::~Table() { fs.close(); }

void Table::holdLeftFork(int seatNr) {
    stringstream ss;
    ss << "Philosopher #" << seatNr << " holds left fork";
    log(ss.str());
}

void Table::releaseLeftFork(int seatNr) {
    stringstream ss;
    ss << "Philosopher #" << seatNr << " released left fork";
    log(ss.str());
}

void Table::holdRightFork(int seatNr) {
    stringstream ss;
    ss << "Philosopher #" << seatNr << " holds right fork";
    log(ss.str());
}

void Table::releaseRightFork(int seatNr) {
    stringstream ss;
    ss << "Philosopher #" << seatNr << " released right fork";
    log(ss.str());
}

void Table::eating(int seatNr) {
    stringstream ss;
    ss << "Philosopher #" << seatNr << " is eating";
    log(ss.str());
}

void Table::finishedEating(int seatNr) {
    stringstream ss;
    ss << "Philosopher #" << seatNr << " finished eating";
    log(ss.str());
}

void Table::thinking(int seatNr) {
    stringstream ss;
    ss << "Philosopher #" << seatNr << " is thinking";
    log(ss.str());
}
