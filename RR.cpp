#include <iostream>
using namespace std;

int main() {
    int n, timeQuantum;
    cout << "Enter number of processes: ";
    cin >> n;

    int arrivalTime[100], burstTime[100], remainingTime[100];
    int waitingTime[100], turnaroundTime[100], completionTime[100];
    int i;

    for (i = 0; i < n; i++) {
        cout << "Enter arrival time for process P" << i + 1 << ": ";
        cin >> arrivalTime[i];
    }

    for (i = 0; i < n; i++) {
        cout << "Enter burst time for process P" << i + 1 << ": ";
        cin >> burstTime[i];
        remainingTime[i] = burstTime[i];
    }

    cout << "Enter time quantum: ";
    cin >> timeQuantum;

    int time = 0, done = 0;
    int queue[100], front = 0, rear = 0;
    bool inQueue[100] = {false};

    for (i = 0; i < n; i++) {
        if ((arrivalTime[i] <= time)&&(!inQueue[i])) {
            queue[rear++] = i;
            inQueue[i] = true;
        }
    }

    while (done < n) {
        if (front == rear) {
            time++;
            for (i = 0; i < n; i++) {
                if ((arrivalTime[i] <= time)&&(!inQueue[i] )&&(remainingTime[i] > 0)){
                    queue[rear++] = i;
                    inQueue[i] = true;
                }
            }
            continue;
        }

        int idx = queue[front++];
        if (remainingTime[idx] > timeQuantum) {
            time += timeQuantum;
            remainingTime[idx] -= timeQuantum;
        } else {
            time += remainingTime[idx];
            remainingTime[idx] = 0;
            completionTime[idx] = time;
            turnaroundTime[idx] = time - arrivalTime[idx];
            waitingTime[idx] = turnaroundTime[idx] - burstTime[idx];
            done++;
        }

        for (i = 0; i < n; i++) {
            if ((arrivalTime[i] <= time)&&(!inQueue[i] )&&(remainingTime[i] > 0)) {
                queue[rear++] = i;
                inQueue[i] = true;
            }
        }

        if (remainingTime[idx] > 0) {
            queue[rear++] = idx;
        }
    }

    float totalWaiting = 0, totalTurnaround = 0;
    cout << "\nPID\tArrival\tBurst\tWaiting\tTurnaround\n";
    for (i = 0; i < n; i++) {
        cout << "P" << i + 1 << "\t" << arrivalTime[i] << "\t" << burstTime[i]<< "\t" << waitingTime[i] << "\t" << turnaroundTime[i] << endl;
        totalWaiting += waitingTime[i];
        totalTurnaround += turnaroundTime[i];
    }

    cout << "Average Waiting Time = " << (totalWaiting / n) << endl;
    cout << "Average Turnaround Time = " << (totalTurnaround / n) << endl;

    return 0;
}
