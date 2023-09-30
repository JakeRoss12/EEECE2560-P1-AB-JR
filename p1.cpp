#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>

using namespace std;

// Code class
class Code {
public:
    // Constructor
    Code(int n, int m);

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
    //set length to n
    length = n;
    //set range to m
    range = m;
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
    cout << "Please enter length and range" << endl;
    cin >> n >> m;
    srand(static_cast<unsigned>(time(0)));

    Code codemaker_code(n, m);
    codemaker_code.Randomize();
    codemaker_code.printCode();

    Code guess_code(n, m);
    guess_code.Randomize();
    guess_code.printCode();

    int correctCount = codemaker_code.checkCorrect(guess_code);
    int incorrectCount = codemaker_code.checkIncorrect(guess_code);

    cout << "Number of correct digits in the correct location: " << correctCount << endl;
    cout << "Number of correct digits in the incorrect location: " << incorrectCount << endl;

}
