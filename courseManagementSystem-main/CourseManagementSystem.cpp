#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <vector>
#include <ctime>
#include <sstream>
#include <fstream>


class CourseManagementSystem {
private:
    std::string registrationId;
    std::map<std::string, std::pair<Course, std::string>> courseEmployeeTrack;
 
public:
    static std::string generateRegistrationId(const std::string& emailId, const std::string& courseId) {
        try {
            std::string inputString = emailId + "_" + courseId;
            return inputString;
        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
            return "";
        }
    }
 
    std::string registerCourse(const std::string& email, const std::string& courseOfferingId) {
        CourseManager courseManager;
        Course course = courseManager.getCourseByCourseId(courseOfferingId);
        std::string status = "NA";
        try {
            if (!course.getCourseOfferingId().empty()) {
                std::tm courseStartDate = course.getCourseStartDate();
                std::tm currentDate = {};
                std::time_t t = std::time(nullptr);
                currentDate = *std::localtime(&t);
 
                std::string registrationId = generateRegistrationId(email, courseOfferingId);
 
                if (std::difftime(std::mktime(&currentDate), std::mktime(&courseStartDate)) < 0) {
                    if (course.getRegisteredEmployees() < course.getMaxEmployees()) {
                        course.incrementRegisteredEmployees();
 
                        status = "PENDING";
 
                        if (course.getRegisteredEmployees() >= course.getMinEmployees()) {
                            status = "ACCEPTED";
                        }
                    } else {
                        status = "COURSE_FULL_ERROR";
                    }
                } else {
                    if (course.getRegisteredEmployees() < course.getMinEmployees()) {
                        status = "COURSE_CANCELLED";
                    } else {
                        status = "COURSE_ALREADY_STARTED";
                    }
                }
 
                courseEmployeeTrack[registrationId] = std::make_pair(course, status);
                std::cout << status << std::endl;
            } else {
                throw std::invalid_argument("Course Not found");
            }
        } catch (const std::exception& e) {
            std::cerr << "Error while registering for course" << std::endl;
            std::cerr << e.what() << std::endl;
        }
        return (status == "ACCEPTED") ? registrationId : "";
    }
 
     void courseAllotment(const std::string& courseOfferingId) {
        for (const auto& iter : courseEmployeeTrack) {
            const std::string& registrationId = iter.first;
            const std::pair<Course, std::string>& p = iter.second;
            const std::string& status = p.second;
            const Course& course = p.first;
 
            std::istringstream iss(registrationId);
            std::string email;
            std::getline(iss, email, '_');
 
            std::tm currentDate = {};
            std::time_t t = std::time(nullptr);
            currentDate = *std::localtime(&t);
 
            std::tm courseStartDate = course.getCourseStartDate();
 
            if (std::difftime(std::mktime(&currentDate), std::mktime(&courseStartDate)) >= 0) {
                if (status == "PENDING" && course.getRegisteredEmployees() >= course.getMinEmployees()) {
                    status = "ACCEPTED";
                } else {
                    status = "COURSE_CANCELLED";
                }
            }
 
            if (course.getCourseOfferingId() == courseOfferingId) {
                if (status == "ACCEPTED") {
                    std::cout << registrationId << " " << email << " " << course.getCourseOfferingId() << " "
                              << course.getCourseName() << " " << course.getInstructor() << " "
                              << std::put_time(&courseStartDate, "%Y-%m-%d") << " " << status << std::endl;
                } else {
                    std::cout << "NULL " << email << " " << course.getCourseOfferingId() << " "
                              << course.getCourseName() << " " << course.getInstructor() << " "
                              << std::put_time(&courseStartDate, "%Y-%m-%d") << " " << status << std::endl;
                }
            }
        }
    }
 
    std::string cancelForCourse(const std::string& courseRegistrationId) {
        if (courseEmployeeTrack.find(courseRegistrationId) != courseEmployeeTrack.end()) {
            const std::string& status = courseEmployeeTrack[courseRegistrationId].second;
            const std::tm& courseStartDate = courseEmployeeTrack[courseRegistrationId].first.getCourseStartDate();
 
            std::tm currentDate = {};
            std::time_t t = std::time(nullptr);
            currentDate = *std::localtime(&t);
 
            if (std::difftime(std::mktime(&currentDate), std::mktime(&courseStartDate)) < 0) {
                if (status == "ACCEPTED" || status == "PENDING") {
                    std::cout << "CANCEL_ACCEPTED" << std::endl;
                    return "CANCEL_ACCEPTED";
                }
            }
        }
        std::cout << "CANCEL_REJECTED" << std::endl;
        return "CANCEL_REJECTED";
    }
};