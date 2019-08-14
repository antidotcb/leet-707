#include <cassert>
#include <iostream>
#include <sstream>
#include <vector>

#include "MyLinkedList.hpp"

std::string
print(MyLinkedList* obj) {
    std::stringstream ss;
    ss << "{";
    auto* elem = obj->getHead();
    auto count = 0;
    while (elem) {
        ss << elem->val << ",";
        elem = elem->next;
        count++;
    }
    ss << "} " << count << "=" << obj->size();

    return ss.str();
}

int
main() {
    auto* obj = new MyLinkedList();

    std::vector<std::string> commands = {"MyLinkedList",
                                         "addAtHead",
                                         "addAtHead",
                                         "addAtHead",
                                         "addAtIndex",
                                         "deleteAtIndex",
                                         "addAtHead",
                                         "addAtTail",
                                         "get",
                                         "addAtHead",
                                         "addAtIndex",
                                         "addAtHead"};
    std::vector<std::vector<int>> args
        = {{}, {7}, {2}, {1}, {3, 0}, {2}, {6}, {4}, {4}, {4}, {5, 0}, {6}};


    obj->addAtHead(1);
    std::cout << print(obj) << std::endl;
    obj->addAtTail(3);
    std::cout << print(obj) << std::endl;
    obj->addAtIndex(1, 2);
    std::cout << print(obj) << std::endl;
    std::cout << obj->get(1) << std::endl;
    std::cout << print(obj) << std::endl;
    obj->deleteAtIndex(1);
    std::cout << print(obj) << std::endl;
    std::cout << obj->get(1) << std::endl;
    std::cout << print(obj) << std::endl;

    delete obj;
    return 0;
}
