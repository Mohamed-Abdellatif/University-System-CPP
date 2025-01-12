#include <iostream>
#include <string>
#include <windows.h>

//----------------ZEYAD Part--------------------------------------------------------
// 1. Student Records Management: Use a Single Linked List (SLL) to store and manage
// student details.
// 2. Course Records Management: Implement a Binary Search Tree (BST) to organize
// and search course information.
//---------------------------------------Omar Part----------------------------------
// 3.Course Enrollment History: Employ a Double Linked List (DLL) to track each
// student's course history.
// 4. Course Prerequisites: Use a Stack to validate prerequisites for course registration.
//---------------------------------------Mazen Part---------------------------------
// 5. Course Waitlists: Manage waitlists with a Queue.
// 6. Search Optimization: Implement Linear and Binary Search algorithms.

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

class singly_student_node // Node for Singly Linked List of Student Records
{
public:
    Student *student;
    singly_student_node *next;

    singly_student_node(Student *s) : student(s), next(NULL) {}
};

class Binary_tree_course_node // Node for binary tree of course records
{
public:
    Course *course;
    Binary_tree_course_node *left;
    Binary_tree_course_node *right;

    Binary_tree_course_node(Course *c) : course(c), left(NULL), right(NULL) {}
};

class doubly_student_node // Node for Doubly Linked List of Course Enrollment History
{
public:
    Student *student;
    doubly_student_node *next;
    doubly_student_node *prev;

    doubly_student_node(Student *s) : student(s), next(NULL), prev(NULL) {}
};

class Singly_StudentDatabase // Singly Linked List for Student Records
{
public:
    singly_student_node *head;
    Singly_StudentDatabase() : head(NULL) {}

    void add(Student *s)
    {
        singly_student_node *newNode = new singly_student_node(s);
        if (!head)
        {
            head = newNode;
        }
        else
        {
            singly_student_node *temp = head;
            while (temp->next)
            {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    void del(long long id)
    {
        singly_student_node *temp = head;
        singly_student_node *prev = NULL;
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

    void display()
    {
        singly_student_node *temp = head;
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

class Binary_Tree_CourseDatabase // Binary Tree for Course Database
{
public:
    Binary_tree_course_node *root;
    Binary_Tree_CourseDatabase() : root(NULL) {}

    void addCourse(Course *c)
    {
        if (!root)
        {
            root = new Binary_tree_course_node(c);
            return;
        }
        Binary_tree_course_node *temp = root;
        while (true)
        {
            if (c->CourseId < temp->course->CourseId)
            {
                if (!temp->left)
                {
                    temp->left = new Binary_tree_course_node(c);
                    return;
                }
                temp = temp->left;
            }
            else if (c->CourseId > temp->course->CourseId)
            {
                if (!temp->right)
                {
                    temp->right = new Binary_tree_course_node(c);
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

        Binary_tree_course_node *node = root;
        Binary_tree_course_node *parent = NULL;

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
                    Binary_tree_course_node *child = node->left ? node->left : node->right;
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
                    Binary_tree_course_node *successor = node->right;
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