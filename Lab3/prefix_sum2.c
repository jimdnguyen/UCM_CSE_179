#include <iostream>
#include <omp.h>
using std::cout;
using std::endl;

const int N = 10;
const int Nthr = 4;
float f(int i) {return (float)i;}

int main(void) {
    omp_set_num_threads(Nthr);
    float* a = new float[N];
    float *suma = new float[Nthr+1];
    suma[0] = 0.0;
    float sum = 0.0;
#pragma omp parallel for schedule(static) firstprivate(sum)
    for (int i=0; i<N; i++) {
        sum += f(i);
        a[i] = sum;
        suma[omp_get_thread_num()+1] = sum;
    }

    // this for-loop is also a commulative sum, but it has only Nthr iterations
    for (int i=1; i<Nthr;i++)
        suma[i] += suma[i-1];

#pragma omp parallel for schedule(static)
    for(int i=0; i< N; i++) {
        a[i] += suma[omp_get_thread_num()];
    }

    for (int i=0; i<N; i++) {
        cout << a[i] << endl;
    }

    delete[] suma;
    int n = 10;
    cout << a[n] << endl << n*(n+1)/2 << endl;
    delete[] a;
    return 0;
}