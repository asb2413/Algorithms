#include <array>
using namespace std;

void merge(int array[], int start, int mid, int end) {
    int left_length = mid - start + 1;
    int right_length = end - mid;
    
    int left_array[left_length];
    int right_array[right_length];
    
    for(int i=0; i < left_length; i++){
        left_array[i] = array[start + i];
    }
    
    for(int j=0; j < right_length; j++){
        right_array[j] = array[mid + 1 + j];
    }

    int i =0, j =0, k = start;
    while(i < left_length && left_array[i] <= 0){

            array[k] = left_array[i];
            i++; 
            k++;
            
    }

    while(j < right_length && right_array[j] <= 0 ){

            array[k] = right_array[j];
            j++;
            k++;
        
    }
    
    while(i < left_length){
        array[k] = left_array[i];
        i++;
        k++;
    }

    while(j < right_length){
        array[k] = right_array[j];
        j++;
        k++;
    }
}


void segregate(int array[], int start, int end) {
    if(end <= start) return;

    int mid = (end + start) / 2;
    segregate(array, start, mid);
    segregate(array, mid+1, end);
    merge(array, start, mid, end);
}
//---------------------------------------------------

/*

// Test the segregate function with an example array
int main() {
    int array[] = {9,5,1,4};
    int size = sizeof(array)/sizeof(array[0]);

    // Print the original array
    cout << "Original array: ";
    for (int i = 0; i < size; i++) {
        cout << array[i] << " ";
    }
    cout << endl;

    // Segregate the array and print the segregated array
    segregate(array, 0, size - 1);
    cout << "Segregated array: ";
    for (int i = 0; i < size; i++) {
        cout << array[i] << " ";
    }
    cout << endl;

    return 0;
}

*/