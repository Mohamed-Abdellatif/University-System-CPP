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

class Student // Student Class
{
public:
    long long id;
    string name;
    string email;
    long long phone;
    string address;
    string password;

    Student(long long uni_id, string uni_name, string uni_email, long long uni_phone, string uni_address, string uni_password) : id(uni_id), name(uni_name), email(uni_email), phone(uni_phone), address(uni_address), password(uni_password) {}
};

class Course // Course Class
{
public:
    long long CourseId;
    string CourseName;
    long long CourseCredits;
    string CourseInstructor;

    Course(long long uni_course_id, string uni_course_name, long long uni_course_credits, string uni_course_instructor) : CourseId(uni_course_id), CourseName(uni_course_name), CourseCredits(uni_course_credits), CourseInstructor(uni_course_instructor) {}
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

    void addStudentRecord(Student *s)
    {
        SinglyStudentNode *newNode = new SinglyStudentNode(s);
        if (!head)
        {
            head = newNode;
        }
        else
        {
            SinglyStudentNode *temp = head;
            while (temp->next)
            {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    void removeStudentByID(long long id)
    {
        SinglyStudentNode *temp = head;
        SinglyStudentNode *prev = NULL;
        while (temp)
        {
            if (temp->student->id == id)
            {
                if (prev)
                    prev->next = temp->next;
                else
                    head = temp->next;
                delete temp;
                cout << "Student Deleted" << endl;
                return;
            }
            prev = temp;
            temp = temp->next;
        }
    }

    void displayStudentDetails()
    {
        SinglyStudentNode *temp = head;
        while (temp)
        {
            cout << "ID: " << temp->student->id << endl;
            cout << "Name: " << temp->student->name << endl;
            cout << "Email: " << temp->student->email << endl;
            cout << "Phone: " << temp->student->phone << endl;
            cout << "Address: " << temp->student->address << endl;
            cout << "---------------------------------------------------------" << endl;
            temp = temp->next;
        }
    }
};

class BinaryTreeCourseDatabase // Binary Tree for Course Database
{
public:
    BinaryTreeCourseNode *root;
    BinaryTreeCourseDatabase() : root(NULL) {}

    void addCourse(Course *c)
    {
        if (!root)
        {
            root = new BinaryTreeCourseNode(c);
            return;
        }
        BinaryTreeCourseNode *temp = root;
        while (true)
        {
            if (c->CourseId < temp->course->CourseId)
            {
                if (!temp->left)
                {
                    temp->left = new BinaryTreeCourseNode(c);
                    return;
                }
                temp = temp->left;
            }
            else if (c->CourseId > temp->course->CourseId)
            {
                if (!temp->right)
                {
                    temp->right = new BinaryTreeCourseNode(c);
                    return;
                }
                temp = temp->right;
            }
            else
            {
                cout << "This Course already exists" << endl;
                return;
            }
        }
    }

    void dropCourse(long long courseId)
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
            if (courseId < node->course->CourseId)
            {
                parent = node;
                node = node->left;
            }
            else if (courseId > node->course->CourseId)
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
                    while (node && node->course->CourseId != successor->course->CourseId)
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

    void addEnrollmentRecord(Student* enrolledStudent)
    {
        DoublyStudentNode *newNode = new DoublyStudentNode(enrolledStudent);

        if (!head)
        {
            head = newNode;           
            return;
        }

        DoublyStudentNode *temp = head;

        while (temp->next)
        {
            temp = temp->next;
        }

        temp->next = newNode;
        newNode->prev = temp;
    }

};

int main()
{
    // Display a simple program header
    cout << "===== C++ Program =====" << endl;
    int x = 10;
    int y = 5;
    int z = x + y;
    cout << z << endl;
    // TODO: Add your implementation here.

    return 0;
}