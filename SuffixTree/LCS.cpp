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
        leafEnd = index;

        ++remainingSuffix; 

        lastNewNode = nullptr;

        while (remainingSuffix)
        {
            if (active.length == 0)
            {
                active.edge = (*text)[index];
            }

            if (active.node->children.find(active.edge) == active.node->children.end())
            {
                active.node->children[active.edge] = new Node(index, &leafEnd);

                if (lastNewNode)
                {
                    lastNewNode->suffixLink = active.node;
                    lastNewNode = nullptr;
                }
            }
            else
            {
                Node *next = active.node->children[active.edge];
                
                if (walkDown(next)) continue;

                if ((*text)[next->start + active.length] == (*text)[index])
                {
                    if (lastNewNode)
                    {
                        lastNewNode->suffixLink = active.node;
                        lastNewNode = nullptr;
                    }

                    ++active.length;
                    break;
                }

                int* splitEnd = new int(next->start + active.length - 1);   // Char right before
                Node *split = new Node(next->start, splitEnd);  // new node
                active.node->children[active.edge] = split; // replace next

                split->children[(*text)[index]] = new Node(index, &leafEnd);

                next->start += split->edgeLength();
                split->children[(*text)[*splitEnd + 1]] = next;


                if (lastNewNode) lastNewNode->suffixLink = split;

                lastNewNode = split;
            }
            
            // only rule 2 reach here, so one suffix has been explicitly added.
            --remainingSuffix;

            if (active.node == root && active.length > 0)
            {
                --active.length;
                active.edge = (*text)[index - remainingSuffix + 1];
            }
            else if (active.node != root)
            {
                active.node = active.node->suffixLink;
            }
        }
    }


    void setSuffixIndex(Node* node ,int height = 0) // set suffix index for leaf nodes using DFS
    {
        // Base case
        if (!node) return;

        bool isLeaf = true;

        for (const auto& it : node->children)
        {
            isLeaf = false;
            setSuffixIndex(it.second, height + node->edgeLength());
        }

        if (isLeaf)
        {
            node->suffixIndex = (*text).length() - height;
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

        if (node->suffixIndex == -1)
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


    void traverseMark(Node* node, int height, bool& previousIsX, bool& previousIsY, const int& splitIndex, 
                        int& maxHeight, int& startingIndex)
    {
        enum nodeType{
            X = -2,
            Y = -3,
            XY = -4
        };

        if (!node) return;

        bool isX = false;
        bool isY = false;

        if (node->suffixIndex < 0)  // internal node
        {
            for (auto& it : node->children)
            {
                traverseMark(it.second, height + node->edgeLength(), isX, isY, 
                            splitIndex, maxHeight, startingIndex);
            }
        }

        // Adjust flags accordingly
        if (node->suffixIndex >= 0)
        {
            printf("%d\n", node->suffixIndex);
            if (node->suffixIndex < splitIndex) 
                previousIsX = true;
            else if (node->suffixIndex > splitIndex)
                previousIsY = true;
        }
        else
        {
            if (isX) previousIsX = true;
            if (isY) previousIsY = true;

            // Change values
            if (isX && isY)
            {
                if (maxHeight < height)
                {
                    maxHeight = height;
                    startingIndex = *(node->end) - height - 1;
                }
            }
        }
        
    }

    void LCS()
    {
        bool isX = false;
        bool isY = false;
        int maxHeight = 0;
        int startIdx = -1;
        traverseMark(root, 0, isX, isY, 5, maxHeight, startIdx);
        return;
    }

    

};


int main()
{
    //std::string text = "dogcatxaxaaxbarrabbarbaraaaaaaf$";
    std::string text = "xabxa#babxba$";
    auto tree = SuffixTree(&text);

    tree.buildTree();

    tree.LCS();

    tree.deleteTree();

}