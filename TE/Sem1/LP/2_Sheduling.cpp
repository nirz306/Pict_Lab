#include<bits/stdc++.h>
using namespace std;

class FCFS{
    map<int,int> at_bt;
    vector <int> ct;
    vector<int> tat;
    vector<int> wt;

    public:
    void input(){
        int n; cout<<"Enter no of processes: "; cin>>n;
        for(int i=0;i<n;i++){
            int At,Bt;
            cout<<"Enter Arrival Time for process "<<i+1<<": "; cin>>At;
            cout<<"Enter Burst Time for process "<<i+1<<": "; cin>>Bt;
            at_bt[At]=Bt;
        }
    }

    void execute_ct(){
        int last_completed_time=0;
        for(auto i:at_bt){
                if(i.first <=last_completed_time){
                    last_completed_time+=i.second;    
                }
                else   
                   { last_completed_time=i.first+i.second;}
             ct.push_back(last_completed_time);
        }
    }

    void execute_tat_wt(){
        int j=0;
       for(auto i:at_bt){
            int Tat = ct[j]-i.first;
            int Wt = Tat-i.second;
            wt.push_back(Wt);
            tat.push_back(Tat);
            j++;
       }
    }

    void display(){
        int j=0;
        cout<<"Arrival Time "<<"  Burst Time "<<"  Completion Time"<<"  Turn Around Time"<<"  Waiting Time"<<endl;
        for(auto i:at_bt){
            cout<<i.first<<"                "<<i.second<<"             "<<ct[j]<<"                  "<<tat[j]<<"              "<<wt[j]<<endl;
            j++;
        }
    }
};

class SJF{
    vector<pair<int,int>> at_bt; 
    vector<int>ct;
    vector<int>tat;
    vector<int>wt;
    
    public:
    void input(){
        int n; cout<<"Enter no of processes: "; cin>>n;
        for(int i=0;i<n;i++){
            int At,Bt;
            cout<<"Enter Arrival Time for process "<<i+1<<": "; cin>>At;
            cout<<"Enter Burst Time for process "<<i+1<<": "; cin>>Bt;
            at_bt.push_back({At,Bt});
        }
    }

    void execute_ct(){
        sort(at_bt.begin(),at_bt.end());
        int last_completed_time=0;
        for(auto i:at_bt){
                if(i.first <=last_completed_time){
                    last_completed_time+=i.second;    
                }
                else   
                   { last_completed_time=i.first+i.second;}
             ct.push_back(last_completed_time);
        }   
    }

        void execute_tat_wt(){
        int j=0;
       for(auto i:at_bt){
            int Tat = ct[j]-i.first;
            int Wt = Tat-i.second;
            wt.push_back(Wt);
            tat.push_back(Tat);
            j++;
       }
    }

     void display(){
        int j=0;
        cout<<"Arrival Time "<<"  Burst Time "<<"  Completion Time"<<"  Turn Around Time"<<"  Waiting Time"<<endl;
        for(auto i:at_bt){
            cout<<i.first<<"                "<<i.second<<"             "<<ct[j]<<"                  "<<tat[j]<<"              "<<wt[j]<<endl;
            j++;
        }
    }




};


class  RR{
    vector<int> at;
    vector<int> bt;
    vector<int> time_arr; int time=0;
    queue<int>ready;
    queue<int>running;
    vector<int>running_arr;
     int TQ;
      int n; 
   

    public:
    
    void input(){
       cout<<"Enter no of processes: "; cin>>n;
        for(int i=0;i<n;i++){
            int At,Bt;
            cout<<"Enter Arrival Time for process "<<i+1<<": "; cin>>At;
            cout<<"Enter Burst Time for process "<<i+1<<": "; cin>>Bt;
            at.push_back(At); bt.push_back(Bt);
        }
        cout<<"Enter Time Quantum: "; cin>>TQ;
    }

     void execute_ct() {
    ready.push(0);  // Start with the first process (index 0)
    int table_ptr = 1;

    while (!ready.empty()) {
        int front = ready.front();
        ready.pop();
        running.push(front);

        if (bt[front] >= TQ) {
            bt[front] -= TQ;
            time += TQ;
        } else {
            time += bt[front];
            bt[front] = 0;
        }

        time_arr.push_back(time);

        // Add new processes to the ready queue if they have arrived
        while (table_ptr < n && time >= at[table_ptr]) {
            ready.push(table_ptr);
            table_ptr++;
        }

        // If the current process still has burst time, re-add it to the ready queue
        if (bt[front] != 0) {
            ready.push(front);
        }
    }
}


    void display(){
        for(auto i:time_arr){
            cout<<i<<" ";
        }

        while(!running.empty()){
            running_arr.push_back(running.front());
            running.pop();
        }

        cout<<endl;

        for(auto i:running_arr){
            cout<<"P"<<i+1<<" ";
        }

    }
    
};
int main(){
    // FCFS obj1;
    // obj1.input();
    // obj1.execute_ct();
    // obj1.execute_tat_wt();
    // obj1.display();
    // SJF obj2;
    // obj2.input();
    // obj2.execute_ct();
    // obj2.execute_tat_wt();
    // obj2.display();
    RR obj3;
    obj3.input();
    obj3.execute_ct();
    obj3.display();
}
