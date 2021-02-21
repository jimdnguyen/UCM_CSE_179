#include <iostream>
#include <sys/time.h>
using namespace std;

int main() {
    struct timeval current_time;
    gettimeofday(&current_time,NULL);
    printf("second: %ld\nmicrosecond: %ld\n", current_time.tv_sec, current_time.tv_usec);
    long start_time_sec = current_time.tv_sec;
    long start_time_usec = current_time.tv_usec;
    int n, firstTerm = 1, secondTerm = 1, nextTerm;
    cout << "Enter number of terms: ";
    cin >> n;

    cout << "Fibonacci Series: " << firstTerm << " + " << secondTerm;

    //measure the execution time of the following loop
    for (int i = 1; i <= n-2; ++i) {
        nextTerm = firstTerm + secondTerm;
        cout << " + " << nextTerm;
        firstTerm = secondTerm;
        secondTerm = nextTerm;
    }

    gettimeofday(&current_time,NULL);
    printf("\nsecond: %ld\nmicrosecond: %ld\n", current_time.tv_sec, current_time.tv_usec);
    long end_time_sec = current_time.tv_sec;
    long end_time_usec = current_time.tv_usec;
    long diff_sec = end_time_sec - start_time_sec;
    long diff_usec = end_time_usec - start_time_usec;

    
    printf("---------------------------------------\n");
    printf("Execution time in seconds: %ld\n", diff_sec);
    printf("Execution time in microseconds: %ld\n", diff_usec);
    printf("---------------------------------------\n");
    return 0;
}
