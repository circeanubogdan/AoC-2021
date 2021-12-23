#include <fstream>
#include <sstream>
#include <vector>
#include <bitset>

#define BOARD_SIZE 5

using namespace std;

ifstream in ("test.in");
ofstream out("test.out");

class Boards {
    vector<int> values;
    vector<int**> boards;
    int sum;
    int value;
    
public:
    Boards () {
        sum = 0;
        value = 0;
    }
    
private:
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
    
    void Read() {
        int value;
        string line;
        getline(in, line);
        
        istringstream iss(line);
        
        while(iss>>value) {
            if (iss.peek() == ',')
                    iss.ignore();
            values.push_back(value);
        }
        
        char temp;
        while(in>>temp) {
            in.seekg(-1,ios::cur);
            
            int** current_matrix = AllocateMatrix(BOARD_SIZE);
            
            for(int i = 0; i < BOARD_SIZE; ++ i) {
                for(int j = 0; j < BOARD_SIZE; ++ j) {
                    in>>current_matrix[i][j];
                }
            }
            
            boards.push_back(current_matrix);
        }
    }
    
    void FindValue(int value) {
        for(auto board : boards) {
            for(int i = 0; i < BOARD_SIZE; ++ i) {
                for(int j = 0; j < BOARD_SIZE; ++ j) {
                    if(board[i][j] == value) {
                        board[i][j] = -1;
                    }
                }
            }
        }
    }
    
    bool CheckLine(int** board, int line) {
        for(int j = 0; j < BOARD_SIZE; ++ j)
            if(board[line][j] >= 0)
                return false;
        return true;
    }
    
    bool CheckColumn(int** board, int col) {
        for(int i = 0; i < BOARD_SIZE; ++ i)
            if(board[i][col] >= 0)
                return false;
        return true;
    }
    
    bool CheckAllLinesColumns(int** board) {
        for(int i = 0; i < BOARD_SIZE; ++ i)
            if(CheckLine(board, i) || CheckColumn(board, i))
                return true;
        return false;
    }
    
    void UpdateSum(int** board) {
        sum = 0;
        for(int i = 0; i < BOARD_SIZE; ++ i) {
            for(int j = 0; j < BOARD_SIZE; ++ j) {
                if(board[i][j] > 0) {
                    sum += board[i][j];
                }
            }
        }
    }
    
    bool CheckWinner() {
        bool found_winner = false;
        
        for(auto board : boards) {
            if(board[0][0] == -2)
                continue;
            if(CheckAllLinesColumns(board)) {
                found_winner = true;
                UpdateSum(board);
                board[0][0] = -2;
            }
        }
        
        return found_winner;
    }
    
public:
    void Run() {
        Read();
        for(auto value : values) {
            FindValue(value);
            if(CheckWinner()) {
                this->value = value;
            }
        }
    }
    
    int GetSol() {
        for(auto board : boards)
            DeallocateMatrix(board, BOARD_SIZE);
        
        return sum * value;
    }
};



int main(int argc, const char * argv[]) {
    
    Boards boards;
    
    boards.Run();
    
    out<<boards.GetSol();
    
    return 0;
}
