#include <fstream>
#include <sstream>
#include <vector>
#include <bitset>

#define FLOOR_SIZE 1000

using namespace std;

ifstream in ("test.in");
ofstream out("test.out");

struct Point {
    int x;
    int y;
    
    Point() {
        
    }
    
    Point(int x, int y) {
        this->x = x;
        this->y = y;
    }
};

struct Line {
    Point a;
    Point b;
    
    Line(Point a, Point b) {
        this->a = a;
        this->b = b;
    };
};

class SeaFloor {
public:
    SeaFloor() {
        floor = AllocateMatrix(FLOOR_SIZE);
    }
    
private:
    vector<Line> lines;
    int** floor;
    
    int** AllocateMatrix(int n) {
        int** matrix = new int*[n];
        for(int i = 0; i < n; ++ i) {
            matrix[i] = new int[n];
        }
        
        return matrix;
    }
    
    void DeallocateMatrix(int** matrix, int n) {
        for(int i = 0; i < n; ++ i) {
            delete matrix[i];
        }
        
        delete matrix;
    }
    
    void FillLine(Line line) {
        if(line.a.x == line.b.x || line.a.y == line.b.y) {
            for(int i = min(line.a.x, line.b.x); i <= max(line.a.x, line.b.x); ++ i) {
                for(int j = min(line.a.y, line.b.y); j <= max(line.a.y, line.b.y); ++ j) {
                    floor[i][j] ++;
                }
            }
        }
    }
    
    void Read() {
        int X1, Y1, X2, Y2;
        while(in >> X1) {
            in.ignore();
            in >> Y1;
            
            in.ignore(4);
            in >> X2;
            
            in.ignore();
            in >> Y2;
            
            lines.push_back(Line(Point(X1, Y1), Point(X2, Y2)));
            
            FillLine(lines.back());
        }
    }
    
    void CountDangerousPoints() {
        int sol = 0;
        
        for(int i = 0; i < FLOOR_SIZE; ++ i) {
            for(int j = 0; j < FLOOR_SIZE; ++ j) {
                if(floor[i][j] > 1)
                    sol ++;
            }
        }
        
        out << sol;
    }
    
public:
    void Run() {
        Read();
        
        CountDangerousPoints();
    }
};

int main(int argc, const char * argv[]) {
    
    SeaFloor sea_floor;
    
    sea_floor.Run();
    
    return 0;
}
