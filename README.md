# Smart Blood Bank Management System

A menu-driven blood bank management application developed in C programming to demonstrate donor management, donation history, blood inventory management, and hospital blood request processing using fundamental data structures.

# Project Overview

The Smart Blood Bank Management System is an academic C programming project designed to organize basic blood bank operations through a simple, menu-driven interface.

The project demonstrates how structures, arrays, and circular queues can be used to manage donor information, track donation records, maintain blood stock, and process blood requests.

#Key Features

- Donor Management: Store and manage donor details.
- Donation History: Maintain records of previous blood donations.
- Donation Frequency Checks: Help prevent donations from being recorded too frequently, according to the implemented eligibility rules.
- Blood Inventory: Track blood stock by blood group.
- Hospital Requests: Manage requests for blood from hospitals.
- Request Queue: Use a circular queue to organize pending requests.
- Stock Transactions: Record changes in blood inventory.
- Menu-Driven Interface: Access available operations through a text-based menu.

Note: Features should be enabled in the final code before they are described as fully implemented.

#Technologies Used

Technology| Purpose
C Programming| Application logic
Structures| Organizing donor and request records
Arrays| Storing records in memory
Circular Queue| Managing queued requests
GCC Compiler| Compiling the source code

# Getting Started

Prerequisites

- A C compiler such as GCC
- A terminal or command prompt
- Git (optional, for cloning the repository)

1. Clone the repository

git clone https://github.com/harishmanickavel21-max/Smart-Blood-Bank-Management-System.git

2. Open the project directory

cd Smart-Blood-Bank-Management-System

3. Compile the program

gcc smart_blood_bank_management_system.c -o blood_bank

4. Run the program

Linux / macOS / Linux-based terminals:

./blood_bank

Windows Command Prompt:

blood_bank.exe

If compilation fails, check the source filename and the compiler error messages.

🧠 Concepts Demonstrated

- Structures and user-defined data types
- Arrays and record management
- Menu-driven programming
- Conditional statements and loops
- Queue operations and circular queue logic
- Inventory updates and request processing
- Basic validation of donor donation history

📂 Project Structure

Smart-Blood-Bank-Management-System/
│
├── smart_blood_bank_management_system.c
└── README.md

Additional files, such as a project report, test cases, screenshots, or sample output, can be added as the project develops.

#Testing

Test the application using scenarios such as:

1. Adding a new donor.
2. Viewing donor records.
3. Recording a donation.
4. Checking donation history and eligibility.
5. Viewing blood stock for different blood groups.
6. Adding and processing hospital requests.
7. Testing queue behavior when it becomes full or empty.
8. Checking invalid menu choices and unavailable stock.

Record the actual results of each test before reporting it as passed.

# Project Scope and Limitations

This project demonstrates basic blood bank management concepts for educational purposes. It is not a certified hospital blood bank system and should not be used to make real clinical decisions.

A production system would require secure persistent storage, authentication, privacy controls, medically validated donor eligibility rules, blood component compatibility checks, traceability, and appropriate clinical oversight.

# Future Enhancements

- Persistent storage using files or a database
- Search and filtering of donor records
- Improved reports for donation history and inventory
- Blood request prioritization
- Automated inventory and request summaries
- A graphical dashboard or web interface

# Author

Harish M

Student project — C Programming and Data Structures

