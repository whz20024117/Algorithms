#include "LinkedList.h"


int main()
{
    List<int> list;

    list.append(6);
    list.append(5);
    list.append(4);
    list.append(3);
    list.append(2);
    list.append(1);

    list.reverse();
    
    list.printList();

}