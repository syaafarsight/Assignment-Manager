# Assignment Deadline Manager
A C++ -based application developed for students to handle academic procrastination by managing schedules, tracking deadlines, and prioritizing courseworks based on its intensity scores.

## Problem Statement = 
Students frequently manage multiple assignments across different courses, often with different deadlines, leading to missed due dates and difficulty with prioritizing tasks. Research shows that academic procrastination is a widespread challenge for students.

## Objective = 
The objective of this project is to provide a tool that helps students overcome poor scheduling, planning, and task prioritization by coordinating assignment tracking.

## Key Features & Urgency Classification
The program categorizes tasks by accumulating points based on Time, Depth, and Volume of tasks:
* **High urgency** = point accumulation of the parameter more than 70.
* **Moderate urgency** = point of the parameter is 40–70.
* **Low urgency** = point accumulation of the parameter less than 40.

## Core Menu Options
1. Add assignment = input name, days left, deep analysis (Y/N), and number of tasks, then calculate urgency
2. View assignments & Reminders = show each assignment's status, days left, tasks, urgency, and due today reminders
3. Work on/complete assignment = handle tasks due today with a mandatory completion loop, or manage pending tasks with progress (resets delay), delay (adds delay count), or finish options
4. Delete assignment = remove the chosen assignment from the list
5. Pass a day = reduce the days left of each unfinished assignment by 1 and recalculate its urgency

## Algorithm
1. Start with an empty assignment list
2. Show the dashboard and menu, then read the user's choice
3. Add: ask for the name, days left, deep analysis (Y/N), and number of tasks. Calculate the urgency and save the assignment
4. View: show each assignment's status, days left, tasks, and urgency. Show a reminder if it is due today
5. Work on/Complete: If it is due today, repeat the question "Is it done?" until the user answers Yes, then mark it completed. If days remain, the user chooses to make progress (reset the delay count), delay (add 1 to the delay count, with a warning at 3 or more), or finish (mark it completed)
6. Delete: remove the chosen assignment from the list
7. Pass a Day: reduce the days left of each unfinished assignment by 1 and recalculate its urgency\
8. Exit: stop the program. Otherwise, go back to step 2