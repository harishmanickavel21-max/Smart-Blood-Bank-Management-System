Smart Blood Bank Management System

A C-Based Blood Bank Management Application with Web Dashboard Integration

Project Overview

The Smart Blood Bank Management System is an academic software project designed to demonstrate how programming and data structures can be applied to blood bank management.

The project combines a C-based management system with a web dashboard built using HTML, CSS, and JavaScript. A Python HTTP server connects the dashboard to the C backend, allowing users to interact with supported blood bank operations through a browser.

The system demonstrates donor management, donation history, blood inventory tracking, hospital requests, and transaction processing.

Problem Statement

Managing donor records, blood availability, donation history, and hospital requests requires organized data handling and reliable processing.

This project demonstrates a software-based approach to these challenges using C programming, fundamental data structures, and a browser-based interface.

Project Objectives

- Organize donor information and donation records.
- Maintain blood inventory for supported blood groups.
- Record and process hospital blood requests.
- Update request status and inventory during fulfilment.
- Apply a configurable 90-day repeat-donation interval rule.
- Demonstrate circular queue operations.
- Connect a web dashboard to a C backend through a Python HTTP server.
- Provide setup instructions for Android and desktop environments.

Key Features

Feature| Description
Donor Management| Register donors and maintain donor records.
Donation History| Record donations and check the configured donation interval.
Blood Inventory| Track blood units and process stock updates.
Hospital Requests| Create requests and track their fulfilment status.
Transaction Queue| Demonstrate circular queue operations.
Web Dashboard| Interact with the application through a browser.
Backend API| Exchange information between the frontend and backend using JSON.
State Monitoring| Retrieve the current backend state through an API endpoint.

Technologies Used

Technology| Purpose
C| Core application logic and data structures
Python 3| HTTP server and communication bridge
HTML5| Dashboard structure
CSS3| Dashboard layout and styling
JavaScript| Frontend interactions and API communication
GCC / Clang| Compiling the C backend
Git and GitHub| Version control and project hosting

System Architecture

The application follows a simple client-server architecture.

User
 |
 v
Web Browser
 |
 v
Dashboard
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
Application Data
Donors, Blood Stock,
Requests and Queue

How It Works

1. The user interacts with the dashboard through a web browser.
2. JavaScript sends supported requests to the Python HTTP server.
3. The Python server communicates with the C backend.
4. The C backend processes the requested operation.
5. The server returns the resulting state as JSON.
6. The dashboard displays the latest information received from the backend.

The original menu-driven C application is maintained separately from the C backend used by the web dashboard.

Repository Structure

Smart-Blood-Bank-Management-System/
|
|-- README.md
|-- smart_blood_bank_management_system.c
|-- original_classroom_backend.c
|-- blood_bank_backend.c
|-- server.py
|-- index.html
|-- styles.css
`-- app.js

File Description

File| Purpose
"smart_blood_bank_management_system.c"| Original menu-driven C management application
"original_classroom_backend.c"| Separate copy of the classroom backend source
"blood_bank_backend.c"| C backend used by the web dashboard
"server.py"| Python HTTP server and backend communication bridge
"index.html"| Dashboard page structure
"styles.css"| Dashboard styling and layout
"app.js"| Frontend logic and API communication
"README.md"| Project documentation and setup instructions

System Requirements

Before running the integrated dashboard, ensure that you have:

- Python 3
- GCC or Clang
- Git
- A modern web browser
- Termux on Android, or a terminal on your computer

Installation and Setup

A. Run on Windows

Step 1: Install the required software

Install Python 3, Git, and a compatible GCC compiler. Ensure the required commands are available in your terminal.

Step 2: Clone the repository

Open Command Prompt or PowerShell and run:

git clone https://github.com/harishmanickavel21-max/Smart-Blood-Bank-Management-System.git

Step 3: Open the project folder

cd Smart-Blood-Bank-Management-System

Step 4: Compile the C backend

gcc blood_bank_backend.c -o blood_bank_backend.exe

Step 5: Start the Python server

python server.py

Step 6: Open the dashboard

Open your browser and visit:

http://127.0.0.1:8000

Keep the terminal and server running while using the application.

B. Run on Linux

Step 1: Install the required packages

On Ubuntu or Debian-based systems:

sudo apt update
sudo apt install git python3 gcc -y

Step 2: Clone the repository

git clone https://github.com/harishmanickavel21-max/Smart-Blood-Bank-Management-System.git

Step 3: Open the project folder

cd Smart-Blood-Bank-Management-System

Step 4: Compile the C backend

gcc blood_bank_backend.c -o blood_bank_backend

Step 5: Start the server

python3 server.py

Step 6: Open the dashboard

Visit http://127.0.0.1:8000 in your browser.

C. Run on Android Using Termux

Step 1: Install the required packages

Open Termux and execute:

pkg update
pkg install git python clang -y

Step 2: Clone the repository

git clone https://github.com/harishmanickavel21-max/Smart-Blood-Bank-Management-System.git

Step 3: Open the project folder

cd Smart-Blood-Bank-Management-System

Step 4: Compile the C backend

clang blood_bank_backend.c -o blood_bank_backend

Step 5: Start the server

python server.py

Step 6: Open the dashboard

Open Chrome on the same phone and visit:

http://127.0.0.1:8000

Keep Termux running while using the dashboard.

Important: These instructions assume the server can locate and execute the compiled backend. If the server expects a different executable name or path, adjust the compilation command to match its configuration.

Backend API

The integrated application provides the following documented endpoints.

Endpoint| Method| Purpose
"/api/state"| GET| Retrieves the current backend state.
"/api/action"| POST| Sends supported operations to the backend.

The API supports the operations implemented by the current integration, including donor registration, donation recording, blood stock updates, hospital request creation, request fulfilment, queue processing, and demonstration or reset operations.

Verify the Backend

After starting the server, open:

http://127.0.0.1:8000/api/state

A JSON response containing the current backend state should appear if the server and backend are running correctly.

The dashboard can then be refreshed to check whether it displays the latest backend state.

Testing and Verification

The following functional checks have been reported as completed:

- Hospital requests are recorded in the backend JSON response.
- Request fulfilment updates request status and blood stock correctly.
- A second donation within the configured 90-day interval is prevented.
- Dashboard refresh displays the current backend state.
- Donor registration and state updates have been tested.
- Blood stock and queue operations have been tested.
- Hospital request creation and fulfilment have been tested.

These checks represent manual functional testing. They do not constitute a complete automated test suite or independent medical validation.

Limitations

- Temporary data: Backend state is held in memory and can be lost when the backend restarts.
- Development server: The local HTTP server is intended for development and demonstration, not public production deployment.
- Simplified donation rule: The 90-day interval is a programming demonstration and does not establish medical eligibility to donate blood.
- Security: Production-grade authentication, authorization, and privacy controls are not provided.
- Testing: Manual verification does not guarantee that every edge case has been tested.
- Clinical use: The application must not be used to make real medical decisions or determine actual blood allocation.

Use fictional donor and hospital information during demonstrations.

Future Enhancements

- Add database storage for persistent records.
- Implement secure authentication and role-based access.
- Improve data validation and error handling.
- Add transaction history and audit logging.
- Introduce automated unit and integration tests.
- Improve notifications for urgent blood requests.
- Strengthen backup, recovery, and privacy protections.
- Prepare the application for secure deployment.

Academic Relevance

This project demonstrates practical applications of:

- Structures, arrays, functions, and conditional logic in C.
- Circular queue implementation and transaction processing.
- Record management and inventory tracking.
- HTTP communication between application components.
- JSON data exchange between a backend and frontend.
- Basic web development and system integration.
- Software testing, debugging, and version control.

Conclusion

The Smart Blood Bank Management System demonstrates how fundamental C programming concepts can be combined with a browser-based dashboard and a lightweight Python HTTP server.

The project provides a practical learning experience in data structures, application logic, inventory management, request processing, and frontend-backend communication. It serves as an educational foundation for further development of healthcare management software.

Author

Harish Manickavel

GitHub: https://github.com/harishmanickavel21-max

Project Information

- Project Name: Smart Blood Bank Management System
- Project Type: Academic / Educational Prototype
- Primary Language: C
- Interface: Web Dashboard
- Repository: https://github.com/harishmanickavel21-max/Smart-Blood-Bank-Management-System

License

No open-source license has been specified. Add an appropriate license if you intend to permit others to reuse, modify, or distribute the project.