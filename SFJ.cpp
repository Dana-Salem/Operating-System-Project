#include <iostream>
using namespace std;

struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int waiting_time;
    int turnaround_time;
};

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;
    Process proc[n];

    
    for (int i = 0; i < n; i++) {
        proc[i].id = i + 1;
        cout << "Enter arrival time and burst time for process P" << proc[i].id << ": ";
        cin >> proc[i].arrival_time >> proc[i].burst_time;
    }

    
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (proc[j].arrival_time > proc[j + 1].arrival_time) {
              
                Process temp = proc[j];
                proc[j] = proc[j + 1];
                proc[j + 1] = temp;
            }
        }
    }

    int current_time = 0;
    int completed_count = 0;
    bool completed[n] = {false}; 

    while (completed_count < n) {
        int id_index = -1;
        int minBurst = 99999; 

      
        for (int i = 0; i < n; i++) {
            if (!completed[i] && proc[i].arrival_time <= current_time && proc[i].burst_time < minBurst) {
                minBurst = proc[i].burst_time;
                id_index = i;
            }
        }

       
        if (id_index == -1) {
            current_time++;
            continue;
        }

       
        proc[id_index].waiting_time = current_time - proc[id_index].arrival_time;
        current_time += proc[id_index].burst_time;
        proc[id_index].turnaround_time = proc[id_index].waiting_time + proc[id_index].burst_time;

        completed[id_index] = true;  
        completed_count++;
    }

   
    cout << "\nP\tAT\tBT\tWT\tTAT\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << proc[i].id << "\t" << proc[i].arrival_time << "\t" << proc[i].burst_time << "\t" 
             << proc[i].waiting_time << "\t" << proc[i].turnaround_time << "\n";
    }

 
    double totalWaiting = 0, totalTurnaround = 0;
    for (int i = 0; i < n; i++) {
        totalWaiting += proc[i].waiting_time;
        totalTurnaround += proc[i].turnaround_time;
    }

    cout << "\nAverage Waiting Time = " << (totalWaiting / n);
    cout << "\nAverage Turnaround Time = " << (totalTurnaround / n) << "\n";

    return 0;
}
