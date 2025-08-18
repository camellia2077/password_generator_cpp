// File: cracker_multithread.cpp
// A multi-threaded brute-force tool to test password strength.
// FOR EDUCATIONAL PURPOSES ONLY.

#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>    // For std::thread
#include <atomic>    // For std::atomic_bool to safely share state
#include <mutex>     // For std::mutex to protect shared counter
#include <cmath>     // For fmod to handle floating-point division
// --- Shared Constants & Globals ---
// "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
// "!@#$%^&*()_+-=[]{}|;:',.<>/?"
// 
const std::string ALL_CHARS =
    
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789";
    
std::atomic<bool> password_found(false); // Atomic flag to signal all threads to stop
unsigned long long total_attempts = 0;
std::mutex attempts_mutex; // Mutex to safely update the counter

/**
 * @brief Recursively generates combinations. (Same as before, but checks the atomic flag)
 */
void find_password_recursive(std::string& current_guess, const std::string& target_password, const int max_depth) {
    if (password_found) {
        return; // Another thread found it, stop searching
    }
    
    if (current_guess == target_password) {
        password_found = true;
        return;
    }

    if (current_guess.length() >= max_depth) {
        return;
    }

    for (char c : ALL_CHARS) {
        if (password_found) return; // Check again before recursing

        current_guess.push_back(c);
        
        // Safely increment the attempt counter
        {
            std::lock_guard<std::mutex> lock(attempts_mutex);
            total_attempts++;
        }

        find_password_recursive(current_guess, target_password, max_depth);
        if (password_found) return;
        current_guess.pop_back();
    }
}

/**
 * @brief The function that each thread will execute.
 * It takes a range of starting characters to be responsible for.
 */
void worker_thread(const std::string& target_password, int start_index, int end_index) {
    for (int i = start_index; i < end_index; ++i) {
        if (password_found) return; // Check if found before starting a new root character

        std::string initial_guess(1, ALL_CHARS[i]);
        
        // Start the recursive search from this initial character
        find_password_recursive(initial_guess, target_password, target_password.length());
    }
}


int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <password_to_crack>" << std::endl;
        return 1;
    }

    std::string target_password = argv[1];
    if (target_password.empty()) {
        std::cerr << "Error: Cannot crack an empty password." << std::endl;
        return 1;
    }

    std::cout << "Attempting to crack password: '" << target_password << "'" << std::endl;

    // Determine the optimal number of threads (usually the number of CPU cores)
    unsigned int num_threads = std::thread::hardware_concurrency();
    if (num_threads == 0) {
        num_threads = 2; // Fallback if detection fails
    }
    std::cout << "Using " << num_threads << " threads for the attack." << std::endl;

    auto start_time = std::chrono::high_resolution_clock::now();

    // --- Thread Creation and Workload Distribution ---
    std::vector<std::thread> threads;
    // Ceiling division to ensure all characters are covered
    int chars_per_thread = (ALL_CHARS.length() + num_threads - 1) / num_threads;

    for (unsigned int i = 0; i < num_threads; ++i) {
        int start_char_index = i * chars_per_thread;
        int end_char_index = std::min((int)ALL_CHARS.length(), start_char_index + chars_per_thread);
        
        if (start_char_index >= (int)ALL_CHARS.length()) break; // No more work to distribute

        // Create and launch a new thread
        threads.emplace_back(worker_thread, std::ref(target_password), start_char_index, end_char_index);
    }

    // Wait for all threads to complete their work
    for (auto& t : threads) {
        t.join();
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_time = end_time - start_time;

    // --- MODIFIED SECTION: Time Formatting ---
    double total_seconds = elapsed_time.count();
    // Use long long to prevent overflow for very long durations
    long long total_seconds_int = static_cast<long long>(total_seconds);

    long long hours = total_seconds_int / 3600;
    long long minutes = (total_seconds_int % 3600) / 60;
    // Use fmod to get the remainder of a floating-point division
    double seconds = fmod(total_seconds, 60.0);
    // --- END OF MODIFIED SECTION ---

    std::cout << "\n--------------------" << std::endl;
    if (password_found) {
        std::cout << "Password found!" << std::endl;
        std::cout << "Password: " << target_password << std::endl;
    } else {
        std::cout << "Password not found. (Ensure it only uses characters from the defined set)" << std::endl;
    }
    
    std::cout << "Total attempts: " << total_attempts << std::endl;
    
    // --- NEW: Display the formatted time ---
    std::cout << "Time taken: " << hours << " hours, " << minutes << " minutes, " << seconds << " seconds." << std::endl;
    
    std::cout << "--------------------" << std::endl;

    return 0;
}