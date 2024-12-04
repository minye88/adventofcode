#include <iostream>
#include <fstream>
#include <string>
#include <vector>

/*
    For debugging.
*/
void printInput(std::vector<std::vector<int>>& vec) {
    for (std::vector<int> currentVec : vec) {
        for (int i : currentVec) {
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }
}

void printVector(std::vector<int>& vec) {
    for (int i : vec)
        std::cout << i << " ";

    std::cout << "\n";
}

enum Sequence {
    INCREASING,
    DECREASING,
    NONE
};

bool checkVector(std::vector<int>& vec) {
    
    int diffThreshold = 3;
    Sequence startingSequence, currentSequence = NONE;

    for (size_t i = 0; i < vec.size(); ++i) {
            
        //std::cout << "Current index is " << i << "\n";

        // If reach the last element, this report is safe.
        if (i + 1 == vec.size()) {
            //std::cout << "Reach index " << i << ", level is safe.\n";
            return true;
        }

        // First, determine increasing or decreasing
        if (i == 0) {
            if ((i + 1) < vec.size() && vec[i] - vec[i + 1] < 0) {
                startingSequence = DECREASING;
                //std::cout << "startingSequence is increasing.\n";
            } else {
                startingSequence = INCREASING;
                //std::cout << "startingSequence is decreasing.\n";
            }
        }

        // Next, check increasing or decreasing (for elements after index 0)
        if (vec[i] - vec[i + 1] < 0)
            currentSequence = DECREASING;
        else
            currentSequence = INCREASING;

        if (currentSequence != startingSequence) {
            //std::cout << "Sequence not consistent, level is not safe.\n";
            return false;
        }

        // Next, check different between levels is more than zero and less than 4
        if (std::abs(vec[i] - vec[i + 1]) == 0 || std::abs(vec[i] - vec[i + 1]) > diffThreshold) {
            //std::cout << "Difference is either 0 or larger than threshold, level is not safe.\n";
            return false;
        }
    }

    return false;
}

bool checkVectorPart2(std::vector<int>& vec) {
    
    int diffThreshold = 3;
    Sequence startingSequence = Sequence::NONE;
    Sequence currentSequence = Sequence::NONE;

    printVector(vec);

    for (size_t j = 0; j < vec.size(); ++j) {
        for (size_t i = 0; i < vec.size(); ++i) {
            
            if (i == j) {
                //std::cout << "Skipping index " << i << "\n";
                continue;
            }

            //std::cout << "Current index is " << i << "\n";
            //std::cout << "startingSequence is " << startingSequence << "\n";

            // If reach the last element, this report is safe.
            if (i + 1 == vec.size()) {
                //std::cout << "Reach index " << i << ", level is safe.\n\n";
                return true;
            }

            size_t next;

            if (i + 1 == j) {
                next = i + 2;

                if (next == vec.size()) 
                    return true;
            }
            else
                next = i + 1;

            // First, determine increasing or decreasing
            if (startingSequence == Sequence::NONE) {
                if ((next) < vec.size() && vec[i] - vec[next] < 0) {
                    startingSequence = DECREASING;
                    //std::cout << "startingSequence is increasing.\n";
                } else {
                    startingSequence = INCREASING;
                    //std::cout << "startingSequence is decreasing.\n";
                }
            }

            // Next, check increasing or decreasing (for elements after index 0)
            if (vec[i] - vec[next] < 0)
                currentSequence = DECREASING;
            else
                currentSequence = INCREASING;

            if (currentSequence != startingSequence) {
                //std::cout << "Sequence not consistent, level is not safe.\n";
                break;
            }

            // Next, check different between levels is more than zero and less than 4
            if (std::abs(vec[i] - vec[next]) == 0 || std::abs(vec[i] - vec[next]) > diffThreshold) {
                //std::cout << "Difference is either 0 or larger than threshold, level is not safe.\n";
                break;
            }
        }
        startingSequence = NONE;
    }

   // std::cout << "Unsafe regardless of which level is removed.\n\n";
    return false;
}

int calculateSafeReports(std::vector<std::vector<int>>& inputVector) {
    int safeReports = 0;

    for (std::vector<int> vec : inputVector) {
        
        // // PART 1
        // if (checkVector(vec))
        //     ++safeReports;

        // PART 2
        if (checkVectorPart2(vec))
            ++safeReports;

    }
    return safeReports;
}

int main(int argc, char * argv[])
{
    std::cout << "Hello, World!" << std::endl;

    std::vector<std::vector<int>> input;

    std::string currentLine;
    std::ifstream inputFile("Day2_input.txt");

    if (inputFile.is_open()) {
        while (std::getline(inputFile, currentLine)) {
            //std::cout << currentLine << std::endl;

            std::vector<int> currentVec{};
            std::string currentValue{};
            
            for (char c : currentLine) {
                if (std::isdigit(c))
                    currentValue += c;
                else {
                    //std::cout << "currentValue: " << currentValue << "\n";
                    currentVec.push_back(std::stoi(currentValue));
                    currentValue = "";
                }
            }
            
            input.push_back(currentVec);
        }

        inputFile.close();
    }

    //printInput(input);

    int safeReports = calculateSafeReports(input);
    std::cout << "Total safe reports: " << safeReports << "\n";

    return 0;
}