#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <vector>
#include <ctime>
#include <sstream>
#include <fstream>

class ValidationHelper {
public:
    bool isValidDate(const std::string& dateStr) {
        std::string format = "yyyy-MM-dd";
        std::tm tm = {};
        std::istringstream ss(dateStr);
        ss >> std::get_time(&tm, format.c_str());
        return !ss.fail();
    }
 
    bool isNotNull(const std::string& value) {
        return !value.empty();
    }
};