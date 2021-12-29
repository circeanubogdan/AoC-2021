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

class InputSet {
public:
    vector<string> all_digits;
    vector<string> value;
    
    InputSet() {
        
    }
    
    void AddToDigits(string digit) {
        all_digits.push_back(digit);
    }
    
    void AddToValue(string digit) {
        value.push_back(digit);
    }
};

class Solution {
public:
    Solution() {
        
    }
    
private:
    vector<InputSet> input_sets;
    
    void Read() {
        string line;
        
        while(getline(in, line)) {
            istringstream iss(line);
            string digit;
            
            InputSet input_set;
            
            for(int i = 0; i <= 9; ++ i) {
                iss >> digit;
                sort(digit.begin(), digit.end());
                input_set.AddToDigits(digit);
            }
            
            // Separator
            iss >> digit;
            
            for(int i = 0; i <= 3; ++ i) {
                iss >> digit;
                sort(digit.begin(), digit.end());
                input_set.AddToValue(digit);
            }
            
            input_sets.push_back(input_set);
            
        }
    }
    
    void GetUniques() {
        int sol = 0;
        
        for(auto input_set : input_sets) {
            for(auto digit : input_set.value) {
                if(digit.size() == 2 || digit.size() == 3 ||
                   digit.size() == 4 || digit.size() == 7) {
                    sol ++;
                }
            }
        }
        
        out << "Digits with unique representation: " << sol << '\n';
    }
    
    bool Included(string d1, string d2) {
        for(auto letter : d2) {
            if(d1.find(letter) >= d1.length()) {
                return false;
            }
        }
        
        return true;
    }
    
    void RemoveByRule(vector<string> &decoded, vector<string> &digits, int digit_to_find, int digit_ruling, bool not_included) {
        for(vector<string>::iterator digit = digits.begin(); digit != digits.end(); ++ digit) {
            bool result = Included(*digit, decoded[digit_ruling]);
            
            if(not_included)
                result = !result;
            
            if(result) {
                decoded[digit_to_find] = *digit;
                digits.erase(digit);
                break;
            }
        }
    }
    
    void Decode() {
        
        int total_sum = 0;
        
        for(auto input_set : input_sets) {
            vector<string> decoded(10);
            vector<string> six_size;
            vector<string> five_size;
            
            for(auto digit : input_set.all_digits) {
                if(digit.size() == 2) {
                    decoded[1] = digit;
                    continue;
                }
                
                if(digit.size() == 3) {
                    decoded[7] = digit;
                    continue;
                }
                
                if(digit.size() == 4) {
                    decoded[4] = digit;
                    continue;
                }
                
                if(digit.size() == 7) {
                    decoded[8] = digit;
                    continue;
                }
                
                if(digit.size() == 6) {
                    six_size.push_back(digit);
                    continue;
                }
                
                if(digit.size() == 5) {
                    five_size.push_back(digit);
                }
            }
            
            RemoveByRule(decoded, six_size, 6, 1, true);
            
            RemoveByRule(decoded, six_size, 0, 4, true);
            
            decoded[9] = six_size.front();
            
            RemoveByRule(decoded, five_size, 3, 1, false);
            
            for(vector<string>::iterator digit = five_size.begin(); digit != five_size.end(); ++ digit) {
                string digit_copy = decoded[6];
                
                for(auto letter : *digit) {
                    unsigned long pos = digit_copy.find(letter);
                    if(pos < digit_copy.size()) {
                        digit_copy.erase(digit_copy.begin() + pos);
                    }
                }
                
                if(digit_copy.size() == 1) {
                    decoded[5] = *digit;
                    five_size.erase(digit);
                    break;
                }
            }
            
            decoded[2] = five_size.front();
            
            int current_value = 0;
            
            for(auto digit : input_set.value) {
                for(int i = 0; i <= 9; ++ i) {
                    if(decoded[i] == digit) {
                        current_value = current_value * 10 + i;
                        break;
                    }
                }
            }
            
            out << "Current Value: " << current_value << '\n';
            
            total_sum += current_value;
        }
        
        out << "\nTotal Sum: " << total_sum << '\n';
        
    }
    
    
    
public:
    void Run() {
        Read();
        
        GetUniques();
        
        Decode();
    }
};


int main(int argc, const char * argv[]) {
    
    Solution solution;
    
    solution.Run();
    
    return 0;
}
