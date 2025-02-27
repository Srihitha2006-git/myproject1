#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Employee Node structure
typedef struct EmployeeNode {
    int emp_id;                 // Employee ID
    char name[100];             // Employee Name
    float salary;               // Employee Salary
    struct EmployeeNode* prev;  // Pointer to the previous node
    struct EmployeeNode* next;  // Pointer to the next node
} EmployeeNode;

// Function to create a new employee node
EmployeeNode* create_employee(int emp_id, const char* name, float salary) {
    EmployeeNode* new_employee = (EmployeeNode*)malloc(sizeof(EmployeeNode));
    new_employee->emp_id = emp_id;
    strcpy(new_employee->name, name);
    new_employee->salary = salary;
    new_employee->prev = NULL;  // Initialize previous pointer to NULL
    new_employee->next = NULL;  // Initialize next pointer to NULL
    return new_employee;
}

// Function to add an employee to the end of the list
EmployeeNode* add_employee(EmployeeNode* head, int emp_id, const char* name, float salary) {
    EmployeeNode* new_employee = create_employee(emp_id, name, salary);
    if (head == NULL) { // If the list is empty, the new employee becomes the head
        return new_employee;
    }

    EmployeeNode* current = head;
    while (current->next != NULL) { // Traverse to the last node
        current = current->next;
    }
    current->next = new_employee; // Link the last node to the new employee
    new_employee->prev = current;  // Link the new employee back to the last node
    return head; // Return the unchanged head
}

// Function to display all employees
void display_employees(EmployeeNode* head) {
    if (!head) {
        printf("No employees in the list.\n");
        return;
    }
    EmployeeNode* current = head;
    while (current) {
        printf("ID: %d, Name: %s, Salary: %.2f\n", current->emp_id, current->name, current->salary);
        current = current->next; // Move to the next node
    }
}

// Function to delete an employee by ID
EmployeeNode* delete_employee(EmployeeNode* head, int emp_id) {
    if (!head) {
        printf("No employees to delete.\n");
        return head;
    }

    // If the head is the node to delete
    if (head->emp_id == emp_id) {
        EmployeeNode* temp = head;
        head = head->next; // Move head to the next node
        if (head) {
            head->prev = NULL; // Update the previous pointer of new head
        }
        free(temp); // Free the old head
        printf("Employee ID %d deleted.\n", emp_id);
        return head;
    }

    // For nodes other than the head
    EmployeeNode* current = head;
    while (current->next && current->next->emp_id != emp_id) {
        current = current->next; // Traverse to find the node to delete
    }
    if (current->next) {
        EmployeeNode* temp = current->next; // Node to be deleted
        current->next = current->next->next; // Link to the next node
        if (current->next) {
            current->next->prev = current; // Update previous pointer of the next node
        }
        free(temp); // Free the deleted node
        printf("Employee ID %d deleted.\n", emp_id);
    } else {
        printf("Employee ID %d not found.\n", emp_id);
    }
    return head;
}

// Function to update an employee's name and salary by ID
void update_employee(EmployeeNode* head, int emp_id, const char* new_name, float new_salary) {
    EmployeeNode* current = head;
    while (current) {
        if (current->emp_id == emp_id) {
            strcpy(current->name, new_name);
            current->salary = new_salary;
            printf("Employee ID %d updated to new name: %s, new salary: %.2f\n", emp_id, new_name, new_salary);
            return;
        }
        current = current->next; // Move to the next node
    }
    printf("Employee ID %d not found.\n", emp_id);
}

// Main function to demonstrate the employee information system
int main() {
    EmployeeNode* head = NULL; // Initialize the head of the list
    int choice, emp_id;
    char name[100];
    float salary;

    do {
        printf("\nEmployee Information System\n");
        printf("1. Add Employee\n");
        printf("2. Display Employees\n");
        printf("3. Update Employee\n");
        printf("4. Delete Employee\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: // Add Employee
                printf("Enter Employee ID: ");
                scanf("%d", &emp_id);
                printf("Enter Employee Name: ");
                scanf(" %[^\n]", name); // Read string with spaces
                printf("Enter Employee Salary: ");
                scanf("%f", &salary);
                head = add_employee(head, emp_id, name, salary);
                break;

            case 2: // Display Employees
                display_employees(head);
                break;

            case 3: // Update Employee
                printf("Enter Employee ID to update: ");
                scanf("%d", &emp_id);
                printf("Enter new name: ");
                scanf(" %[^\n]", name);
                printf("Enter new salary: ");
                scanf("%f", &salary);
                update_employee(head, emp_id, name, salary);
                break;

            case 4: // Delete Employee
                printf("Enter Employee ID to delete: ");
                scanf("%d", &emp_id);
                head = delete_employee(head, emp_id);
                break;

            case 5: // Exit
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    // Clean up memory
    while (head) {
        EmployeeNode* temp = head;
        head = head->next; // Move to the next node
        free(temp); // Free the old head
    }

    return 0;
}
