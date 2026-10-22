Smart Blood Bank Management System

A C-Based Blood Bank Management Application with Web Dashboard Integration

Project Overview:
       The Smart Blood Bank Management System is an academic software project that demonstrates how fundamental C programming concepts and data structures can be applied to blood bank operations. The project combines a C-based management backend with a browser-based dashboard, connected through a lightweight Python HTTP server.

The application provides a practical demonstration of donor management, donation history, blood inventory updates, hospital blood requests, request fulfilment, and backend state monitoring. It also demonstrates communication between a frontend interface and a C backend using HTTP requests and JSON data. 

This project is developed for educational purposes and demonstrates programming logic, data structures, and basic client-server integration.

Problem Statement:
        Managing donor records, donation history, available blood stock, and hospital requests requires organized data handling and consistent transaction processing. This project explores how these operations can be represented in a software application using C programming, data structures, and a web-based interface.

Objectives

- Apply C programming concepts to a practical management problem.
- Organize donor records and blood inventory using structures and arrays.
- Demonstrate circular queue operations for transaction processing.
- Maintain donation history and enforce a configurable 90-day repeat-donation interval.
- Create and process hospital blood requests.
- Integrate a C backend with a browser-based dashboard through Python.
- Demonstrate real-time retrieval of the current backend state.

Key Features:
- Donor Management:
     Register donors and maintain donor records required by the application.
     
- Donation History:
     Record donation events and check the configured 90-day interval before accepting another donation from the same donor.
     
- Blood Inventory Management:
     Track blood stock and demonstrate stock updates when blood units are added or issued.
     
- Hospital Blood Requests:
     Create hospital requests, track their fulfilment status, and update inventory when requests are fulfilled.
     
- Circular Queue Processing:
     Use a circular queue to demonstrate structured transaction processing.
     
- Interactive Web Dashboard:
     Access the system through a browser-based interface built with HTML, CSS, and JavaScript.
     
- Backend Integration:
     Use a Python HTTP server to connect dashboard actions to the C backend and exchange application state in JSON format.

Technology Stack

- C: Core application logic, record management, and data structures.
- Python 3: Local HTTP server and communication bridge.
- HTML5: Dashboard structure.
- CSS3: Dashboard styling and layout.
- JavaScript: User interactions and API communication.
- GCC / Clang: C compilation.
- Git and GitHub: Version control and project hosting.

System Architecture

The application follows a simple client-server architecture.

1. The user interacts with the web dashboard through a browser.
2. JavaScript sends HTTP requests to the Python server.
3. The Python server communicates with the C backend.
4. The C backend processes supported operations and updates application state.
5. The server returns the resulting state as JSON.
6. The dashboard displays the updated information.


Project Structure

Smart-Blood-Bank-Management-System/
├── README.md
├── smart_blood_bank_management_system.c
├── original_classroom_backend.c
├── blood_bank_backend.c
├── server.py
├── index.html
├── styles.css
└── app.js

File Descriptions

- "smart_blood_bank_management_system.c" — Standalone C management application.
- "original_classroom_backend.c" — Separate copy of the original classroom backend source.
- "blood_bank_backend.c" — C backend used by the web dashboard.
- "server.py" — HTTP server that connects the dashboard to the C backend.
- "index.html" — Dashboard page structure.
- "styles.css" — Dashboard styling.
- "app.js" — Frontend interactions and backend communication.
- "README.md" — Project documentation and setup instructions.

Requirements

- Git
- Python 3
- GCC or Clang
- A modern web browser
- Windows, Linux, or Android with Termux

Installation and Setup

1. Clone the Repository

Open a terminal or command prompt and run:

git clone https://github.com/harishmanickavel21-max/Smart-Blood-Bank-Management-System.git

Navigate to the project directory:

cd Smart-Blood-Bank-Management-System

2. Compile the C Backend

On Linux or Android Termux:

gcc blood_bank_backend.c -o blood_bank_backend

On Windows, using a compatible GCC installation:

gcc blood_bank_backend.c -o blood_bank_backend.exe

3. Start the Python Server

On Linux or Android Termux:

python3 server.py

On Windows:

python server.py

If the server uses a platform-specific executable name, ensure that the compiled backend filename matches the name expected by "server.py".

4. Open the Dashboard

Open a browser on the same device and visit:

http://127.0.0.1:8000

Keep the terminal and server running while using the dashboard.

5. Verify the Backend

Open the following address in your browser:

http://127.0.0.1:8000/api/state

A JSON response should display the current backend state when the server and backend are running correctly.

Note: These instructions assume the project dependencies are installed and the server is configured to use port 8000.

API Overview

The dashboard communicates with the backend through the following endpoints:

- "GET /api/state" — Retrieves the current application state.
- "POST /api/action" — Sends supported operations to the backend.

Supported operations include donor registration, donation recording, stock updates, hospital request creation, request fulfilment, queue processing, and demonstration/reset actions.

The exact accepted request formats depend on the implementation in "server.py" and "blood_bank_backend.c".

Testing and Verification

The following functional checks have been completed:

- Hospital requests appear in the backend JSON state.
- Request fulfilment updates the request status and blood stock correctly.
- A second donation within the configured 90-day interval is prevented.
- Dashboard refresh reflects the current backend state.

These checks demonstrate the core workflows of the application. They represent manual functional testing rather than a complete automated test suite.

Conclusion

The Smart Blood Bank Management System demonstrates how fundamental programming concepts can be combined with a web dashboard to build an interactive management application. By integrating C, Python, and frontend technologies, the project provides practical experience in data structures, application logic, backend communication, and software testing.

The project serves as a foundation for further development into a more persistent, secure, and feature-rich management application.

Author

HARISH M

Presidency University


