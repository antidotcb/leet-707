#include <cassert>
#include <functional>
#include <iostream>
#include <iterator>
#include <memory>
#include <sstream>
#include <unordered_map>
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


class Invoker {
 public:
    virtual ~Invoker() = default;
    virtual void Invoke(MyLinkedList* obj, const std::vector<int>& arguments) = 0;
};


template <typename T>
class BaseInvoker : public Invoker {
 public:
    explicit BaseInvoker(T method)
        : m_method{method} {}

 protected:
    void Invoke(MyLinkedList*, const std::vector<int>&) override {
        throw;
    }

    T m_method;
};

template <typename T>
struct SpecInvoker : public BaseInvoker<T> {
    void Invoke(MyLinkedList*, const std::vector<int>&) override {
        throw;
    }
};


using IntRIntAMethodSignature = int (MyLinkedList::*)(int) const;
template <>
struct SpecInvoker<IntRIntAMethodSignature> : public BaseInvoker<IntRIntAMethodSignature> {
    explicit SpecInvoker(IntRIntAMethodSignature method)
        : BaseInvoker<IntRIntAMethodSignature>{method} {}

    void Invoke(MyLinkedList* obj, const std::vector<int>& arguments) override {
        assert(arguments.size() == 1);
        (obj->*m_method)(arguments.front());
    }
};

using VoidRIntAMethodSignature = void (MyLinkedList::*)(int);
template <>
struct SpecInvoker<VoidRIntAMethodSignature> : public BaseInvoker<VoidRIntAMethodSignature> {
    explicit SpecInvoker(VoidRIntAMethodSignature method)
        : BaseInvoker<VoidRIntAMethodSignature>{method} {}

    void Invoke(MyLinkedList* obj, const std::vector<int>& arguments) override {
        assert(arguments.size() == 1);
        (obj->*m_method)(arguments.front());
    }
};

using VoidRIntIntAMethodSignature = void (MyLinkedList::*)(int, int);
template <>
struct SpecInvoker<VoidRIntIntAMethodSignature> : public BaseInvoker<VoidRIntIntAMethodSignature> {
    explicit SpecInvoker(VoidRIntIntAMethodSignature method)
        : BaseInvoker<VoidRIntIntAMethodSignature>{method} {}

    void Invoke(MyLinkedList* obj, const std::vector<int>& arguments) override {
        assert(arguments.size() == 2);
        (obj->*m_method)(arguments.front(), arguments.back());
    }
};

template <typename T>
std::pair<std::string, std::shared_ptr<Invoker>>
prepare(std::string&& str, T t) {
    return {std::move(str), std::make_shared<SpecInvoker<T>>(t)};
}

int
main() {
    MyLinkedList* obj = nullptr;

    const std::vector<std::string> commands
        = {"MyLinkedList", "addAtIndex", "get", "deleteAtIndex"};
    const std::vector<std::vector<int>> args = {{}, {-1, 0}, {0}, {-1}};

    const std::unordered_map<std::string, std::shared_ptr<Invoker>> lookup = {
        prepare("addAtHead", &MyLinkedList::addAtHead),
        prepare("addAtIndex", &MyLinkedList::addAtIndex),
        prepare("addAtTail", &MyLinkedList::addAtTail),
        prepare("deleteAtIndex", &MyLinkedList::deleteAtIndex),
        prepare("get", &MyLinkedList::get),
    };


    assert(args.size() == commands.size());
    for (int i = 0; i < std::min(args.size(), commands.size()); ++i) {
        const auto& cmd = commands[i];
        const auto& arg = args[i];
        std::cout << cmd << "(";
        std::copy(arg.begin(), arg.end(), std::ostream_iterator<int>(std::cout, ","));
        std::cout << ") = ";
        if (cmd == "MyLinkedList") {
            obj = new MyLinkedList();
        } else {
            const auto& invoker = lookup.at(cmd);
            invoker->Invoke(obj, arg);
        }
        std::cout << print(obj) << std::endl;
    }

    delete obj;
    return 0;
}
