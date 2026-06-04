# Smart ATM Simulator

A simple,console-based ATM machine simulation application built using C++.This project was created to demonstrate foundational coding principles,focusing heavily on Object-Oriented Programming (OOP) and persistent file-handling systems.

## 🚀 Key Features

**` PIN Security:`** Authenticates users via a 4-digit PIN and automatically blocks the session after 5 consecutive incorrect attempts.
**`Balance Inquiry:`** Fetches and displays the user's real-time account balance directly from a data file.
**`Cash Deposits:`** Allows users to add money to their account, instantly updating their total balance.
**`Cash Withdrawals:`** Validates user requests against their current balance to prevent overdrafts before dispensing cash.
**`Live History Log:`** Maintains a persistent ledger tracking the exact date and time of every transaction using the `<chrono>` library.

## 📁 Project Structure & Code Files

**`atm_simulator.cpp:`** The core source code containing the logic, classes, and menu operations for the application.
**`account.txt:`** Acts as a mock database storing sensitive customer data including Account Numbers, PINs, and current balances.
**`history.txt:`** A permanent record file where successful transactions are appended with real-time timestamps.
**`temp.txt:`** A temporary placeholder file utilized during deposits or withdrawals to securely update records without corrupting data.

## ⚙️ How to Setup and Run

# 1. Prerequisites
Make sure you have a C++ compiler installed on your system (like GCC/MinGW) or an Integrated Development Environment (IDE) such as VS Code, Code::Blocks, or Dev-C++.

# 2. Prepare the Database File
Before running the code, create a text file named account.txt in the exact same directory as your atm_simulator.cpp file. 

Add a header line and at least one sample user data account into account.txt using the format (AccountNumber<tab>PIN<tab>Balance). 
For example:
Acc    Password   Balance
1234   1122      5000.50

## Learning Objectives

This project helped me practice:
▫️ C++ Programming Basics
▫️ Functions
▫️ Loops and Conditions
▫️ File Handling
▫️ Problem Solving
▫️ Menu-Driven Programs

## Author
Tanmoy Sarker, First-Year CSE Student
