Smart Blood Bank Management System

A C-Based Blood Bank Management Application with Web Dashboard Integration

"Language" (https://img.shields.io/badge/Language-C-blue)
"Frontend" (https://img.shields.io/badge/Frontend-HTML%20%7C%20CSS%20%7C%20JavaScript-orange)
"Backend" (https://img.shields.io/badge/Backend-C%20%2B%20Python-green)
"Platform" (https://img.shields.io/badge/Platform-Android%20%7C%20Linux%20%7C%20Windows-lightgrey)

1. Project Overview

The Smart Blood Bank Management System is an academic software project designed to demonstrate the use of C programming and fundamental data structures in managing basic blood bank operations.

The project includes a C-based management application and a browser-based dashboard connected to a C backend through a Python HTTP server. It provides an interactive way to demonstrate donor registration, blood stock management, donation records, hospital requests, and transaction processing.

The project combines core programming concepts with basic frontend and backend integration to illustrate how a traditional C application can communicate with a web interface.

2. Problem Statement

Managing donor details, blood stock, donation records, and hospital blood requests requires organized data handling and reliable transaction processing.

This project demonstrates a software-based approach to these tasks using structures, arrays, and a circular queue in C, together with a web interface for interacting with the backend.

This is an educational prototype and is not intended to replace a production blood bank management platform.

3. Objectives

- Apply C programming concepts to a practical management problem.
- Use structures and arrays to organize donor and blood stock information.
- Demonstrate circular queue operations for transaction processing.
- Maintain donation history and apply a simplified donation interval rule.
- Manage hospital blood requests and fulfilment.
- Integrate a browser-based dashboard with a C backend using Python.
- Provide a reproducible setup for testing on Android and desktop computers.

4. Key Features

Module| Description
Donor Management| Register donors and maintain donor records.
Donation History| Record donation events and check the configured 90-day interval rule.
Blood Stock| Add and issue units for supported blood groups.
Hospital Requests| Create requests and track fulfilment status.
Transaction Queue| Demonstrate circular queue processing.
Web Dashboard| Interact with the system through a browser interface.
Backend API| Exchange data between the dashboard and the C backend using JSON.
State Monitoring| Retrieve the current backend state through an API endpoint.

5. Technologies Used

- C: Core management logic and data structures.
- Python 3: Local HTTP server and communication bridge.
- HTML5: Dashboard structure.
- CSS3: Dashboard styling and layout.
- JavaScript: Frontend interactions and API requests.
- Git and GitHub: Version control and source code hosting.
- Clang/GCC: C compilation.

6. System Architecture

             User
               |
               v
      Web Browser / Dashboard
        HTML + CSS + JavaScript
               |
               v
        Python HTTP Server
          server.py
               |
               v
          C Backend
     blood_bank_backend.c
               |
               v
     Data Structures and Logic
  Donors | Stock | Requests | Queue

The browser communicates with the Python server through HTTP endpoints. The Python server forwards supported operations to the C backend process and returns the resulting state as JSON.

The original C application is retained separately from the C backend used by the web dashboard.

7. Repository Structure

Smart-Blood-Bank-Management-System/
│
├── README.md
├── smart_blood_bank_management_system.c
├── original_classroom_backend.c
├── blood_bank_backend.c
├── server.py
├── index.html
├── styles.css
└── app.js

File| Purpose
"smart_blood_bank_management_system.c"| Original C management application.
"original_classroom_backend.c"| Separate copy of the classroom backend source.
"blood_bank_backend.c"| C backend used by the web integration.
"server.py"| HTTP server and bridge between the web interface and C process.
"index.html"| Dashboard page structure.
"styles.css"| Dashboard visual styling.
"app.js"| Frontend logic and backend communication.
"README.md"| Project overview and setup documentation.

8. Installation and Setup

Requirements

- Git
- Python 3
- Clang or GCC
- A modern web browser
- Termux for Android, or a terminal on a desktop operating system

A. Run on Android Using Termux

Step 1 — Install dependencies

Open Termux and run:

pkg update
pkg install git python clang -y

Step 2 — Clone the repository

git clone https://github.com/harishmanickavel21-max/Smart-Blood-Bank-Management-System.git

Step 3 — Open the project directory

cd Smart-Blood-Bank-Management-System

Step 4 — Check the project files

ls

Confirm that "blood_bank_backend.c", "server.py", "index.html", "styles.css", and "app.js" are present.

Step 5 — Compile the C backend

clang blood_bank_backend.c -o blood_bank_backend

Step 6 — Start the server

python server.py

Step 7 — Open the dashboard

Open Chrome on the same Android phone and visit:

"http://127.0.0.1:8000"

Keep Termux running while using the application.

Step 8 — Check the backend API

Open:

"http://127.0.0.1:8000/api/state"

A JSON response should display the current backend state if the server and C backend are running correctly.

To stop the server, press "Ctrl+C" in Termux.

B. Run on a Linux Laptop

Install Python 3, Git, and GCC. Then execute:

git clone https://github.com/harishmanickavel21-max/Smart-Blood-Bank-Management-System.git
cd Smart-Blood-Bank-Management-System
gcc blood_bank_backend.c -o blood_bank_backend
python3 server.py

Open "http://127.0.0.1:8000" in your browser.

C. Run on Windows

Install Python 3, Git, and a compatible C compiler. From the project directory, compile the backend to the executable name expected by the server:

gcc blood_bank_backend.c -o blood_bank_backend.exe
python server.py

Open "http://127.0.0.1:8000" in your browser.

If GCC is not available in your Windows terminal, install a compatible compiler and configure its executable path before running these commands.

9. API Overview

Endpoint| Method| Purpose
"/api/state"| GET| Retrieves the current backend state.
"/api/action"| POST| Sends supported operations to the backend.

Supported actions implemented by the integration include donor registration, donation recording, stock updates, request creation, request fulfilment, queue processing, and demonstration/reset operations.

The API is intended for local development and educational demonstration.

10. Testing and Verification

The following workflows have been manually tested in the Android development environment:

- Dashboard access through the local HTTP server.
- Backend state retrieval through "/api/state".
- Donor registration and state updates.
- Blood stock updates.
- Queue operations and processing.
- Hospital request creation and fulfilment.
- Enforcement of the configured repeat-donation interval rule.
- Dashboard refresh reflecting backend state.

These are manual functional checks, not a complete automated test suite or independent clinical validation.

11. Limitations

- Volatile state: Backend data is held in memory and can be lost when the backend restarts.
- Development server: The local server is not hardened for public deployment.
- Simplified eligibility logic: The 90-day rule is a programming demonstration and does not establish medical eligibility to donate blood.
- Security: Authentication, authorization, and production-grade privacy controls are not provided by this prototype.
- Testing scope: Manual tests do not guarantee that every edge case or failure condition has been covered.

Important: Use fictional donor and hospital information during demonstrations. Do not use this application to make real medical or blood-allocation decisions.

12. Future Enhancements

- Persistent data storage using a database.
- Secure login and role-based access for administrators and hospital users.
- Improved validation and error handling.
- Automated unit and integration testing.
- Transaction history and audit logging.
- Secure deployment with appropriate privacy and access controls.

13. Academic Relevance

This project demonstrates practical applications of:

- Structures and arrays in C.
- Circular queue operations.
- Conditional logic, validation, and record management.
- Client-server communication.
- HTTP request handling and JSON data exchange.
- Integration of a C backend with a browser-based user interface.

14. Conclusion

The Smart Blood Bank Management System provides an educational demonstration of how fundamental C programming concepts can be combined with a web dashboard and a lightweight HTTP bridge. It offers a foundation for learning data structures, application logic, and basic system integration.

---

Project Repository: "Smart-Blood-Bank-Management-System" (https://github.com/harishmanickavel21-max/Smart-Blood-Bank-Management-System)

Project Type: Academic / Educational Prototype
