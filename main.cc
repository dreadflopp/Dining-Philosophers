/**
 * @desc Solution for the dining philosophers
 * @author Mattias Lindell
 * @date 190117
 */

#include <iostream>
#include <memory>
#include <cstring>
#include "Table.h"
#include "Philosopher.h"

using namespace std;

int main(int argc, char *argv[]) {
    // default values
    int philosophersCount = 6;
    int plates = 5;
    string logFilename = "philo.log";

    // parse command line parameters
    bool parametersOK = true;
    for (int i = 1; i < argc; i = i+2)
        if (i < argc) {
            if (strcmp(argv[i], "-n") == 0) {
                philosophersCount = stoi(argv[i + 1]);
            } else if (strcmp(argv[i], "-d") == 0) {
                plates = stoi(argv[i + 1]);
            } else if (strcmp(argv[i], "-f") == 0) {
                logFilename = argv[i + 1];
            } else {
                parametersOK = false;
            }
        } else {
            parametersOK = false;
    }

    if (philosophersCount < 4 || philosophersCount > 14)
        parametersOK = false;
    if (plates < 4 || plates > 10)
        parametersOK = false;

    if (!parametersOK) {
        cout << "Usage: " << argv[0] << " -n <nr of philosophers (4-14)> -d <nr of plates (4-10) -f <log filename>" << endl;
        return 0;
    }

    // create table and philosophers. Each philosopher is created in its own thread.
    //Table tbl(philosophersCount, logFilename);
    //shared_ptr<Table> table =
    //shared_ptr<Table> table = make_shared<Table>(philosophersCount, logFilename);
    shared_ptr<Table> table(new Table(philosophersCount, logFilename));

    vector<thread> philosopherThreads; // stores philosopher threads
    for (int i = 0; i < philosophersCount; i++) {
        philosopherThreads.emplace_back([table, i, plates](){
            Philosopher ph(table, i, plates);
            ph.startDinner();
        });
    }

    // Join threads
    for (auto &thr: philosopherThreads) {
        thr.join();
        cout << "** Thread joined!" << endl;
    }
    return 0;
}