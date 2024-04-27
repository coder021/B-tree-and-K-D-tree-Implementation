#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

class BTree
{
private:
    int MAX_KEYS;
    int MAX_CHILDREN;
    struct node
    {
        int n;    // no. of keys in the node
        int *key; //
        struct node **child;
        bool leaf;
    };

public:
    BTree(int keys, int children)
    {
        MAX_KEYS = keys;
        MAX_CHILDREN = children;
        m_root = NULL;
    }

    struct node *createNode(bool);
    void insertNonFull(struct node *, int);
    void insert(int);
    void splitChild(int, struct node *, struct node *);
    void deletion(struct node*,int);
    int callSearch(int);
    struct node *search(struct node *, int);
    void callDisplay();
    void display(struct node *);
    int getPredecessor(struct node*,int);
    int getSuccessor(struct node*,int);
    void fill(struct node*,int);
    void removeFromNonLeaf(struct node*,int);
    void borrowFromPrev(struct node *,int);
    void borrowFromNext(struct node *,int);
    void merge(struct node *,int);
    struct node *m_root;
    ~BTree() {}
};

int main(void)
{
    int btree_order;
    printf("Enter the order of B Tree: ");
    if (scanf("%d", &btree_order) != 1)
    {
        printf("Error: Invalid input. Please enter an integer.\n");
        while (getchar() != '\n');
        return 0;
    }
    if(btree_order<=1)
    {
        printf("Order of b tree can't be lesser than 1 ");
        return 0;
    }
    BTree b(btree_order - 1, btree_order);
    int ch = 0, num;
    while (ch != 5)
    {
        printf("\nMenu:\n1. Insert\n2. Delete\n3. Search\n4. Display\n5. Exit\n\nEnter your choice: ");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
        {
             int num;
             printf("Enter number to insert: ");
             if (scanf("%d", &num) != 1)
             {
                 printf("Error: Invalid input. Please enter an integer.\n");
                 while (getchar() != '\n');
                 break;
             }
             b.insert(num);
             printf("Insertion Successful !");
             break;
        }
        case 2:
        {
            printf("Enter a number to delete : ");
            if (scanf("%d", &num) != 1)
            {
                 printf("Error: Invalid input. Please enter an integer.\n");
                 while (getchar() != '\n');
                 break;
            }
            b.deletion(b.m_root,num);
            break;
        }
        case 3:
        {
            printf("Enter a number to search : ");
            if (scanf("%d", &num) != 1)
            {
                 printf("Error: Invalid input. Please enter an integer.\n");
                 while (getchar() != '\n');
                 break;
            }
            int res = b.callSearch(num);
            if (res==1)
            {
                printf("%d found in B-tree",num);
            }
            else
            {
                printf("%d not found",num);
            }
            break;
        }
        case 4:
        {
            printf("Displaying the contents in B-tree \n");
            b.callDisplay();
            break;
        }
        case 5:
        {
            printf("Exiting... Thank you!\n");
            break;
        }
        default:
        {
            printf("Enter valid choice!\n");
        }
        }
    }
}

// Method to create a new node
BTree::node *BTree::createNode(bool isleaf)
{
    struct node *newnode = (struct node *)malloc(sizeof(struct node));
    newnode->key = (int *)malloc((2 * MAX_CHILDREN - 1) * sizeof(int));
    newnode->child = (struct node **)malloc((2 * MAX_CHILDREN) * sizeof(struct node *));
    newnode->n = 0;
    newnode->leaf = isleaf;
    return newnode;
}

// Method to insert a node into a non full b tree
void BTree::insertNonFull(struct node *node, int num)
{
    int i = node->n - 1;
    if (node->leaf == true)
    {
        while (i >= 0 && node->key[i] > num)
        {
            node->key[i + 1] = node->key[i];
            i--;
        }
        node->key[i + 1] = num;
        node->n = node->n + 1;
    }
    else
    {
        while (i >= 0 && node->key[i] > num)
        {
            i--;
        }
        if (node->child[i + 1]->n == 2 * MAX_CHILDREN - 1)
        {
            splitChild(i + 1, node->child[i + 1], node);
            if (node->key[i + 1] < num)
            {
                i++;
            }
        }
        insertNonFull(node->child[i + 1], num);
    }
}

// Method to split a node
void BTree::splitChild(int i, struct node *node, struct node *newnode)
{
    struct node *lastNode = createNode(node->leaf);
    lastNode->n = MAX_CHILDREN - 1;

    for (int j = 0; j < MAX_CHILDREN - 1; j++)
    {
        lastNode->key[j] = node->key[j + MAX_CHILDREN];
    }
    if (node->leaf == false)
    {
        for (int j = 0; j < MAX_CHILDREN; j++)
        {
            lastNode->child[j] = node->child[j + MAX_CHILDREN];
        }
    }
    node->n = MAX_CHILDREN - 1;

    for (int j = newnode->n; j >= i + 1; j--)
    {
        newnode->child[j + 1] = newnode->child[j];
    }
    newnode->child[i + 1] = lastNode;

    for (int j = node->n - 1; j >= i; j--)
    {
        newnode->key[j + 1] = newnode->key[j];
    }
    newnode->key[i] = node->key[MAX_CHILDREN - 1];
    newnode->n = newnode->n + 1;
}

// Method to insert a node into a b tree
void BTree::insert(int num)
{
    if (m_root == NULL)
    {
        struct node *newnode = createNode(true);
        newnode->key[0] = num;
        newnode->n = 1;
        m_root = newnode;
    }
    else
    {
        if (m_root->n == 2 * MAX_CHILDREN - 1)
        {
            struct node *newnode = createNode(false);
            newnode->child[0] = m_root;

            splitChild(0, m_root, newnode);

            int i = 0;
            if (newnode->key[0] < num)
            {
                i++;
            }
            insertNonFull(newnode->child[i], num);
            m_root = newnode;
        }
        else
        {
            insertNonFull(m_root, num);
        }
    }
}

// Method to delete in a b tree

// Method to call the search method
int BTree::callSearch(int num)
{
    if (search(m_root, num) != NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// Method to search in a b tree
BTree::node *BTree::search(struct node *temp, int num)
{
    int i = 0;
    while (i < temp->n && num > temp->key[i])
    {
        i++;
    }
    if (i < temp->n && num == temp->key[i])
    {
        return temp;
    }
    if (temp->leaf)
    {
        return NULL;
    }
    return search(temp->child[i], num);
}

// Method to call the display method
void BTree::callDisplay()
{
    display(m_root);
}

// Method to display b tree
void BTree::display(struct node *temp)
{
    int i;
    if (m_root == NULL)
    {
        printf("B Tree is empty!\n");
        return;
    }
    for (i = 0; i < temp->n; i++)
    {
        if (temp->leaf == false)
        {
            display(temp->child[i]);
        }
        printf("%d ", temp->key[i]);
    }
    if (temp->leaf == false)
    {
        display(temp->child[i]);
    }
}

void BTree::deletion(struct node* temp, int value)
{
    if(m_root==NULL)
    {
        printf("B-tree empty");
        return;
    }
    int index = 0;
    while (index < temp->n && temp->key[index] < value)
    {
        ++index;
    }
    if (index < temp->n && temp->key[index] == value)
    {
        if (temp->leaf)
        {
            for (int i = index + 1; i < temp->n; i++)
            {
                temp->key[i - 1] = temp->key[i];
            }
            temp->n--;
            printf("The %d was successfully deleted from the tree\n", value);
            return;
        }
        else
        {
            removeFromNonLeaf(temp, index);
        }
    }
    else
    {
        bool foundInChild = (index < temp->n) ? false : true;

        if (temp->child[index] != NULL)
            deletion(temp->child[index], value);

        if (!foundInChild)
        {
            if (temp->child[index + 1] != NULL)
                deletion(temp->child[index + 1], value);
        }
    }

    if (temp->child[index] != NULL && temp->child[index]->n < MAX_CHILDREN)
    {
        fill(temp, index);
    }
    else if (index == temp->n)
    {
        printf("The %d is not found in the Btree\n", value);
        return;
    }
}


void BTree::removeFromNonLeaf(struct node* temp, int index)
{
    if (temp->child[index]->n >= MAX_CHILDREN)
    {
        int pred = getPredecessor(temp, index);
        temp->key[index] = pred;
        deletion(temp->child[index], pred);
    }
    else if (temp->child[index + 1]->n >= MAX_CHILDREN)
    {
        int succ = getSuccessor(temp, index);
        temp->key[index] = succ;
        deletion(temp->child[index + 1], succ);
    }
    else
    {
        merge(temp, index);
        deletion(temp->child[index], temp->key[index]);
    }
}


int BTree::getSuccessor(struct node* temp, int index)
{
    struct node* current = temp->child[index + 1];
    while (!current->leaf)
    {
        current = current->child[0];
    }
    return current->key[0];
}

int BTree::getPredecessor(struct node* temp, int index)
{
    struct node* current = temp->child[index];
    while (!current->leaf)
    {
        current = current->child[current->n-1];
    }
    return current->key[current->n - 1];
}

void BTree::fill(struct node* temp, int index)
{
    if (index != 0 && temp->child[index - 1]->n >= MAX_CHILDREN)
    {
        borrowFromPrev(temp,index);
    }
    else if (index != temp->n && temp->child[index + 1]->n >= MAX_CHILDREN)
    {
        borrowFromNext(temp,index);
    }
    else
    {
        if (index != temp->n)
        {
            merge(temp,index);
        }
        else
        {
            merge(temp,index - 1);
        }
    }
}


void BTree::borrowFromPrev(struct node *current, int index)
{
    struct node *child = current->child[index];
    struct node *sibling = current->child[index - 1];

    // Move the last key from the sibling node to the current node
    for (int i = child->n - 1; i >= 0; --i)
        child->key[i + 1] = child->key[i];

    // If the child node is not a leaf, move the last child pointer from the sibling to the child
    if (!child->leaf)
    {
        for (int i = child->n; i >= 0; --i)
            child->child[i + 1] = child->child[i];
    }

    // Set the first key of the current node to the key from the parent node
    child->key[0] = current->key[index - 1];

    // If the child node is not a leaf, set its first child pointer to the last child of the sibling
    if (!child->leaf)
        child->child[0] = sibling->child[sibling->n];

    // Move the last key of the sibling to the parent node
    current->key[index - 1] = sibling->key[sibling->n - 1];

    // Adjust the number of keys in the child and the sibling nodes
    child->n += 1;
    sibling->n -= 1;

    // If the sibling node is not a leaf, recursively call borrowFromPrev on it
    if (!sibling->leaf)
        borrowFromPrev(sibling, sibling->n + 1);
}

void BTree::borrowFromNext(struct node *current, int index)
{
    struct node *child1 = current->child[index];
    struct node *sibling = current->child[index + 1];

    // keys[idx] is inserted as the last key in C[idx]
    child1->key[(child1->n)] = current->key[index];

    // Sibling's first child is inserted as the last child into C[idx]
    if (!(child1->leaf))
        child1->child[(child1->n) + 1] = sibling->child[0];

    // The first key from sibling is inserted into keys[idx]
    current->key[index] = sibling->key[0];

    // Moving all keys in sibling one step behind
    for (int i = 1; i < sibling->n; ++i)
        sibling->key[i - 1] = sibling->key[i];

    // Moving the child pointers one step behind
    if (!sibling->leaf)
    {
        for (int i = 1; i <= sibling->n; ++i)
            sibling->child[i - 1] = sibling->child[i];
    }

    // Increasing and decreasing the key count of C[idx] and C[idx+1] respectively
    child1->n += 1;
    sibling->n -= 1;
}

void BTree::merge(struct node *current, int idx)
{
    struct node *child1 = current->child[idx];
    struct node *child2 = current->child[idx + 1];

    // Pulling a key from the current node and inserting it into (t-1)th position of C[idx]
    child1->key[MAX_CHILDREN - 1] = current->key[idx];

    // Copying the keys from C[idx+1] to C[idx] at the end
    for (int i = 0; i < child2->n; ++i)
        child1->key[i + MAX_CHILDREN] = child2->key[i];

    // Copying the child pointers from C[idx+1] to C[idx]
    if (!child1->leaf)
    {
        for (int i = 0; i <= child2->n; ++i)
            child1->child[i + MAX_CHILDREN] = child2->child[i];
    }

    // Moving all keys after idx in the current node one step before
    for (int i = idx + 1; i < current->n; ++i)
        current->key[i - 1] = current->key[i];

    // Moving the child pointers after (idx+1) in the current node one step before
    for (int i = idx + 2; i <= current->n; ++i)
        current->child[i - 1] = current->child[i];

    // Updating the key count of child and the current node
    child1->n += child2->n + 1;
    current->n--;

    // Freeing the memory occupied by child2
    free(child2);
}
