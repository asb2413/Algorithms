#include <iostream>
#include <array>
using namespace std;
class char_frequencies{

    public:

    char_frequencies(){};

    void ASCII_method(string text){

        cout<< "ASCII_method"<<endl;
        int array[127]={0};
        for(char c : text){
            int current_char = int(c);
            array[current_char]++;
        }
        cout<<"char frequencies"<<endl;
        cout<<"-----------------"<<endl;
        cout<<text<<endl;
        for(int i = 0; i < 127; i++){

            if(array[i] > 0 ){

                cout << char(i) <<" , "<< array[i]<<endl;

            }else{continue;}       

        }

    }

};