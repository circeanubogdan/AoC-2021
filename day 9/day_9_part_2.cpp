#include <fstream>
#include <sstream>
#include <vector>
#include <bitset>
#include <algorithm>
#include <cmath>
#include <queue>

#define TIMER_SIZE 9
#define GENERATION_SPAN 256

using namespace std;

ifstream in ("test.in");
ofstream out("test.out");

struct QueueElem {
    int x;
    int y;
    int color;
};

class Solution {
public:
    Solution() {
        
    }
    
private:
    vector<vector<int>> terrain;
    vector<vector<int>> coloring;
    queue<QueueElem> q;
    vector<int> basins;
    
    int dx[4] = {0, 0, -1, 1};
    int dy[4] = {-1, 1, 0, 0};
    
    void Read() {
        string line;
        
        while(getline(in, line)) {
            vector<int> current_line;
            
            for(auto height : line) {
                current_line.push_back(height - '0');
            }
            
            vector<int> temp(current_line.size());
            
            terrain.push_back(current_line);
            coloring.push_back(temp);
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
        for(int i = 0; i < terrain.size(); ++ i) {
            for(int j = 0; j < terrain[i].size(); ++ j) {
                if(IsLowPoint(i, j, (int) terrain.size(), (int) terrain[i].size())) {
                    basins.push_back(1);
                    
                    q.push({i, j, (int) basins.size()});
                    
                    coloring[i][j] = basins.size();
                }
            }
        }
    }
    
    void RunBFS() {
        while(!q.empty()) {
            int x = q.front().x;
            int y = q.front().y;
            int color = q.front().color;
            
            q.pop();
            
            for(int dir = 0; dir < 4; ++ dir) {
                int new_x = x + dx[dir];
                int new_y = y + dy[dir];
                if(IsInBounds(new_x, new_y, (int) terrain.size(), (int) terrain[0].size()) &&
                   coloring[new_x][new_y] == 0 && terrain[new_x][new_y] != 9) {
                    coloring[new_x][new_y] = color;
                    
                    q.push({new_x, new_y, color});
                    
                    basins[color - 1] ++;
                }
            }
        }
        
        sort(basins.begin(), basins.end());
        
        long long result = basins[basins.size() - 1] * basins[basins.size() - 2] *
                            basins[basins.size() - 3];
        
        out << "Product of largest 3 basins: " << result << '\n';
    }
    
public:
    void Run() {
        Read();
        
        GetLowPoints();
        
        RunBFS();
    }
};


int main(int argc, const char * argv[]) {
    
    Solution solution;
    
    solution.Run();
    
    return 0;
}
