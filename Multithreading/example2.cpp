// An example program demonstrating using multithreading to finding the average for a vector of numbers of length N

#include <vector>
#include <thread>
#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

int THREAD_COUNT = 16; //The Apple M1 chip has 8 cores with 2 threads per core. Adjust as needed. 

typedef std::chrono::high_resolution_clock Clock;

void avg(vector<double> chunck, double& result) {
        double sum = 0.0f;
        for (int i = 0; i < chunck.size(); i++)
            sum += chunck[i];
        result = sum / double(chunck.size());
    }

int main() {

    // Make initial input vector
    int n = 100000000;
    vector<double> input(n);
    for (int i = 0; i < n; i++)
        input[i] = i + 1;
    
    // First let's do it singlethreaded
    auto t1 = Clock::now();
    double result = 0.0f;
    avg(input, result);
    auto t2 = Clock::now();
    auto duration = duration_cast<milliseconds>(t2 - t1);
    cout << "[Singlethreaded][" << duration.count() << "ms] The total average is: " << result << endl;

    // And now let's do it multithreaded
    auto t3 = Clock::now();
    int chunkSize = n / THREAD_COUNT;
    vector<thread> threads(THREAD_COUNT);    
    vector<double> results(THREAD_COUNT);

    for (int i = 0; i < THREAD_COUNT; i++) {
        results[i] = 0.0f;
        threads[i] = thread(avg, vector<double>(input.begin() + (i * chunkSize), input.begin() + ((i + 1) * chunkSize)), 
                            ref(results[i]));
    }

    for (int i = 0; i < THREAD_COUNT; i++)
        threads[i].join();

    double result2 = 0.0f;
    avg(results, result2);
    auto t4 = Clock::now();
    auto duration2 = duration_cast<milliseconds>(t4 - t3);
    cout << "[Multithreaded][" << duration2.count() << "ms] The total average is: " << result2 << endl;
    return 0;
}
