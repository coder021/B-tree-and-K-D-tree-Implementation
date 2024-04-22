// Program to implement B tree using Single linked list

#include <stdio.h>

class BTree
{
private:
    int MAX_KEYS;
    int MAX_CHILDREN;
    struct node
    {
        int n; // no. of keys in the node
        int key[MAX_KEYS]; // 
        node *child[MAX_CHILDREN];
        bool leaf;
    };

public:
    BTree(int keys, int children)
    {
        MAX_KEYS = keys;
        MAX_CHILDREN = children;
    }

    int insert();
    int del();
    int callSearch(int);
    struct node *search(struct node *, int);

    ~BTree()
    {

    }
};

int main(void)
{
    BTree b;
    int btree_order;
    printf("Enter the order of B Tree: ");
    scanf("%d", &btree_order);

}

// Method to insert into a b tree

// Method to delete in a b tree

// Method to call the search method
int BTree::callSearch(int num)
{
    if (search(root, num) == NULL)
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
}

// Method to display b tree
