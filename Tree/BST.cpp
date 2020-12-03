#include <iostream>

class Node
{

public:
    int val=0;
    Node* left=nullptr;
    Node* right=nullptr;
    //int height = 0;

    Node(int val)
    {
        this->val = val;
    }

};

class BST
{
    Node* root;

    static Node* successor(Node* node)
    {
        if (node->left)
        {
            node = successor(node->left);
        }
        return node;
    }

    // Recursive insert
    static Node* insert(Node* node, int n)
    {
        if (!node)
        {
            return new Node(n);
        } 
        else
        {
            if (n < node->val) node->left = insert(node->left, n);
            else if (n > node->val) node->right = insert(node->right, n);
        }
        return node;
    }


    // Recursive Remove
    static Node* remove(Node* node, int n)
    {
        if (!node) return node;

        if (n < node->val)
        {
            node->left = remove(node->left, n);
        }
        else if (n > node->val)
        {
            node->right = remove(node->right, n);
        }
        else
        {
            // Node found
            if (node->left == nullptr && node->right == nullptr)
            {
                // Leaf node
                delete node;
                return nullptr;
            }
            else if (node->right == nullptr)
            {
                // Only left child
                Node* ret = node->left;
                delete node;
                return ret;
            }
            else if (node->left == nullptr)
            {
                // Only right child
                Node* ret = node->right;
                delete node;
                return ret;
            }
            else
            {
                // Both children present, need to find successor
                Node* u = successor(node->right);
                node->val = u->val;
                node->right = remove(node->right, node->val);
                return node;
            }
            
        }
        return node;

    }


    // Helper function to validate tree
    static void inOrder(Node* node)
    {
        if (!node) return;

        inOrder(node->left);
        std::cout << node->val << ", ";
        inOrder(node->right);
    }

public:
    void insert(int n)
    {
        if (!root)
        {
            root = new Node(n);
        }
        else
        {
            insert(root, n);
        }
    }

    void remove(int n)
    {
        remove(root, n);
    }

    void inOrder()
    {
        inOrder(root);
        std::cout << std::endl;
    }

};


int main()
{
    auto tree = BST();

    tree.insert(1);
    tree.insert(10);
    tree.insert(5);
    tree.insert(3);
    tree.insert(12);
    tree.insert(7);
    std::cout << "Before remove: " << std::endl;
    tree.inOrder();
    
    
    
    tree.remove(10);
    std::cout << "After remove: " << std::endl;
    tree.inOrder();
}