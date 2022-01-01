#include <fstream>
#include <sstream>
#include <vector>
#include <bitset>
#include <algorithm>
#include <cmath>

#define TIMER_SIZE 9
#define GENERATION_SPAN 256

using namespace std;

ifstream in ("test.in");
ofstream out("test.out");


class Solution {
public:
    Solution() {
        
    }
    
private:
    vector<vector<int>> terrain;
    
    int dx[4] = {0, 0, -1, 1};
    int dy[4] = {-1, 1, 0, 0};
    
    void Read() {
        string line;
        
        while(getline(in, line)) {
            vector<int> current_line;
            
            for(auto height : line) {
                current_line.push_back(height - '0');
            }
            
            terrain.push_back(current_line);
        }
    }
    
    bool IsInBounds(int x, int y, int n, int m) {
        return x >= 0 && x < n && y >= 0 && y < m;
    }
    
    bool IsLowPoint(int x, int y, int n, int m) {
        for(int dir = 0; dir < 4; ++ dir) {
            int new_x = x + dx[dir];
            int new_y = y + dy[dir];
            if(IsInBounds(new_x, new_y, n, m) && terrain[new_x][new_y] <= terrain[x][y])
                return false;
        }
        
        return true;
    }
    
    void GetLowPoints() {
        int sol = 0;
        
        for(int i = 0; i < terrain.size(); ++ i) {
            for(int j = 0; j < terrain[i].size(); ++ j) {
                if(IsLowPoint(i, j, terrain.size(), terrain[i].size()))
                    sol += terrain[i][j] + 1;
            }
        }
        
        out << "Sum of lowest points: " << sol << '\n';
    }
    
public:
    void Run() {
        Read();
        
        GetLowPoints();
    }
};


int main(int argc, const char * argv[]) {
    
    Solution solution;
    
    solution.Run();
    
    return 0;
}
