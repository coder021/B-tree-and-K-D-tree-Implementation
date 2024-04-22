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
    node* m_root;

public:
    BTree(int keys, int children)
    {
        MAX_KEYS = keys;
        MAX_CHILDREN = children;
        m_root->key = (int *)malloc(MAX_KEYS * sizeof(int));
        m_root->child = (struct node **)malloc(MAX_CHILDREN * sizeof(struct node));
    }

    int insert();
    int del();
    int callSearch(int);
    struct node *search(struct node *, int);
    void callDisplay();
    void display(struct node*);

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
}

// Method to insert into a b tree

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
void BTree::display(struct node* temp)
{
    int i;
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
