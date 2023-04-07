// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

int GetPrior(char a) {
    switch (a) {
        case '(':
            return 0;
        case ')':
            return 1;
        case '+':
            return 2;
        case '-':
            return 2;
        case '*':
            return 3;
        case '/':
            return 3;
    }
    return -1;
}

std::string infx2pstfx(std::string inf) {
    TStack<char, 100> stack1;
    std::string postf;
    for (int i = 0; i < inf.length(); i++) {
        if (inf[i] >= '0' && inf[i] <= '9') {
            postf += inf[i];
            postf += ' ';
        }
        else if (inf[i] == '(' || GetPrior(inf[i]) > GetPrior(stack1.get()) ||stack1.isEmpty()) {
            stack1.push(inf[i]);
        }
        else if ((GetPrior(inf[i]) <= GetPrior(stack1.get())) &&(GetPrior(inf[i]) != 1)) {
            while (GetPrior(inf[i]) <= GetPrior(stack1.get())) {
                postf += stack1.get();
                postf += ' ';
                stack1.pop();
            }
            stack1.push(inf[i]);
        }
        else if (inf[i] == ')') {
            while (stack1.get() != '(') {
                postf += stack1.get();
                postf += ' ';
                stack1.pop();
            }
            stack1.pop();
        }
        if (i == (inf.length() - 1)) {
            while (stack1.isEmpty() != true) {
                postf += stack1.get();
                postf += ' ';
                stack1.pop();
            }
        }
    }
    return postf;
}

int prived(char cur) { return cur - '0'; }

int eval(std::string post) {
    TStack<int, 100> stack2;
    int summ = 0;
    for (int i = 0; i < post.length(); i++) {
        if (post[i] == ' ') {
            continue;
        }
        if (post[i] >= '0' && post[i] <= '9') {
            stack2.push(prived(post[i]));
        }
        if (post[i] == '+') {
            int cur1 = stack2.get();
            stack2.pop();
            int cur2 = stack2.get();
            summ = (cur2 + cur1);
            stack2.pop();
            stack2.push(summ);
        }
        if (post[i] == '-') {
            int cur1 = stack2.get();
            stack2.pop();
            int cur2 = stack2.get();
            summ = (cur2 - cur1);
            stack2.pop();
            stack2.push(summ);
        }
        if (post[i] == '*') {
            int cur1 = stack2.get();
            stack2.pop();
            int cur2 = stack2.get();
            summ = (cur2 * cur1);
            stack2.pop();
            stack2.push(summ);
        }
        if (post[i] == '/') {
            int cur1 = stack2.get();
            stack2.pop();
            int cur2 = stack2.get();
            summ = (cur2 / cur1);
            stack2.pop();
            stack2.push(summ);
        }
    }
    return stack2.get();
}
