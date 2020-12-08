#include "LinkedList.h"
#include <vector>


ListNode<int>* findMid(List<int> list)
{
    ListNode<int>* slow = list.getRoot();
    ListNode<int>* fast = list.getRoot()->next;

    while(fast)
    {
        fast = fast->next;
        if(fast)
        {
            fast = fast->next;
            slow = slow->next;
        }
    }

    return slow;

}


int main()
{
    List<int> list;

    list.push(3);
    list.push(2);
    list.push(1);
    list.append(3);
    list.append(2);
    list.append(1);
    list.printList();



    // remove first item
    list.removeFirstOccurance(1);
    list.append(4);

    list.printList();

    // remove last item
    list.removeFirstOccurance(4);
    list.append(5);
    
    list.printList();

    // Find mid point
    list.append(6);
    list.printList();
    
    std::cout << "Mid point is: " << findMid(list) -> data << std::endl;

}