using System;
using System.Collections;
using System.Collections.Generic;

class Solution {
    public const int MAX_VALUE = 1000000;

    public int solution(int[] A) {
        HashSet<int> uniquePositives = new HashSet<int>();
        for (int i = 0; i < A.Length; i++) {
            if (A[i] > 0)
                uniquePositives.Add(A[i]);
        }

        for (int i = 1; i <= MAX_VALUE; i++) {
            if (!uniquePositives.Contains(i))
                return i;
        }
        
        return MAX_VALUE + 1;   
    }
}