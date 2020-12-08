#include <iostream>

template <class T>
class ListNode{
public:
    T data;
    ListNode* next = nullptr;

    explicit ListNode(T value)
    {
        data = value;
    }
};


template <class T>
class List{
    ListNode<T>* root;
    ListNode<T>* head;

    ListNode<T>* reverse(ListNode<T>* node);

public:
    List() : root(nullptr), head(nullptr)
    {}

    explicit List(ListNode<T>* node)
        : root(node) {}

    // ~List()
    // {
    //     while(root)
    //     {
    //         ListNode<T>* temp = root->next;
    //         delete root;
    //         root = temp;
    //     }
    // }

    void push(T value);
    void append(T value);
    void removeFirstOccurance(T value);

    void printList();
    void reverse();
    ListNode<T>* const getRoot();
};


// Definations of member functions

template <class T>
void List<T>::push(T value)
{
    if (!root) {
        root = new ListNode<T>(value);
        head = root;
    }
    else
    {
        ListNode<T>* newNode = new ListNode<T>(value);
        newNode->next = root;
        root = newNode;
    }
}

template <class T>
void List<T>::append(T value)
{
    if (!root)
    {
        root = new ListNode<T>(std::move(value));
        head = root;
    }
    else
    {
        ListNode<T>* newNode = new ListNode<T>(value);
        head->next = newNode;
        head = newNode;
    }
}

template <class T>
void List<T>::removeFirstOccurance(T value)
{
    if (!root)
    {
        return;
    }

    if (root->data == value)
    {
        ListNode<T>* temp = root->next;
        delete root;
        if (head == root)
            head = temp;
        root = temp;
        return;
    }

    ListNode<T>* node = root;
    while (node->next)
    {
        if (node->next->data != value)
        {
            node = node->next;
        }
        else
        {
            ListNode<T>* temp = node->next->next;
            delete node->next;
            if (head == node->next)
                head = node;
            node->next = temp;
            break;
        }
    }
}


template<class T>
void List<T>::printList()
{
    ListNode<T>* node = root;
    while(node)
    {
        std::cout << node->data << ", ";
        node = node->next;
    }

    std::cout << std::endl;
}


// Reverse

template<class T>
ListNode<T>* List<T>::reverse(ListNode<T>* node)
{
    // Base case 1 (root is null)
    if (!node)
        return nullptr;
    
    // Base case 2 (find last element)
    if (!node->next)
    {
        root = node;
        return node;
    }
    else
    {
        
        ListNode<T>* nextNode = reverse(node->next);    // This way we get the pointer of next node
        nextNode->next = node;  // reverse
        return node;    // Tell previous node my pointer so that next can be set.

    }
    
}


template<class T>
void List<T>::reverse()
{
    ListNode<T>* newHead = reverse(root);

    // Take care the new head
    newHead->next = nullptr;
    head = newHead;
    
}


template<class T>
ListNode<T>* const List<T>::getRoot()
{
    return root;
}