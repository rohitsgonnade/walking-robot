//compile :   g++ main.cpp -o main -std=c++11
//run :  ./main -1 -1 EAST W2LW2LW2LW2

//Note. use C++11 

#include<iostream>
#include<string>
#include<bits/stdc++.h>

using namespace std;

class Walking_robot {
private:

    //position of robot
    int pos_X, pos_Y;

    const string direction[4] = {"NORTH", "EAST", "SOUTH", "WEST"};

    //North = 0, East = 1,south = 2, west = 3;
    //Right means clockwise i.e. increment value, after 3 return to 0
    //left means counter-clockwise i.e. decrement value , after 0 return to 3
    int index;

public:

    //constructor

    Walking_robot(int x, int y, string direction) {
        pos_X = x;
        pos_Y = y;

        //convert direction to lowercase to handle upper or lower case commands
        transform(direction.begin(), direction.end(), direction.begin(), ::tolower);

        if (direction == "north")
            index = 0;
        else if (direction == "east")
            index = 1;
        else if (direction == "south")
            index = 2;
        else
            index = 3;

    }

    /*
     * get position of robot
     */
    void get_position() const {

        cout << pos_X << " " << pos_Y << " " << direction[index] << "\n\n";
    }

    /*
     * move the robot given the string instructions
     */
    void walk(string move_str) {

        //convert to lowercase
        transform(move_str.begin(), move_str.end(), move_str.begin(), ::tolower);

        int i = 0;

        //until end of commands
        while (move_str[i] != '\0') {

            //walk
            if (move_str[i] == 'w') {

                i++;
                int v = 0;

                while (move_str[i] >= '0' && move_str[i] <= '9') {
                    //convert char into array digit
                    v = (v * 10) + ((move_str[i]) - '0');
                    i++;
                }
                //if in negative Y or negative X direction
                if (index == 2 || index == 3)
                    v = v * -1;

                //if in Y direction
                if (index == 0 || index == 2)
                    pos_Y += v;
                else
                    pos_X += v;


            }
            else {
                if (move_str[i] == 'l') // move counter-clockwise
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
            }

        }//end while
    }

};

int main(int argc, char * argv[]) {

    //Walking_robot robot(-1, -1, "EAST");
    //robot.walk("W2lW2Lw2LW2Lw4");
    //robot.get_position();

    if (argc == 5) {
        
        int x, y;
        
        try
        {
            x = stoi(argv[1]);
            y = stoi(argv[2]);
        }
        catch(...)
        {
            cerr << "invalid argument exception Integer excepted "<< "\n";
            return -1;
        }
        

        Walking_robot robot(x,y, argv[3]);

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
 * 
 *  0 0 WEST rW12RRW12   => 0 0 SOUTH
 * 
 *  0 0 WEST RW12RRW1Lw11   => 11 11 EAST
 */