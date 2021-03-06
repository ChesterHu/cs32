#include <cassert>  // test functions
#include <iostream> // use cout to test
#include <stack>    // use stack data structure
#include <string>   // use std::string to present infix and postfix
using namespace std;

bool lessEqual(const char &lhs, const char &rhs);
// Return true if lhs <= rhs, return false otherwise.

bool postfixEval(const std::string &postfix, bool &result);
// Evaluate postfix boolean expression,
//   If postfix is valid, return true and store result,
//   otherwise return false, and don't modify the result.

int evaluate(std::string infix, std::string &postfix, bool &result);
// Evaluates a boolean express
//   If infix is a syntactically valid infix boolean expression,
//   then set postfix to the postfix form of that expression, set
//   result to the value of the expression, and return zero, If
//   in fix is not a syntactically valid expression, return 1; in
//   that case, postfix may or may not be changed, but result must
//   be unchanged.

// function implementation
/////////////////////////////////////////////////////////////////////////////
bool lessEqual(const char &lhs, const char &rhs) {
  if (rhs == '!' || (rhs == '&' && lhs != '!') || (rhs == '|' && lhs == '|'))
    return true;
  return false;
}

bool postfixEval(const std::string &postfix, bool &result) {
  stack<bool> operandStack; // initialize the operand stack

  for (int i = 0; i < postfix.size(); ++i) // for each character in the postfix
  {
    char ch = postfix[i];
    if (ch == 'T' || ch == 'F') // if the value is operand push in stack
    {
      operandStack.push(ch == 'T');
      continue;
    }

    bool operand1, operand2;
    switch (ch) {
    case '!':
      if (operandStack.empty()) // when operator is ! (not), return false if
        return false;           // stack is empty,
                                // push back operand result
      operand1 = operandStack.top();
      operandStack.pop();
      operandStack.push(!operand1);
      break;

    case '&':
    case '|':
      if (operandStack.size() < 2) // when operator is | (or), return false if
        return false;              // stack doesn't have enough operand.
                                   // push back operand result
      operand1 = operandStack.top();
      operandStack.pop();
      operand2 = operandStack.top();
      operandStack.pop();
      if (ch == '|')
        operandStack.push(operand1 || operand2);
      else
        operandStack.push(operand1 && operand2);
      break;

    default: // if char is neither operand nor operator
      return false;
    }
  }

  if (operandStack.size() == 1) {
    result = operandStack.top();
    return true;
  }
  return false;
}

int evaluate(std::string infix, std::string &postfix, bool &result) {
  std::string temp_postfix;  // initialize postfix to empty
  stack<char> operatorStack; // initialize operator stack

  for (int i = 0; i < infix.size(); ++i) // convert infix to postfix
  {
    char ch = infix[i];
    switch (ch) {
    case ' ':
      continue; // if it's a space, skip

    case 'T':
    case 'F':
      temp_postfix += ch;
      break;

    case '(':
      operatorStack.push(ch); // if it's a '(' push it on operator stack
      break;

    case ')':
      if (i == 0)
        return 1;
      for (int j = i - 1; j >= 0; j--) {
        if (infix[j] == '(')
          return 1;
        else if (infix[j] == ' ')
          continue;
        else
          break;
      }

      while (!operatorStack.empty() &&
             operatorStack.top() != '(') // pop stack until meet '('
      {
        temp_postfix += operatorStack.top();
        operatorStack.pop();
      }
      if (operatorStack.empty())
        return 1;
      operatorStack.pop(); // pop the '('
      break;

    case '&':
    case '|':
      if (i == 0)
        return 1;
      for (int j = i - 1; j >= 0; j--) // move to nearest non-blank char
      {
        if (infix[j] == 'F' || infix[j] == 'T' || infix[j] == ')') // valid
          break;
        if (infix[j] != ' ')
          return 1;
      }

    case '!':
      while (i + 1 < infix.size() && infix[i + 1] == ' ')
        ++i; // if it's ! or | or &, there should at one non-space char
      if (i == infix.size() - 1)
        return 1;
      while (!operatorStack.empty() && operatorStack.top() != '(' &&
             lessEqual(ch, operatorStack.top())) {
        temp_postfix += operatorStack.top();
        operatorStack.pop();
      }
      operatorStack.push(ch);
      break;

    default:
      return 1;
    }
  }
  while (!operatorStack.empty()) {
    temp_postfix += operatorStack.top();
    operatorStack.pop();
  }
  // cout << temp_postfix << endl;
  if (postfixEval(temp_postfix, result)) {
    postfix.swap(temp_postfix);
    return 0;
  }
  return 1;
}
