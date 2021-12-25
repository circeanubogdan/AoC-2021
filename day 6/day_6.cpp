#include <fstream>
#include <sstream>
#include <vector>
#include <bitset>

#define TIMER_SIZE 9
#define GENERATION_SPAN 256

using namespace std;

ifstream in ("test.in");
ofstream out("test.out");

class FishGang {
public:
    FishGang() {
        
    }
    
private:
    long long timers[10] = {};
    long long temp_timers[10] = {};
    
    void Read() {
        int current_timer;
        while(in >> current_timer) {
            in.ignore();
            timers[current_timer] ++;
        }
    }
    
    void RunDay() {
        memset(temp_timers, 0, TIMER_SIZE * sizeof(long long));
        
        temp_timers[6] += timers[0];
        temp_timers[8] += timers[0];
        
        for(int i = 0; i < TIMER_SIZE - 1; ++ i) {
            temp_timers[i] += timers[i + 1];
        }
        
        memcpy(timers, temp_timers, TIMER_SIZE * sizeof(long long));
    }
    
    void RunDays(int days_count) {
        for(int i = 0; i < days_count; ++ i)
            RunDay();
    }
    
    void GetSol() {
        long long sol = 0;
        
        for(int i = 0; i < TIMER_SIZE; ++ i) {
            sol += timers[i];
        }
        
        out<<sol<<'\n';
    }
    
public:
    void Run() {
        Read();
        
        RunDays(GENERATION_SPAN);
        
        GetSol();
    }
};


int main(int argc, const char * argv[]) {
    
    FishGang fish_gang;
    
    fish_gang.Run();
    
    return 0;
}
