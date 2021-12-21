#include <fstream>
#include <string>
#include <vector>

using namespace std;

ifstream in ("test.in");
ofstream out("test.out");

struct Command {
    string direction;
    int value;
};

class Position {
public:
    int vertical;
    int horizontal;
    
    Position(int vertical, int horizontal) {
        this->vertical = vertical;
        this->horizontal = horizontal;
    }
    
    void move(string direction, int value) {
        if(direction == "forward") {
            horizontal += value;
        }
        
        if(direction == "down") {
            vertical += value;
        }
        
        if(direction == "up") {
            vertical -= value;
        }
    }
};

class Ship {
public:
    vector<Command> commands;
    
    Position position;
    
    Ship() : position(0, 0) {
        
    }
    
    void Read() {
        string direction;
        int value;
        
        while(in>>direction>>value) {
            commands.push_back({direction, value});
        }
    }
    
    void ApplyCommands() {
        for(auto command : commands) {
            position.move(command.direction, command.value);
        }
    }
    
    int GetResult() {
        return position.vertical * position.horizontal;
    }
    
};

int main(int argc, const char * argv[]) {
    
    Ship ship;
    
    ship.Read();
    
    ship.ApplyCommands();
    
    out<<ship.GetResult();
    
    return 0;
}
