#include <iostream>
#include <string>
#include <ctime>

class Course {
private:
    std::string courseName;
    std::string instructor;
    std::tm courseStartDate;
    int minEmployees;
    int maxEmployees;
    int registeredEmployees;
    std::string courseOfferingId;
 
public:
    Course() {}
    Course(const std::string& courseName, const std::string& instructor, const std::tm& courseStartDate,
           int minEmployees, int maxEmployees, int registeredEmployees, const std::string& courseOfferingId)
        : courseName(courseName), instructor(instructor), courseStartDate(courseStartDate),
          minEmployees(minEmployees), maxEmployees(maxEmployees), registeredEmployees(registeredEmployees),
          courseOfferingId(courseOfferingId) {}
 
    // Getter and setter methods for Course attributes
 
    std::string getCourseName() const {
        return courseName;
    }
 
    Course& setCourseName(const std::string& courseName) {
        this->courseName = courseName;
        return *this;
    }
 
    std::string getInstructor() const {
        return instructor;
    }
 
    Course& setInstructor(const std::string& instructor) {
        this->instructor = instructor;
        return *this;
    }
 
    std::tm getCourseStartDate() const {
        return courseStartDate;
    }
 
    Course& setCourseStartDate(const std::tm& courseStartDate) {
        this->courseStartDate = courseStartDate;
        return *this;
    }
 
    int getMinEmployees() const {
        return minEmployees;
    }
 
    Course& setMinEmployees(int minEmployees) {
        this->minEmployees = minEmployees;
        return *this;
    }
 
    int getMaxEmployees() const {
        return maxEmployees;
    }
 
    Course& setMaxEmployees(int maxEmployees) {
        this->maxEmployees = maxEmployees;
        return *this;
    }
 
    int getRegisteredEmployees() const {
        return registeredEmployees;
    }
 
    Course& incrementRegisteredEmployees() {
        registeredEmployees++;
        return *this;
    }
 
    std::string getCourseOfferingId() const {
        return courseOfferingId;
    }
 
    Course& setCourseOfferingId(const std::string& courseOfferingId) {
        this->courseOfferingId = courseOfferingId;
        return *this;
    }
};