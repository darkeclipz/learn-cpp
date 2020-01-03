#include <iostream>
#include <string>

int square_digits(int n) {
    std::string digits = std::to_string(n);
    int result = 0;
    for(int i=0; i < digits.size(); i++) {
        int digit = std::atoi(std::string(1, digits[i]).c_str());
        result += digit * digit;
    }
    return result;
}

int chain(int n) {
    do {
        n = square_digits(n);
    }
    while(n != 1 && n != 89);
    return n;
}

int main() {
    std::cout << "Project Euler: Problem 92\nSquare digit chains\n\nCalculating chains...\n";
    int limit = 10000000;
    int answer = 0;
    for(int i=1; i < limit; i++) {
        answer += chain(i) == 89 ? 1 : 0;
        if(i % 100000 == 0) {
           std::cout << "\r[" << i << "/" << limit << "] Intermediary result: " << answer;
        }
    }
    std::cout << "\nAnswer is " << answer << std::endl;
    return 0;
}