requires visual studio and git https://git-scm.com/downloads

1 enter x64 Native Tools Command Prompt for VS 2022 in startmenu
2 nav to project folder
cd path\to\TodoListCPP
3 compile programs
cl /EHsc /std:c++17 Task.cpp TodoList.cpp manager.cpp /Fe:manager.exe
cl /EHsc /std:c++17 Task.cpp TodoList.cpp editor.cpp /Fe:editor.exe
4 run in any cmd prompt

git pull
manager.exe create_list Homework2 02.06.2025 "Finish Math" "Read Chapter 5"
editor.exe view_tasks Homework
editor.exe complete_task Homework 1
git add .
git commit -m "finished task 1 in Homework"
git push

list of functions:
manager.exe
(Defined in manager.cpp — responsible for managing tasks within a specific list)

Available commands:

add_task <list_name> <task_description>
➤ Adds a new task to the specified list.

Example:
manager.exe add_task Homework2 "Finish physics exercises"

complete_task <list_name> <task_id>
➤ Marks the task with the given ID as completed.

Example:
manager.exe complete_task Homework2 2

view_tasks <list_name>
➤ Displays all tasks in the specified list with their status.

Example:
manager.exe view_tasks Homework2

📂 editor.exe
(Defined in editor.cpp — responsible for creating and deleting lists)

Available commands:

create_list <list_name> <DD.MM.YYYY> <task1> <task2> ...
➤ Creates a new list with the given name, date, and tasks.

Example:
editor.exe create_list Homework2 06.06.2025 "Finish Math" "Read Chapter 5"

delete_list <list_name>
➤ Deletes the list file and removes it from index.txt.

Example:
editor.exe delete_list Homework2

view_lists
➤ Displays all existing list names stored in index.txt.

Example:
editor.exe view_lists
