#include <iostream>
#include <string>
#include <windows.h>
#include <stack>
#include <map>

//---------------------------------------ZEYAD Part----------------------------------
// 1. Student Records Management: Use a Single Linked List (SLL) to store and manage
// student details.
// 2. Course Records Management: Implement a Binary Search Tree (BST) to organize
// and search course information.
//
//---------------------------------------Omar Part----------------------------------
// 3. Course Enrollment History: Employ a Double Linked List (DLL) to track each
// student's course history.
// 4. Course Prerequisites: Use a Stack to validate prerequisites for course registration.
//
//---------------------------------------Mazen Part---------------------------------
// 5. Course Waitlists: Manage waitlists with a Queue.
// 6. Search Optimization: Implement Linear and Binary Search algorithms.
//
// Important Notes
// 1. Proper Variable Names
// 2. Single responsibility principle
// 3. Commit every time you add a new feature or change an old feature with a proper
//    message that explains what happened
// 4. Clean Code of course

using namespace std;

// Function declarations (if any) can go here.
class PrerequisiteCourseStack;
class Student;

class Course // Course Class that stores Course information.
{
public:
    long long courseID;
    double courseCredits;
    string courseName;
    string courseInstructor;
    PrerequisiteCourseStack *prereqStack;

    Course(long long uni_course_ID, string uni_course_name, double uni_course_credits, string uni_course_instructor, PrerequisiteCourseStack *coursePrereqStack)
        : courseID(uni_course_ID), courseName(uni_course_name), courseCredits(uni_course_credits), courseInstructor(uni_course_instructor), prereqStack(coursePrereqStack) {}
};

class DoublyEnrollmentNode // Node for Doubly Linked List of Course Enrollment History.
{
public:
    Course *course;
    DoublyEnrollmentNode *next;
    DoublyEnrollmentNode *prev;

    DoublyEnrollmentNode(Course *c) : course(c), next(NULL), prev(NULL) {}
};

class DoublyEnrollmentHistory // Doubly Linked List for Course Enrollment History for Students.
{
public:
    DoublyEnrollmentNode *head;
    DoublyEnrollmentHistory() : head(NULL) {}

    /**
     * @brief Adds a new course enrollment record to the doubly linked list of course enrollment history.
     *
     * This function creates a new course enrollment node with the given course object and adds it to the end of the linked list.
     * If the linked list is empty, the new node becomes the head of the list.
     *
     * @param enrolledCourse A pointer to the course object representing the course that the student is enrolling in.
     *
     * @return void
     */
    void addEnrollmentRecord(Course *enrolledCourse)
    {
        DoublyEnrollmentNode *newCourseNode = new DoublyEnrollmentNode(enrolledCourse);

        if (!head)
        {
            head = newCourseNode;
            return;
        }

        DoublyEnrollmentNode *tempCourseNode = head;

        while (tempCourseNode->next)
        {
            tempCourseNode = tempCourseNode->next;
        }

        tempCourseNode->next = newCourseNode;
        newCourseNode->prev = tempCourseNode;
    }

    /**
     * @brief Displays the details of all courses in the student's enrollment history.
     *
     * This function iterates through the doubly linked list of course enrollment history and prints the details of each course.
     * The details include the course's ID, name, credits, and instructor.
     *
     * @return void
     */
    void displayEnrollmentHistory()
    {
        // TODO: display that there are no courses in the history if there are none
        DoublyEnrollmentNode *tempCourseNode = head;
        while (tempCourseNode)
        {
            cout << "          Course ID: " << tempCourseNode->course->courseID << endl;
            cout << "          Course Name: " << tempCourseNode->course->courseName << endl;
            cout << "          Course Credits: " << tempCourseNode->course->courseCredits << endl;
            cout << "          Course Instructor: " << tempCourseNode->course->courseInstructor << endl;
            cout << "          -------------------------------------------" << endl;
            tempCourseNode = tempCourseNode->next;
        }
    }

    /**
     * @brief Checks if a given course exists in the student's enrollment history.
     *
     * This function iterates through the doubly linked list of courses in the student's enrollment history.
     * If a matching course node is found, the function returns true.
     * If no matching course node is found, the function returns false.
     *
     * @param courseToBeSearched A pointer to the course object to be searched for in the student's enrollment history.
     *
     * @return bool Returns true if the course is found in the student's enrollment history, false otherwise.
     */
    bool checkCourseExistence(Course *courseToBeSearched)
    {
        DoublyEnrollmentNode *tempCourseNode = head;
        while (tempCourseNode)
        {
            if (courseToBeSearched == tempCourseNode->course)
            {
                return true;
            }
            tempCourseNode = tempCourseNode->next;
        }
        return false;
    }
};

class Student // Student Class that stores Student information.
{
public:
    long long ID, phoneNumber;
    string firstName, middleName, lastName, studentEmail, studentAddress, studentPassword;
    DoublyEnrollmentHistory *enrollmentHistory = new DoublyEnrollmentHistory();

    Student(long long uni_ID, string uni_first_name, string uni_middle_name, string uni_last_name, string uni_student_email, long long uni_phone_number, string uni_student_address, string uni_student_password)
        : ID(uni_ID), firstName(uni_first_name), middleName(uni_middle_name), lastName(uni_last_name), studentEmail(uni_student_email), phoneNumber(uni_phone_number), studentAddress(uni_student_address), studentPassword(uni_student_password) {}
};

class SinglyStudentNode // Node for Singly Linked List of Student Records.
{
public:
    Student *student;
    SinglyStudentNode *next;

    SinglyStudentNode(Student *s) : student(s), next(NULL) {}
};

class SinglyStudentDatabase // Singly Linked List for Student Records.
{
public:
    SinglyStudentNode *head;
    SinglyStudentDatabase() : head(NULL) {}
    int size = 0;

    /**
     * @brief Adds a new student record to the singly linked list of student records.
     *
     * This function creates a new student node with the given student object and adds it to the end of the linked list.
     * If the linked list is empty, the new node becomes the head of the list.
     *
     * @param studentToBeAdded A pointer to the student object to be added to the linked list.
     *
     * @return void
     */
    void addStudentRecord(Student *studentToBeAdded)
    {
        SinglyStudentNode *newStudentNode = new SinglyStudentNode(studentToBeAdded);
        if (!head)
        {
            head = newStudentNode;
        }
        else
        {
            SinglyStudentNode *tempStudentNode = head;
            while (tempStudentNode->next)
            {
                tempStudentNode = tempStudentNode->next;
            }
            tempStudentNode->next = newStudentNode;
        }
        size++;
    }

    /**
     * @brief Removes a student record from the singly linked list of student records based on the given ID.
     *
     * This function iterates through the linked list to find a student node with the matching ID.
     * If a matching student node is found, it is removed from the linked list and the memory is deallocated.
     * If no matching student node is found, nothing happens.
     *
     * @param ID The unique identifier of the student to be removed.
     *
     * @return void
     */
    void removeStudentByID(long long ID)
    {
        SinglyStudentNode *tempStudentNode = head;
        SinglyStudentNode *prev = NULL;
        if (size == 0)
        {
            return;
        };
        while (tempStudentNode)
        {
            if (tempStudentNode->student->ID == ID)
            {
                if (prev)
                    prev->next = tempStudentNode->next;
                else
                    head = tempStudentNode->next;
                delete tempStudentNode;
                size--;
                return;
            }
            prev = tempStudentNode;
            tempStudentNode = tempStudentNode->next;
        }
    }

    /**
     * @brief Displays the details of all students in the student records database.
     *
     * This function iterates through the singly linked list of student records and prints the details of each student.
     * The details include the student's ID, name, email, phone number, and address.
     *
     * @return void
     */
    void displayStudentDetails()
    {

        SinglyStudentNode *tempStudentNode = head;
        while (tempStudentNode)
        {
            cout << "Student ID: " << tempStudentNode->student->ID << endl;
            cout << "Student First Name: " << tempStudentNode->student->firstName << endl;
            cout << "Student Middle Name: " << tempStudentNode->student->middleName << endl;
            cout << "Student Last Name: " << tempStudentNode->student->lastName << endl;
            cout << "Student Email: " << tempStudentNode->student->studentEmail << endl;
            cout << "Student Phone Number: " << tempStudentNode->student->phoneNumber << endl;
            cout << "Student Address: " << tempStudentNode->student->studentAddress << endl;
            cout << "Student Enrollment History:" << endl;
            tempStudentNode->student->enrollmentHistory->displayEnrollmentHistory();
            cout << "---------------------------------------------------------" << endl;
            tempStudentNode = tempStudentNode->next;
        }
    }

    /**
     * @brief Searches for a student in the student records database based on the given ID.
     *
     * This function iterates through the singly linked list of student records to find a student node with the matching ID.
     * If a matching student node is found, the function returns a pointer to the student object.
     * If no matching student node is found, the function returns NULL.
     *
     * @param ID The unique identifier of the student to be searched.
     *
     * @return Student* Returns a pointer to the student object if found, NULL otherwise.
     */
    Student *searchStudentByID(long long ID)
    {
        SinglyStudentNode *tempStudentNode = head;
        while (tempStudentNode)
        {
            if (tempStudentNode->student->ID == ID)
            {
                return tempStudentNode->student;
            }
            tempStudentNode = tempStudentNode->next;
        }
        return NULL;
    }
};

class BinaryTreeCourseNode // Node for Binary Tree of Course Records.
{
public:
    Course *course;
    BinaryTreeCourseNode *left;
    BinaryTreeCourseNode *right;

    BinaryTreeCourseNode(Course *c) : course(c), left(NULL), right(NULL) {}
};

class BinaryTreeCourseDatabase // Binary Tree for Course Database.
{
public:
    BinaryTreeCourseNode *root;
    BinaryTreeCourseDatabase() : root(NULL) {}

    /**
     * @brief Adds a new course to the binary tree of course records.
     *
     * This function traverses the binary tree to find the appropriate position for the new course based on its ID.
     * If the tree is empty, the new course becomes the root of the tree.
     * If the new course's ID is less than the current node's ID, the function traverses to the left child.
     * If the new course's ID is greater than the current node's ID, the function traverses to the right child.
     * If the new course's ID is equal to the current node's ID, it means the course already exists, and a message is printed.
     *
     * @param courseToBeAdded A pointer to the course object to be added to the binary tree.
     *
     * @return void
     */
    void addCourse(Course *courseToBeAdded)
    {
        if (!root)
        {
            root = new BinaryTreeCourseNode(courseToBeAdded);
            return;
        }
        BinaryTreeCourseNode *tempStudentNode = root;
        while (true)
        {
            if (courseToBeAdded->courseID < tempStudentNode->course->courseID)
            {
                if (!tempStudentNode->left)
                {
                    tempStudentNode->left = new BinaryTreeCourseNode(courseToBeAdded);
                    return;
                }
                tempStudentNode = tempStudentNode->left;
            }
            else if (courseToBeAdded->courseID > tempStudentNode->course->courseID)
            {
                if (!tempStudentNode->right)
                {
                    tempStudentNode->right = new BinaryTreeCourseNode(courseToBeAdded);
                    return;
                }
                tempStudentNode = tempStudentNode->right;
            }
            else
            {
                cout << "This Course already exists." << endl;
                return;
            }
        }
    }

    /**
     * @brief Removes a course from the binary tree of course records based on the given ID.
     *
     * This function traverses the binary tree to find the course node with the matching ID.
     * If a matching course node is found, it is removed from the binary tree and the memory is deallocated.
     * If no matching course node is found, a message is printed indicating that the course was not found.
     *
     * @param courseID The unique identifier of the course to be removed.
     *
     * @return void
     */
    void dropCourse(long long courseID)
    {
        if (!root)
        {
            cout << "Course not found." << endl;
            return;
        }

        BinaryTreeCourseNode *node = root;
        BinaryTreeCourseNode *parent = NULL;

        while (node)
        {
            if (courseID < node->course->courseID)
            {
                parent = node;
                node = node->left;
            }
            else if (courseID > node->course->courseID)
            {
                parent = node;
                node = node->right;
            }
            else
            {
                if (!node->left && !node->right) // If the Node has no children.
                {
                    if (parent == NULL)
                    {
                        root = NULL;
                    }
                    else if (parent->left == node)
                    {
                        parent->left = NULL;
                    }
                    else
                    {
                        parent->right = NULL;
                    }
                    delete node;
                }
                else if (!node->left || !node->right) // If the node has one child.
                {
                    BinaryTreeCourseNode *child = node->left ? node->left : node->right;
                    if (parent == NULL)
                    {
                        root = child;
                    }
                    else if (parent->left == node)
                    {
                        parent->left = child;
                    }
                    else
                    {
                        parent->right = child;
                    }
                    delete node;
                }
                else // If the node has two children.
                {
                    BinaryTreeCourseNode *successor = node->right;
                    while (successor && successor->left)
                    {
                        successor = successor->left;
                    }
                    node->course = successor->course;
                    parent = node;
                    node = node->right;
                    while (node && node->course->courseID != successor->course->courseID)
                    {
                        parent = node;
                        node = node->left;
                    }
                    if (parent->left == node)
                    {
                        parent->left = node->right;
                    }
                    else
                    {
                        parent->right = node->right;
                    }
                    delete node;
                }
                return;
            }
        }
        cout << "Course not found." << endl;
    }
};

class PrerequisiteCourseStackNode // Node for the Prerequisite Stack made using Singly Linked List implementation.
{
public:
    Course *course;
    PrerequisiteCourseStackNode *next;

    PrerequisiteCourseStackNode(Course *c) : course(c), next(NULL) {}
};

class PrerequisiteCourseStack // Stack that contains the Prerequisite Courses for a Student to register for a certain Course.
{
public:
    int size = 0;
    PrerequisiteCourseStackNode *top;
    PrerequisiteCourseStack() : top(NULL) {}

    /**
     * @brief Adds a new course prerequisite to the stack.
     *
     * This function creates a new prerequisite course node with the given course object and adds it to the top of the stack.
     * If the stack is empty, the new node becomes the top of the stack.
     *
     * @param prereqCourseToAdd A pointer to the course object representing the prerequisite course to be added to the stack.
     *
     * @return void
     */
    void addToStack(Course *prereqCourseToAdd)
    {
        PrerequisiteCourseStackNode *newCourseNode = new PrerequisiteCourseStackNode(prereqCourseToAdd);

        if (!top)
        {
            top = newCourseNode;
            return;
        }

        newCourseNode->next = top;
        top = newCourseNode;
        size++;
    }

    /**
     * @brief Removes and deallocates the top node from the stack.
     *
     * This function checks if the stack is empty. If the stack is not empty, it removes the top node from the stack,
     * deallocates the memory for the removed node, and updates the top pointer to the next node in the stack.
     * If the stack is empty, it prints a message indicating that no prerequisite courses were found.
     *
     * @return void
     */
    void popFromStack()
    {
        if (!top)
        {
            cout << "No Prerequisite Courses Found!" << endl;
            return;
        }

        PrerequisiteCourseStackNode *courseNodeToPop;

        courseNodeToPop = top;
        top = top->next;
        delete courseNodeToPop;
        size--;
    }

    /**
     * @brief Displays the names of all prerequisite courses in the stack.
     *
     * This function iterates through the stack of prerequisite courses and prints the name of each course.
     * If the stack is empty, it prints a message indicating that no prerequisite courses were found.
     *
     * @return void
     */
    void displayCoursePrerequisites()
    {
        PrerequisiteCourseStackNode *tempCourseNode = top;
        if (size == 0)
        {
            cout << "No Prerequisite Courses Found!" << endl;
            return;
        };
        while (tempCourseNode)
        {
            cout << tempCourseNode->course->courseName << endl;
            tempCourseNode = tempCourseNode->next;
        }
    }

    /**
     * @brief Validates the prerequisite courses for a student to register for a certain course.
     *
     * This function iterates through the stack of prerequisite courses for a student and checks if the student has taken each prerequisite course.
     * If a prerequisite course is not found in the student's enrollment history, the course is added back to the stack.
     * If all prerequisite courses are found in the student's enrollment history, the function returns true.
     * If any prerequisite courses are missing, the function displays the missing courses and returns false.
     *
     * @param studentID The unique identifier of the student.
     * @param students A pointer to the student database containing the student records.
     *
     * @return bool Returns true if all prerequisite courses are found in the student's enrollment history, false otherwise.
     */
    bool validateCoursePrerequisites(long long studentID, SinglyStudentDatabase *students)
    {
        stack<PrerequisiteCourseStackNode *> prereqCoursesToBeTaken;
        Student *student = students->searchStudentByID(studentID);
        PrerequisiteCourseStackNode *tempCourseNode = top;

        while (tempCourseNode && student && size != 0)
        {
            popFromStack();
            if (student->enrollmentHistory->checkCourseExistence(tempCourseNode->course) == false)
            {
                prereqCoursesToBeTaken.push(tempCourseNode);
            }
            tempCourseNode = tempCourseNode->next;
        };

        while (!prereqCoursesToBeTaken.empty())
        {
            addToStack(prereqCoursesToBeTaken.top()->course);
            prereqCoursesToBeTaken.pop();
        };
        if (size == 0)
        {
            return true;
        }
        else
        {
            cout << "---------------------------------------" << endl;
            cout << "Prerequisite Courses Missing:" << endl;
            displayCoursePrerequisites();

            return false;
        };
    }
};

class UniversityManagementSystem
{
public:
    SinglyStudentDatabase studentsDB;
    void addStudentToDatabase()
    {
        long long ID, phoneNumber;
        string firstName, middleName, lastName, studentEmail, studentAddress, studentPassword;
        cout << "Enter Student ID: ";
        cin >> ID;
        cin.ignore();
        cout << "Enter First Name: ";
        getline(cin, firstName);
        cout << "Enter Middle Name: ";
        getline(cin, middleName);
        cout << "Enter Last Name: ";
        getline(cin, lastName);
        cout << "Enter Student Email: ";
        getline(cin, studentEmail);
        cout << "Enter Student Address: ";
        getline(cin, studentAddress);
        cout << "Enter Student Phone Number: ";
        cin >> phoneNumber;
        cin.ignore();
        cout << "Enter Student Password: ";
        getline(cin, studentPassword);
        studentsDB.addStudentRecord(new Student(ID, firstName, middleName, lastName, studentEmail, phoneNumber, studentAddress, studentPassword));
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "Student Added Successfully!" << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    };

    void displayStudentsFromDB()
    {
        if (studentsDB.size == 0)
        {
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << "There are no students in the database" << endl;
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            return;
        }
        studentsDB.displayStudentDetails();
    }

    void removeStudentFromDatabase()
    {
        if (studentsDB.size == 0)
        {
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << "There are no students in the database to remove" << endl;
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            return;
        }
        long long studentID;
        cout << "Enter Student ID to Remove: ";
        cin >> studentID;
        studentsDB.removeStudentByID(studentID);
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "Student Removed Successfully!" << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    }
};

int main()
{
    UniversityManagementSystem NU;
    // std::map<std::string, PrerequisiteCourseStack*> variables;
    // // TODO: add your implementation here to check if the code is working and for the rest to see your progress
    // SinglyStudentDatabase studentsDB;
    // PrerequisiteCourseStack *prereqCourse1Stack = new PrerequisiteCourseStack();

    // // Singly student list implementation.
    // Student *student1 = new Student(231000491, "Omar", "Tamer", "AbouHussein", "O.Tamer2391@nu.edu.eg", 010200, "80th Pickle Jar Street", "verysecurepassword@heilhit123");
    // Student *student2 = new Student(231000010, "Zeyad", "Ahmed", "Mohamed", "Z.Ahmed2310@nu.edu.eg", 010, "81st Pickle Jar Street", "verysecurepassword@heilhit1234");
    // Student *student3 = new Student(231000119, "Mohamed", "Abdellatif", "Abdellatif", "M.Abdellatif2319@nu.edu.eg", 010200, "82nd Pickle Jar Street", "verysecurepassword@heilhit12345");
    // Student *student4 = new Student(231000137, "Mazen", "Ahmed", "El-Mallah", "M.ElMallah2337@nu.edu.eg", 0102, "83rd Pickle Jar Street", "verysecurepassword@heilhit123456");

    // // student3->enrollmentHistory->addEnrollmentRecord(course3);
    // string courseName="math101";
    // studentDB.addStudentRecord(student1);
    // studentDB.addStudentRecord(student2);
    // studentDB.addStudentRecord(student3);
    // studentDB.addStudentRecord(student4);

    // variables[courseName]=new PrerequisiteCourseStack();

    // // Stack implemenetation.
    // Course *course1 = new Course(101, "Electric Circuits", 3.0, "Tamer Abu Elfadl", prereqCourse1Stack);
    // Course *course2 = new Course(211, "Discrete Mathematics", 3.0, "Tamer Abu Elfadl", NULL);
    // prereqCourse1Stack->addToStack(course1);
    // student1->enrollmentHistory->addEnrollmentRecord(course1);
    // student2->enrollmentHistory->addEnrollmentRecord(course2);
    // //studentDB.displayStudentDetails();
    // variables[courseName]->displayCoursePrerequisites();
    // NU.addStudentToDatabase();
    // NU.displayStudentsFromDB();
    NU.removeStudentFromDatabase();
    NU.displayStudentsFromDB();
    cout << "Code working..." << endl;
    return 0;
}