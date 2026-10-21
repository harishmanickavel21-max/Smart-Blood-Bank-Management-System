Smart Blood Bank Management System

Project Overview

The Smart Blood Bank Management System is a software application developed to simplify blood bank operations and improve the management of donor information, blood inventory, and hospital requests. The project combines a C-based backend with a web dashboard developed using HTML, CSS, and JavaScript. A Python HTTP server connects the dashboard to the C backend, enabling communication between the frontend and backend components.

Problem Statement

Managing blood donors, monitoring blood availability, maintaining donation records, and processing hospital requests can be challenging without an organized system. This project demonstrates how software can help manage these activities systematically and improve the efficiency of blood bank operations.

Objectives

The main objective of this project is to develop a system that manages donor information, tracks blood availability, records hospital requests, and updates inventory during request fulfilment. It also implements a configurable 90-day interval rule to prevent repeat donations within the specified period. The project demonstrates the practical application of C programming, data structures, web technologies, and backend integration.

Key Features

Donor Management

The system maintains donor information and donation records to support organized donor management.

Blood Inventory Management

The application tracks available blood units across supported blood groups and updates stock when blood requests are fulfilled.

Hospital Request Management

The system records hospital blood requests and tracks their fulfilment status.

Donation Eligibility

The application checks donation history and prevents repeat donations within the configured 90-day interval.

Web Dashboard

The web dashboard provides an interface for interacting with the application and viewing information received from the backend.

Backend Integration

A Python HTTP server connects the web dashboard to the C backend and exchanges application data in JSON format.

Technologies Used

The project uses C for core application logic and data structures, Python for the HTTP server, HTML for webpage structure, CSS for styling, and JavaScript for frontend interactions and backend communication. GCC or Clang can be used to compile the C backend. Git and GitHub are used for version control and project hosting.

Project Structure

The repository contains the main C application in "smart_blood_bank_management_system.c", the original classroom backend in "original_classroom_backend.c", the integrated C backend in "blood_bank_backend.c", and the Python server in "server.py". The web dashboard consists of "index.html", "styles.css", and "app.js". The "README.md" file provides project documentation and setup instructions.

System Requirements

To run the integrated application, a compatible operating system, Python 3, GCC or Clang, and a modern web browser are required. Git is needed if the repository is to be cloned from GitHub. Android users can use Termux with the required packages installed.

Installation and Execution

First, clone the repository using the following command:

git clone https://github.com/harishmanickavel21-max/Smart-Blood-Bank-Management-System.git

Open the project directory:

cd Smart-Blood-Bank-Management-System

Compile the C backend using GCC:

gcc blood_bank_backend.c -o blood_bank_backend

Start the Python server:

python server.py

Once the server is running, open a web browser and visit "http://127.0.0.1:8000" to access the dashboard.

On Windows, the compiler command may need to produce "blood_bank_backend.exe", depending on how the Python server launches the backend. On Linux or Android using Termux, Clang can be used instead of GCC. The compilation command and executable name must match the configuration in "server.py".

Backend API

The application uses HTTP endpoints to exchange information between the frontend and backend. The "GET /api/state" endpoint retrieves the current backend state, while the "POST /api/action" endpoint processes supported operations. These endpoints enable the dashboard to request application data and submit operations to the backend.

To check whether the server is responding, open "http://127.0.0.1:8000/api/state" in a browser. A JSON response should appear when the endpoint is available and functioning correctly.

Testing and Verification

The following functional checks have been reported as completed during project testing: hospital requests appear in the backend JSON data, request fulfilment updates the request status and blood inventory correctly, repeat donations within the configured 90-day interval are prevented, and refreshing the dashboard displays the current backend state. These results should be verified again after significant code changes.

Limitations

The current backend maintains its application state in memory, so data may be lost when the backend restarts. The application is intended for educational demonstrations and does not include all the security, authentication, privacy, and reliability requirements of a production healthcare system. The 90-day donation interval is a programming rule for this project and must not be treated as medical advice or a determination of actual donor eligibility.

Future Enhancements

Future improvements may include database integration for permanent storage, secure authentication for administrators and hospitals, improved input validation, transaction history, automated testing, notifications for urgent requests, and stronger data backup and recovery mechanisms.

Learning Outcomes

This project provides practical experience in C programming, structures, arrays, functions, conditional statements, loops, data management, circular queues, inventory tracking, and request processing. It also demonstrates frontend-backend integration, HTTP communication, JSON data exchange, software testing, debugging, and version control.

Conclusion

The Smart Blood Bank Management System demonstrates how programming and web technologies can be combined to organize blood bank operations. By integrating a C backend with a web dashboard through a Python HTTP server, the project provides a practical learning experience in software development, data structures, and application integration.

Author

Harish M

GitHub Profile: https://github.com/harishmanickavel21-max

Project Repository: https://github.com/harishmanickavel21-max/Smart-Blood-Bank-Management-System


