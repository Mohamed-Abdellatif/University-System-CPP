#include <iostream>
#include <string>
#include <windows.h>

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
class DoublyEnrollmentHistory;

class Student // Student Class that stores Student information.
{
public:
    long long ID, phoneNumber;
    string firstName, middleName, lastName, studentEmail, studentAddress, studentPassword;
    DoublyEnrollmentHistory *enrollmentHistory;

    Student(long long uni_ID, string uni_first_name, string uni_middle_name, string uni_last_name, string uni_student_email, long long uni_phone_number, string uni_student_address, string uni_student_password, DoublyEnrollmentHistory *studentEnrollmentHistory)
     : ID(uni_ID), firstName(uni_first_name), middleName(uni_middle_name), lastName(uni_last_name), studentEmail(uni_student_email), phoneNumber(uni_phone_number), studentAddress(uni_student_address), studentPassword(uni_student_password), enrollmentHistory(studentEnrollmentHistory) {}
};

class Course // Course Class that stores Course information.
{
public:
    long long courseID;
    double courseCredits;
    string courseName;
    string courseInstructor;

    Course(long long uni_course_ID, string uni_course_name, double uni_course_credits, string uni_course_instructor)
     : courseID(uni_course_ID), courseName(uni_course_name), courseCredits(uni_course_credits), courseInstructor(uni_course_instructor) {}
};

class SinglyStudentNode // Node for Singly Linked List of Student Records.
{
public:
    Student *student;
    SinglyStudentNode *next;

    SinglyStudentNode(Student *s) : student(s), next(NULL) {}
};

class BinaryTreeCourseNode // Node for Binary Tree of Course Records.
{
public:
    Course *course;
    BinaryTreeCourseNode *left;
    BinaryTreeCourseNode *right;

    BinaryTreeCourseNode(Course *c) : course(c), left(NULL), right(NULL) {}
};

class PrerequisiteCourseStackNode // Node for the Prerequisite Stack made using Singly Linked List implementation.
{
public:
    Course *course;
    PrerequisiteCourseStackNode *next;

    PrerequisiteCourseStackNode(Course *c) : course(c), next(NULL) {}
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
        //TODO: display that there are no courses in the history if there are none
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
};

class SinglyStudentDatabase // Singly Linked List for Student Records.
{
public:
    SinglyStudentNode *head;
    SinglyStudentDatabase() : head(NULL) {}

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
        while (tempStudentNode)
        {
            if (tempStudentNode->student->ID == ID)
            {
                if (prev)
                    prev->next = tempStudentNode->next;
                else
                    head = tempStudentNode->next;
                delete tempStudentNode;
                cout << "Student Removed." << endl;
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
        //TODO: display that there are no students in the database if there are none
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

class PrerequisiteCourseStack // Stack that contains the Prerequisite Courses for a Student to register for a certain Course.
{
public:
    PrerequisiteCourseStackNode *top;
    PrerequisiteCourseStack() : top(NULL) {}

    /**
     * @brief Adds a new course to the prerequisite course stack.
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
    }

    // TODO: Change the return type from void to PrerequisiteCourseStackNode, and find a way to save the node and return it before deletion.
    void popFromStack()
    {
        if (!top)
        {
            cout << "No Prerequisite Courses Found!" << endl;
            return;
        }

        PrerequisiteCourseStackNode *courseNodeToPop = new PrerequisiteCourseStackNode();

        courseNodeToPop = top;
        top = top->next;
        delete courseNodeToPop;
        
        // return top;
    }


    PrerequisiteCourseStack* validateCoursePrerequisites(long long courseID, long long studentID)
    {
        // TODO: Make the algorithm for this, such that it saves the student ID and course ID in a temp node,
        // and if the Course Enrollment History of the Student has a Course ID that matches a future Course's ID, then it is popped from the stack.
    }
};

int main()
{
    // TODO: add your implementation here to check if the code is working and for the rest to see your progress
    SinglyStudentDatabase studentDB;
    DoublyEnrollmentHistory *student1EnrollmentHistory = new DoublyEnrollmentHistory();
    DoublyEnrollmentHistory *student2EnrollmentHistory = new DoublyEnrollmentHistory();
    DoublyEnrollmentHistory *student3EnrollmentHistory = new DoublyEnrollmentHistory();
    DoublyEnrollmentHistory *student4EnrollmentHistory = new DoublyEnrollmentHistory();

    // Singly student list implementation.
    Student *student1 = new Student(231000491, "Omar", "Tamer", "AbouHussein", "O.Tamer2391@nu.edu.eg", 010200, "80th Pickle Jar Street", "verysecurepassword@heilhit123", student1EnrollmentHistory);
    Student *student2 = new Student(231000010, "Zeyad", "Ahmed", "Mohamed", "Z.Ahmed2310@nu.edu.eg", 010, "81st Pickle Jar Street", "verysecurepassword@heilhit1234", student2EnrollmentHistory);
    Student *student3 = new Student(231000119, "Mohamed", "Abdellatif", "Abdellatif", "M.Abdellatif2319@nu.edu.eg", 010200, "82nd Pickle Jar Street", "verysecurepassword@heilhit12345", student3EnrollmentHistory);
    Student *student4 = new Student(231000137, "Mazen", "Ahmed", "El-Mallah", "M.ElMallah2337@nu.edu.eg", 0102, "83rd Pickle Jar Street", "verysecurepassword@heilhit123456", student4EnrollmentHistory);

    // Doubly enrollment list implementation.
    Course *course1 = new Course(101, "Electric Circuits", 3.0, "Tamer Abu Elfadl");
    Course *course2 = new Course(211, "Discrete Mathematics", 3.0, "Tamer Abu Elfadl");
    Course *course3 = new Course(301, "Differential Equations", 3.0, "Tamer Abu Elfadl");

    student1->enrollmentHistory->addEnrollmentRecord(course1);
    student2->enrollmentHistory->addEnrollmentRecord(course2);
    student3->enrollmentHistory->addEnrollmentRecord(course3);

    studentDB.addStudentRecord(student1);
    studentDB.addStudentRecord(student2);
    studentDB.addStudentRecord(student3);
    studentDB.addStudentRecord(student4);
    studentDB.displayStudentDetails();

    cout << "Code working..." << endl;
    return 0;
}