# Study Time Tracker
A desktop application for tracking and analyzing study/work sessions.
Built using *Qt Widgets*, pure C++ avoiding drag-and-drop (Qt Designer), and *SQLite*.
The application allows users to start, pause, and stop timed sessions, automatically storing session data in a local SQLite database for later review and filtering.

# Features
* Timer page with start, stop and pause buttons
* Automatic insertion of completed sessions
* View session history in a sorted table (by decreasing start date)
* Filter sessions by date range
* Calculation of total tracked time, depending on the range chosen
* Automatic session save when the app closes

## How it's made
**Tech used:** C++, Qt (Qt Widgets, Signals & Slots, Qt SQL), SQLite
* All the GUI and event handling implemented using Qt Widgets
* Timer logic controlled using Qt signals and slots
* Database logic is separated into a dedicated SessionTable class that handles table creation and session storage.
* Session history displayed, sorted and filtered using QSqlTableModel.

The app was intentionally built without Qt Designer to strengthen understanding of programmatic UI construction.

## Why I built this
This application was designed to help track and analyze personal study time.
The project was created to:
* Work with relational databases (SQLite)
* Strengthen C++ object-oriented design skills
* Practice GUI development with Qt
* Implement event-driven programming using signals and slots

## Build instructions
Requires Qt 6.x
1. Clone the repo: ```git clone https://github.com/H4elme/StudyTracker.git```
2. Open CMakeLists.txt in Qt Creator
3. Build and run
4. The SQLite database will be initialized automatically on the first launch

