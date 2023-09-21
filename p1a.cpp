//Aral Balsari & Jake Ross
//Project 1
//Mastermind Game

#include <iostream>
#include <vector>

using namespace std;

//Code class
class Code{

    public:
    //constructor
    Code(int n, int m);
    //randomize values in vector
    void Randomize();
    //return how many numbers match value and location
    int checkCorrect(Code guess()) const;
    //return how many numbers match value but not location
    int checkIncorrect(Code guess()) const;
    //print the code
    void printCode() const;

    private:
    //length of the vector
    int length;
    //possible range of values
    int range;
    //code vector
    vector<int> code_obj;
}; //end Code class

//Code class: constructor
Code::Code(int n, int m) {
    //set length to n
    length = n;
    //set range to m
    range = m;
}

//Code class: randomize values in vector
void Code::Randomize() {
    for (int i = 0; i < length; i++) {
        srand((unsigned) time(NULL)); //reset rand seed
        int new_value = rand() % range;
        code_obj.push_back(new_value);
    }
}

//Code class: print the code
void Code::printCode () const {
    cout << "{";
    for (int i = 0; i < (length-1); i++) {
        cout << code_obj[i] << ", ";
    }
    cout << code_obj[length-1] << "}" << endl;
}

int main() {
    int n;
    int m;
    cout << "Please enter length and range" << endl;
    cin >> n >> m;
    Code codemaker_code(n, m);
    codemaker_code.Randomize();
    codemaker_code.printCode();
    codemaker_code.Randomize();
    codemaker_code.printCode();
    codemaker_code.Randomize();
    codemaker_code.printCode();    
}