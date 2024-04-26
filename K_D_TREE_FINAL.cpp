#include <iostream> // For printf, scanf, and exit
#include <cstdio>
#include <cstdlib>

class KDTree {
private:
    struct Node {
        int* point; // To store k dimensional point
        Node* left, *right;
    };

    Node* newNode(int* arr, int k);
    Node* insertRec(Node* root, int* point, unsigned depth, int k);
    bool arePointsSame(int* point1, int* point2, int k);
    bool searchRec(Node* root, int* point, unsigned depth, int k);
    Node* minNode(Node* x, Node* y, Node* z, int d);
    Node* findMinRec(Node* root, int d, unsigned depth, int k);
    void copyPoint(int* p1, int* p2, int k);
    Node* deleteNodeRec(Node* root, int* point, int depth, int k);

public:
    KDTree();
    Node* root;
    void insert(int* point, int k);
    bool search(int* point, int k);
    bool deleteNode(int* point, int k);
    ~KDTree();
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
        break;
    }

    while (true) {
        printf("\nMenu:\n");
        printf("1. Insert a point\n");
        printf("2. Search for a point\n");
        printf("3. Delete a point\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: {
                printf("Enter the point to insert (each point should have %d coordinates):\n", k);
                int* point = new int[k];
                for (int i = 0; i < k; i++)
                    scanf("%d", &point[i]);
                tree.insert(point, k);
                printf("Point inserted successfully.\n");
                delete[] point;
                break;
            }
            case 2: {
                if (tree.root == NULL) {
                    printf("Tree is empty. Cannot perform search.\n");
                    break;
                }
                printf("Enter the point to search (each point should have %d coordinates):\n", k);
                int* point = new int[k];
                for (int i = 0; i < k; i++)
                    scanf("%d", &point[i]);
                if (tree.search(point, k))
                    printf("Point found.\n");
                else
                    printf("Point not found.\n");
                delete[] point;
                break;
            }
            case 3: {
                if (tree.root == NULL) {
                    printf("Tree is empty. Cannot perform deletion.\n");
                    break;
                }
                printf("Enter the point to delete (each point should have %d coordinates):\n", k);
                int* point = new int[k];
                for (int i = 0; i < k; i++)
                    scanf("%d", &point[i]);
                if (tree.deleteNode(point, k))
                    printf("Point deleted successfully.\n");
                else
                    printf("No deletion performed.\n");
                delete[] point;
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
    // Implement destructor
}

KDTree::Node* KDTree::newNode(int* arr, int k) {
    Node* temp = new Node;
    temp->point = new int[k];

    for (int i = 0; i < k; i++)
        temp->point[i] = arr[i];

    temp->left = temp->right = NULL;
    return temp;
}

void KDTree::insert(int* point, int k) {
    root = insertRec(root, point, 0, k);
}

KDTree::Node* KDTree::insertRec(Node* root, int* point, unsigned depth, int k) {
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
    for (int i = 0; i < k; ++i)
        if (point1[i] != point2[i])
            return false;

    return true;
}

bool KDTree::search(int* point, int k) {
    return searchRec(root, point, 0, k);
}

bool KDTree::searchRec(Node* root, int* point, unsigned depth, int k) {
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
    Node* res = x;
    if (y != NULL && y->point[d] < res->point[d])
        res = y;
    if (z != NULL && z->point[d] < res->point[d])
        res = z;
    return res;
}

KDTree::Node* KDTree::findMinRec(Node* root, int d, unsigned depth, int k) {
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
    for (int i = 0; i < k; i++)
        p1[i] = p2[i];
}
bool KDTree::deleteNode(int* point, int k) {
    if (!search(point, k)) {
        printf("Point not found.\n");
        return false;
    }
    root = deleteNodeRec(root, point, 0, k);
    return true;
}

KDTree::Node* KDTree::deleteNodeRec(Node* root, int* point, int depth, int k) {
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


