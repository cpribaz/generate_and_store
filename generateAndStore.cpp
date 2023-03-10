#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <chrono>
#include <thread>
#include <signal.h>
#include <vector> 

using namespace std;

vector<pid_t> childPids;

void terminateChild(){
    for(int i=0; i<childPids.size(); i++){
        kill(childPids[i], SIGKILL);
    }
}

int main() {
    while (true) {
        string userData;
        cout << "Enter some text (type 'Done' to exit): ";
        getline(cin, userData);
        if (userData == "Done") {
            terminateChild();
            break;
        }

        pid_t pid = fork();

        if (pid == 0) {
            ofstream file;
            file.open("pid_" + to_string(getpid()) + ".txt");

            while(true){
                file << userData << endl;
                sleep(1);
            }

            file.close();
        } else {
            childPids.push_back(pid);
        }
    }

    return 0;
}