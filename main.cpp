//compile :   g++ main.cpp -o main -std=c++11
//run :  ./main -1 -1 EAST W2LW2LW2LW2

//Note. use C++11 

#include<iostream>
#include<string>

using namespace std;

class Walking_robot {
private:
    
    //position of robot
    int pos_X, pos_Y;

    const  string direction[4] = {"NORTH", "EAST", "SOUTH", "WEST"};

    //North = 0, East = 1,south = 2, west = 3;
    //Right means clockwise i.e. increment value, after 3 return to 0
    //left means counter-clockwise i.e. decrement value , after 0 return to 3
    int index;

public:

    //constructor
    Walking_robot(int x, int y, string direction) {
        pos_X = x;
        pos_Y = y;


        if (direction == "NORTH")
            index = 0;
        else if (direction == "EAST")
            index = 1;
        else if (direction == "SOUTH")
            index = 2;
        else
            index = 3;

    }

    /*
     * get position of robot
     */
    void get_position() const {

        cout << pos_X << " " << pos_Y << " " << direction[index] <<"\n\n";
    }

    /*
     * move the robot given the string instructions
     */
    void walk(string move_str) {
        int i = 0;

        //until end of commands
        while (move_str[i] != '\0') {
            
            //walk
            if (move_str[i] == 'W') {
                //convert char into array digit
                int v = (move_str[++i]) - '0';

                //if in negative Y or negative X direction
                if (index == 2 || index == 3)
                    v = v * -1;

                //if in Y direction
                if (index == 0 || index == 2)
                    pos_Y += v;
                else
                    pos_X += v;

            
            }
            
            else if (move_str[i] == 'L') // move counter-clockwise
            {
                index--;

                //after 0 on left 3 will come
                if (index == -1)
                    index = 3;
            } else { 
                //move clockwise
                index++;

                //after 3 on right 0 will come
                if (index == 4)
                    index = 0;
            }

            i++;
        }//end while
    }

};

int main(int argc, char * argv[]) {

    if (argc == 5) {
        Walking_robot robot(stoi(argv[1]), stoi(argv[2]), argv[3]);

        robot.walk(argv[4]);
        robot.get_position();
    } else
        cout << "\nIncorrect number of command arguments\n";

    return 0;
}

/*
 * arguments 
 *   0 0 NORTH RW2RRW2R  => 0 0 NORTH
 * 
 *   5 2 SOUTH RW2LW4R    => 3 -2 WEST

 *   0 0 NORTH LW3RW3RW5  =>  2 3 EAST
 * 
 *   -1 -1 EAST W2LW2LW2LW2  => -1 -1 SOUTH
 * 
 *  -1 -1 EAST W2LW2LW2LW2LW4  => 3 -1 EAST
 */