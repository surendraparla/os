
#include <iostream>
#include <thread>
#include <vector>
using namespace std;

#define BufferSize 5

vector<int> Buffer(BufferSize,0);
static int mutex=1, emp = BufferSize, full = 0;
static int in = 0, out = 0;
void wait(int &sem){
    while(sem <= 0);
        sem--;
}
void signal(int &sem){
    sem++;

}
void producer(){
    cout<< "running producer" <<endl;
    while(1){
        wait(emp);
        wait(mutex);
        Buffer[in] = in+1;
        cout<<"item produced: "<< in+1 <<endl;
        in = (in+1)%BufferSize;
     // cout<<empty<<"  "<<full<<"  "  ;
        signal(mutex);
        signal(full);
    }
}
void consumer(){
    cout<<"running consumer" <<endl;
   // cout<<empty<<"  "<<full<<"  "  ;
    while(1){
        wait(full);
        wait(mutex);
        cout<<"item consumed: "<< Buffer[out] <<endl;
        out = (out + 1)%BufferSize;
        //Buffer[full] = full;
      //  cout<<empty<<"  "<<full<<"  "  ;
        signal(mutex);
        signal(emp);
    }
}
int main(){
    cout<<"Starting main function"<<endl;
    thread con(consumer);
     thread prod(producer);
    prod.join();
      con.join();
    return 0;
}
