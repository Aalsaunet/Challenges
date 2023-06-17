// Not faster than example3 but uses lambda instead.

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

double avg(const vector<double>& input, const vector<double>::const_iterator start,
           const vector<double>::const_iterator stop, double chunkSize) {
    return accumulate(start, stop, 0.0) / chunkSize;
}

int main() {
    // Make initial input vector
    int n = 1000000000;
    vector<double> input(n);
    for (int i = 0; i < n; i++)
        input[i] = i + 1;

    // First let's do it singlethreaded (for N=1000000000 this took me ~39442ms)
    auto t1 = Clock::now();
    double result = avg(input, input.begin(), input.end(), static_cast<double>(input.size()));
    auto t2 = Clock::now();
    auto duration = duration_cast<milliseconds>(t2 - t1);
    cout << "[Singlethreaded][" << duration.count() << "ms] The total average is: " << result << endl;

    // And now let's do it multithreaded (for N=1000000000 this took me ~8131ms - ~5x faster!)
    auto t3 = Clock::now();
    int chunkSize = n / THREAD_COUNT;
    vector<thread> threads(THREAD_COUNT);
    vector<double> results(THREAD_COUNT);

    auto threadFunc = [&](int i) {
        auto start = input.cbegin() + (i * chunkSize);
        auto stop = start + chunkSize;
        results[i] = avg(input, start, stop, static_cast<double>(chunkSize));
    };

    for (int i = 0; i < THREAD_COUNT; i++)
        threads[i] = thread(threadFunc, i);

    for (int i = 0; i < THREAD_COUNT; i++)
        threads[i].join();

    double result2 = avg(results, results.cbegin(), results.cend(), static_cast<double>(results.size()));
    auto t4 = Clock::now();
    auto duration2 = duration_cast<milliseconds>(t4 - t3);
    cout << "[Multithreaded][" << duration2.count() << "ms] The total average is: " << result2 << endl;

    return 0;
}
