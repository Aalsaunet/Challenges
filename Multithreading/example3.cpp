// Improved on example2 by reducing the amount uneccessary copying, which significantly improves the runtime.

#include <vector>
#include <thread>
#include <iostream>
#include <chrono>
#include <numeric>
#include <algorithm>

using namespace std;
using namespace std::chrono;

int THREAD_COUNT = 16;

typedef std::chrono::high_resolution_clock Clock;

void avg(const vector<double>& input, const vector<double>::iterator start, 
            const vector<double>::iterator stop, int chunkSize, double& result) {
    result = accumulate(start, stop, 0.0) / double(chunkSize);
}

int main() {
    // Make initial input vector
    int n = 1000000000;
    vector<double> input(n);
    for (int i = 0; i < n; i++)
        input[i] = i + 1;

    // First let's do it singlethreaded (for N=1000000000 this took me ~39442ms)
    auto t1 = Clock::now();
    double result = 0.0;
    avg(input, input.begin(), input.end(), input.size(), result);
    auto t2 = Clock::now();
    auto duration = duration_cast<milliseconds>(t2 - t1);
    cout << "[Singlethreaded][" << duration.count() << "ms] The total average is: " << result << endl;

    // And now let's do it multithreaded (for N=1000000000 this took me ~8131ms - ~5x faster!)
    auto t3 = Clock::now();
    int chunkSize = n / THREAD_COUNT;
    vector<thread> threads(THREAD_COUNT);
    vector<double> results(THREAD_COUNT);

    for (int i = 0; i < THREAD_COUNT; i++) {
        auto start = input.begin() + (i * chunkSize);
        threads[i] = thread(avg, ref(input), start, start + chunkSize, chunkSize, ref(results[i]));
    }

    for (int i = 0; i < THREAD_COUNT; i++)
        threads[i].join();

    double result2 = 0.0;
    avg(results, results.begin(), results.end(), results.size(), result2);
    auto t4 = Clock::now();
    auto duration2 = duration_cast<milliseconds>(t4 - t3);
    cout << "[Multithreaded][" << duration2.count() << "ms] The total average is: " << result2 << endl;

    return 0;
}
