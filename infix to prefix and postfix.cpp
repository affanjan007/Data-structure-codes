#include <iostream>
#include <stack>
#include <string>

using namespace std;

class Node {
public:
    char data;
    Node* next;
    Node(char d) {
        data = d;
        next = nullptr;
    }
};

class Stack {
public:
    int size;
    Node* head;
    Stack() {
        size = 0;
        head = nullptr;
    }

    void display() {
        Node* current = head;
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void push(char c) {
        size++;
        Node* temp = new Node(c);
        if (!head) {
            head = temp;
        }
        else {
            temp->next = head;
            head = temp;
        }
    }

    char pop() {
        if (!head) {
            cout << "Empty!" << endl;
            return '\0';
        }
        else {
            size--;
            char popped = head->data;
            Node* temp = head;
            head = head->next;
            delete temp;
            return popped;
        }
    }

    char peek() {
        if (!isEmpty()) {
            return head->data;
        }
        else {
            cout << "Empty!" << endl;
            return '\0';
        }
    }

    bool isEmpty() {
        return size == 0;
    }
};

int GetPrecedence(char op) {
    if (op == '-' || op == '+') {
        return 1;
    }
    else if (op == '*' || op == '/') {
        return 2;
    }
    else if (op == '^') {
        return 3;
    }
    else {
        return 0;
    }
}

string InfixToPrefix(const string& infix) {
    string prefix = "";
    Stack stack;

    for (int i = infix.length() - 1; i >= 0; --i) {
        char c = infix[i];

        if (isalnum(c)) {
            prefix = c + prefix;
        }
        else if (c == ')') {
            stack.push(c);
        }
        else if (c == '(') {
            while (!stack.isEmpty() && stack.peek() != ')') {
                prefix = stack.pop() + prefix;
            }
            stack.pop();
        }
        else {
            while (!stack.isEmpty() && GetPrecedence(stack.peek()) >= GetPrecedence(c)) {
                prefix = stack.pop() + prefix;
            }
            stack.push(c);
        }
    }
    while (!stack.isEmpty()) {
        prefix = stack.pop() + prefix;
    }
    return prefix;
}

string InfixToPostfix(const string& infix) {
    string postfix = "";
    Stack stack;

    for (char c : infix) {
        if (isalnum(c)) {
            postfix += c;
        }
        else if (c == '(') {
            stack.push(c);
        }
        else if (c == ')') {
            while (!stack.isEmpty() && stack.peek() != '(') {
                postfix += stack.pop();
            }
            stack.pop();
        }
        else {
            while (!stack.isEmpty() && GetPrecedence(stack.peek()) >= GetPrecedence(c)) {
                postfix += stack.pop();
            }
            stack.push(c);
        }
    }

    while (!stack.isEmpty()) {
        postfix += stack.pop();
    }
    return postfix;
}

int main() {
    string infixExpression;
    cout << "Enter an infix expression: ";
    getline(cin, infixExpression);

    string prefixExpression = InfixToPrefix(infixExpression);
    cout << "Prefix expression: " << prefixExpression << endl;

    string postfixExpression = InfixToPostfix(infixExpression);
    cout << "Postfix expression: " << postfixExpression << endl;

    return 0;
}
