#include <iostream>

class Node
{

public:
    int val=0;
    Node* left=nullptr;
    Node* right=nullptr;
    int height = 1;

    Node(int val)
    {
        this->val = val;
    }

};


class AVL
{
    Node* root=nullptr;
    
    static int max(int a, int b)
    {
        return a<b?b:a;
    }

    static int height(Node* node)
    {
        if (!node) return 0;
        else return node->height;
    }

    static Node* rotateRight(Node* node)
    {
        Node* np = node->left;
        node->left = np->right;
        np->right = node;

        // Heights
        node->height = max(height(node->left), height(node->right)) + 1;
        np->height = max(height(np->left), height(np->right)) + 1;

        // if parent pointer is not saved in the node, new root (parent) need to be returned for information passing
        return np; 
    }

    static Node* rotateLeft(Node* node)
    {
        Node* np = node->right;
        node->right = np->left;
        np->left = node;

        // Heights
        node->height = max(height(node->left), height(node->right)) + 1;
        np->height = max(height(np->left), height(np->right)) + 1;

        return np;
    }


    static int heightDiff(Node* node)
    {
        if (!node) return 0;
        return height(node->left) - height(node->right);
    }

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
        
        // AVL stuff
        // Update heights
        node->height = max(height(node->left), height(node->right)) + 1;

        // Check balancing
        int diff = heightDiff(node);    //left - right
        if (diff < -1) // skew to right, rotate left
        {
            if (n > node->right->val) //Right Right
            {
                return rotateLeft(node);
            }
            else    // Right Left
            {
                node->right = rotateRight(node->right);
                return rotateLeft(node);
            }
        }
        else if (diff > 1)  //skew to left, rotate right
        {
            if (n < node->left->val)    // Left Left
            {
                return rotateRight(node);
            }
            else    //Left Right
            {
                node->left = rotateLeft(node->left);
                return rotateRight(node);
            }
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

        // AVL stuff
        
        // Again start from adjusting heights
        node->height = max(height(node->left), height(node->right)) + 1;
        
        // Check balancing
        int diff = heightDiff(node);

        if (diff < -1) // skew to right, rotate left
        {
            if (heightDiff(node->right) <= 0) //Right Right
            {
                return rotateLeft(node);
            }
            else    // Right Left
            {
                node->right = rotateRight(node->right);
                return rotateLeft(node);
            }
        }
        else if (diff > 1)  //skew to left, rotate right
        {
            if (heightDiff(node->left) >= 0)    // Left Left
            {
                return rotateRight(node);
            }
            else    //Left Right
            {
                node->left = rotateLeft(node->left);
                return rotateRight(node);
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
        root = insert(root, n);
    }

    void remove(int n)
    {
        root = remove(root, n);
    }

    void inOrder()
    {
        inOrder(root);
        std::cout << std::endl;
    }

    void printDiff()
    {
        std::cout << heightDiff(root) << std::endl;
    }

};


int main()
{
    auto tree = AVL();

    tree.insert(1);
    tree.insert(10);
    tree.insert(5);
    tree.insert(3);
    tree.insert(12);
    tree.insert(7);
    tree.insert(9);
    std::cout << "Before remove: " << std::endl;
    tree.inOrder();
    std::cout << "Height Difference: " << std::endl;
    tree.printDiff();
    
    
    
    tree.remove(10);
    tree.remove(12);
    std::cout << "After remove: " << std::endl;
    tree.inOrder();
    std::cout << "Height Difference: " << std::endl;
    tree.printDiff();
}