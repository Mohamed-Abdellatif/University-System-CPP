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
// 4. Course Prerequisites: Use a Stack to valIDate prerequisites for course registration.
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

class Student // Student Class
{
    // TODO: Add the course enrollment history here and add the implementation to add a course every time the student takes a new course
public:
    long long ID, phoneNumber;
    string name, studentEmail, studentAddress, studentPassword;

    Student(long long uni_ID, string uni_name, string uni_student_email, long long uni_phone_number, string uni_student_address, string uni_student_password) : ID(uni_ID), name(uni_name), studentEmail(uni_student_email), phoneNumber(uni_phone_number), studentAddress(uni_student_address), studentPassword(uni_student_password) {}
};

class Course // Course Class
{
public:
    long long courseID;
    string courseName;
    long long courseCredits;
    string courseInstructor;

    Course(long long uni_course_ID, string uni_course_name, long long uni_course_credits, string uni_course_instructor) : courseID(uni_course_ID), courseName(uni_course_name), courseCredits(uni_course_credits), courseInstructor(uni_course_instructor) {}
};

class SinglyStudentNode // Node for Singly Linked List of Student Records
{
public:
    Student *student;
    SinglyStudentNode *next;

    SinglyStudentNode(Student *s) : student(s), next(NULL) {}
};

class BinaryTreeCourseNode // Node for binary tree of course records
{
public:
    Course *course;
    BinaryTreeCourseNode *left;
    BinaryTreeCourseNode *right;

    BinaryTreeCourseNode(Course *c) : course(c), left(NULL), right(NULL) {}
};

class DoublyStudentNode // Node for Doubly Linked List of Course Enrollment History
{
public:
    Student *student;
    DoublyStudentNode *next;
    DoublyStudentNode *prev;

    DoublyStudentNode(Student *s) : student(s), next(NULL), prev(NULL) {}
};

class SinglyStudentDatabase // Singly Linked List for Student Records
{
public:
    SinglyStudentNode *head;
    SinglyStudentDatabase() : head(NULL) {}

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

    void displayStudentDetails()
    {
        SinglyStudentNode *tempStudentNode = head;
        while (tempStudentNode)
        {
            cout << "Student ID: " << tempStudentNode->student->ID << endl;
            cout << "Student Name: " << tempStudentNode->student->name << endl;
            cout << "Student Email: " << tempStudentNode->student->studentEmail << endl;
            cout << "Student Phone Number: " << tempStudentNode->student->phoneNumber << endl;
            cout << "Student Address: " << tempStudentNode->student->studentAddress << endl;
            cout << "---------------------------------------------------------" << endl;
            tempStudentNode = tempStudentNode->next;
        }
    }
};

class BinaryTreeCourseDatabase // Binary Tree for Course Database
{
public:
    BinaryTreeCourseNode *root;
    BinaryTreeCourseDatabase() : root(NULL) {}

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
                if (!node->left && !node->right) // No children
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
                else if (!node->left || !node->right) // One child
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
                else // Two children
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

class DoublyEnrollmentHistory
{
public:
    DoublyStudentNode *head = NULL;

    void addEnrollmentRecord(Student *enrolledStudent)
    {
        DoublyStudentNode *newStudentNode = new DoublyStudentNode(enrolledStudent);

        if (!head)
        {
            head = newStudentNode;
            return;
        }

        DoublyStudentNode *tempStudentNode = head;

        while (tempStudentNode->next)
        {
            tempStudentNode = tempStudentNode->next;
        }

        tempStudentNode->next = newStudentNode;
        newStudentNode->prev = tempStudentNode;
    }
};

int main()
{
    //TODO: add your implementation here to check if the code is working and for the rest to see your progress

    return 0;
}