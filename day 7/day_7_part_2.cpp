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
    vector<int> positions;
    
    void Read() {
        int current_position;
        
        while(in >> current_position) {
            in.ignore();
            positions.push_back(current_position);
        }
    }
    
    void GetAverage() {
        int sol = 0;
        
        for(auto position : positions) {
            sol += position;
        }
        
        double val_not_rounded = ((double) sol / (double) positions.size());
        sol = (int) round(val_not_rounded);
        
        const int delta = 5;
        
        int minim = 2e9;
        int min_pos = 0;
        
        for(int current_sol = sol - delta; current_sol <= sol + delta; ++ current_sol) {
            int total_sum = 0;
            
            for(auto position : positions) {
                int dist = abs(position - current_sol);
                total_sum += dist * (dist + 1) / 2;
            }
            
            if(total_sum < minim) {
                minim = total_sum;
                min_pos = current_sol;
            }
        }
        
        out << "Not rounded: " << val_not_rounded << "\nRounded: " << sol << "\nMinimum pos: " << min_pos << "\nMinimum sum: " << minim;
        
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
