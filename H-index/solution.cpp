#include <vector>

using namespace std;

class Solution {
public:
    int hIndex(vector<int>& citations) {
        // h-index: published at least h papers that have 
        // each been cited at least h times.
        int numPapers = citations.size();
        int currentMaxH = 0;

        for (int i = 0; i < numPapers; i++) {
            if (citations[i] < currentMaxH)
                continue;

            int numPapersWithAtLeastHCitations = 0;
            for (int j = 0; j < numPapers; j++) {
                if (citations[j] >= citations[i])
                    numPapersWithAtLeastHCitations++;
            }

            if (numPapersWithAtLeastHCitations >= citations[i])
                currentMaxH = citations[i];
            else if (numPapersWithAtLeastHCitations > currentMaxH)
                currentMaxH = numPapersWithAtLeastHCitations;
        }

        return currentMaxH;
    }
};