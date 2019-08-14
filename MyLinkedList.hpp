class MyLinkedList {
 private:
    struct Element {
        int val = 0;
        Element* next = nullptr;
        Element* prev = nullptr;

        explicit Element(int i)
            : val{i} {}
    };

 public:
    [[nodiscard]] Element* getHead() const {
        return head;
    }

    [[nodiscard]] int size() const {
        return length;
    }

 public:
    /** Initialize your data structure here. */
    MyLinkedList() = default;

    ~MyLinkedList() {
        while (head) {
            auto* deleted = head;
            head = head->next;
            delete deleted;
        }
    }

    /** Get the value of the index-th node in the linked list. If the index is
     * invalid, return -1. */
    [[nodiscard]] int get(int index) const {
        if (auto element = getElementAt(index); element) {
            return element->val;
        }
        return -1;
    }

    /** Add a node of value val before the first element of the linked list. After
     * the insertion, the new node will be the first node of the linked list. */
    void addAtHead(int val) {
        auto* new_element = new Element(val);
        if (!head) {
            head = new_element;
            tail = new_element;
        } else {
            new_element->next = head;
            head = new_element;
        }
        ++length;
    }

    /** Append a node of value val to the last element of the linked list. */
    void addAtTail(int val) {
        auto* new_element = new Element(val);
        if (!tail) {
            head = new_element;
            tail = new_element;
        } else {
            new_element->prev = tail;
            tail->next = new_element;
            tail = new_element;
        }
        ++length;
    }

    /** Add a node of value val before the index-th node in the linked list. If
     * index equals to the length of linked list, the node will be appended to the
     * end of linked list. If index is greater than the length, the node will not
     * be inserted. */
    void addAtIndex(int index, int val) {
        if (index > length || index < 0) {
            return;
        } else if (index == length) {
            addAtTail(val);
            return;
        } else if (index == 0) {
            addAtHead(val);
            return;
        }

        Element* element = getElementAt(index);
        assert(element != nullptr);

        auto* new_element = new Element(val);

        new_element->prev = element->prev;
        new_element->next = element;

        if (element->prev) {
            element->prev->next = new_element;
        }

        element->prev = new_element;
        ++length;
    }

    /** Delete the index-th node in the linked list, if the index is valid. */
    void deleteAtIndex(int index) {
        if (!length || index < 0 || index >= length)
            return;
        Element* deleted = nullptr;
        if (index == 0) {
            deleted = head;
            assert(!deleted->prev);
            head = head->next;
            if (!length)
                tail = nullptr;
        } else if (index == length - 1) {
            deleted = tail;
            assert(!deleted->next);
            tail = tail->prev;
            if (!length)
                head = nullptr;
        } else {
            deleted = getElementAt(index);
        }
        assert(deleted);
        if (deleted->next) {
            deleted->next->prev = deleted->prev;
        }
        if (deleted->prev) {
            deleted->prev->next = deleted->next;
        }
        delete deleted;
        --length;
    }

 private:
    [[nodiscard]] Element* getElementAt(const int index) const {
        if (index < 0 || index > length) {
            return nullptr;
        } else if (index == length - 1) {
            return tail;
        } else if (index == 0) {
            return head;
        }

        const auto offset = index > ((length + 1) / 2) ? -1 : 1;
        Element* element = offset > 0 ? head : tail;
        int i = offset > 0 ? 0 : length - 1;
        while (element && i != index) {
            element = offset > 0 ? element->next : element->prev;
            i += offset;
        }

        return element;
    }

 private:
    Element* head = nullptr;
    Element* tail = nullptr;
    int length = 0;
};
