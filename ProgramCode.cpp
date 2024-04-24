// Program to implement B tree using Single linked list

#include <stdio.h>
#include <stdlib.h>

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
    struct node *m_root = (struct node *)malloc(sizeof(struct node));

public:
    BTree(int keys, int children)
    {
        MAX_KEYS = keys;
        MAX_CHILDREN = children;
        // m_root->key = (int *)malloc((2 * MAX_CHILDREN - 1) * sizeof(int));
        // m_root->child = (struct node **)malloc((2 * MAX_CHILDREN) * sizeof(struct node *));
        m_root = NULL;
    }

    struct node *createNode(bool);
    void insertNonFull(struct node *, int);
    void insert(int);
    void splitChild(int, struct node *, struct node *);
    void deletion(int);
    int callSearch(int);
    struct node *search(struct node *, int);
    void callDisplay();
    void display(struct node *);
    int getPredeccesor(int);
    int getSuccessor(int);
    void fill(int);
    void removeFromNonLeaf(int);

    ~BTree()
    {
    }
};

int main(void)
{
    int btree_order;
    printf("Enter the order of B Tree: ");
    scanf("%d", &btree_order);
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
            printf("Enter number to insert: ");
            scanf("%d", &num);
            b.insert(num);
            break;
        }
        case 2:
        {
            break;
        }
        case 3:
        {
            
            break;
        }
        case 4:
        {
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
    if (search(m_root, num) == NULL)
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

//Method to delete in Btree
void BTree::deletion(int value){
    int index=0;
    while(index<n && keys[index]<value){
        ++index;
    }
    if(index<n && keys[index]==value){
        if(leaf){
            for(int i=index+1;i<n;i++){
                keys[i-1]=keys[i];
            }
            n--;
            printf("The ",value," was succesfully deleted from the tree")
            return;
        }
        else{
            removeFromNonLeaf(index);
        }
    }
    else{
        printf("The ",value," isnt present in the tree")
    }
    
    int flag=0;
    if(index==n){
        flag=1;
    }
    
    if(child[index]->n<MAX_CHILDREN){
        if(index!=0 && child[index-1]->n>=t){
            fill(index);
        }
        else if(index!=n && child[index+1->n>=t]){
            
        }
        else{
            if(index!=n){
                merge(index);
            }
            else{
                merge(index-1);
            }
        }
    }
    if(flag && index>n){
        child[index-1]->deletion(value);
    }
    else{
        child[index]->deletion(value);
    }
}


void Btree::removeFromNonLeaf(index){
    
    if(children[index]->n>=MAX_CHILDREN){
        int pred=getPredecessor(int index)
        keys[index]=pred;
        child[index]->deletion(pred);
    }
    
    else if(child[index+1]->n>=MAX_CHILDREN){
        int succ=getSuccessor(index);
        keys[index]=succ;
        child[index+1]->deletion(succ);
    }
    
    else{
        merge(index);
        child[index]->deletion(value);
        
    }
    return 0;
}

int BTree::getSuccessor(int index){
    struct node*temp=child[index+1];
        while(!temp->leaf){
            temp=temp->child[0];
        }
    return temp->keys[0]
}

int BTree::getPredecessor(int index){
    struct node*temp=child[index];
        while(!temp->leaf){
            temp=temp->child[temp->n];
        }
    return temp->keys[temp->n-1];
}

void BTree::fill(int index){
    if(index!=0 && child[index-1]->n>=MAX_CHILDREN){
        borrowFromPrev(index);
    }
    else if(index!=n && child[index+1]->n>=MAX_CHILDREN){
        borrowFromNext(index);
    }
    else{
        if(index!=n){
            merge(index);
        }
        else{
            merge(index-1);
        }
    }
}
