#include<iostream>
using namespace std;

int main()
{
    int n;
    cout<<"Please enter the number of processes: ";
    cin>>n;

    int id[20];
    int at[20], bt[20], rt[20], wait[20] = {0}, tat[20] = {0};
    int finished = 0, t = 0;
    bool done[20] = {false};

    for(int i=0;i<n;i++)
    {
        id[i] = i+1;
        cout<<"Please enter arrival time and burst time for process "<<i+1<<": ";
        cin>>at[i]>>bt[i];
        rt[i]=bt[i];
    }

    while(finished < n)
    {
        int MIN_RT = 100000;
        int j = -1;

        for(int i=0;i<n;i++)
        {
            if(at[i]<=t && rt[i]>0 && rt[i] < MIN_RT)
            {
                MIN_RT=rt[i];
                j = i;
            }
        }

        if(j!=-1)
        {
            rt[j]--;
            t++;
            if(rt[j] == 0)
            {
                tat[j] = t - at[j];
                wait[j] = tat[j] - bt[j];
                done[j] = true;
                finished++;
            }
        }
        else
            t++;


    }

    double totalWaiting = 0, totalTurnAround = 0;
    cout<<"\nProcess\tat\tbt\twt\ttat"<<endl;

    for(int i=0;i<n;i++)
    {
        cout<<"P"<<id[i] <<"\t" <<at[i] <<"\t"<<bt[i]<< "\t" << wait[i]<<"\t"<<tat[i]<<endl;
        totalWaiting+=wait[i];
        totalTurnAround+=tat[i];

    }

     cout<<"\nAverage Waiting Time = "<<totalWaiting/n<<"\n"<<"Average Turnaround Time = "<<totalTurnAround/n<<endl;
    return 0;
}