
#include <iostream>
#include <thread>
#include <vector> 
using namespace std;

 int BufferSize = 5;
 vector<int> Buffer(BufferSize,0);
int mutex=1, empty = BufferSize, full = 0;
static int in = 0, out = 0;
void wait(int *sem){
    while(*sem <= 0);
      *sem--;
}
void signal(int *sem){
    *sem++;
}
void producer(){
    cout<< "running producer" <<endl;
    while(1){
        wait(&empty);
        wait(&mutex);
        Buffer[in] = in+1;
        cout<<"item produced: "<< in+1 <<endl;
        in = (in+1)%BufferSize;
        //Buffer[full] = full;
        signal(&mutex);
        signal(&full);
    }
}
void consumer(){
    cout<<"running consumer" <<endl;
    while(1){
        wait(&full);
        wait(&mutex);
        cout<<"item consumed: "<< Buffer[out] <<endl;
        out = (out + 1)%BufferSize;
        //Buffer[full] = full;
        signal(&mutex);
        signal(&empty);
    }
}
int main(){
    int n;
    cout<<"Enter the BufferSize"<<endl;
    cin>>BufferSize;
    thread con(consumer);
    thread prod(producer);
    con.join();
    prod.join();
    return 0;
}