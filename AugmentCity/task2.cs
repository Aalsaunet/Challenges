using System;

class Solution {
    // Since there can be multiple valid triangles amoung the points we just have to return the first valid one we find
    
    public int[] solution(int[] X, int[] Y) {
        Point2D[] points = new Point2D[X.Length];
        for (int i = 0; i < X.Length; i++)
            points[i] = new Point2D(X[i], Y[i]); 

        for (int i = 0; i < X.Length; i++) {
            for (int j = i + 1; j < X.Length; j++) {
                for (int k = j + 1; k < X.Length; k++) {
                    if (!HasPositiveArea(points[i], points[j], points[k]))
                        continue;
                    
                    Triangle candidateTriangle = new Triangle(points[i], points[j], points[k]);
                    bool hasIntersectingPoint = false;
                    for (int l = 0; l < X.Length; l++) {
                        if (l == i || l == j | l == k)
                            continue;
                        
                        if (candidateTriangle.ContainsPoint(points[l])) {
                            hasIntersectingPoint = true;
                            break;
                        }
                    }

                    if (!hasIntersectingPoint)
                       return new int[] {i, j, k}; 
      
                }
            }
        }

        return new int[0]; 
    }

    private bool HasPositiveArea(Point2D p1, Point2D p2, Point2D p3) {
        // Use the Shoelace formula to determine if the triangle has a positive area
        return ((1/2) * ((p1.x * p2.y + p2.x * p3.y + p3.x * p1.y) - (p2.x * p1.y + p3.x * p2.y + p1.x * p3.y))) > 0;
    }
}

class Triangle {
    public Point2D p1;
    public Point2D p2;
    public Point2D p3;

    public Triangle(Point2D p1, Point2D p2, Point2D p3) {
        this.p1 = p1;
        this.p2 = p2;
        this.p3 = p3;
    }

    public bool ContainsPoint(Point2D p) {
        // Calculate vectors
        double v0X = p3.x - p1.x;
        double v0Y = p3.y - p1.y;
        double v1X = p2.x - p1.x;
        double v1Y = p2.y - p1.y;
        double v2X = p.x - p1.x;
        double v2Y = p.y - p1.y;

        // Compute dot products
        double dot00 = v0X * v0X + v0Y * v0Y;
        double dot01 = v0X * v1X + v0Y * v1Y;
        double dot02 = v0X * v2X + v0Y * v2Y;
        double dot11 = v1X * v1X + v1Y * v1Y;
        double dot12 = v1X * v2X + v1Y * v2Y;

        // Compute barycentric coordinates
        double invDenom = 1 / (dot00 * dot11 - dot01 * dot01);
        double u = (dot11 * dot02 - dot01 * dot12) * invDenom;
        double v = (dot00 * dot12 - dot01 * dot02) * invDenom;

        // Check if point is in triangle
        return (u >= 0) && (v >= 0) && (u + v < 1);
    }
}

class Point2D {
    public int x;
    public int y;

    public Point2D(int x, int y) {
        this.x = x;
        this.y = y;
    }
}
