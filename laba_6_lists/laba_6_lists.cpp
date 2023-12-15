#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include <limits>
#include <climits>
#include <cstddef>
#include <locale>

using namespace std;

// Definition of the linked list node structure
struct Node {
    int data;     
    Node* next;    
};

// Definition of the structure for the stack
struct StackNode {
    int data;         
    StackNode* next;  
};

// Function to perform insertion sort on a linked list
void insertionSort(Node** head) {
    if (*head == NULL || (*head)->next == NULL) {
        cout << "The list is already sorted or empty. Nothing to sort." << endl;
        return;
    }

    Node* sorted = NULL;
    Node* current = *head;

    while (current != NULL) {
        Node* next = current->next;

        if (sorted == NULL || sorted->data >= current->data) {
            // Insert the current node at the beginning of the sorted list
            current->next = sorted;
            sorted = current;
        }
        else {
            // Find the right place to insert the current node in the sorted list
            Node* search = sorted;
            while (search->next != NULL && search->next->data < current->data) {
                search = search->next;
            }

            // Insert the current node after the node 'search'
            current->next = search->next;
            search->next = current;
        }

        current = next;
    }

    // Update the head of the list
    *head = sorted;
}

// Function to add a new node to the list
void push(Node** head, int newData) {
    Node* newNode = new Node();
    newNode->data = newData;
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
        return;
    }

    Node* last = *head;
    while (last->next != NULL) {
        last = last->next;
    }

    last->next = newNode;
}

// Function to merge two sorted lists (does not modify the original lists)
Node* mergeLists(const Node* list1, const Node* list2) {
    if (list1 == NULL) {
        return list2 ? new Node(*list2) : NULL;
    }
    if (list2 == NULL) {
        return new Node(*list1);
    }

    Node* mergedList = NULL;
    Node* current = NULL;

    while (list1 != NULL && list2 != NULL) {
        if (mergedList == NULL) {
            mergedList = new Node(*list1);
            current = mergedList;
        }
        else {
            current->next = new Node(*list1);
            current = current->next;
        }

        current->next = new Node(*list2);
        current = current->next;

        list1 = list1->next;
        list2 = list2->next;
    }

    // Add remaining elements from the first list
    while (list1 != NULL) {
        current->next = new Node(*list1);
        list1 = list1->next;
        current = current->next;
    }

    // Add remaining elements from the second list
    while (list2 != NULL) {
        current->next = new Node(*list2);
        list2 = list2->next;
        current = current->next;
    }

    return mergedList;
}

// Function to print the list
void printList(const Node* head) {
    const Node* current = head;
    while (current != NULL) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

// Function to swap the minimum and maximum elements of a list
void swapMinMax(Node* head) {
    if (head == NULL || head->next == NULL) {
        cout << "The list is empty or contains only one element. Nothing to swap." << endl;
        return;
    }

    Node* minNode = head;
    Node* maxNode = head;
    Node* current = head->next;

    while (current != NULL) {
        if (current->data < minNode->data) {
            minNode = current;
        }
        if (current->data > maxNode->data) {
            maxNode = current;
        }
        current = current->next;
    }

    int temp = minNode->data;
    minNode->data = maxNode->data;
    maxNode->data = temp;

    cout << "The minimum and maximum elements of the list have been successfully swapped." << endl;
}

// Function to display the menu
void printMenu() {
    cout << "\nMenu:\n";
    cout << "1. Merge lists\n";
    cout << "2. Swap the minimum and maximum elements\n";
    cout << "3. Stack operations\n";
    cout << "4. Insertion sort of a list\n";
    cout << "5. Depth-first traversal of a graph (The algorithm works only with 1 vertex; the function to choose the starting vertex is not implemented)\n";
    cout << "6. Topological sorting of graph vertices\n";
    cout << "7. Exit\n";
    cout << "Choose an action: ";
}

// Function for keyboard input of a list
void pushWithInput(Node** head) {
    string input;
    getline(cin, input);
    stringstream ss(input);
    int num;

    while (ss >> num) {
        push(head, num);
    }
}

// Function to input a new list from the keyboard
Node* pushnewList() {
    Node* head = NULL;
    cout << "Enter the elements of a new list (separated by spaces): ";
    pushWithInput(&head);
    return head;
}

// Function to input a list from a file
Node* pushFromFile(const string& filename) {
    Node* head = NULL;
    ifstream file(filename);

    if (!file) {
        cout << "Failed to open the file " << filename << endl;
        return NULL;
    }

    int num;
    while (file >> num) {
        push(&head, num);
    }

    return head;
}

// Function to add an element to the stack
void pushStack(StackNode** top, int newData) {
    StackNode* newNode = new StackNode();
    newNode->data = newData;
    newNode->next = *top;
    *top = newNode;
}

// Function to remove an element from the stack
int popStack(StackNode** top) {
    if (*top == NULL) {
        cout << "The stack is empty." << endl;
        return INT_MIN;
    }

    int poppedData = (*top)->data;
    StackNode* temp = *top;
    *top = (*top)->next;
    delete temp;

    return poppedData;
}

// Function to print the contents of the stack
void printStack(const StackNode* top) {
    const StackNode* current = top;
    cout << "Stack content: ";
    while (current != NULL) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

// Function to clear the input buffer
void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Function to perform topological sort of a graph
void topologicalSort(const vector<vector<int>>& topologicMatrix, vector<bool>& visited, int vertex, stack<int>& sortedStack) {
    visited[vertex] = true;
    for (int i = 0; i < topologicMatrix.size(); ++i) {
        if (!visited[i] && topologicMatrix[vertex][i]) {
            topologicalSort(topologicMatrix, visited, i, sortedStack);
        }
    }
    sortedStack.push(vertex);
}

// Function to perform topological sort of a graph
void performTopologicalSort(const vector<vector<int>>& topologicMatrix, vector<bool>& visited, stack<int>& sortedStack) {
    for (int i = 0; i < topologicMatrix.size(); ++i) {
        if (!visited[i]) {
            topologicalSort(topologicMatrix, visited, i, sortedStack);
        }
    }
}

// Function to perform depth-first traversal of a graph
void DFS(int vertex, const vector<vector<int>>& adjacencyMatrix, vector<bool>& visited, Node** dfsList) {
    visited[vertex] = true;
    push(dfsList, vertex); // Add the vertex to the DFS list

    for (int i = 0; i < adjacencyMatrix.size(); ++i) {
        if (adjacencyMatrix[vertex][i] == 1 && !visited[i]) {
            DFS(i, adjacencyMatrix, visited, dfsList);
        }
    }
}

// Function to count the number of nodes in a list
int countNodes(const Node* head) {
    int count = 0;
    const Node* current = head;
    while (current != NULL) {
        ++count;
        current = current->next;
    }
    return count;
}

int main() {
    Node* list1 = NULL;
    cout << "Enter the elements of the first list (separated by spaces): ";
    pushWithInput(&list1);

    cout << "First list: ";
    printList(list1);

    Node* list2 = NULL;
    cout << "Enter the elements of the second list (separated by spaces): ";
    pushWithInput(&list2);

    cout << "Second list: ";
    printList(list2);

    int choice;
    do {
        printMenu();
        cin >> choice;

        switch (choice) {
        case 1: {
            Node* mergedList = mergeLists(list1, list2);
            cout << "Merged list: ";
            printList(mergedList);
            break;
        }

        case 2: {
            Node* mergedList = mergeLists(list1, list2);
            swapMinMax(mergedList);
            cout << "List after swapping: ";
            printList(mergedList);
            break;
        }

        case 3: {
            StackNode* stackTop = NULL;
            int stackChoice;
            do {
                cout << "\nStack menu:\n";
                cout << "1. Add an element to the stack\n";
                cout << "2. Remove an element from the stack\n";
                cout << "3. Print the contents of the stack\n";
                cout << "4. Return to the main menu\n";
                cout << "Choose an action: ";
                cin >> stackChoice;

                switch (stackChoice) {
                case 1: {
                    cout << "Enter elements to add to the stack (separated by spaces): ";
                    cin.ignore(); // Clear the buffer after the previous input
                    string input;
                    getline(cin, input);

                    stringstream ss(input);
                    int num;

                    while (ss >> num) {
                        pushStack(&stackTop, num);
                    }

                    cout << "Elements successfully added to the stack." << endl;
                    break;
                }

                case 2: {
                    int poppedData = popStack(&stackTop);
                    if (poppedData != INT_MIN) {
                        cout << "Removed element from the stack: " << poppedData << endl;
                    }
                    break;
                }

                case 3:
                    printStack(stackTop);
                    break;

                case 4:
                    cout << "Returning to the main menu." << endl;
                    break;

                default:
                    cout << "Incorrect choice. Please try again.";
                }

                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } while (stackChoice != 4);
            break;
        }
        case 4: {
            int sortChoice;
            do {
                cout << "\nSorting Menu:\n";
                cout << "1. Sort the first list using simple insertion method\n";
                cout << "2. Sort the second list using simple insertion method\n";
                cout << "3. Add a new list\n";
                cout << "4. Return to the main menu\n";
                cout << "Choose an action: ";
                cin >> sortChoice;

                switch (sortChoice) {
                case 1:
                    cout << "Sorting the first list using simple insertion method." << endl;
                    insertionSort(&list1);
                    cout << "Ordered first list: ";
                    printList(list1);
                    break;

                case 2:
                    cout << "Sorting the second list using simple insertion method." << endl;
                    insertionSort(&list2);
                    cout << "Ordered second list: ";
                    printList(list2);
                    break;

                case 3: {
                    Node* newList = pushnewList();
                    int newListChoice;
                    cout << "\nNew list menu:\n";
                    cout << "1. Display the new list\n";
                    cout << "2. Skip display and return to the main menu\n";
                    cout << "Choose an action: ";
                    cin >> newListChoice;

                    switch (newListChoice) {
                    case 1:
                        cout << "New list: ";
                        printList(newList);
                        break;

                    case 2:
                        cout << "Returning to the main menu." << endl;
                        break;

                    default:
                        cout << "Incorrect choice. Returning to the main menu." << endl;
                    }

                    // Free memory allocated for the new list
                    Node* current = newList;
                    Node* next;
                    while (current != NULL) {
                        next = current->next;
                        delete current;
                        current = next;
                    }
                    break;
                }
                case 4:
                    cout << "Returning to the main menu." << endl;
                    continue;

                default:
                    cout << "Incorrect choice. Please try again." << endl;
                }

            } while (sortChoice != 4);

            break;
        }

        case 5: {
            int graphSize;
            cout << "Enter the graph size (number of vertices): ";
            cin >> graphSize;

            // Get the adjacency matrix
            vector<vector<int>> adjacencyMatrix(graphSize, vector<int>(graphSize, 0));

            cout << "Enter the adjacency matrix (separate with spaces):" << endl;
            for (int i = 0; i < graphSize; ++i) {
                for (int j = 0; j < graphSize; ++j) {
                    cin >> adjacencyMatrix[i][j];
                }
            }

            // Depth-first traversal of the graph
            vector<bool> visited(graphSize, false);
            Node* dfsList = NULL;

            for (int i = 0; i < graphSize; ++i) {
                if (!visited[i]) {
                    DFS(i, adjacencyMatrix, visited, &dfsList);
                }
            }

            cout << "List of vertices during depth-first traversal: ";
            printList(dfsList);
            break;
        }
        case 6: {
            int graphSize;
            cout << "Enter the graph size (number of vertices): ";
            cin >> graphSize;

            vector<vector<int>> topologicMatrix(graphSize, vector<int>(graphSize, 0));
            cout << "Enter the adjacency matrix (separate with spaces):\n";
            for (int i = 0; i < graphSize; ++i) {
                for (int j = 0; j < graphSize; ++j) {
                    cin >> topologicMatrix[i][j];
                }
            }

            vector<bool> visited(graphSize, false);
            stack<int> sortedStack;

            // Call the function for topological sorting
            performTopologicalSort(topologicMatrix, visited, sortedStack);

            cout << "Topologically sorted list of vertices: ";
            while (!sortedStack.empty()) {
                cout << sortedStack.top() << " ";
                sortedStack.pop();
            }
            cout << endl;

            break;
        }

        case 7:
            cout << "Exiting the program. Goodbye!";
            break;

        default:
            cout << "Incorrect choice. Please try again.";
        }
    } while (choice != 4);
    
    Node* current = list1;
    Node* next;
    while (current != NULL) {
        next = current->next;
        delete current;
        current = next;
    }

    current = list2;
    while (current != NULL) {
        next = current->next;
        delete current;
        current = next;
    }
    return 0;
}


