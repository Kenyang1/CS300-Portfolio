//============================================================================
// Name        : Project2.cpp
// Author      : Kenyang Lual
// Version     : 1.0
// Copyright   : Copyright � 2023 SNHU COCE
// Description : Project 2 ABCU Advising Program
//============================================================================
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

// Represents a node within the binary search tree.
class CourseNode {
public:
    string courseId;  
    string courseName; 
    vector<string> prerequisites;  
    CourseNode* leftChild;  
    CourseNode* rightChild;  

    // Constructor initializes the node with course details and sets child pointers to nullptr.
    CourseNode(string id, string name, vector<string> prereqs) :
        courseId(id), 
        courseName(name), 
        prerequisites(prereqs), 
        leftChild(nullptr), 
        rightChild(nullptr) {
    }
};

// Manages the binary search tree of courses.
class CourseBST {
    CourseNode* root; 

public:
    // Constructor initializes the root as nullptr indicating an empty tree.
    CourseBST() : root(nullptr) {}

    // Inserts a new node into the BST. If the tree is empty, the new node becomes the root.
    void insert(string id, string name, vector<string> prereqs) {
        if (root == nullptr) {
            root = new CourseNode(id, name, prereqs);
        }
        else {
            recursiveInsert(root, id, name, prereqs);
        }
    }

    // Helper function to insert a node recursively into the BST.
    void recursiveInsert(CourseNode* node, string id, string name, vector<string> prereqs) {
        if (id < node->courseId) {
            if (node->leftChild == nullptr) {
                node->leftChild = new CourseNode(id, name, prereqs);
            }
            else {
                recursiveInsert(node->leftChild, id, name, prereqs);
            }
        }
        else {
            if (node->rightChild == nullptr) {
                node->rightChild = new CourseNode(id, name, prereqs);
            }
            else {
                recursiveInsert(node->rightChild, id, name, prereqs);
            }
        }
    }

    // Performs an in-order traversal of the BST to display courses in sorted order.
    void inOrderTraversal(CourseNode* node) {
        if (node != nullptr) {
            inOrderTraversal(node->leftChild);
            displayCourse(node);
            inOrderTraversal(node->rightChild);
        }
    }

    // Loads courses from a specified file into the BST.
    void loadCoursesFromFile(const string& fileName) {
        ifstream inFile(fileName);
        string line;

        if (!inFile.is_open()) {
            cout << "Could not open the file: " << fileName << endl;
            return;
        }

        while (getline(inFile, line)) {
            stringstream ss(line);
            string courseId, courseName, temp;
            vector<string> prerequisites;

            getline(ss, courseId, ',');
            getline(ss, courseName, ',');

            while (getline(ss, temp, ',')) {
                prerequisites.push_back(temp);
            }

            insert(courseId, courseName, prerequisites);
        }
        inFile.close();
    }

    // Searches for a course by its ID and returns the corresponding node.
    CourseNode* searchCourse(CourseNode* node, string id) {
        CourseNode* currentNode = node;

        while (currentNode != nullptr) {
            if (currentNode->courseId == id) {
                return currentNode;
            }
            else if (id < currentNode->courseId) {
                currentNode = currentNode->leftChild;
            }
            else {
                currentNode = currentNode->rightChild;
            }
        }
        return nullptr;
    }

    // Displays information about a specific course.
    void displayCourse(CourseNode* node) {
        if (node == nullptr) {
            cout << "Course not found." << endl;
            return;
        }
        cout << "Course ID: " << node->courseId
            << " Course Name: " << node->courseName
            << " Course Prerequisites: ";
        if (node->prerequisites.empty()) {
            cout << "None" << endl;
        }
        else {
            for (const string& prereq : node->prerequisites) {
                cout << prereq << ", ";
            }
            cout << endl;
        }
    }

    // Displays a menu to the user and handles user input to navigate different actions.
    void displayMenu() {
        bool fileLoaded = false;
        string userIdInput;

        while (true) {
            cout << "1. Load Course Data" << endl;
            cout << "2. Print Course List" << endl;
            cout << "3. Print Course Details" << endl;
            cout << "9. Exit" << endl;

            int userChoice;
            cout << "Enter your choice: ";
            cin >> userChoice;

            switch (userChoice) {
            case 1:
            {
                cin.ignore();
                string fileName;
                cout << "Enter the course data file name: ";
                getline(cin, fileName);
                loadCoursesFromFile(fileName);
                fileLoaded = true;
                cout << "File Successfully Loaded" << endl;
                break;
            }
            case 2:
                if (!fileLoaded) {
                    cout << "Please load the course data first." << endl;
                }
                else {
                    inOrderTraversal(root);
                }
                break;
            case 3:
                if (!fileLoaded) {
                    cout << "Please load the course data first." << endl;
                }
                else {
                    cout << "Enter Course ID: ";
                    cin >> userIdInput;
                    CourseNode* course = searchCourse(root, userIdInput);
                    displayCourse(course);
                }
                break;
            case 9:
                cout << "Exiting Program." << endl;
                return;
            default:
                cout << "Invalid option. Please try again." << endl;
                break;
            }
        }
    }
};

int main() {

    CourseBST bst;  // Creating an instance of CourseBST
    bst.displayMenu();  // Initiating the menu for user interaction

    return 0;
}
