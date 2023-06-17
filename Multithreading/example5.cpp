#include <vector>
#include <thread>
#include <iostream>
#include <chrono>
#include <numeric>
#include <algorithm>

using namespace std;
using namespace std::chrono;

typedef std::chrono::high_resolution_clock Clock;

template<typename Iterator,typename T>

struct accumulate_block {
    void operator()(Iterator first,Iterator last,T& result) {
        result=std::accumulate(first,last,result);
    }
};

template<typename Iterator,typename T>

T parallel_accumulate(Iterator first,Iterator last,T init) {
    unsigned long const length=std::distance(first,last);
    if(!length)
        return init;
    unsigned long const min_per_thread=25;
    unsigned long const max_threads=
        (length+min_per_thread-1)/min_per_thread;
    unsigned long const hardware_threads=
        std::thread::hardware_concurrency();
    unsigned long const num_threads=
        std::min(hardware_threads!=0?hardware_threads:2,max_threads);
    unsigned long const block_size=length/num_threads;
    std::vector<T> results(num_threads);
    std::vector<std::thread>  threads(num_threads-1);
    Iterator block_start=first;
    for(unsigned long i=0;i<(num_threads-1);++i)
    {
        Iterator block_end=block_start;
        std::advance(block_end,block_size);
        threads[i]=std::thread(
            accumulate_block<Iterator,T>(),
            block_start,block_end,std::ref(results[i]));
        block_start=block_end;
    }
    accumulate_block<Iterator,T>()(
        block_start,last,results[num_threads-1]);

    for(auto& entry: threads)
           entry.join();
    return std::accumulate(results.begin(),results.end(),init);
}

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
    int result2 = parallel_accumulate(input.begin(), input.end(), 0);
    auto t4 = Clock::now();
    auto duration2 = duration_cast<milliseconds>(t4 - t3);
    cout << "[Multithreaded][" << duration2.count() << "ms] The total average is: " << result2 << endl;

    return 0;
}