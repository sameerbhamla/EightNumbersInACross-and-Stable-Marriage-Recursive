#include <iostream>
#include <cmath>
using namespace std;

//making the helper array for the Eight Numbers in a Cross problem
static int helperArray[8][5] = {
  {-1},
      {0,-1},
      {0,1,-1},
      {0,2,-1},
      {1,2,-1},
      {1,2,3,4,-1},
      {2,3,5,-1},
      {4,5,6,-1},
};

//Making a bool function to check the boxes
bool test(int cross[], int size) {

    for (int i = 0; i < size; i++) {

        for (int j = 0; helperArray[size][j] != -1; j++) {

            //test each box using the helperArray
            if (abs(cross[size] - cross[helperArray[size][j]]) == 1 || cross[size] == cross[i]) {
                return false;

            }

        }

    }

    return true;
}

void printCross(int cross[], int num) {

    //Making count a global variable
    static int count = 0;

    //print
    cout << "Solution number: " << ++count << endl;
    cout << " " << cross[1] << cross[4] << endl;
    cout << cross[0] << cross[2] << cross[5] << cross[7] << endl;
    cout << " " << cross[3] << cross[6] << endl << endl;
    return;
}

//Recursive formula
void recursiveEightCross(int* q, int startingNum) {

    //If the starting point reaches the end then it will end and return the cross
    if (startingNum == 8) {
        printCross(q, startingNum);
        return;
    }

    //Checking each box after the first for a valid number for box then moving to the next box
    for (int i = 1; i < 9; i++) {
        q[startingNum] = i;
        if (test(q, startingNum)) {
            recursiveEightCross(q, startingNum + 1);
        }
    }
}
//THE CODE ABOVE IS FOR EIGHT NUMBERS IN A CROSS ONLY

//Stable marriage recursion

//Setting up both preferences as global variables
 static int mp[3][3] = { { 0 , 2 , 1}, //0
                         { 0 , 2 , 1}, //1
                         { 1 , 2 , 0}  //2 
                        // 0   1   2
        };  

 static int wp[3][3] = { { 2 , 1 , 0}, //0
                         { 0 , 1 , 2}, //1
                         { 2 , 0 , 1}  //2
                        // 0   1   2
        };

//Reusing same ok function from old Stable marriage
bool ok(int q[], int col, int mp[3][3], int wp[3][3]) {

    // setting new man and women
    int nm = col;
    int nw = q[col];

    for (int i = 0; i < col; i++) {

        if (q[col] == q[i]) {  // checking if new women has already been assigned to a man
            return false;

        }
        else if ((mp[col][q[i]] < mp[col][q[col]]) && // check condition a. above
            (wp[q[i]][col] < wp[q[i]][i])) {     //check condition b. above
            return false;

        }
        else if ((wp[q[col]][i] < wp[q[col]][col]) && // checks condition c
            (mp[i][q[col]] < mp[i][q[i]])) {     //checks condition d
            return false;

        }
        else {
            return true; // condition e
        }
    }
    return true;
}

//Reusing same print function as old stable marriage
void print(int q[], int c){

  for(int i = 0; i < c; i++){
    cout << "Man " << i << " With women " << q[i] << endl;

  }  
}

//New recursive function 
void StableMarriage(int* q, int i){ 

  //If we reach the end of the col (which is size 3) then end the recursive formula
    if(i == 3){
        print(q, 3);
        return;
    }
    
    //Checking preferences between each person to find best match
    for(int j = 0; j < 3; j++){ 

        q[i] = j;

        if( ok (q, i, mp, wp) ) 
          StableMarriage(q, i + 1); //If its ok then move on to the next person
    }
}
int main() {
  
  cout << "Eight numbers in cross" << endl;
   //Calling eight numbers in cross
  int cross[8];
  recursiveEightCross(cross, 0);

  cout << "Stable marriage" << endl;
   //Calling stable marriage
  int q[3]; 
  q[0] = 0;
  StableMarriage(q, 0);

}
