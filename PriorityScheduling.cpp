#include<iostream>
using namespace std;

int main()
{
    int n;
    cout<<"Please enter the number of processes: ";
    cin>>n;

    int id[20];
    int arrival[20],burst[20],priority[20],wait[20],turnAround[20],done[20] = {0};

    for(int i=0;i<n;i++)
    {
        id[i] = i+1;
        cout<<"Please enter arrival time, burst time, and priority for process "<<i+1<<": ";
        cin>>arrival[i]>>burst[i]>>priority[i];
    }
    int t=0,finished=0;
    while(finished<n)
    {
        int j=-1;
        int min_pr=100000;
        for(int i=0;i<n;i++)
        {
            if(!done[i] && arrival[i] <= t && priority[i] < min_pr)
             {
                 min_pr = priority[i];
                 j = i;
             }
        }


       if(j!=-1)
       {
           wait[j] = t-arrival[j];
           t+=burst[j];
           turnAround[j] = t - arrival[j];
           done[j] = 1;
           finished++;

       }
       else
       t++;

    }


    double totalWait = 0, total = 0;
    cout<<"\nProcess\tAT\tBT\tP\tWT\tTAT"<<endl;
    for(int i=0;i<n;i++)
    {
        cout<<"P"<<id[i] <<"\t" <<arrival[i] <<"\t"<<burst[i]<< "\t" << priority[i]<< "\t" << wait[i]<<"\t"<<turnAround[i]<<endl;
        totalWait+=wait[i];
        total+=turnAround[i];
    }

    cout<<"\nAverage Waiting Time = "<<totalWait/n<<"\n"<<"Average Turnaround Time = "<<total/n<<endl;
    return 0;
}