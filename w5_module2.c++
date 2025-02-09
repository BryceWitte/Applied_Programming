#include <iostream>
#include <vector>
#include <fstream>
#include <string>

class Task {
public:
    std::string description;
    bool completed;

    Task(std::string desc) : description(desc), completed(false) {}

    void markCompleted() {
        completed = true;
    }

    void display() const {
        std::cout << (completed ? "[X] " : "[ ] ") << description << std::endl;
    }
};

class ToDoList {
private:
    std::vector<Task> tasks;

public:
    void addTask(const std::string& description) {
        tasks.emplace_back(description);
    }

    void removeTask(int index) {
        if (index >= 0 && index < tasks.size()) {
            tasks.erase(tasks.begin() + index);
        } else {
            std::cout << "Invalid task index." << std::endl;
        }
    }

    void markTaskCompleted(int index) {
        if (index >= 0 && index < tasks.size()) {
            tasks[index].markCompleted();
        } else {
            std::cout << "Invalid task index." << std::endl;
        }
    }

    void displayTasks() const {
        for (size_t i = 0; i < tasks.size(); ++i) {
            std::cout << i + 1 << ". ";
            tasks[i].display();
        }
    }

    void saveToFile(const std::string& filename) {
        std::ofstream file(filename);
        for (const auto& task : tasks) {
            file << task.description << "|" << task.completed << std::endl;
        }
        file.close();
    }

    void loadFromFile(const std::string& filename) {
        std::ifstream file(filename);
        std::string line;
        while (std::getline(file, line)) {
            size_t pos = line.find('|');
            if (pos != std::string::npos) {
                std::string desc = line.substr(0, pos);
                bool completed = (line.substr(pos + 1) == "1");
                Task task(desc);
                if (completed) {
                    task.markCompleted();
                }
                tasks.push_back(task);
            }
        }
        file.close();
    }
};

int main() {
    ToDoList todoList;
    todoList.loadFromFile("tasks.txt");

    int choice;
    std::string taskDescription;

    do {
        std::cout << "\nTo-Do List Manager\n";
        std::cout << "1. Add Task\n";
        std::cout << "2. Remove Task\n";
        std::cout << "3. Mark Task Completed\n";
        std::cout << "4. View Tasks\n";
        std::cout << "5. Save and Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Enter task description: ";
                std::cin.ignore();
                std::getline(std::cin, taskDescription);
                todoList.addTask(taskDescription);
                break;
            case 2:
                std::cout << "Enter task number to remove: ";
                int removeIndex;
                std::cin >> removeIndex;
                todoList.removeTask(removeIndex - 1);
                break;
            case 3:
                std::cout << "Enter task number to mark as completed: ";
                int completeIndex;
                std::cin >> completeIndex;
                todoList.markTaskCompleted(completeIndex - 1);
                break;
            case 4:
                todoList.displayTasks();
                break;
            case 5:
                todoList.saveToFile("tasks.txt");
                std::cout << "Tasks saved. Exiting..." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    } while (choice != 5);

    return 0;
}
