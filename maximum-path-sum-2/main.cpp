/*
    Projec Euler Problem 67: Maximum Path Sum II

    Problem:    By starting at the top of the triangle below and moving to adjacent numbers 
                on the row below, the maximum total from top to bottom is 23.

                    3
                    7 4
                    2 4 6
                    8 5 9 3

                That is, 3 + 7 + 4 + 9 = 23.

                Find the maximum total from top to bottom in triangle.txt containing 
                a triangle with one-hundred rows.

    Solution:   Let rows be the number of rows. First create an array:
                    
                    result = [0, 0, 0, 0, ..., r], 
                    
                initialised to zero (0). The result can then be found with the following algorithm:

                For each row in the triangle:

                    For each index p in row q:

                        buffer = [result[p], max(result[p-1], result[p]), ..., max(result[p-1], result[p])]

                    Copy the buffer into the result
                
                Find maximum value in result
                Print result

*/  
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>

int main() {
    std::fstream file;                  // Input file.
    file.open("triangle.txt");          
    int rows = 100;                     // The number of rows in the triangle.
    int* result = new int[rows]{0};     // The final result.
    int* temp = new int[rows]{0};       // The intermediate result for each row.
    int row_index = 0;                  // Start at position 0.
    int row_size = 1;                   // Start at row 1.
    std::string str;                    // Holds the current digit as string.

    while(file >> str) {

        // Convert the digit to an integer.
        int n = std::atoi(str.c_str());

        if(row_index == 0) {
            // We are on a new row, get the value from above.
            temp[row_index] = result[row_index] + n;
        }
        else {
            // Get the two upper values and see which one is bigger.
            temp[row_index] = std::max(result[row_index-1] + n, result[row_index] + n);
        }

        // Move to the next column.
        ++row_index; 

        // Reached end of the row, increment row...
        if(row_index == row_size) {

            // Reset the column.
            row_index = 0; 

            // Move to the next row.
            row_size++;   

            // Copy the temp buffer into the result.
            for(int i=0; i < row_size; i++) {
                result[i] = temp[i];
            }

            // Reset the temp buffer.
            delete[] temp;
            temp = new int[rows]{0};
        }
    }
    file.close();

    // Find the maximum value in the result.
    int max = 0;
    for(int i=0; i < rows; i++) {
        if(result[i] > max) {
            max = result[i];
        }
    }

    std::cout << "Answer: " << max << std::endl;

    // Clean
    delete[] temp;
    delete[] result;

    return 0;
}