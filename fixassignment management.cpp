#include <iostream>
#include <string>

using namespace std;

struct Assignment {
    char name[100];
    int daysLeft;
    int tasksCount;
    char needsDeepAnalysis;
    string urgency;
    bool isDone;
    int delayCount; 
};

string calculateUrgency(int days, char deepAnalysis, int tasks) {
    int score = 0;
    
    if (days >= 1) {
        if (days <= 3) {
            score += 50;
        }
    }
    
    if (days > 3) {
        if (days <= 7) {
            score += 30;
        }
    }
    
    if (days > 7) {
        score += 10;
    }

    if (deepAnalysis == 'Y') {
        score += 25;
    }
    
    if (deepAnalysis == 'y') {
        score += 25;
    }

    if (tasks > 5) {
        score += 25;
    }
    
    if (tasks < 3) {
        score += 10;
    }
    
    if (tasks >= 3) {
        if (tasks <= 5) {
            score += 15;
        }
    }

    if (score > 70) {
        return "[Red] HIGH URGENCY";
    }
    
    if (score >= 40) {
        return "[Yellow] MODERATE URGENCY";
    }
    
    return "[Green] LOW URGENCY";
}

string getQuoteByDays(int daysLeft) {
    string quotes[6] = {
        "\"It always seems impossible until it's done.\" - Nelson Mandela", 
        "\"The secret of getting ahead is getting started.\" - Mark Twain", 
        "\"Quality is not an act, it is a habit.\" - Aristotle", 
        "\"Well done is better than well said.\" - Benjamin Franklin", 
        "\"The only way to do great work is to love what you do.\" - Steve Jobs", 
        "\"Success is not final, failure is not fatal: it is the courage to continue that counts.\" - Winston Churchill"
    };
    
    if (daysLeft >= 7) return quotes[0];
    if (daysLeft >= 5) return quotes[1];
    if (daysLeft >= 3) return quotes[2];
    if (daysLeft >= 1) return quotes[3];
    if (daysLeft == 0) return quotes[4];
    
    return quotes[5];
}

int printMenu(Assignment list[], int count) {
    int choice;
    cout << "\n========================================\n";
    cout << "      Assignment Deadline Manager       \n";
    cout << "========================================\n";
    
    if (count == 0) {
        cout << ">>> Current List: No assignments tracked yet.\n";
    } 
    
    if (count > 0) {
        cout << "--- DASHBOARD: CURRENT ASSIGNMENTS ---\n";
        for (int i = 0; i < count; i++) {
            cout << "[" << i + 1 << "] " << list[i].name 
                 << " | Due: " << list[i].daysLeft << " days"
                 << " | " << list[i].urgency;
                 
            if (list[i].isDone) {
                cout << " (COMPLETED)";
            }
            cout << "\n";
        }
    }
    
    cout << "========================================\n";
    cout << "1. Add assignment\n";
    cout << "2. View assignments & reminders (Detailed)\n";
    cout << "3. Work on / Complete assignment\n";
    cout << "4. Delete assignment\n";
    cout << "5. Pass a Day (Decrease deadlines)\n";
    cout << "0. Exit\n";
    cout << "Selection: ";
    
    cin >> choice;
    
    if (cin.fail()) {
        cin.clear(); 
        choice = -1; 
    }
    cin.ignore(10000, '\n'); 
    
    return choice;
}

int main() {
    Assignment list[100];
    int count = 0;
    bool running = true;

    while (running) {
        int option = printMenu(list, count);

        if (option == 1) {
            if (count < 100) {
                cout << "\n--- ADD NEW ASSIGNMENT ---\n";
                cout << "Assignment name: ";
                cin.getline(list[count].name, 100); 
                
                cout << "Days until due: ";
                cin >> list[count].daysLeft;
                if (cin.fail()) { cin.clear(); list[count].daysLeft = 0; }
                cin.ignore(10000, '\n'); 
                
                cout << "Does it need deep analytics? (Y/N): ";
                cin >> list[count].needsDeepAnalysis;
                if (cin.fail()) { cin.clear(); list[count].needsDeepAnalysis = 'N'; }
                cin.ignore(10000, '\n'); 
                
                cout << "Number of tasks: ";
                cin >> list[count].tasksCount;
                if (cin.fail()) { cin.clear(); list[count].tasksCount = 1; }
                cin.ignore(10000, '\n'); 

                list[count].urgency = calculateUrgency(list[count].daysLeft, list[count].needsDeepAnalysis, list[count].tasksCount);
                list[count].isDone = false;
                list[count].delayCount = 0;
                
                cout << "\n>> URGENCY CLASSIFICATION RESULT:\n";
                cout << "Based on your inputs, this assignment is categorized as: " << list[count].urgency << "\n";
                
                count++;
                
                cout << "----------------------------------------\n";
                cout << "[SUCCESS] Assignment saved to Dashboard!\n";
                cout << "[TIP] To start working on this assignment, select Option 3 from the Main Menu.\n";
                cout << "----------------------------------------\n";
            } 
            
            if (count >= 100) {
                cout << "Assignment list is full.\n";
            }
        } 
        
        if (option == 2) {
            if (count == 0) {
                cout << "No assignments tracked.\n";
            } 
            
            if (count > 0) {
                for (int i = 0; i < count; i++) {
                    cout << "\n[" << i + 1 << "] " << list[i].name << "\n";
                    
                    if (list[i].isDone) {
                        cout << "Status: COMPLETED\n";
                    } 
                    
                    if (!list[i].isDone) {
                        cout << "Status: PENDING\n";
                        cout << "Days Left: " << list[i].daysLeft << "\n";
                        cout << "Tasks: " << list[i].tasksCount << "\n";
                        cout << "Urgency: " << list[i].urgency << "\n"; 
                        
                        if (list[i].daysLeft == 0) {
                            cout << ">>> REMINDER: DUE TODAY! <<<\n";
                        }
                    }
                }
            }
        } 
        
        if (option == 3) {
            int index;
            cout << "Select assignment number to work on: ";
            cin >> index;
            if (cin.fail()) { cin.clear(); index = -1; }
            cin.ignore(10000, '\n'); 
            
            if (index > 0) {
                if (index <= count) {
                    int actualIndex = index - 1;
                    bool initiallyDone = list[actualIndex].isDone;
                    
                    if (!initiallyDone) {
                        if (list[actualIndex].daysLeft == 0) {
                            cout << "\n[!] DUE DATE TODAY! [!]\n";
                            char doneStatus;
                            do {
                                cout << "Is the assignment completely done? (Y/N): ";
                                cin >> doneStatus;
                                if (cin.fail()) { cin.clear(); doneStatus = 'N'; }
                                cin.ignore(10000, '\n'); 

                                if (doneStatus == 'Y') list[actualIndex].isDone = true;
                                if (doneStatus == 'y') list[actualIndex].isDone = true;
                                
                                if (!list[actualIndex].isDone) {
                                    cout << ">> Status: Not done. You MUST do the task right now!\n";
                                }
                            } while (!list[actualIndex].isDone);
                            
                            cout << "\nGreat job! You managed to finish it right on the deadline.\n";
                            cout << getQuoteByDays(list[actualIndex].daysLeft) << "\n";
                        } 
                        
                        if (list[actualIndex].daysLeft > 0) {
                            cout << "\nOptions for '" << list[actualIndex].name << "':\n";
                            cout << "1. Make progress today\n";
                            cout << "2. Delay it\n";
                            cout << "3. Finish and Complete it today\n";
                            cout << "Pick an option (1/2/3): ";
                            
                            int workOption;
                            cin >> workOption;
                            if (cin.fail()) { cin.clear(); workOption = -1; }
                            cin.ignore(10000, '\n'); 
                            
                            if (workOption == 1) {
                                cout << "Great job making progress today!\n";
                            }
                            
                            if (workOption == 2) {
                                list[actualIndex].delayCount++;
                                
                                if (list[actualIndex].daysLeft == 1) {
                                    cout << "\n[!] CRITICAL: Deadline is tomorrow (H-1)! Delaying now is highly not recommended. Brace yourself for an all-nighter!\n";
                                } 
                                
                                if (list[actualIndex].daysLeft != 1) {
                                    if (list[actualIndex].delayCount == 1) {
                                        cout << "1st Delay: It's fine for now, taking a quick break. But make sure to work on it tomorrow.\n";
                                    } 
                                    if (list[actualIndex].delayCount == 2) {
                                        cout << "2nd Delay: You are procrastinating. Don't let the tasks pile up and ruin your schedule!\n";
                                    } 
                                    if (list[actualIndex].delayCount == 3) {
                                        cout << "\n[!] 3rd Delay WARNING: You have delayed this 3 times! You seriously need to start working now!\n";
                                    } 
                                    if (list[actualIndex].delayCount > 3) { 
                                        cout << "\n[!] SEVERE WARNING: Over 3 delays! This is a dangerous level of procrastination. Stop putting it off!\n";
                                    }
                                }
                            }
                            
                            if (workOption == 3) {
                                list[actualIndex].isDone = true;
                                cout << "\nAwesome work! Assignment is marked as completed.\n";
                                cout << getQuoteByDays(list[actualIndex].daysLeft) << "\n";
                            }
                            
                            if (workOption < 1) cout << "Invalid input. Returning to menu.\n";
                            if (workOption > 3) cout << "Invalid input. Returning to menu.\n";
                        }
                    } 
                    
                    if (initiallyDone) {
                        cout << "This assignment is already completed.\n";
                    }
                }
            } 
            
            if (index <= 0) cout << "Invalid selection.\n";
            if (index > count) cout << "Invalid selection.\n";
        } 
        
        if (option == 4) {
            int index;
            cout << "Select assignment number to delete: ";
            cin >> index;
            if (cin.fail()) { cin.clear(); index = -1; }
            cin.ignore(10000, '\n'); 
            
            if (index > 0) {
                if (index <= count) {
                    for (int i = index - 1; i < count - 1; i++) {
                        list[i] = list[i + 1];
                    }
                    count--;
                    cout << "Assignment deleted.\n";
                }
            } 
            
            if (index <= 0) cout << "Invalid selection.\n";
            if (index > count) cout << "Invalid selection.\n";
        } 
        
        if (option == 5) {
            for (int i = 0; i < count; i++) {
                if (!list[i].isDone) {
                    if (list[i].daysLeft > 0) {
                        list[i].daysLeft--;
                        list[i].urgency = calculateUrgency(list[i].daysLeft, list[i].needsDeepAnalysis, list[i].tasksCount);
                    }
                }
            }
            cout << "One day has passed. All deadlines and urgency statuses have been updated.\n";
        } 
        
        if (option == 0) {
            running = false;
        } 
        
        if (option > 5) cout << "Invalid selection.\n";
        if (option < 0) {
            if (option != -1) {
                cout << "Invalid selection.\n";
            }
        }
    }
    return 0;
}
