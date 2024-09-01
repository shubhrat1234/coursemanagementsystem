#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <vector>
#include <ctime>
#include <sstream>
#include <fstream>

class CourseManager {
private:
    std::map<std::string, Course> registeredCourses;
 
public:
    void addCourse(const std::string& courseName, const std::string& instructor, const std::string& courseStartDate,
                   int minEmployees, int maxEmployees) {
        ValidationHelper validationCheck;
        try {
            bool validDate = validationCheck.isValidDate(courseStartDate);
            bool validName = validationCheck.isNotNull(courseName) && validationCheck.isNotNull(instructor);
 
            if (!validDate || !validName) {
                throw std::invalid_argument("Invalid Input");
            }
 
            std::tm tm = {};
            std::istringstream ss(courseStartDate);
            ss >> std::get_time(&tm, "%Y-%m-%d");
            Course course(courseName, instructor, tm, minEmployees, maxEmployees, 0, "");
 
            std::string courseOfferingId = generateCourseOfferingId(course);
            course.setCourseOfferingId(courseOfferingId);
            registeredCourses[courseOfferingId] = course;
            std::cout << courseOfferingId << std::endl;
        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }
 
    Course getCourseByCourseId(const std::string& courseOfferingId) {
        auto it = registeredCourses.find(courseOfferingId);
        return (it != registeredCourses.end()) ? it->second : Course();
    }
 
private:
    static std::string generateCourseOfferingId(const Course& course) {
        std::string courseString = course.getCourseName() + std::to_string(course.getMinEmployees()) +
                                   std::to_string(course.getMaxEmployees()) + course.getInstructor();
 
        try {
            std::hash<std::string> hasher;
            return std::to_string(hasher(courseString));
        } catch (const std::exception& e) {
            return "";
        }
    }
};