This project is a simple and functional Student Management System written in C language.
It allows two types of users: Admin and Student to log in and perform different operations such as adding student details, viewing records, searching students, updating marks, and deleting student entries.

The project uses file handling in C to store credentials and student data permanently in text files.

📌 Features
🔐 Login System

Separate credentials.txt file for storing username & password.

Password input is hidden (not visible) while typing.

Users get 3 attempts to enter the correct password.

👨‍💻 Admin Functionalities

Admins have complete control over data and can perform:

➕ Add New Student

📋 View All Students

🔍 Search Student

By Roll Number

By Name

By Partial Name Match (Any substring)

✏️ Update Marks

❌ Delete Student

🚪 Logout

👨‍🎓 Student Functionalities

Students can:

🔍 Search Their Details

By their username, roll number, or name (partial allowed)

📋 View Their Marks & Information

🚪 Logout

📁 Required Files

The system uses these files:

students.txt

Stores all student details in the format:

roll name marks

credentials.txt

Stores login credentials in this format:

admin admin123
student student123


You can add more users by editing this file.

📂 Project File Structure
📦 Student-Management-System
├── students.txt
├── credentials.txt
├── main.cpp (or main.c)
├── program.exe (if compiled)
└── README.md

▶️ How to Run the Program
🔹 On Windows (CodeBlocks / Dev C++ / MinGW)

Open your IDE

Create a new C project

Paste the code into main.c

Place students.txt and credentials.txt in the same folder

Compile & Run

🔹 On Linux (GCC terminal)
gcc main.c -o sms
./sms

✏️ How to Use
1️⃣ Login

Enter username → press Enter

Enter password → characters remain hidden

After 3 failed attempts → program exits

2️⃣ Choose Role-based Operations

Admins get full access, students get limited access.

🔍 Search Function

Search supports:

Exact name

Partial name

Case-insensitive input

Roll number search

Username-based auto search

🗑️ Delete and Update Operations

Admin can:

Delete student by roll number

Update marks for any student

🔒 Security Features

Hidden password input

Tries limited to 3

Invalid entries handled safely

📜 Future Enhancements (Optional)

You may add these to make the project even better:

GUI using C++ and Qt

CSV export

Password encryption

Role-based permissions

Sorting of student list
