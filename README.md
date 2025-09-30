# Arbitrary Precision Calculator (bc-like Tool)

## 📖 Overview
This project is an **arbitrary-precision calculator** written in C, inspired by the classic Unix/Linux `bc` command.  
It supports **large numbers up to 10,000+ digits**, precise decimal arithmetic, negative numbers, and full **infix expression evaluation**.  

Unlike typical integer-based calculators, this tool implements **arbitrary precision arithmetic** using a custom `NUMBER` Abstract Data Type (ADT).  
Expressions are parsed using a **Finite State Machine (FSM)** and evaluated via a **stack-based algorithm**, similar to how compilers handle infix-to-postfix transformations.

---

## ✨ Features
- Supports **6 arithmetic operations**: Addition, Subtraction, Multiplication, Division, Exponentiation (with negative exponents), and Modulus.  
- **Arbitrary precision arithmetic** with custom doubly linked list storage (10,000+ digits).  
- **Decimal precision handling** up to user-defined scale.  
- **Sign flag** and **decimal flag** for correct signed decimal evaluation.  
- **Relational operators**: `==`, `<`, `>`, `<=`, `>=`, `!=`.  
- **Expression evaluation** using operator & operand stacks.  
- **Parentheses handling** and error detection (`divide by zero`, invalid input).  

---

## ⚙️  Data Structures Design  

### **NUMBER ADT**
Numbers are stored as **doubly linked lists**, where each node contains a digit.  
Each `NUMBER` object stores:  
- Doubly linked list of digits  
- Decimal point position  
- Sign flag  
- Decimal flag  

### **Stacks**
- **Operator Stack** → Stores operators during parsing.  
- **Operand Stack (ADT of Numbers)** → Stores NUMBER ADTs.  

### **Padding Function**
Ensures correct decimal alignment before arithmetic operations.  

### **Expression Evaluation**
1. **Parsing:** Implemented using a **Finite State Machine** (FSM) to tokenize input.  
2. **Conversion:** Expressions are validated and prepared using **stacks**.  
3. **Evaluation:** Operators popped & applied on NUMBER ADTs using linked list arithmetic.  

---

## 🖼️ Project Diagram  

![ADTs for Binary Calculator](ADTs.png)

---

## 📚 Technologies Used
- **C Programming Language**  
- **Makefile** for build automation  
- **Custom Data Structures** (Doubly Linked List, Stacks)  
- **Finite State Machine (FSM)** for parsing  
- Reference: **GNU bc** command (`man bc`)  

---

## 🚀 Installation
Clone the repository and build using `make`:
```bash
git clone https://github.com/username/arbitrary-precision-calculator.git
cd arbitrary-precision-calculator
make
./calc
```
