using System;

// To check whether one laser can be used for more than one statue we will have to check if there exist a multipler 
// M that can be applied to the X and Y coordinates of one statue so it matches the X and Y condinates of another
// Initial solution in O(N^2) 
// [1, 2] -> [2, 4]

class Solution {
    public int solution(Point2D[] A) {
        int requiredLasers = A.Length; 
        bool[] covered = new bool[A.Length];

        for (int i = 0; i < A.Length; i++) {
            for (int j = i + 1; j < A.Length; j++) {
                if (covered[j])
                    continue;
                
                double m = Math.Abs(A[j].x) / Math.Abs(A[i].x); // e.g 2 / 1 == 2
                if (Math.Abs(A[j].y) * m == Math.Abs(A[i].y)) { // eg 2 * 2 == 4
                    covered[j] = true;
                    requiredLasers--;
                }
            }
        }

        return requiredLasers;
    }
}
