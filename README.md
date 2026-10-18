
# Online Examination System

A menu-driven examination system built with C++ that allows Admins to manage exams, Teachers to create exams and add multiple-choice questions, and Students to take exams, view their scores, and check the leaderboard. The project demonstrates Object-Oriented Programming (OOP), file handling, and the C++ Standard Template Library (STL).

## Features

- **Role-Based Login:** Separate login options for Admin, Teacher, and Student.
- **User Registration:** Register users with a username, password, and role.
- **Exam Management:** View, edit, and delete exams as an Admin.
- **Exam Creation:** Create exams with a name and time-limit setting.
- **MCQ Management:** Add multiple-choice questions with four options and a correct answer.
- **Online Examination:** Allow Students to take available exams.
- **Automatic Scoring:** Calculate scores based on correct answers.
- **Pass/Fail Evaluation:** Determine results using a 40% passing threshold.
- **Leaderboard:** Rank participants according to their scores.
- **File Handling:** Save and load exam data using text files.
- **Object-Oriented Design:** Organize functionality using classes, inheritance, and virtual functions.

## Tech Stack

- **Language:** C++
- **Standard:** C++17
- **Core Concepts:** OOP, Inheritance, Polymorphism, File Handling
- **STL:** Vector, String, Algorithm
- **Compiler:** GCC (g++)

## Project Structure

```text
Online-Examination-System/
├── README.md
├── code.cpp
├── a.exe
├── users.txt
├── exams.txt
└── certificate.txt
```

- `code.cpp` — Main C++ source code.
- `a.exe` — Compiled Windows executable.
- `users.txt` — User credentials and role data.
- `exams.txt` — Saved examination data and questions.
- `certificate.txt` — Reserved for certificate-related data, if needed.
- `README.md` — Project documentation.

## Getting Started

### Option 1: Run the Existing Executable

If you are using Windows, you can run the precompiled program.

**1. Clone the repository**

```bash
git clone https://github.com/sristymohona/Online-Examination-System.git
```

**2. Open the project directory**

```bash
cd Online-Examination-System
```

**3. Run the program**

```bash
a.exe
```

Alternatively, open the project folder in File Explorer and double-click `a.exe`.

### Option 2: Compile from Source

If you have GCC installed, you can compile the source code yourself.

**1. Compile the program**

```bash
g++ -std=c++17 code.cpp -o a.exe
```

**2. Run the executable**

```bash
a.exe
```

**Note:** The precompiled executable is intended for compatible Windows systems. You may need to compile the source code on your own system if the executable is incompatible.

## How to Use

When you start the program, the main menu displays the following options:

| Option | Action |
|---|---|
| 1 | Admin Login |
| 2 | Teacher Login |
| 3 | Student Login |
| 4 | Register |
| 5 | Exit |

### Admin Dashboard

An Admin can:

- View all available exams.
- Delete an exam using its ID.
- Edit an exam name.
- Clear the questions from an exam.

### Teacher Dashboard

A Teacher can:

- Create a new exam.
- Set an exam name and time limit.
- Add multiple-choice questions.
- Provide four answer options for each question.
- Specify the correct answer.

### Student Dashboard

A Student can:

- View available exams.
- Select an exam using its ID.
- Answer multiple-choice questions.
- View the final score.
- Check the pass/fail result.
- View the leaderboard.

## Scoring System

- Each correct answer earns one point.
- The score is displayed as the number of correct answers out of the total questions.
- Students pass when their score reaches at least 40% of the total questions.

## Concepts Demonstrated

This project provides practical experience with:

- Classes and objects.
- Inheritance and polymorphism.
- Abstract classes and virtual functions.
- Vectors and strings.
- File input and output using `ifstream` and `ofstream`.
- Sorting results using the STL `sort()` algorithm.
- Lambda expressions.
- Menu-driven programming.

## Current Limitations

- Registering a user currently overwrites the existing `users.txt` file.
- Passwords are stored as plain text.
- The exam time limit is displayed but is not enforced by a timer.
- Leaderboard results are not saved between program runs.
- The application uses text files instead of a database.
- Input validation and authentication can be improved.

## Future Improvements

- Support multiple user registrations without overwriting existing accounts.
- Improve authentication and password security.
- Implement a functional exam timer.
- Save student results permanently.
- Add question editing and deletion.
- Integrate a database for users, exams, and results.
- Develop a graphical or web-based interface.

## Author

**Montaha Ahmed Mohona**

- GitHub: [@sristymohona](https://github.com/sristymohona)
- LinkedIn: [Montaha Ahmed Mohona](https://www.linkedin.com/in/montaha-ahmed-m/)

---

*Learning as I go, building as I learn, and growing with every step.* ✧

