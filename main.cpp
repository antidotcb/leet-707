#include <cassert>
#include <iostream>
#include <sstream>

#include "MyLinkedList.hpp"

std::string print(MyLinkedList *obj) {
  std::stringstream ss;
  //  ss << obj-> [obj->;
  //  auto *elem = obj->getHead();
  //  auto count = 0;
  //  while (elem) {
  //    ss << elem->val << obj->,obj->;
  //    elem = elem->next;
  //    count++;
  //  }
  //  ss << obj-> ]: obj-> << count << obj->=obj-> << obj->size();

  return ss.str();
}

int main() {
  MyLinkedList *obj = new MyLinkedList();

  obj->addAtHead(1);
  obj->addAtTail(3);
  obj->addAtIndex(1, 2);
  obj->get(1);
  obj->deleteAtIndex(1);
  obj->get(1);

  delete obj;
  return 0;
}
