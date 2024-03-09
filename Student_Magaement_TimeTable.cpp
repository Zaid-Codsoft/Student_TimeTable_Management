// Name : zaid , Section SE-A , Roll No : 22i-2513

 #include <iostream>
#include<fstream>
#include<string>
 #include <vector>
 #include <cstdlib>
 #include <ctime>

using namespace std;

class COURSE {
public:
    string CourseN;
};

class STUDENT {
public:
    int SID;
    string StudentN;
    COURSE Courses[5];
    vector<int> TimeTable[5];
};

class Node {
public:
    STUDENT Student;
    Node* Next;

    Node(STUDENT St) {
        Student = St;
        Next = nullptr;
    }
};

class circularLinkedList {
private:
    Node* head;

public:
    circularLinkedList() {
        head = nullptr;
    }

    void ADDStudent(STUDENT StudentOf) {
        Node* NewNode = new Node(StudentOf);
        if (head == nullptr) {
            head = NewNode;
            NewNode->Next = head;
        }
        else {
            Node* TEMP = head;
            while (TEMP->Next != head) {

                TEMP = TEMP->Next;
            }

            TEMP->Next = NewNode;
            NewNode->Next = head;

        }
    
    }

    void ReMoveStuDent(int ID) {
        if (head == nullptr) {
            cout << "LIST EMPTY\n";
            return;
        }

        Node* TEMP = head;
        Node* PREV = nullptr;

        if (TEMP->Student.SID == ID) {
            Node* LasT = head;
            while (LasT->Next != head){
                LasT = LasT->Next;
            }
                
            LasT->Next = head->Next;
            
            head = head->Next;
           
            delete TEMP;
            return;
        }

        while (TEMP->Next != head && TEMP->Student.SID != ID) {
            
            PREV = TEMP;
            
            TEMP = TEMP->Next;
        }

        if (TEMP->Next == head) {
            cout << "STUDENT ID " << ID << " NOT FOUND\n";
            return;
        }
        PREV->Next = TEMP->Next;
        delete TEMP;
    }

    void Display() {
       
        if ( head == nullptr) {
            cout << "NO STUDENT ENROLLED\n" ;

            return;
        }

        Node* Current = head;
        do {
            cout << "STUDENT ID: " << Current->Student.SID << "    Name: " << Current->Student.StudentN << endl << endl;
            for (int i = 0; i < 5; ++i) {
                cout << "   Course: " << Current->Student.Courses[i].CourseN << "        Timetable: ";
                for (int TIME : Current->Student.TimeTable[i]) {
                    cout << TIME << ":00" << "-"<<TIME+1 << ":00  O'Clock ";
                }
               
                cout << endl;
           
            }
            cout << endl;
            Current = Current->Next;
        } while (Current != head);
    }

    Node* SEARCH(int ID) {
        if (head == nullptr) {
            cout << "LIST EMPTY\n";
            return nullptr;
        }

        Node* Current = head;
        do {
            if (Current->Student.SID == ID) {
                cout << "STUDENT ID " << ID << " FOUND  NAME: " << Current->Student.StudentN << endl;
                return Current;
            }
            Current = Current->Next;
        } while (Current != head);

        cout << "STUDENT ID " << ID << " NOT FOUND...\n" ;
        return nullptr;
    }

    bool CheckConflictTime(const vector<int>& TimeTble, int TIME) {
      
        for (int s : TimeTble) {
            if (s == TIME) {
                return true; 
            }
        }

        return false; 
    }
        void display2() {
        if (head == nullptr) {
            cout << "No students enrolled." << endl;
            return;
        }

        Node* temp = head;
        do {
            cout << "Student ID: " << temp->Student.SID << ", Name: " << temp->Student.StudentN<< ", Courses: ";
            for (int i = 0; i < 5; ++i) {
                cout << temp->Student.Courses[i].CourseN<< " ";
            }
            cout << endl;
            temp = temp->Next;
        } while (temp != head);
    }

    void AutoGenerateTimeTable() {
        if (head == nullptr) {
            cout << "NO STUDENT ENROLLED" << endl;
            return;
        }

        srand(time(nullptr)); 

        Node* Current = head;
        do {
            for (int i = 0; i < 5; ++i) {
                Current->Student.TimeTable[i].clear(); 
                if (Current->Student.Courses[i].CourseN != "\0") {
                    for (int j = 0; j < 1; ++j) {
                        int TIME = rand() % 17 + 1; 

                        while (CheckConflictTime(Current->Student.TimeTable[i], TIME)) {
                            TIME = rand() % 17 + 1;
                        }

                        Current->Student.TimeTable[i].push_back(TIME); 
                    }
                }
            }

            Current = Current->Next;
        } while (Current != head);
    }

    void MakeFile(const string& FILE) {
        ofstream ofile(FILE);
        if (!ofile) {
            cout << "ERROR TO OPEN FILE" << endl;
            return;
        }

        Node* Current = head;
        do {
            ofile << "STUDENT ID: " << Current->Student.SID << "  NAME:  " << Current->Student.StudentN << endl;
            for (int i = 0; i < 5; ++i) {
                ofile << "COURSE: " << Current->Student.Courses[i].CourseN << "       TIMETABLE: ";
                for (int TIME : Current->Student.TimeTable[i]) {
                    ofile << TIME << ":00-" << TIME + 1 << ":00 ";
                }
                ofile << endl;
            }
            ofile << endl;
            Current = Current->Next;
        } while (Current != head);

        ofile.close();
        cout << "DATA WRITTEN INTO FILE : " << FILE << endl;
    }

    

};



int main() {
    circularLinkedList ERS;

    bool CHECK = false;
    while (!CHECK) {
        cout << "\nX---------------X-------------------X-----------------------X-----------------------------X";

        cout << "\n\n------ ENROLLMENT STUDENT SYSTEM ------\n\n";
        cout << "1. ADD STUDENT\n";
        cout << "2. REMOVE STUDENT\n";
        cout << "3. DISPLAY STUDENTS WITH TIME TABLE\n";
        cout << "4. AUTO GENERATE TIMETABLE\n";
        cout << "5. SEARCH STUDENT WITH ID\n";
        cout << "6. WRITE DATA INTO FILE\n";
        cout << "7. EXIT\n";
        cout << "ENTER YOUR CHOICE : ";

        int CHO;
        cin >> CHO;

        switch (CHO) {
        case 1: {
            cout << "ENTER STUDENT ID: ";
            int ID;
            cin >> ID;
            cout << "ENTER STUDENT NAME: ";
            string NAME;
            cin >> NAME;
            cout << "ENTER COURSE (UP TO 5,TYPE 'end' TO STOP):\n";
            vector<string> Courses;
            string COURSE;
            for (int i = 0; i < 5; ++i) {
                cin >> COURSE;
                if (COURSE == "end")
                    break;
                Courses.push_back(COURSE);
            }
            STUDENT newStudent = { ID, NAME };
            
            for (int i = 0; i < Courses.size(); ++i) {
            
                newStudent.Courses[i].CourseN = Courses[i];
            
            }
            
            
            ERS.ADDStudent(newStudent);
            break;
        }
        case 2: {
            cout << "ENTER STUDENT ID TO REMOVE: ";
            int ID;
            cin >> ID;
            ERS.ReMoveStuDent(ID);
            break;
        }
        case 3: {
            ERS.Display();
            break;
        }
        case 4: {
            ERS.AutoGenerateTimeTable();
            cout << "TIMETABLE AUTO GENERATED.\n";
            break;
        }
        case 5: {
            cout << "ENTER STUDENT ID TO SEARCH: ";
            int id;
            cin >> id;
            ERS.SEARCH(id);
            break;
        }
        case 6: {
            string filename;
            cout << "ENTER FILENAME TO WRITE DATA: ";
            cin >> filename;
            ERS.MakeFile(filename);
            break;
        }
        
        case 7: {
            CHECK = true;
            break;
        } 
        default: {
            cout << "INVALID CHOICE TRY AGAIN....\n";
            break;
        }
        }
    }

    return 0;
}

