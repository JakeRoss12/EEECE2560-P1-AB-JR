//Aral Balsari & Jake Ross
//Project 1b
//Mastermind Game

#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>
#include <limits>

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
    Mastermind(int n, int m, Code secretCode);
    Mastermind(Code secretCode);

    // Prints Secret Code
    void printCode();

    // Get human guess
    Code humanGuess(int n, int m);

    // Gets Response of guess
    Response getResponse(const Code &guess);

    // Checks if solved
    bool isSolved(const Response &response);

    // Initializes game
    void playGame();

private:
    Code secret_code;
    int secret_length;
    int secret_range;
};

// Mastermind Class: constructors
// Currently giving errors I don't understand
Mastermind::Mastermind(int n, int m, Code secretCode) : secret_code(secretCode) {
    secret_length = n;
    secret_range = m;
}
Mastermind::Mastermind(Code secretCode) : secret_code(secretCode) {
    secret_length = 5;
    secret_range = 10;
}

// Mastermind Class: print secret code
void Mastermind::printCode() {
    secret_code.printCode();
}

// Mastermind Class: Get human guess
Code Mastermind::humanGuess(int n, int m) {
    vector<int> guess;
    int current_guess;
    cout << "Please enter your guess one number at a time and press enter: " << endl;
    for (int i = 0; i < n; i++) {
        cin >> current_guess;
        // check if user input triggers fail state
        if (cin.fail()) {
            cout << "That is not an integer, please renter a guess in range: " << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            i--;
        }
        // make sure number is in range, get a new one if not
        else if ((current_guess >= m) || (current_guess < 0)) {
            cout << "That number is out of range, please renter one in range: " << endl;
            i--;
        }
        else {
            guess.push_back(current_guess);
        }
    }
    Code human_guess(n, m, guess);
    return human_guess;
}

// Mastermind Class: get response to guess
Response Mastermind::getResponse(const Code &guess) {
    Response response;
    response.Set(secret_code.checkCorrect(guess), secret_code.checkIncorrect(guess));
    return response;
}

// Mastermind Class: check if solved
bool Mastermind::isSolved(const Response &guess) {
    Response correct;
    correct.Set(secret_length, 0);
    if (correct == guess) {
        return true;
    }
    else {
        return false;
    }
}

void Mastermind::playGame() {
    cout << "I have generated a secret code of length " << secret_length << " and range " << secret_range << "." << endl;

    int attempts = 0;

    while (attempts < 10) {  // You can adjust the maximum number of attempt
        cout << "Attempt " << attempts + 1 << ":" << endl;

        // Get the human guess
        Code guess = humanGuess(secret_length, secret_range);

        // Get the response
        Response response = getResponse(guess);

        // Print the response
        cout << "Response: " << response << endl;

        // Check if the code is solved
        if (isSolved(response)) {
            cout << "Congratulations! You've cracked the code!" << endl;
            cout << "Codebreaker (you) won the game!" << endl;
            break;
        }

        attempts++;
    }

    if (attempts >= 10) {
        cout << "Sorry, you've reached the maximum number of attempts. The secret code was: ";
        secret_code.printCode();
        cout << "Codemaker (computer) won the game!" << endl;
    }
}

int main () {
    // Set the random seed for code generation
    srand(time(0));

    // Welcome user to game
    cout << "Welcome to Mastermind game!" << endl;

    // Get code length and range from user
    int length;
    int range;

    cout << "Please input the length of the code you would like to break: ";
    for (int i = 0; i < 1; i++) {
        cin >> length;
        // check if input stream enters fail state from not getting an int
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please input a length as an integer: ";
            i--;
        }
        // check if length is greater than 0
        else if (length <= 0) {
            cout << "Please input a length greater than 0: ";
            i--;
        }
    }
    
    cout << "Please input the range of the digits in the code you would like to break: ";
    for (int i = 0; i < 1; i++) {
        cin >> range;
        // check if input stream enters fail state from not getting an int
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please input a length as an integer: ";
            i--;
        }
        // check if length is greater than 0
        else if (range <= 0) {
            cout << "Please input a length greater than 0: ";
            i--;
        }
    }

    // Create a Mastermind game with a code from user input
    Code secretcode(length, range);

    cout << "Secret Code: ";
    secretcode.printCode();

    Mastermind game(length, range, secretcode);

    // Play the game
    game.playGame();
}