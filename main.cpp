#include <iostream>
#include <string>
#include <windows.h>
#include <stack>
#include <map>

using namespace std;

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

class PrerequisiteCourseStack;
class Student;
void startUniversityManagmentSystem();

class WaitlistQueueNode {
public:
    Student* student;  // Student in waitlist
    WaitlistQueueNode* next;  // Pointer to next node in queue
    WaitlistQueueNode(Student* student) : student(student), next(nullptr) {}
};

class WaitlistQueue {
public:
    WaitlistQueueNode* front;
    WaitlistQueueNode* rear;

    WaitlistQueue() : front(nullptr), rear(nullptr) {}

    // Enqueue a student to the waitlist
    void enqueue(Student* student) {
        WaitlistQueueNode* newNode = new WaitlistQueueNode(student);
        if (rear == nullptr) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
    }

    Student* dequeue() {
        if (front == nullptr) {
            return nullptr;  // Queue empty
        }
        WaitlistQueueNode* temp = front;
        Student* student = front->student;
        front = front->next;
        if (front == nullptr) {
            rear = nullptr;  // If queue becomes empty
        }
        delete temp;  // Cleanup
        return student;
    }
    
    bool isEmpty() {
        return front == nullptr;
    }
// Display all students in the waitlist
    void displayWaitlist() {
        if (isEmpty()) {
            cout << "Waitlist is empty!" << endl;
            return;
        }

        WaitlistQueueNode* temp = front;
        while (temp != nullptr) {
            cout << "Student ID: " << temp->student->ID << ", Name: " << temp->student->firstName << " " << temp->student->lastName << endl;
            temp = temp->next;
        }
    }
};
class Course // Course Class that stores Course information.
{
public:
    long long courseID;
    double courseCredits;
    int courseSeats=60;
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
            cout << "-------------------------------------------" << endl;
            cout << "Students Database:" << endl;
            cout << "Student ID: " << tempStudentNode->student->ID << endl;
            cout << "Student First Name: " << tempStudentNode->student->firstName << endl;
            cout << "Student Middle Name: " << tempStudentNode->student->middleName << endl;
            cout << "Student Last Name: " << tempStudentNode->student->lastName << endl;
            cout << "Student Email: " << tempStudentNode->student->studentEmail << endl;
            cout << "Student Phone Number: " << tempStudentNode->student->phoneNumber << endl;
            cout << "Student Address: " << tempStudentNode->student->studentAddress << endl;
            cout << "Student Enrollment History:" << endl;
            tempStudentNode->student->enrollmentHistory->displayEnrollmentHistory();
            cout << "-------------------------------------------" << endl;
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
    Student *getStudentByID(long long ID)
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
/**
     * @brief Sorts the students in ascending order by ID using Bubble Sort
     *
     * This function iterates through the singly linked list and swaps student objects (pointers)
     * instead of actual values, (swapping values in a linked list is inefficient).
     */
    void bubbleSortByID()
    {
        if (!head || !head->next)
        {
            return; // No need to sort empty or single-element list
        }
        bool swapped;
        SinglyStudentNode *current;
        SinglyStudentNode *lastSorted = nullptr;
        do
        {
            swapped = false;
            current = head;
            while (current->next != lastSorted)
            {
                if (current->student->ID > current->next->student->ID)
                {
                    // Swap student pointers
                    Student *temp = current->student;
                    current->student = current->next->student;
                    current->next->student = temp;
                    swapped = true;
                }
                current = current->next;
            }
            lastSorted = current; // Mark last sorted node
        } while (swapped);
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
    PrerequisiteCourseStack() : top(nullptr) {}

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
            size++;
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
        if (size == 0)
        {
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
            cout << "No Prerequisite Courses" << endl;
            return;
        };
        cout << "Course Prerequisites:" << endl;
        while (tempCourseNode)
        {

            cout << "                     Course: " << tempCourseNode->course->courseName << endl;
            tempCourseNode = tempCourseNode->next;
        }
    }
    bool isPrereqExistByID(long long courseID)

    {
        PrerequisiteCourseStackNode *tempCourseNode = top;
        if (size == 0)
        {
            return false;
        };

        while (tempCourseNode)
        {
            if (tempCourseNode->course->courseID == courseID)
            {
                return true;
            }
            tempCourseNode = tempCourseNode->next;
        }
        return false;
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
        Student *student = students->getStudentByID(studentID);
        PrerequisiteCourseStackNode *tempCourseNode = top;

        while (tempCourseNode && student && size != 0)
        {
            if (student->enrollmentHistory->checkCourseExistence(tempCourseNode->course) == false)
            {
                prereqCoursesToBeTaken.push(tempCourseNode);
            }
            tempCourseNode = tempCourseNode->next;
        };

        while (!prereqCoursesToBeTaken.empty())
        {
            if (!isPrereqExistByID(prereqCoursesToBeTaken.top()->course->courseID))
            {
                addToStack(prereqCoursesToBeTaken.top()->course);
            }
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
    int size = 0;

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
            size++;
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
                    size++;
                    return;
                }
                tempStudentNode = tempStudentNode->left;
            }
            else if (courseToBeAdded->courseID > tempStudentNode->course->courseID)
            {
                if (!tempStudentNode->right)
                {
                    tempStudentNode->right = new BinaryTreeCourseNode(courseToBeAdded);
                    size++;
                    return;
                }
                tempStudentNode = tempStudentNode->right;
            }
            else
            {
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
                size--;
                return;
            }
        }
        cout << "Course not found." << endl;
    }

    void displaytree(BinaryTreeCourseNode *node)
    {
        if (node == NULL)
        {
            return;
        }
        displaytree(node->left);
        cout << "-------------------------------------------" << endl;
        cout << "University Courses:" << endl;
        cout << "Course ID: " << node->course->courseID << endl;
        cout << "Course Name: " << node->course->courseName << endl;
        cout << "Course Credits: " << node->course->courseCredits << endl;
        cout << "Course Instructor: " << node->course->courseInstructor << endl;
        node->course->prereqStack->displayCoursePrerequisites();
        cout << "-------------------------------------------" << endl;
        displaytree(node->right);
    }
    Course *getCourseByName(BinaryTreeCourseNode *node, string courseName)
    {

        if (node == NULL)
        {
            return nullptr;
        }

        Course *leftResult = getCourseByName(node->left, courseName);
        if (leftResult != nullptr)
        {
            return leftResult;
        }

        // Check the current node
        if (node->course->courseName == courseName)
        {
            return node->course;
        }

        return getCourseByName(node->right, courseName);
    }

    Course *getCourseByID(BinaryTreeCourseNode *node, long long courseID)
    {
        if (node == NULL)
        {
            return nullptr;
        }
        if (node->course->courseID == courseID) 
        {
            return node->course;
        }
        else if (courseID < node->course->courseID) 
        {
            return getCourseByID(node->left, courseID); // Search in left subtree
        }
        else 
        {
            return getCourseByID(node->right, courseID); // Search in right subtree
        }
    }

    bool isCourseExistById(BinaryTreeCourseNode *node, long long courseID)
    {
        if (node == NULL)
        {
            return false;
        }
        if (node->course->courseID == courseID) 
        {
            return true;
        }
        else if (courseID < node->course->courseID) 
        {
            return isCourseExistById(node->left, courseID);
        }
        else 
        {
            return isCourseExistById(node->right, courseID);
        }
    }
};

class UniversityManagementSystem
{
    SinglyStudentDatabase studentsDB;
    BinaryTreeCourseDatabase coursesDB;
    map<string, PrerequisiteCourseStack *> variables;

public:
    void returnToMenu()
    {
        int choice;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "Return to Main Menu?" << endl;
        cout << "1. Yes" << endl;
        cout << "2. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        if (choice == 1)
        {
            startUniversityManagmentSystem();
        }
        return;
    }
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
        returnToMenu();
    };

    void displayStudentsFromDB()
    {
        if (studentsDB.size == 0)
        {
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << "There are no students in the database" << endl;
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            returnToMenu();
            return;
        }
        studentsDB.displayStudentDetails();
        returnToMenu();
    }

    void removeStudentFromDatabase()
    {
        if (studentsDB.size == 0)
        {
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << "There are no students in the database to remove" << endl;
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            returnToMenu();
            return;
        }
        long long studentID;
        cout << "Enter Student ID to Remove: ";
        cin >> studentID;
        studentsDB.removeStudentByID(studentID);
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "Student Removed Successfully!" << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        returnToMenu();
    }

    void askForPrerequisiteCourse(PrerequisiteCourseStack *prereqStack)
    {
        string courseName;
        int addAnotherCourseChoice = 0;
        cin.ignore();
        cout << "Enter Course Name: ";
        getline(cin, courseName);
        Course *course = coursesDB.getCourseByName(coursesDB.root, courseName);
        if (course != nullptr)
        {
            prereqStack->addToStack(course);
            cout << "Prerequisite Course Added Successfully!" << endl;
        }
        else
        {
            cout << "Course Not Found!" << endl;
        };
        cout << "Does this course have another prerequisite course? (Enter 1 for Yes , 0 for No):";
        cin >> addAnotherCourseChoice;
        if (addAnotherCourseChoice == 1)
        {
            askForPrerequisiteCourse(prereqStack);
        };
    }

    void addCourseToDatabase()
    {
        int addPrerequisiteChoice = 0;
        long long courseID;
        double courseCredits;
        string courseName;
        string courseInstructor;
        cout << "Enter Course ID: ";
        cin >> courseID;
        if (coursesDB.isCourseExistById(coursesDB.root, courseID))
        {
            cout << "Course ID already exists! Change the course Id" << endl;
            addCourseToDatabase();
            return;
        };
        cout << "Enter Course Name: ";
        cin.ignore();
        getline(cin, courseName);
        cout << "Enter Course Credits: ";
        cin >> courseCredits;
        cout << "Enter Course Instructor: ";
        cin.ignore();
        getline(cin, courseInstructor);
        variables[courseName] = new PrerequisiteCourseStack();
        coursesDB.addCourse(new Course(courseID, courseName, courseCredits, courseInstructor, variables[courseName]));
        cout << "Does this course have any prerequisite courses? (Enter 1 for Yes , 0 for No):";
        cin >> addPrerequisiteChoice;
        if (addPrerequisiteChoice == 1)
        {
            askForPrerequisiteCourse(variables[courseName]);
        }
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "Course Added Successfully!" << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        returnToMenu();
    }

    void displayCoursesFromDB()
    {
        if (coursesDB.size == 0)
        {
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << "There are no courses in the database" << endl;
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            returnToMenu();
            return;
        }
        coursesDB.displaytree(coursesDB.root);
        returnToMenu();
    }

    void removeCourseFromDatabase()
    {
        if (coursesDB.size == 0)
        {
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << "There are no courses in the database to remove" << endl;
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            returnToMenu();
            return;
        }
        long long courseID;
        cout << "Enter Course ID to Remove: ";
        cin >> courseID;
        coursesDB.dropCourse(courseID);
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "Course Removed Successfully!" << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        returnToMenu();
    }

    void addEnrollmentRecordToStudent()
    {
        long long studentID, courseID;
        int choice;
        cout << "Enter the student ID to add an enrollment record: ";
        cin >> studentID;
        cout << "Enter the course ID that the student will enroll in: ";
        cin >> courseID;
        Course *course = coursesDB.getCourseByID(coursesDB.root, courseID);
        Student *student = studentsDB.getStudentByID(studentID);
        if (!coursesDB.isCourseExistById(coursesDB.root, courseID) && student == NULL)
        {
            cout << "Course or Student does not exist! Enter 1 to re-enter or 0 to Exit: ";
            cin >> choice;
            if (choice == 0)
            {
                returnToMenu();
                return;
            }
            addEnrollmentRecordToStudent();
            return;
        };

        if (course->prereqStack->validateCoursePrerequisites(studentID, &studentsDB))
        {
            student->enrollmentHistory->addEnrollmentRecord(course);
            course->courseSeats=course->courseSeats-1;
            cout << "Enrollment record added successfully!" << endl;
        };
        returnToMenu();
    }

    void displayEnrollmentRecordsByStudent()
    {
        long long studentID;
        int choice;
        cout << "Enter the student ID to display their enrollment records: ";
        cin >> studentID;
        Student *student = studentsDB.getStudentByID(studentID);
        if (student != nullptr)
        {
            student->enrollmentHistory->displayEnrollmentHistory();
            return;
        }

        cout << "Student not found! To enter a valid student ID [1] or [0] to EXIT: ";
        cin >> choice;
        if (choice == 0)
        {
            returnToMenu();
            return;
        }
        displayEnrollmentRecordsByStudent();
        returnToMenu();
    }

    void checkIfPrereqsAreMet()
    {
        long long studentID, courseID;
        int choice;
        cout << "Enter the student ID: ";
        cin >> studentID;
        cout << "Enter the course ID: ";
        cin >> courseID;
        Course *course = coursesDB.getCourseByID(coursesDB.root, courseID);
        Student *student = studentsDB.getStudentByID(studentID);
        if (!coursesDB.isCourseExistById(coursesDB.root, courseID) && student == NULL)
        {
            cout << "Course or Student does not exist! Enter 1 to re-enter or 0 To Exit: ";
            cin >> choice;
            if (choice == 0)
            {
                returnToMenu();
                return;
            }
            addEnrollmentRecordToStudent();
            return;
        };

        if (course->prereqStack->validateCoursePrerequisites(studentID, &studentsDB))
        {
            cout << "Student can take this course" << endl;
        };
        returnToMenu();
    }
};

UniversityManagementSystem NU;

void startUniversityManagmentSystem()
{
    int choice;
    cout << "===================================================" << "\n";
    cout << "         University Management System Menu" << "\n";
    cout << "===================================================" << "\n";
    cout << " 1. Add Student" << "\n";
    cout << " 2. Remove Students by ID" << "\n";
    cout << " 3. Display All students" << "\n";
    cout << " 4. Add Course" << "\n";
    cout << " 5. Remove Course by ID" << "\n";
    cout << " 6. View All Courses" << "\n";
    cout << " 7. Enroll Student in Course" << "\n";
    cout << " 8. Display Student Enrollment History" << "\n";
    cout << " 9. Check If Student Finished Course Prerequisites" << "\n";
    cout << "10. Exit" << "\n";
    cout << "===================================================" << "\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
    {
        NU.addStudentToDatabase();
        break;
    }
    case 2:
    {
        NU.removeStudentFromDatabase();
        break;
    }
    case 3:
    {
        NU.displayStudentsFromDB();
        break;
    }
    case 4:
    {
        NU.addCourseToDatabase();
        break;
    }
    case 5:
    {
        NU.removeCourseFromDatabase();
        break;
    }
    case 6:
    {
        NU.displayCoursesFromDB();
        break;
    }
    case 7:
    {
        NU.addEnrollmentRecordToStudent();
        break;
    }
    case 8:
    {
        NU.displayEnrollmentRecordsByStudent();
        break;
    }
    case 9:
    {
        NU.checkIfPrereqsAreMet();
        break;
    }
    case 10:
    {
        cout << "Exiting the University Management System. Goodbye!" << endl;
        return;
        break;
    }
    default:
    {
        cout << "Invalid choice. Please enter a number between 1 and 10." << endl;
        break;
    }
    }
};

int main()
{
    startUniversityManagmentSystem();
    return 0;
}