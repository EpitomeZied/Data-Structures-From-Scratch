#pragma once
#include <iostream>

class LinkedList {
private:
    struct Node {
        int value;
        Node* next;
        Node(int value) : value(value), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    int length;

public:
    LinkedList(int value) {
        Node* newNode = new Node(value);
        head = newNode;
        tail = newNode;
        length = 1;
    }

    ~LinkedList() {
        Node* temp = head;
        while (head) {
            head = head->next;
            delete temp;
            temp = head;
        }
    }

    LinkedList(const LinkedList& other) : head(nullptr), tail(nullptr), length(0) {
        Node* temp = other.head;
        while (temp) {
            append(temp->value);
            temp = temp->next;
        }
    }

    LinkedList& operator=(const LinkedList& other) {
        if (this == &other) return *this;
        Node* temp = head;
        while (head) {
            head = head->next;
            delete temp;
            temp = head;
        }
        tail = nullptr;
        length = 0;
        Node* src = other.head;
        while (src) {
            append(src->value);
            src = src->next;
        }
        return *this;
    }

    void printList() const {
        Node* temp = head;
        if (temp == nullptr) {
            std::cout << "empty";
        } else {
            while (temp != nullptr) {
                std::cout << temp->value;
                temp = temp->next;
                if (temp != nullptr) {
                    std::cout << " -> ";
                }
            }
        }
        std::cout << std::endl;
    }

    int getLength() const {
        return length;
    }

    void append(int value) {
        Node* newNode = new Node(value);
        if (length == 0) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        length++;
    }

    void deleteLast() {
        if (length == 0) return;
        Node* temp = head;
        if (length == 1) {
            head = nullptr;
            tail = nullptr;
        } else {
            Node* pre = head;
            while (temp->next) {
                pre = temp;
                temp = temp->next;
            }
            tail = pre;
            tail->next = nullptr;
        }
        delete temp;
        length--;
    }

    void prepend(int value) {
        Node* newNode = new Node(value);
        if (length == 0) {
            head = newNode;
            tail = newNode;
        } else {
            newNode->next = head;
            head = newNode;
        }
        length++;
    }

    void deleteFirst() {
        if (length == 0) return;
        Node* temp = head;
        if (length == 1) {
            head = nullptr;
            tail = nullptr;
        } else {
            head = head->next;
        }
        delete temp;
        length--;
    }

    Node* get(int index) const {
        if (index < 0 || index >= length) return nullptr;
        Node* temp = head;
        for (int i = 0; i < index; ++i) {
            temp = temp->next;
        }
        return temp;
    }

    bool set(int index, int value) {
        Node* temp = get(index);
        if (temp) {
            temp->value = value;
            return true;
        }
        return false;
    }

    bool insert(int index, int value) {
        if (index < 0 || index > length) return false;
        if (index == 0) {
            prepend(value);
            return true;
        }
        if (index == length) {
            append(value);
            return true;
        }
        Node* newNode = new Node(value);
        Node* temp = get(index - 1);
        newNode->next = temp->next;
        temp->next = newNode;
        length++;
        return true;
    }

    void deleteNode(int index) {
        if (index < 0 || index >= length) return;
        if (index == 0) return deleteFirst();
        if (index == length - 1) return deleteLast();

        Node* prev = get(index - 1);
        Node* temp = prev->next;
        prev->next = temp->next;
        delete temp;
        length--;
    }

    void reverse() {
        if (length <= 1) return;
        Node* temp = head;
        head = tail;
        tail = temp;
        Node* after = nullptr;
        Node* before = nullptr;
        for (int i = 0; i < length; ++i) {
            after = temp->next;
            temp->next = before;
            before = temp;
            temp = after;
        }
    }
};
