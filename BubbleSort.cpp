#include <iostream>
#include <vector>
#include <ctime>
#include <cassert>
using namespace std;

// MergeSort function declarations
void mergeSort(vector<int>& a, vector<int>& tmp, int left, int right);
void mergeSortedLists(vector<int>& a, vector<int>& tmp, int leftPos, int rightPos, int rightEnd);

// BubbleSort function declaration
void swap (int *a, int *b);
void bubbleSort(int *a, int n);

int main(int argc, char* argv[]) {

    // check if the terminal input is not 3, if not then let the user re-do
    if (argc != 3){
        cout << "So sorry that you miss some inputs! Please RE-run and TYPE in: ./BubbleSort <Seed> <Size>" << endl;
        cout << endl;
        exit(1);

    }

    cout << endl << "-----------------------Welcome to Long's Sorting Family!------------------------------------" << endl;

    // unit test for merge
    // print out messages for the comparsion between
    // the original unit test vector's expected sorted vector and the actual one
    cout << " * SWAP's Unit Test will be conducted first~" << endl;
    int unitestSwapArr[] = {1, 100000000};
    int unitestExpecytedSwapArr[] = {100000000, 1};
    swap(unitestSwapArr[0], unitestSwapArr[1]);

    cout << " * * Expect array {1, 100000000} to get {100000000, 1}" << endl;
    cout << "                         - Actually get {";
    for(int unittest = 0; unittest < 2; unittest++) {
        if (unittest == 0){
            cout << unitestSwapArr[unittest] << ", ";
        }
        else{
            cout << unitestSwapArr[unittest] << "}" << endl;
        }
    }
    for(int i = 0; i < 2; i++) {
        assert(unitestSwapArr[i] == unitestExpecytedSwapArr[i]);
    }



    cout << " * BUBBLESORT's Unit Test will be conducted~" << endl;
    //declare variables for the unit test
    int unittestArray[] = {1, 3, 98, 4, 99, 2, 97};
    int unittestExpectedOutput[] = {1, 2, 3, 4, 97, 98, 99};

    cout << " * * Expect array {1, 3, 98, 4, 99, 2, 97} to get {1, 2, 3, 4, 97, 98, 99}" << endl;
    cout << "                                   - Actually get {";

    // call the bubbleSort method for sorting
    // bubbleSort(array to be sorted, size);
    bubbleSort(unittestArray, 7);
    // print the sorted vector by using a for loop
    for(int unittest = 0; unittest < 7; unittest++) {
        if (unittest != 6){
            cout << unittestArray[unittest] << ", ";
        }
        else{
            cout << unittestArray[unittest] << "}" << endl << endl;
        }
    }
    // use assert to double check the unit test
    for(int i = 0; i < 7; i++) {
        assert(unittestArray[i] == unittestExpectedOutput[i]);
    }

    cout << " * Here comes your own vectors: " << endl;

    // get input: first is random seed, second is vector length
    int seed;
    cout << "Please Use Terminal to Enter Seed. " << endl;
    seed = atoi(argv[1]);
    //cin >> seed ;

    // get input: first is random seed, second is vector length
    int length;
    cout << "Please Use Terminal to Enter Length. " ;
    length = atoi(argv[2]);
    //cin >> length;




    // srand() function
    srand(seed);
    cout << endl;

    vector<int> v(length); // vector to be sorted
    vector<int> t(length); // temporary workspace

    // define an integer pointer dynamically allocate an array of integers
    // int arr[length]; // Static declaration
    int * arr = new int[length]; // Dynamic declaration
    int *s = arr;

    // initialize and print input
    cout << "Unsorted:      " ;
    for (int i = 0; i < v.size(); i++) {
        v.at(i) = rand() % 100;
        cout << v.at(i) << '\t';
    }
    cout << endl;

    // copy the random list of integers from vector to array
    for(int j = 0; j < length; j++){
        arr[j] = v.at(j);
    }

    clock_t start_mergeSort = clock();
    // sort vector using mergeSort
    mergeSort(v,t, 0, v.size() - 1);
    clock_t end_mergeSort = clock();

    // check output, make sure vector is sorted after mergeSort
    for(int i = 1; i < v.size(); i++) {
        assert(v.at(i-1) <= v.at(i));
    }


    clock_t start_bubbleSort = clock();
    // sort array using bubbleSort
    bubbleSort(s, length);
    clock_t end_bubbleSort = clock();


    // check output, make sure array is sorted after bubbleSort
    /* your code here */
    for(int j = 1; j < v.size(); j++) {
        assert(arr[j-1] <= arr[j]);
    }


    // print sorted vector after mergeSort
    cout << "Merge Sorted:   " ;
    for (int i = 0; i < v.size(); i++) {
        cout << v.at(i) << '\t';
    }
    cout << endl;

    // print sorted array after bubbleSort
    cout << "Bubble Sorted:  " ;
    for (int j = 0; j < v.size(); j++) {
        cout << arr[j] << '\t';
    }
    cout << endl;


    // print elapsed time for mergeSort and bubbleSort
    double elapsed_mergeSort = double(end_mergeSort - start_mergeSort) / CLOCKS_PER_SEC;
    double elapsed_bubbleSort = double(end_bubbleSort - start_bubbleSort) / CLOCKS_PER_SEC;

    cout << " * Elapsed time for sorting a " << length << "-element array: " << endl;
    cout << "                                             MergeSort: " << elapsed_mergeSort << endl;
    cout << "                                            BubbleSort: " << elapsed_bubbleSort << endl;

    delete[] arr;
    arr = nullptr;

    cout << "--------------------------------------------------------------------------------------------" << endl;
    return 0;
}

void mergeSortedLists(vector<int>& a, vector<int>& tmp, int leftPos, int rightPos, int rightEnd) {
    int leftEnd = rightPos - 1;
    int tempPos = leftPos;
    int numElements = rightEnd - leftPos + 1;

    while (leftPos <= leftEnd && rightPos <= rightEnd) {
        if (a[leftPos] <= a[rightPos]) {
            tmp[tempPos++] = a[leftPos++];
        } else {
            tmp[tempPos++] = a[rightPos++];
        }
    }

    while (leftPos <= leftEnd) {
        tmp[tempPos++] = a[leftPos++];
    }
    while (rightPos <= rightEnd) {
        tmp[tempPos++] = a[rightPos++];
    }

    for (int i = 0; i < numElements; i++, --rightEnd) {
        a[rightEnd] = tmp[rightEnd];
    }
}

void mergeSort(vector<int>& a, vector<int>& tmp, int left, int right) {
    if (left < right) {
        int center = ( left + right ) / 2;
        mergeSort(a, tmp, left, center);
        mergeSort(a, tmp, center + 1, right);
        mergeSortedLists(a, tmp, left, center + 1, right);
    }
}

// Swap function
void swap(int *a, int *b) {
    /* your code here */
    // exchange the number of a & b by using temp
    int *temp = a;
    *a = *b;
    *b = *temp;
}

// BubbleSort function
void bubbleSort(int *a, int n) {
    /* your code here */
    // construction two loops for sorting
    // the bigger loop make sures the program should at least run size-1 times
    for (int i = 0; i < n - 1; i++) {
        // the smaller loop reaches every value expect for the biggest number in the last
        for (int j = 0; j < n - i - 1; j++) {
            // compare the number in the array
            if (a[j] > a[j + 1]) {
                // call the swap function
                swap(a[j], a[j + 1]);
            }
        }
    }
}