#include <iostream>
#include <thread>
#include <random>
#include <cmath>

#include <ctime>
#include <chrono>

using namespace std;

// CHOOSE ONE
// #define is_static
// #define is_dynamic

// CHOOSE ONE
// #define is_seq
// #define is_cycle

// CHOOSE A VALUE
// #define P 4

const int N = 10'000'000;

#ifdef is_static
  int a[N];
  int b[N];
  int c[N];
#endif

#ifdef is_dynamic
  int *a;
  int *b;
  int *c;
#endif

void op(int i) {
  c[i] = a[i] + b[i];
}

// void op(int i) {
//   c[i] = sqrt(float(a[i] + b[i]));
// }

#ifdef is_static
  #ifdef is_seq
    void run_seq_static(int start, int end) {
      for (int i = start; i < end; ++i) {
        op(i);
      }
    }
  #endif

  #ifdef is_cycle
    void run_cycle_static(int id, int p) {
      for (int i = id; i < N; i += p) {
        op(i);
      }
    }
  #endif
#endif

#ifdef is_dynamic
  #ifdef is_seq
    void run_seq_dynamic(int start, int end) {
      for (int i = start; i < end; ++i) {
        op(i);
      }
    }
  #endif

  #ifdef is_cycle
    void run_cycle_dynamic(int id, int p) {
      for (int i = id; i < N; i += p) {
        op(i);
      }
    }
  #endif
#endif

int main() {
  #ifdef is_dynamic
    a = new int[N];
    b = new int[N];
    c = new int[N];
  #endif
  
  for (int i = 0; i < N; ++i) {
    a[i] = i;
    b[i] = i;
    c[i] = 0;
  }
  
  int p = P;

  auto t_start = std::chrono::high_resolution_clock::now();

  thread threads[p];
  int start = 0;
  int end = 0;
  for (int i = 0; i < p; ++i) {
    int len = N/p;
    if (i < N%p) {
      len += 1;
    }

    end += len;

    #ifdef is_static
      #ifdef is_seq
        threads[i] = thread(run_seq_static, start, end);
      #endif
      #ifdef is_cycle
        threads[i] = thread(run_cycle_static, i, p);
      #endif
    #endif

    #ifdef is_dynamic
      #ifdef is_seq
        threads[i] = thread(run_seq_dynamic, start, end);
      #endif
      #ifdef is_cycle
        threads[i] = thread(run_cycle_dynamic, i, p);
      #endif
    #endif

    start += len;
  }

  for (int i = 0; i < p; ++i) {
    threads[i].join();
  }

  auto t_end = std::chrono::high_resolution_clock::now();
  double elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();
  // cout << "elapsed_time_ms = " << elapsed_time_ms << "\n";
  cout << elapsed_time_ms << "\n";

  // for (int i = 0; i < N; ++i) {
  //   cout << a[i] << " + " << b[i] << " = " << c[i] << "\n";
  // }

  #ifdef is_dynamic
    delete[] a;
    delete[] b;
    delete[] c;
  #endif
  
  return 0;
}
