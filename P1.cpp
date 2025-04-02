#include <iostream>
#include <string>

int main() {
    std::string str;
    
    std::cout << "Enter String: ";
    std::getline(std::cin, str);
    
    int length = str.length();
    if (length < 2) {
        std::cout << "\nInvalid String";
        return 0;
    }
    
    if (str[0] != 'a') {
        std::cout << "\nInvalid String";
        return 0;
    }
    
    int i = 0;
    while (i < length && str[i] == 'a') {
        i++;
    }
    
    if (i < length && str[i] == 'b' && (i + 1 < length) && str[i + 1] == 'b' && (i + 2 == length)) {
        std::cout << "\nValid String";
    } else {
        std::cout << "\nInvalid String";
    }
    
    return 0;
}