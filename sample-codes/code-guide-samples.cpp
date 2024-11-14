#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <array>

int maxSize = 3; // NOT ALLOWED
const int MAX_SIZE = 3; // ALLOWED

std::stack<int> undoHistory;
std::stack<int> redoHistory;

// std::stack<int> *history[2] = {&undoHistory, &redoHistory}; 
// avoid this

struct History {
    std::stack<int> *undoHistory;
    std::stack<int> *redoHistory;
};

History history = {&undoHistory, &redoHistory};
// do this instead

void checkCharacterStatistics (int *playerHealth, int *enemyHealth, std::vector<std::string> *playerStatusEffects, std::vector<std::string> *enemyStatusEffects) {
    --*playerHealth; // this is how you increment and decrement the value of a pointer variable btw
    --*enemyHealth;

    // too long, right?

}

struct CharacterStatistics {
    int *playerHealth;
    int *enemyHealth;
    std::vector<std::string> *playerStatusEffects;
    std::vector<std::string> *enemyStatusEffects;

};

void checkCharacterStatistics (CharacterStatistics *characterStatistics) {
    --*characterStatistics->playerHealth;
    --*characterStatistics->enemyHealth;

    // voila, decreased!!!

}

std::vector<int> extractNumbersIntoVector (std::stack<int> numberStack, int numberToRemove) {
    int originalSize = numberStack.size();
    int removedNumberCounter = 0;
    std::vector<int> newNumberVector;

    for (int counter = 0; counter < originalSize; counter++) {
        // now that we stored the value of numberStack.size into originalSize beforehand
        // it won't be affected by the .pop() 
        if (!(numberStack.top() == numberToRemove)) {
            newNumberVector.push_back(numberStack.top());

        }

        numberStack.pop();
        // this will iterate properly even with this .pop()

    }

    return newNumberVector;
}

// std::vector<int> extractNumbersIntoVector (std::stack<int> numberStack, int numberToRemove) {
//     int removedNumberCounter = 0;
//     std::vector<int> newNumberVector;

//     for (int counter = 0; counter < numberStack.size(); counter++) {
//         // notice how the actual stack's .size() is being used
//         // that .size()'s value will change every iteration because of the .pop() method being executed
//         if (!(numberStack.top() == numberToRemove)) {
//             newNumberVector.push_back(numberStack.top());

//         }

//         numberStack.pop();

//     }

//     return newNumberVector;
// }

void displayVector (std::vector<int> vector) {
    for (int index = 0; index < vector.size(); index++) {
        std::cout << vector[index] << '\n';

    }

}


int main () {
    std::vector<std::string> sdsd;
    std::vector<std::string> sdse;

    int playerHealth = 10;
    int enemyHealth = 10;

    CharacterStatistics characters = {&playerHealth, &enemyHealth, &sdse, &sdsd};

    checkCharacterStatistics(&characters);

    //std::cout << *characters.playerHealth << '\n';

    // int preIncrementSample = 10;
    // int postIncrementSample = 10;
    // int preDecrementSample = 10;
    // int postDecrementSample = 10;

    // std::cout << '\n';
    // std::cout << "Pre-Increment: " << ++preIncrementSample << '\n';
    // std::cout << '\n';

    // std::cout << "Post-Increment: " << postIncrementSample++ << '\n'; 
    // std::cout << "When called again: " << postIncrementSample << '\n';
    // std::cout << '\n';
    // std::cout << '\n';
    
    // std::cout << "Pre-Decrement: " << --preDecrementSample << '\n';
    // std::cout << '\n';
    
    // std::cout << "Post-Decrement: " << postDecrementSample-- << '\n'; 
    // std::cout << "When called again: " << postDecrementSample << '\n';
    // std::cout << '\n';

    //if (1) {
        //std::cout << 1 << '\n';
    // extra space before the next condition

    //} else if (2) {
        //std::cout << 2 << '\n';
    // extra space includes comments

    //} else {
        //std::cout << 3 << '\n';
    // extra space even if there isn't a next condition
    
    //}

    // std::string helloWorld = "Hello world!";

    // for (int index = 0; index < helloWorld.size(); index++) {
    //     std::cout << helloWorld[index] << '\n';

    // }

    // for (int counter = 0; counter < 10; counter++) {
    //     std::cout << helloWorld << '\n';

    // }

    std::stack<int> numberStack;
    std::vector<int> numberVector;

    numberStack.push(1);
    numberStack.push(1);
    numberStack.push(22);
    numberStack.push(1);
    numberStack.push(1);
    numberStack.push(1);
    numberStack.push(34);
    numberStack.push(1);
    numberStack.push(1);
    numberStack.push(5);
    numberStack.push(1);
    numberStack.push(6);

    numberVector = extractNumbersIntoVector(numberStack, 1);

    displayVector(numberVector);
}