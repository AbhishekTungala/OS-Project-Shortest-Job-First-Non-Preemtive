#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

enum ProcessType {
    CPU_BOUND,
    IO_BOUND
};

struct Process {
    string name;
    int arrival_time;
    int burst_time;
    ProcessType type;
};

bool compare(Process a, Process b) {
    return a.burst_time < b.burst_time;
}

void SJF(vector<Process> processes) {
    sort(processes.begin(), processes.end(), compare);
    int n = processes.size();
    int waiting_time[n], turnaround_time[n], total_waiting_time = 0, total_turnaround_time = 0;
    waiting_time[0] = 0;
    turnaround_time[0] = processes[0].burst_time;

    for (int i = 1; i < n; i++) {
        int time_passed = 0;
        for (int j = 0; j < i; j++) {
            time_passed += processes[j].burst_time;
        }
        waiting_time[i] = max(0, time_passed - processes[i].arrival_time);
        turnaround_time[i] = waiting_time[i] + processes[i].burst_time;
    }

    cout << "Process\tArrival Time\tBurst Time\tType\tWaiting Time\tTurnaround Time\n";

    for (int i = 0; i < n; i++) {
        total_waiting_time += waiting_time[i];
        total_turnaround_time += turnaround_time[i];
        cout << processes[i].name << "\t\t" << processes[i].arrival_time << "\t\t" << processes[i].burst_time << "\t\t";
        if (processes[i].type == CPU_BOUND) {
            cout << "CPU-Bound\t";
        } else {
            cout << "I/O-Bound\t";
        }
        cout << waiting_time[i] << "\t\t" << turnaround_time[i] << endl;
    }

    double avg_waiting_time = (double)total_waiting_time / n;
    double avg_turnaround_time = (double)total_turnaround_time / n;

    cout << "Average Waiting Time: " << avg_waiting_time << endl;
    cout << "Average Turnaround Time: " << avg_turnaround_time << endl;
}

int main() {
    vector<Process> processes;
    int n;

    cout << "Enter the number of processes: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        Process process;
        cout << "Enter process name, arrival time, burst time, and type (0 for CPU-bound, 1 for I/O-bound): ";
        cin >> process.name >> process.arrival_time >> process.burst_time >> (int&)process.type;
        processes.push_back(process);
    }

    SJF(processes);

    return 0;
}
