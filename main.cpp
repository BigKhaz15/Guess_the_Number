#include <iostream>
#include <random>
#include <string>
#include <cctype>
#include <cstdlib>


int get_int(const std::string prompt);

int main(int argc, char* args[]) {
    // Obtain a random number to be guessed
    std::random_device rd; // Creating the random device object
    std::mt19937 gen(rd()); // Seed the mersenne twister using a value from the rd
    std::uniform_int_distribution<uint16_t> distrib(1, 100);
    int num_to_guess = distrib(gen);
    int guess = 0;
    int num_tries = 0;
    bool running = true;
    // Welcome user and prompt to guess number
    std::cout << "Welcome to the random number guessing game!\n";
    std::cout << "To begin please enter your first guess below (1-100), then I will tell you if it was correct or higher or lower than thetarget.\n";

    // Check if number was correct, yes => tell them they won, no => tell them higher or lower, repeat
    while (running) {
        guess = get_int("\nPlease enter your guess: ");
        if (guess == -1) {
            std::cout << "Input is unavailable, ending the game.\n";
            return EXIT_FAILURE;
        }
        num_tries++;
        if (guess > num_to_guess)
            std::cout << "Too high!\n";
        else if (guess < num_to_guess)
            std::cout << "Too low!\n";
        else {
            running = false;
            std::cout << "You win! It took you " << num_tries << " guesses to beat me! Way to go!\n";
        }
    }
    // End
    return 0;
}
int get_int(const std::string prompt) {
    std::string input_str{};
    while (true) {
        std::cout << prompt;
        if (std::getline(std::cin, input_str)) {
            if (input_str.empty()) {
                std::cout << "You can't guess nothing!\n";
                continue;
            }
            // Skip leading whitespace
            size_t start = 0;
            while (start < input_str.length() && std::isspace(static_cast<unsigned char>(input_str[start])))
                start++;
            // Skip trailing whitespace
            size_t end = input_str.length() - 1;
            while (end > start && std::isspace(static_cast<unsigned char>(input_str[end])))
                end--;
            // Keep the remaining text
            input_str = input_str.substr(start, end - start + 1);
            if (input_str.empty()) {
                std::cout << "You can't guess nothing!\n";
                continue;
            }
            bool non_digit_found = false;
            for (char c : input_str) {
                if (!isdigit(static_cast<unsigned char>(c))) {
                    non_digit_found = true;
                    break;
                }
            }
            if (non_digit_found) {
                std::cout << "Invalid input! Please enter digits only. e.g. 12.\n";
                continue;
            }
            if (input_str.length() > 3) {
                std::cout << "Please keep the number between 1 and 100.\n";
                continue;
            }
            int good_num = stoi(input_str);
            if (good_num < 1 || good_num > 100) {
                std::cout << "Please keep the number between 1 and 100.\n";
                continue;
            }
            return good_num;
        }
        else
            return -1;
    }
}