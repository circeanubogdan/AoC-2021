#include <fstream>
#include <vector>
#include <bitset>

#define BITS_LENGTH 12

using namespace std;

ifstream in ("test.in");
ofstream out("test.out");

class Solution {
    
private:
    vector<bitset<BITS_LENGTH>> bits_oxygen;
    vector<bitset<BITS_LENGTH>> bits_co2;
    vector<int> count_ones;
    vector<int> count_zeros;
    
public:
    Solution() : count_ones(BITS_LENGTH), count_zeros(BITS_LENGTH){
        
    }
    
private:
    void Read() {
        string current_bits;
        while(in>>current_bits) {
            bits_oxygen.push_back(bitset<BITS_LENGTH> (current_bits));
            bits_co2.push_back(bitset<BITS_LENGTH> (current_bits));
        }
    }
    
    void Count(vector<bitset<BITS_LENGTH>> bits, int pos) {
        count_ones[pos] = 0;
        count_zeros[pos] = 0;
        
        for(auto current_set : bits) {
            count_ones[pos] += current_set[pos];
            count_zeros[pos] += 1 - current_set[pos];
        }
    }
    
    void CalculateValuesType(vector<bitset<BITS_LENGTH>>& bits, bool type) {
        for(int pos = BITS_LENGTH - 1; pos >= 0 && bits.size() > 1; -- pos) {
            Count(bits, pos);
            bool most_common = (count_ones[pos] > count_zeros[pos]);
            
            bool equal = (count_ones[pos] == count_zeros[pos]);
            
            vector<bitset<BITS_LENGTH>> temp;
            for(auto current_bits : bits) {
                if(equal) {
                    if(type == current_bits[pos])
                        temp.push_back(current_bits);
                    continue;
                }
                
                if(type == 1 && current_bits[pos] == most_common) {
                    temp.push_back(current_bits);
                }
                
                if(type == 0 && current_bits[pos] != most_common) {
                    temp.push_back(current_bits);
                }
            }
            
            bits.clear();
            
            bits = temp;
        }
    }
    
    void CalculateValues() {
        CalculateValuesType(bits_oxygen, 1);
        CalculateValuesType(bits_co2, 0);
    }
    
public:
    void Run() {
        Read();
        CalculateValues();
    }
    
    int GetResult() {
        return ((int) bits_oxygen.front().to_ulong()) * ((int) bits_co2.front().to_ulong());
    }
    
};

int main(int argc, const char * argv[]) {
    
    Solution solution;
    
    solution.Run();
    
    out<<solution.GetResult();
    
    return 0;
}
