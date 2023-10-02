//Aral Balsari & Jake Ross
//Project 1a
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

int main() {
    int n;
    int m;
    cout << "Please enter the length of the secret code: ";
    cin >> n;
    cout << "Please enter the range of numbers: ";
    cin >> m;
    srand(static_cast<unsigned>(time(0)));

    // Create the secret code
    Code codemaker_code(n, m);
    cout << "Secret Code: ";
    codemaker_code.printCode();

    // Sample guess codes
    Code guess1(n, m, {5, 0, 3, 2, 6});
    cout << "Guess Code 1: ";
    guess1.printCode();

    Code guess2(n, m, {2, 1, 2, 2, 2});
    cout << "Guess Code 2: ";
    guess2.printCode();

    Code guess3(n, m, {1, 3, 3, 4, 5});
    cout << "Guess Code 3: ";
    guess3.printCode();

    int correctCount1 = codemaker_code.checkCorrect(guess1);
    int incorrectCount1 = codemaker_code.checkIncorrect(guess1);

    int correctCount2 = codemaker_code.checkCorrect(guess2);
    int incorrectCount2 = codemaker_code.checkIncorrect(guess2);

    int correctCount3 = codemaker_code.checkCorrect(guess3);
    int incorrectCount3 = codemaker_code.checkIncorrect(guess3);

    cout << "Guess 1 - Correct: " << correctCount1 << " Incorrect: " << incorrectCount1 << endl;
    cout << "Guess 2 - Correct: " << correctCount2 << " Incorrect: " << incorrectCount2 << endl;
    cout << "Guess 3 - Correct: " << correctCount3 << " Incorrect: " << incorrectCount3 << endl;
}
