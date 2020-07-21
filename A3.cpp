// Created on 14/06/2020 11:16AM
// @sq
// A3.cpp
// Class Knapsack Definition and main() file

/* DEBUG COMMENTS / CODE LINES ARE ENCLOSED IN THIS COMMENT STYLE */

// Header includes
#include <iostream>
#include <queue>
#include <map>
#include <vector>
#include <random>
//#include <cstdlib>
#include <algorithm>
#include "collect.h"

/* std::string testStr = "CBDFBGAFF"; */

// Class Declaration
class Knapsack {

// Public functions
public:
    // Contructor
    Knapsack(size_t iSize, size_t iSeed);

    // To launch program
    void start_generation();

    // Template function addToKnapsack, which takes input as template parameter
    template<typename ValueType>
    bool addToKnapsack();

    // Template function to check if Knapsack has space
    template<typename ValueType>
    bool knapsackHasSpaceFor(const ValueType &iObject);

    // Function to generate output at stoout
    void showReports();

    /* char debug_enter(); */

// Private fields
private:
    size_t mSize{};                     // Knapsack Size
    size_t mSeed{};                     // Seed value
    size_t mAddedSize{};                // Filled Size
    std::queue<char> mKnapsack{};       // Knapsack
    std::map<char, std::pair<size_t, size_t>> mCount{}; // Map to keep track of count of objects and size
};

// Member function definitions

Knapsack::Knapsack(size_t iSize, size_t iSeed) {
    mSize = iSize;
    mSeed = iSeed;

}

void Knapsack::start_generation() {

    //std::mt19937 random_generator(mSeed);
    // srand(mSeed);
    // To check if the result of generate() is correct or not
    std::vector<char> possible_classes{'A','B','C','D','E','F','G'};
    bool success_status;
    do {
        //char to_add = generate(random_generator());
        char to_add = generate(mSeed);
        // Check generate() correctness
        if (std::find(possible_classes.begin(),possible_classes.end(),to_add) == possible_classes.end()) {
            std::cout << "\n Incorrect return value from generate(), assuming class A\n";
            to_add = 'A';
        }

        /* char to_add = debug_enter(); */
        success_status = false;

        // Call addToKnapsack with corresponding template argument
        switch (to_add) {
            case 'A':
                success_status = addToKnapsack<A>();
                break;

            case 'B':
                success_status = addToKnapsack<B>();
                break;

            case 'C':
                success_status = addToKnapsack<C>();
                break;

            case 'D':
                success_status = addToKnapsack<D>();
                break;

            case 'E':
                success_status = addToKnapsack<E>();
                break;

            case 'F':
                success_status = addToKnapsack<F>();
                break;

            case 'G':
                success_status = addToKnapsack<G>();
                break;
        }

    } while (success_status);

}

template<typename ValueType>
bool Knapsack::addToKnapsack() {
    ValueType obj;

    // Add object to knapsack if it has space
    if (knapsackHasSpaceFor(obj)) {
        mKnapsack.push(obj.getName());

        // Update corresponding parameters
        mCount[obj.getName()].first = sizeof(obj);
        mCount[obj.getName()].second++;
        mAddedSize += sizeof(obj);
        return true;
    } else
        return false;
}

template<typename ValueType>
bool Knapsack::knapsackHasSpaceFor(const ValueType &iObject) {
    return (sizeof(iObject) + mAddedSize <= mSize);
}

void Knapsack::showReports() {
    std::cout << "\nKnapsack size: " << mSize
              << "\nAdded object size: " << mAddedSize << "\n";

    // Use the queue's FIFO ordering to display objects in order of insertion
    while (!mKnapsack.empty()) {
        std::cout << mKnapsack.front();
        mKnapsack.pop();
    }

    // Iterate over map and display
    for (const auto &i : mCount) {
        std::cout << "\n" << i.first << " : " << (i.second).first << ", " << (i.second).second;
    }

}

/*
char Knapsack::debug_enter() {
    static int index = 0;
    index++;
    return testStr[index - 1];

}
*/

// main() function
int main(int argc, char *argv[]) {

    /* std::cout << "\n argc = " << argc << "\n";  */

    // Check input command-line parameters
    if (argc != 3) {
        std::cout << "\n ERROR: Incorrect number of arguments provided."
                  << "\n Usage:\n"
                  << "\t ./KAP <knapsack-size> <randomizer-seed>"
                  << "\n Both arguments should be strictly positive.\n";
        exit(-1);
    } else if (std::stoi(argv[1]) < 1 || std::stoi(argv[2]) < 1) {
        std::cout << "\n ERROR: Incorrect values of arguments provided."
                  << "\n Usage:\n"
                  << "\t ./KAP <knapsack-size> <randomizer-seed>"
                  << "\n Both arguments should be strictly positive.\n";
        exit(-1);
    }

    // Instantiate Knapsack Object
    Knapsack theKnapsack(std::stoi(argv[1]), std::stoi(argv[2]));

    // Start generation
    theKnapsack.start_generation();

    // Show reports
    theKnapsack.showReports();

    std::cout << "\n";
    return 0;
}