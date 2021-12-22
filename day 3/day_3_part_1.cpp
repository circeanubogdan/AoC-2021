#include <fstream>
#include <vector>
#include <bitset>

#define BITS_LENGTH 12

using namespace std;

ifstream in ("test.in");
ofstream out("test.out");

class Solution {
    
private:
    vector<bitset<BITS_LENGTH>> bits;
    bitset<BITS_LENGTH> gamma;
    bitset<BITS_LENGTH> epsilon;
    vector<int> count_ones;
    vector<int> count_zeros;
    
public:
    Solution() : count_ones(BITS_LENGTH), count_zeros(BITS_LENGTH){
        
    }
    
private:
    void Read() {
        string current_bits;
        while(in>>current_bits) {
            bits.push_back(bitset<BITS_LENGTH> (current_bits));
        }
    }
    
    void Count() {
        for(auto current_set : bits) {
            for(int i = 0; i < current_set.size(); ++ i) {
                count_ones[i] += current_set[i];
                count_zeros[i] += 1 - current_set[i];
            }
        }
    }
    
    void CalculateValues() {
        for(int i = 0; i < gamma.size(); ++ i) {
            if(count_ones[i] > count_zeros[i])
                gamma[i] = true;
            else
                epsilon[i] = true;
        }
    }
    
public:
    void Run() {
        Read();
        Count();
        CalculateValues();
    }
    
    int GetResult() {
        return ((int) gamma.to_ulong()) * ((int) epsilon.to_ulong());
    }
    
};

int main(int argc, const char * argv[]) {
    
    Solution solution;
    
    solution.Run();
    
    out<<solution.GetResult();
    
    return 0;
}
