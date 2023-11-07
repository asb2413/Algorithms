#include <iostream>
#include <array>
using namespace std;
void activiy_selector(int start[],int end[]){

    int result[6]={0};
    int i=1;
    int j=0;

    for(;i<6;i++){

        if(start[i]>= end[j]){

            result[i] = i;
            cout<<" start: " << start[i] << " end: " << end[i]<<endl;
            j = i;
        }

    }
    
    
}
//---------------------------------------------------
/*
int main() {
    
    int start[6]={9,11,11,12,14,16};
    int end[6]={10,12,12,13,14,15};
    activiy_selector(start,end);

    return 0;
}*/