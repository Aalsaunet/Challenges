#include <vector>
#include <thread>
#include <iostream>

using namespace std;

void avg(vector<float> chunck, float& result) {
        float sum = 0.0f;
        for (int i = 0; i < chunck.size(); i++)
            sum += chunck[i];
        result = sum / float(chunck.size());
    }

int main() {

    // Make initial input vector
    int n = 100000000;
    vector<float> input(n);
    for (int i = 0; i < n; i++)
        input[i] = i;
    
    // First let's do it singlethreaded
    float result = 0.0f;
    avg(input, result);
    cout << "[Singlethreaded] The total average is: " << result << endl;

    // And now let's do it multithreaded
    int threadCount = 4;
    int chunkSize = n / threadCount;
    vector<thread> threads(threadCount);
    vector<float> results(threadCount);

    // [1, 2, 3, 4]
    for (int i = 0; i < threadCount; i++) {
        results[i] = 0.0f;
        threads[i] = thread(avg, vector<float>(input.begin() + (i * chunkSize), input.begin() + ((i + 1) * chunkSize)), 
                            ref(results[i]));
    }

    for (int i = 0; i < threadCount; i++)
        threads[i].join();

    result = 0.0f;
    avg(results, result);
    cout << "[Multithreaded] The total average is: " << result << endl;
    
    return 0;
}

//thread th(avg, vector<int>(input.begin() + (i * chunkSize), input.end()), ref(results[i]));