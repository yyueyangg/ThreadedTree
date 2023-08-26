# include <iostream>

using namespace std;

# ifndef THREADED_TREE
# define THREADED_TREE

template<class T>
class ThreadedNode
{
    public:
    ThreadedNode()
    {
        left = right = 0;
    }
    ThreadedNode(const T& e, ThreadedNode *l = 0, ThreadedNode *r = 0)
    {
        el = e;
        left = l;
        right = r;
        successor = 0;
    }

    T el;
    ThreadedNode *left, *right;
    unsigned int successor : 1;
};

template<class T>
class ThreadedTree
{
    public:
    ThreadedTree()
    {
        root = 0;
    }

    void insert(const T& el)
    {
        ThreadedNode<T> *p, *prev = 0, *newNode; 
        newNode = new ThreadedNode<T>(el);
        if (root == 0) 
        { 
            root = newNode;
            return; 
        }
        p = root;
        while (p != 0) 
        {
            prev = p;
            if (p->el > el)
            // tree is empty;
            // find a place to insert newNode;
                p = p->left;
            else if (p->successor == 0) // go to the right node only if it
                p = p->right; // is a descendant, not a successor; 
            else break; // don’t follow successor link;
        }
        if (prev->el > el) 
        { // if newNode is left child of
            prev->left = newNode; // its parent, the parent 
            newNode->successor = 1; // also becomes its successor; 
            newNode->right = prev;
        }
        else if (prev->successor == 1) 
        {// if the parent of newNode
            newNode->successor = 1; // is not the rightmost node, 
            prev->successor = 0; // make parent’s successor 
            newNode->right = prev->right; // newNode’s successor, 
            prev->right = newNode;
        }
        else prev->right = newNode; // otherwise it has no successor; 
    }

    void inorder()
    {
        ThreadedNode<T> *prev, *p = root;
        // process only non empty trees 
        if (p!=0)
        {
            // go to the left most node 
            while (p->left != 0)
            {
                p = p->left;
            }
            while (p!=0)
            {
                visit(p);
                prev = p;
                // go to the right node and only if its a 
                // descendant go to the left most node 
                // otherwise visit the successor 
                p = p->right;
                if (p!=0 && prev->successor == 0)
                {
                    while (p->left != 0)
                    {
                        p = p->left;
                    }
                }
            }
        }
    }


    protected:
    ThreadedNode<T> *root;
    virtual void visit(ThreadedNode<T>* p)
    {
        cout << p->el << ' ';
    }
};

# endif

int main()
{
    ThreadedTree<int> tree;
    tree.insert(20);
    tree.insert(15);
    tree.insert(25);
    tree.insert(10);
    tree.insert(17);
    tree.inorder();

}