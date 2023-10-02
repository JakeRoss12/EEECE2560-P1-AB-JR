//Aral Balsari & Jake Ross
//Project 1b
//Mastermind Game

#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>

using namespace std;

// Code class
class Code {
public:
    // Constructors
    Code(int n, int m);
    Code(int n, int m, vector<int> v);

    // Randomize values in vector
    void Randomize();

    // Return how many numbers match value and location
    int checkCorrect(const Code& guess) const;

    // Return how many numbers match value but not location
    int checkIncorrect(const Code& guess) const;

    // Print the code
    void printCode() const;

private:
    int length;
    int range;
    vector<int> code_obj;
};

// Code class: Constructor
Code::Code(int n, int m) {
    // Set length to n
    length = n;
    // Set range to m
    range = m;
    // Randomize the code
    Randomize();
}

// Code class: Constructor with provided vector
Code::Code(int n, int m, vector<int> v) {
    length = n;
    range = m;
    code_obj = v;
}

// Code class: Randomize values in vector
void Code::Randomize() {
    code_obj.clear(); // Clear existing code
    for (int i = 0; i < length; i++) {
        int new_value = rand() % range;
        code_obj.push_back(new_value);
    }
}

// Code class: Return how many numbers match value and location
int Code::checkCorrect(const Code& guess) const {
    int correctCount = 0;
    for (int i = 0; i < length; i++) {
        if (code_obj[i] == guess.code_obj[i]) {
            correctCount++;
        }
    }
    return correctCount;
}

// Code class: Return how many numbers match value but not location
int Code::checkIncorrect(const Code& guess) const {
    int incorrectCount = 0;
    vector<bool> codeUsed(length, false);
    vector<bool> guessUsed(length, false);

    for (int i = 0; i < length; i++) {
        if (code_obj[i] == guess.code_obj[i]) {
            codeUsed[i] = true;
            guessUsed[i] = true;
        }
    }

    for (int i = 0; i < length; i++) {
        if (!codeUsed[i]) {
            for (int j = 0; j < length; j++) {
                if (!guessUsed[j] && code_obj[i] == guess.code_obj[j]) {
                    incorrectCount++;
                    guessUsed[j] = true;
                    break;
                }
            }
        }
    }

    return incorrectCount;
}

// Code class: Print the code
void Code::printCode() const {
    cout << "{";
    for (int i = 0; i < (length - 1); i++) {
        cout << code_obj[i] << ", ";
    }
    cout << code_obj[length - 1] << "}" << endl;
}


// Response Class
class Response {
    public:
    // Constructor
    Response();

    // Set values
    void Set(int x, int y);
    // Get values
    int getCorrect();
    int getIncorrect();

    // equal
    friend bool operator==(const Response &A, const Response &B);
    // output
    friend ostream & operator<<(ostream&out, Response&A);

    private:
    int num_correct;
    int num_incorrect;
};

// Response Class: constructor
Response::Response() {
    num_correct = 0;
    num_incorrect = 0;
}

// Response Class: Set values
void Response::Set(int x, int y) {
    num_correct = x;
    num_incorrect = y;
}

// Response Class: Get values
int Response::getCorrect() {
    return num_correct;
}
int Response::getIncorrect() {
    return num_incorrect;
}

// Response Class: Equal
bool operator== (const Response &A, const Response &B) {
    return (A.num_correct == B.num_correct) && (A.num_incorrect == B.num_incorrect);
}

// Response Class: Output
ostream & operator<<(ostream&out, Response&A) {
    out<<"("<<A.getCorrect()<<", "<<A.getIncorrect()<<")";
    return out;
}

// Mastermind Class
class Mastermind {
    public:
    // Constructors
    Mastermind(int x, int y);
    Mastermind();

    // Prints Secret Code
    void printCode();

    // Take human guess
    Code humanGuess();

    // Gets Response of guess
    Response getResponse(const Code &guess);

    // Checks if solved
    bool isSolved(const Response &response);

    // Initializes game
    void playGame();

    private:
    Code secret_code;
};
