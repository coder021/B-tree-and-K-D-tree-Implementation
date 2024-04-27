#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <sstream> // for stringstream
#include <string> // for string
#include <cctype>

class KDTree {
private:
    struct Node {
        int* point; // To store k dimensional point
        Node* left, *right;
    };

    // Private member functions
    Node* newNode(int* arr, int k); // Create a new node
    Node* insertRec(Node* root, int* point, unsigned depth, int k); // Recursive helper function for insertion
    bool arePointsSame(int* point1, int* point2, int k); // Check if two points are the same
    bool searchRec(Node* root, int* point, unsigned depth, int k); // Recursive helper function for search
    Node* minNode(Node* x, Node* y, Node* z, int d); // Find the node with the minimum value along a given dimension
    Node* findMinRec(Node* root, int d, unsigned depth, int k); // Recursive helper function to find the node with the minimum value along a given dimension
    void copyPoint(int* p1, int* p2, int k); // Copy the contents of one point to another
    Node* deleteNodeRec(Node* root, int* point, int depth, int k); // Recursive helper function for deletion

public:
    KDTree(); // Constructor
    Node* root; // Root node of the tree
    void insert(int* point, int k); // Insert a point into the tree
    bool search(int* point, int k); // Search for a point in the tree
    bool deleteNode(int* point, int k); // Delete a point from the tree
    ~KDTree(); // Destructor
};

int main() {
    KDTree tree;
    int k, choice;

    // Loop until valid input for k is provided
    while (true) {
        printf("Enter the value of k (number of dimensions): ");
        if (scanf("%d", &k) != 1 || getchar() != '\n') {
            printf("Invalid input. Please enter a single integer for k.\n");
            // Clear input buffer
            while (getchar() != '\n');
            continue;
        }
         if(k<1){
            printf("Invalid input. Please enter an integer greater than 0 for k.\n");

            continue;}

        break;
    }

    std::string line; // For storing the entire line of input
    std::istringstream iss; // Input string stream

    while (true) {
        printf("\nMenu:\n");
        printf("1. Insert a point\n");
        printf("2. Search for a point\n");
        printf("3. Delete a point\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");

        // Read the choice
        std::getline(std::cin, line); // Read the entire line
        iss.clear(); // Clear the stream state
        iss.str(line); // Set the input string stream to the line

        // Attempt to extract a single integer from the input
        if (!(iss >> choice) || !iss.eof()) {
            printf("Invalid choice. Please enter a single integer.\n");
            continue; // Restart the loop to get valid input
        }

        switch (choice) {
            case 1: {
            // Insertion operation
            while (true) {
                printf("Enter the point to insert (each point should have %d coordinates): ", k);
                std::getline(std::cin, line); // Read the entire line
                iss.clear(); // Clear the stream state
                iss.str(line); // Set the input string stream to the line
                int* point = new int[k];
                int count = 0; // Counter for the number of coordinates read
                bool invalidInput = false;
                for (int i = 0; i < k; i++) {
                    if (!(iss >> point[i])) {
                        invalidInput = true;
                        break; // Break out of the loop when invalid input is encountered
                    }
                    count++;
                }
                if (count != k || invalidInput || !iss.eof()) {
                    printf("Invalid input format.\n");
                    delete[] point; // Free memory
                    continue; // Stay in the loop for valid input
                }
                tree.insert(point, k);
                printf("Point inserted successfully.\n");
                delete[] point; // Free memory
                break; // Break out of the loop after successful insertion
            }
            break;
        }
            case 2: {
            // Search operation
            if (tree.root == nullptr) {
                printf("Tree is empty. Cannot perform search.\n");
                continue; // Stay in the loop for valid input
            }
            while (true) {
                printf("Enter the point to search (each point should have %d coordinates): ", k);
                std::getline(std::cin, line); // Read the entire line
                iss.clear(); // Clear the stream state
                iss.str(line); // Set the input string stream to the line
                int* point = new int[k];
                int count = 0; // Counter for the number of coordinates read
                bool invalidInput = false;
                for (int i = 0; i < k; i++) {
                    if (!(iss >> point[i])) {
                        invalidInput = true;
                        break; // Break out of the loop when invalid input is encountered
                    }
                    count++;
                }
                if (count != k || invalidInput || !iss.eof()) {
                    printf("Invalid input format.\n");
                    delete[] point; // Free memory
                    continue; // Stay in the loop for valid input
                }
                if (tree.search(point, k))
                    printf("Point found.\n");
                else
                    printf("Point not found.\n");
                delete[] point; // Free memory
                break; // Break out of the loop after search is performed
            }
            break;
            }
            case 3: {
                // Deletion operation
                if (tree.root == nullptr) {
                    printf("Tree is empty. Cannot perform deletion.\n");
                    continue; // Stay in the loop for valid input
                }
                while (true) {
                    printf("Enter the point to delete (each point should have %d coordinates): ", k);
                    std::getline(std::cin, line); // Read the entire line
                    iss.clear(); // Clear the stream state
                    iss.str(line); // Set the input string stream to the line
                    int* point = new int[k];
                    int count = 0; // Counter for the number of coordinates read
                    bool invalidInput = false;
                    for (int i = 0; i < k; i++) {
                        if (!(iss >> point[i])) {
                            invalidInput = true;
                            break; // Break out of the loop when invalid input is encountered
                        }
                        count++;
                    }
                    if (count != k || invalidInput || !iss.eof()) {
                        printf("Invalid input format.\n");
                        delete[] point; // Free memory
                        continue; // Stay in the loop for valid input
                    }
                    if (tree.deleteNode(point, k))
                        printf("Point deleted successfully.\n");
                    else
                        printf("No deletion performed.\n");
                    delete[] point; // Free memory
                    break; // Break out of the loop after deletion is performed
                }
                break;
            }
            case 4: {
                printf("Exiting...\n");
                exit(0);
            }
            default:
                printf("Invalid choice. Please enter a valid option.\n");

        }

    }

    return 0;
}

KDTree::KDTree() {
    root = NULL;
}

KDTree::~KDTree() {
    // Destructor implementation goes here
}

KDTree::Node* KDTree::newNode(int* arr, int k) {
    // Create a new node with the given coordinates
    Node* temp = new Node;
    temp->point = new int[k];

    for (int i = 0; i < k; i++)
        temp->point[i] = arr[i];

    temp->left = temp->right = NULL;
    return temp;
}

void KDTree::insert(int* point, int k) {
    // Insert a point into the tree
    root = insertRec(root, point, 0, k);
}

KDTree::Node* KDTree::insertRec(Node* root, int* point, unsigned depth, int k) {
    // Recursive helper function for insertion
    if (root == NULL)
        return newNode(point, k);

    unsigned cd = depth % k;

    if (point[cd] < (root->point[cd]))
        root->left = insertRec(root->left, point, depth + 1, k);
    else
        root->right = insertRec(root->right, point, depth + 1, k);

    return root;
}

bool KDTree::arePointsSame(int* point1, int* point2, int k) {
    // Check if two points are the same
    for (int i = 0; i < k; ++i)
        if (point1[i] != point2[i])
            return false;

    return true;
}

bool KDTree::search(int* point, int k) {
    // Search for a point in the tree
    return searchRec(root, point, 0, k);
}

bool KDTree::searchRec(Node* root, int* point, unsigned depth, int k) {
    // Recursive helper function for search
    if (root == NULL)
        return false;
    if (arePointsSame(root->point, point, k))
        return true;

    unsigned cd = depth % k;

    if (point[cd] < root->point[cd])
        return searchRec(root->left, point, depth + 1, k);

    return searchRec(root->right, point, depth + 1, k);
}

KDTree::Node* KDTree::minNode(Node* x, Node* y, Node* z, int d) {
    // Find the node with the minimum value along a given dimension
    Node* res = x;
    if (y != NULL && y->point[d] < res->point[d])
        res = y;
    if (z != NULL && z->point[d] < res->point[d])
        res = z;
    return res;
}

KDTree::Node* KDTree::findMinRec(Node* root, int d, unsigned depth, int k) {
    // Recursive helper function to find the node with the minimum value along a given dimension
    if (root == NULL)
        return NULL;

    unsigned cd = depth % k;

    if (cd == d) {
        if (root->left == NULL)
            return root;
        return findMinRec(root->left, d, depth + 1, k);
    }

    return minNode(root,
        findMinRec(root->left, d, depth + 1, k),
        findMinRec(root->right, d, depth + 1, k), d);
}

void KDTree::copyPoint(int* p1, int* p2, int k) {
    // Copy the contents of one point to another
    for (int i = 0; i < k; i++)
        p1[i] = p2[i];
}

bool KDTree::deleteNode(int* point, int k) {
    // Delete a point from the tree
    if (!search(point, k)) {
        printf("Point not found.\n");
        return false;
    }
    root = deleteNodeRec(root, point, 0, k);
    return true;
}

KDTree::Node* KDTree::deleteNodeRec(Node* root, int* point, int depth, int k) {
    // Recursive helper function for deletion
    if (root == NULL)
        return NULL;

    int cd = depth % k;

    if (arePointsSame(root->point, point, k)) {
        // If the node to be deleted has two children
        if (root->left != NULL && root->right != NULL) {
            // Delete the node as usual
            Node* min = findMinRec(root->right, cd, depth + 1, k);
            copyPoint(root->point, min->point, k);
            root->right = deleteNodeRec(root->right, min->point, depth + 1, k);
            delete min; // Delete the minimum node after copying its value
        }
        // If the node to be deleted has only one child
        else if (root->left != NULL || root->right != NULL) {
            // Delete the node as usual
            Node* child = (root->left != NULL) ? root->left : root->right;
            delete[] root->point;
            delete root;
            return child;
        }
        // If the node to be deleted is a leaf node
        else {
            delete[] root->point; // Delete the dynamically allocated point array
            delete root; // Delete the node
            return NULL;
        }
    }

    if (point[cd] < root->point[cd])
        root->left = deleteNodeRec(root->left, point, depth + 1, k);
    else
        root->right = deleteNodeRec(root->right, point, depth + 1, k);
    return root;
}
