#include <fstream>
#include <sstream>
#include <vector>
#include <bitset>
#include <algorithm>

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
    vector<int> positions;
    
    void Read() {
        int current_position;
        
        while(in >> current_position) {
            in.ignore();
            positions.push_back(current_position);
        }
    }
    
    void GetAverage() {
        int sol;
        
        if (positions.size() % 2) {
            int pos = positions.size() / 2 - 1;
            nth_element(positions.begin(), positions.begin() + pos, positions.end());
            sol = positions[pos];
        } else {
            int pos = positions.size() / 2 - 1;
            nth_element(positions.begin(), positions.begin() + pos, positions.end());
            nth_element(positions.begin(), positions.begin() + pos + 1, positions.end());
            sol = (positions[pos] + positions[pos + 1]) / 2;
        }
        
        int total_sum = 0;
        
        for(auto position : positions) {
            total_sum += abs(position - sol);
        }
        
        out << total_sum;
    }
    
    
    
public:
    void Run() {
        Read();
        
        GetAverage();
    }
};


int main(int argc, const char * argv[]) {
    
    Solution solution;
    
    solution.Run();
    
    return 0;
}
