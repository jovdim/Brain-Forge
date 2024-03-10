#include <iostream>
#include <deque>
#include <random>
#include <chrono>
#include <thread>
#include <cstdlib>

using namespace std;

//  to generate a random number between min and max 
int generateRandomNumber(int min, int max) {
    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<int> distribution(min, max);
    return distribution(generator);
}

// display a sequence of numbers 
void displaySequenceWithIntroduction(const deque<int>& sequence) {
    cout << "\nPrepare yourself! The sequence is about to appear.\n";
    this_thread::sleep_for(chrono::seconds(1));

    cout << "\nMemorize the following sequence:\n\n";
    for (const auto& num : sequence) {
        cout << "   ";
        this_thread::sleep_for(chrono::milliseconds(500));
        cout << num << "   ";
    }
    cout << "\n\n";
    this_thread::sleep_for(chrono::seconds(1));

#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

//  to get player input and check if it matches the sequence
bool validateInput(const deque<int>& sequence) {
    cout << "\nEnter the remembered sequence: ";

    deque<int> userInput;
    int num;

    while (cin >> num) {
        userInput.push_back(num);
    }


    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (!cin.eof() && userInput.empty()) {
        cout << "\nWarning: Invalid number detected.\n";
        return false;
    }

    // Compare user input with sequence
    return (userInput == sequence);
}

// Function to print a separator line
void printSeparator(char symbol, int count) {
    for (int i = 0; i < count; ++i) {
        cout << symbol;
    }
    cout << endl;
}

//  print game information
void printGameInfo(int level, int score) {
    printSeparator('=', 50);
    cout << "Level: " << level << " | Score: " << score << "\n";
    printSeparator('=', 50);
}

//  print the main menu
void printMainMenu() {
    cout << "\n===================================================" << endl;
    cout << "             BRAIN FORGE MENU             " << endl;
    cout << "===================================================\n";
    cout << "1. Start Game\n";
    cout << "2. View Rules\n";
    cout << "3. Exit\n";
    cout << "===================================================\n";
}

//  print the rules
void printRules() {
    printSeparator('=', 50);
    cout << "Rules:\n";
    cout << "1. You will be shown a sequence of numbers to memorize.\n";
    cout << "2. Enter the remembered sequence.\n";
    cout << "3. Each level increases the difficulty with a longer sequence.\n";
    cout << "4. Correct entries earn points. Incorrect entries end the game.\n";
    printSeparator('=', 50);
}

//  to print a fancy message for correct game over
void printCorrectGameOver() {
    cout << "\nCorrect! Moving to the next level.\n";
}


void printDynamicSequence(const deque<int>& sequence) {
    cout << "\nHere's the correct sequence: ";
    for (const auto& num : sequence) {
        cout << num << "   ";
        this_thread::sleep_for(chrono::milliseconds(500));
    }
    cout << "\n";
}

//  to print a message for incorrect game over
void printIncorrectGameOver(int score) {
    cout << "\nIncorrect! Game over.\n";
    printSeparator('=', 50);
    cout << "Your final score: " << score << "\n";
    printSeparator('=', 50);
}

//  to print a fancy thank you message lmaopo
void printThankYouMessage() {
    printSeparator('*', 50);
    cout << "\n\t\t\tThank you for playing!\n";
    cout << "\t\t\tHope you enjoyed the game.\n";
    printSeparator('*', 50);
}


void printDynamicSeparator(char symbol, int count) {
    for (int i = 0; i < count; ++i) {
        cout << symbol;
    }
    cout << endl;
}

int main() {
    const int MAX_LEVEL = 30;
    const int SEQUENCE_LENGTH_START = 1;
    const int POINTS_PER_LEVEL = 10;
    const int MIN_NUMBER = 1;
    const int MAX_NUMBER = 9;

    int level = 1;
    int score = 0;

    deque<int> sequence;

    while (true) {
        printMainMenu();
        cout << "Select an option: ";
        int choice;
        cin >> choice;

        switch (choice) {
        case 1:
            system("clear");
            cout << "Starting the game...\n";
            this_thread::sleep_for(chrono::seconds(1));
            break;
        case 2:
            printRules();
            continue;
        case 3:
            printThankYouMessage();
            return 0;
        default:
            cout << "Invalid choice. Please select a valid option.\n";
            continue;
        }

        while (level <= MAX_LEVEL) {
            printGameInfo(level, score);

            sequence.clear();
            for (int i = 0; i < level - SEQUENCE_LENGTH_START + 1; ++i) {
                sequence.push_back(generateRandomNumber(MIN_NUMBER, MAX_NUMBER));
            }

            displaySequenceWithIntroduction(sequence);

            if (validateInput(sequence)) {
                printCorrectGameOver();
                score += POINTS_PER_LEVEL;
                level++;
            }
            else {
                printIncorrectGameOver(score);
                printDynamicSequence(sequence);
                break;
            }
        }

        cout << "Do you want to play again? (1 for Yes / 2 for No): ";
        int playAgain;
        cin >> playAgain;
        if (playAgain != 1) {
            printThankYouMessage();
            break;
        }
        else {
            level = 1;
            score = 0;
            cout << "\nStarting a new game...\n";
            this_thread::sleep_for(chrono::seconds(1));
        }
    }

    return 0;
}
