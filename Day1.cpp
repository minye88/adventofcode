#include <iostream>
#include <fstream>
#include <string>
#include <vector>

/*
    Insert a value into the list in the correct position (like in insertion sort).
*/
void insertValue(int value, std::vector<int>& vec) {
    
    size_t size = vec.size();
    //std::cout << "size: " << size << '\n';

    if (size == 0) {
        vec.push_back(value);
        return;
    }
    else {
        for (size_t i = 0; i < size; ++i) {
            if (value <= vec[i]) {
                std::vector<int>::iterator it = vec.begin();
                vec.insert(it + i, value);
                return;
            }
        }
    }

    vec.insert(vec.end(), value);
}

/*
    For debugging.
*/
void printVec(std::vector<int>& vec) {
    for (int x : vec)
        std::cout << x << "\n";
}

/*
    Calculate the difference between values of the same index in each list.
*/
int calculateDiff(std::vector<int>& left, std::vector<int>& right) {
    size_t size = left.size();
    size_t sizeRight = right.size();

    //std::cout << "sizeLeft: " << size << "\tsizeRight: " << sizeRight << "\n";

    int totalDiff = 0;
    for (size_t i = 0; i < size; ++i) {
        int currentDiff = std::abs(left[i] - right[i]);
        std::cout << "[" << i << "] " << left[i] << " - " << right[i] << " = " << currentDiff << "\n";
        totalDiff += std::abs(left[i] - right[i]);
    }
    return totalDiff;
}

int main(int argc, char * argv[])
{
    std::cout << "Hello, World!" << std::endl;

    std::vector<int> left, right;

    std::string currentLine;
    std::ifstream inputFile("Day1_input.txt");

    if (inputFile.is_open()) {
        while (std::getline(inputFile, currentLine)) {
            //std::cout << currentLine << std::endl;

            std::string leftString, rightString;
            int leftValue, rightValue;

            leftString = currentLine.substr(0, currentLine.find(" "));
            rightString = currentLine.substr(currentLine.find(" "));

            //std::cout << "leftString: " << leftString << "\trightString: " << rightString << std::endl;

            leftValue = std::stoi(leftString);
            rightValue = std::stoi(rightString);

            insertValue(leftValue, left);
            insertValue(rightValue, right);
        }

        inputFile.close();
    }

    //printVec(left);
    //printVec(right);

    int totalDiff = calculateDiff(left, right);

    std::cout << "Total distance between lists: " << totalDiff << "\n";

    return 0;
}