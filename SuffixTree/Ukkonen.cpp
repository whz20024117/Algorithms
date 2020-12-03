#include <iostream>
#include <unordered_map>
#include <string>

class Node
{
    Node& operator=(const Node&)
    {}
public:
    std::unordered_map<char, Node*> children;
    Node* suffixLink = nullptr; // for internal nodes

    // These are actually stored in child nodes.
    int start;
    int* end;

    int suffixIndex = -1;

    // Constructor
    Node(int _start, int* _end)
    : start(_start), end(_end)
    {}

    Node() = delete;

    // Helpers
    int edgeLength()
    {
        return *end - start + 1;
    }
};


class ActivePoint
{
public:
    char edge = 0;
    int length = 0;
    Node* node = nullptr;
};


// Suffix Tree classs
class SuffixTree
{
    Node* root = nullptr;
    Node* lastNewNode = nullptr;    // for suffix link reset
    std::string* text;

    ActivePoint active;

    int remainingSuffix = 0;
    int leafEnd = -1;   // "global" end for nodes

    bool walkDown(Node* nextNode)
    {
        if (active.length >= nextNode->edgeLength())
        {
            active.length -= nextNode->edgeLength();
            active.edge = (*text)[nextNode->start + nextNode->edgeLength()];
            active.node = nextNode;
            return true;
        }
        return false; // did not walk down
    }


    // Phase
    void nextPhase(int index)
    {
        // Rule 1: extend existing leafs
        leafEnd = index;
        
        // only add one more remaining, since: remain + i - (i - 1). i - 1 suffixes follows rule 1
        ++remainingSuffix; 

        lastNewNode = nullptr; //since new phase, no suffix link needs to be set

        // No update on activepoint for rule 1, since rule 1 has no traverse.

        /* 
        process until all remaining Suffix proceeded, or break by rule 3
        In principle, last phase should be terminal char so that all 
        suffix will have a new leaf added to aviod implicit tree.
        */
        while (remainingSuffix) // Avoiding using for since no need to have j
        {
            if (active.length == 0) //active length is 0: select edge to char we are searching
            {
                active.edge = (*text)[index];
            }

            // if edge is not exist in the node 
            /* 
            Rule 2 case 1: path ends at a non-leaf node. You know this is not leaf,
            because all leaf nodes have been updated by rule 1 so that leaf nodes
            will have the character match. Also traverse always starts from active point,
            which is a internal node.
            */
            if (active.node->children.find(active.edge) == active.node->children.end())
            {
                active.node->children[active.edge] = new Node(index, &leafEnd);

                // If any waiting new nodes from prvious extensions
                if (lastNewNode)
                {
                    lastNewNode->suffixLink = active.node;
                    lastNewNode = nullptr;
                }
            }
            else    // Edge on the node, there will be next node(s) connected
            {
                Node *next = active.node->children[active.edge];
                
                if (walkDown(next)) continue;   // active point changed, start over

                // if current char is on the edge, Rule 3: stop the phase
                if ((*text)[next->start + active.length] == (*text)[index])
                {
                    if (lastNewNode) // if any new node waiting for link
                    {
                        lastNewNode->suffixLink = active.node;
                        lastNewNode = nullptr;
                    }

                    // update active point for rule 3
                    ++active.length;
                    break;
                }

                // If did not break earlier, Rule 2 case 2: current char not on the edge

                // Need to create new internal node
                int* splitEnd = new int(next->start + active.length - 1);   // Char right before
                Node *split = new Node(next->start, splitEnd);  // new node
                active.node->children[active.edge] = split; // replace next

                // split (new node) will have a new child start with new char
                split->children[(*text)[index]] = new Node(index, &leafEnd);
                // split (new node) will also point to next, which is splitted
                next->start += split->edgeLength();
                split->children[(*text)[*splitEnd + 1]] = next;

                // Suffix link stuff for new node
                if (lastNewNode) lastNewNode->suffixLink = split;

                lastNewNode = split;
            }
            
            // only rule 2 reach here, so one suffix has been explicitly added.
            --remainingSuffix;

            // update active point for rule 2
            if (active.node == root && active.length > 0)
            {
                // Case 1, active node is root, then we change the edge to next remaining suffix
                // Don't forget to decrese the length by 1 (next suffix is shorter)
                --active.length;
                active.edge = (*text)[index - remainingSuffix + 1];
            }
            else if (active.node != root)
            {
                // Follow the suffixLink to find internal node with more branches
                active.node = active.node->suffixLink;
            }
        }
    }


    void setSuffixIndex(Node* node ,int height = 0) // set suffix index for leaf nodes using DFS
    {
        // Base case
        if (!node) return;

        bool isLeaf = true;

        // print suffix
        if (node->start >=0)
        {
            std::cout << (*text).substr(node->start, (*text).length()) << std::endl;
        }

        for (const auto& it : node->children)
        {
            isLeaf = false;
            setSuffixIndex(it.second, height + node->edgeLength());
        }

        if (isLeaf)
        {
            node->suffixIndex = (*text).length() - height;
            // std::cout << "Suffix: " << (*text).substr(node->start, *(node->end));
            // std::cout << ", Index:" << node->suffixIndex << std::endl;
        }
    }

    void recursiveFree(Node* node)
    {
        // Base case
        if (!node) return;

        for (const auto& it : node->children)
        {
            recursiveFree(it.second);
        }

        if (node->suffixIndex == -1)    // non-leaf
        {
            delete node->end;
        }

        delete node;
    }

public:
    
    explicit SuffixTree(std::string* t)
    {
        text = t;
    }

    void buildTree()
    {   
        if (root)
        {
            std::cout << "Tree already exists!" << std::endl;
            return;
        }

        int* rootEnd = new int(-1);

        root = new Node(-1, rootEnd);
        active.node = root;

        for (int i=0; i < (*text).length(); ++i)
        {
            nextPhase(i);
        }
        setSuffixIndex(root);
    }

    void deleteTree()
    {
        if (!root) return;
        recursiveFree(root);
    }

};


int main()
{
    //std::string text = "dogcatxaxaaxbarrabbarbaraaaaaaf$";
    std::string text = "xabxac";
    auto tree = SuffixTree(&text);

    tree.buildTree();

    tree.deleteTree();

}