#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <vector>
#include <ctime>
#include <sstream>
#include <fstream>

int main() {
    CourseManager courseManager;
    CourseManagementSystem courseManagementSystem;
 
    // Sample code to read from file
    try {
        std::ifstream file("input.txt"); // Replace "input.txt" with your file name
        if (!file.is_open()) {
            throw std::runtime_error("Unable to open file");
        }
 
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::vector<std::string> words{std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{}};
 
            if (words[0] == "ADD-COURSE-OFFERING") {
                courseManager.addCourse(words[1], words[2], words[3], std::stoi(words[4]), std::stoi(words[5]));
            } else if (words[0] == "REGISTER") {
                courseManagementSystem.registerCourse(words[1], words[2]);
            } else if (words[0] == "ALLOT-COURSE") {
                courseManagementSystem.courseAllotment(words[1]);
            } else if (words[0] == "CANCEL") {
                courseManagementSystem.cancelForCourse(words[1]);
            } else {
                throw std::invalid_argument("Invalid Input");
            }
        }
 
        file.close();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
 
    return 0;
}