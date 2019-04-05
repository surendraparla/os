#include <iostream>
#include <thread>
#include <vector>
using namespace std;

static int rw_mutex = 1, mutex =1, rc = 0;
void wait(int &sem){
    while(sem <= 0);
        sem--;
}
void sig(int &sem){
    sem++;

}
void writer(){
    cout<<" writers function " <<endl;
    while(1){
        wait(rw_mutex);
        cout<<"writing is performed" << endl;
        sig(rw_mutex);
    }
}
void readers(){
    cout<<" readers function " <<endl;
    while(1){
        wait(mutex);
        rc++;
        if(rc == 1)
         wait(rw_mutex);
         sig(mutex);
         cout<<"reading is being performed"<<endl;
         wait(mutex);
         rc--;
         if(rc == 0)
          sig(rw_mutex);
          sig(mutex);
    }
}
int main() {
	cout<<"Starting main function"<<endl;
    thread read(readers);
    thread write(writer);
    read.join();
    write.join();
	return 0;
}
