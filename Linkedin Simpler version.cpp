///////////////////////////////////////////////////////////////////////////////////////////////////////////
#include<iostream>
#include<queue>
#include<string>
#include<fstream>
using namespace std;

///////////////////////////////////////// LINKEDIN - DSA PROJECT /////////////////////////////////////////
//------------------------------------- Author : SYED FAISAL ABRAR --------------------------------------
///////////////////////////////////////////////////////////////////////////////////////////////////////////
class ConnectNode{

    ConnectNode* left;
    ConnectNode* right;
    string connectedUser;
    double ID;
public:
    ConnectNode():left(NULL), right(NULL), connectedUser(""), ID(0){}
    ConnectNode(string data, double ID):left(NULL), right(NULL), connectedUser(data), ID(ID){}
    string getConnectedUser(){return connectedUser;}
    double getID(){return ID;}
    ConnectNode* getLeft(){return left;}
    ConnectNode* getRight(){return right;}

    void setId(double uid){this->ID = uid;}
    void setLeft(ConnectNode* left){this->left = left;}
    void setRight(ConnectNode* right){this->right = right;}
    void setConnectedUser(string data){this->connectedUser = data;}
};

//BST For User Connections in LinkedIn..............
class Connections{
    LinkedInProfiles* profiles;
    ConnectNode* root;
public:
        Connections():root(NULL){}
        
    ConnectNode* AddToConnection(ConnectNode* r, string data, double ID){
        if(r == NULL){
                r = new ConnectNode(data, ID);
                return r;
            }

        int status = r->getConnectedUser().compare(data);
        if(status < 0 ){
            AddToConnection(r->getRight(), data, ID);
        }
        else if(status > 0){
            AddToConnection(r->getLeft(), data, ID);
        }
        else
            return r;

        return r;    
    }

    void displayConnections(ConnectNode* r){
        if(r==NULL)
            return;
        int i=0;
        if(i==0){
            cout<<" __________________________________________________________________________________"<<endl;
            cout<<"|                                CONNECTIONS                                       |"<<endl;
        }
        i++;
        displayConnections(r->getLeft());
        cout<<" __________________________________________________________________________________"<<endl;
        cout<<"|-   "<<r->getConnectedUser() <<"  ---------  UID ----> "<<r->getID()<<endl;
        displayConnections(r->getRight());
        int choice=0;
        cout<<"Press 1 if you want to go to User Profile , and 0 to exit : ";
        cin>>choice;
        while(1){
            if(choice == 1)
                {
                    double enteredId = 0;
                    cout<<"  Enter UID from Above to Search : ";
                    cin>>enteredId;

                    //Searching User In Hash Table......................
                    UserNode* uNode = profiles->searchById(enteredId);
                    UserProfile user = uNode->getUser();
                    user.displayData();
                    break;
                }
            else if(choice == 0)
                break;
            else{
                cout<<"_____________________________ Invalid Choice Entered _________________________________"<<endl;
                continue;
            }
        }
    }
};

class UserDetails{
    string name;
    int age;
    char gender;
    string email;
    double userId;
    Connections con;
public:
    UserDetails():name(""), age(0),gender('-'), email(""),userId(0){}
    UserDetails(string name, int age, char gender, string email, double userId){
        this->name = name; this->age = age; this->gender = gender; this->email = email;
        this->userId = userId;
    }

    string getName(){return name;}
    int getAge(){return age;}
    char getGender(){return gender;}
    string getEmail(){return email;}
    double getId(){return userId;}

    void setName(string name){this->name = name;}
    void setAge(int age){this->age = age;}
    void setGender(char gender){this->gender = gender;}
    void setEmail(string email){this->email = email;}
    void setUserId(double id){this->userId = id;}
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////
class MessageNode{
    string message;
    string from;
    MessageNode* next;
public:
    MessageNode(): message(""), from(""),next(NULL){}
    MessageNode(string message, string from ):message(this->message),from(this->from) ,next(NULL){}

    void setMessage(string msg){
        this->message = msg;
    }
    void setFrom(string from){
        this->from = from;
    }
    void setNext(MessageNode* nxt){
        this->next = nxt;
    }
    string getMessage(){
        return message;
    }
    string getFrom(){
        return from;
    }
    MessageNode* getNext(){
        return next;
    }

};
class Inbox{
    MessageNode* front;
    MessageNode* rear;

public:

    Inbox(): front(NULL), rear(NULL){}
    
    void addMessage(Inbox* inbox, string msg, string from){

        MessageNode* NewMsg = new MessageNode(msg, from);

        if(front == NULL)
            inbox->front = NewMsg;
        else    
            inbox->rear->setNext(NewMsg);
        
        inbox->rear = NewMsg;
        inbox->rear->setNext(front);    
    }
    bool checkUser(string from){
        ifstream read;
        read.open("LinkedIn_Users.txt");

        if(read.is_open())
            return false;
        else{

        }
    }
    void deleteMessage(Inbox* inbox, string from){

        if(inbox->front == NULL){
            cout<<"Inbox is Empty.."<<endl;
        }

        if(inbox->front == inbox->rear){
            
            inbox->front= NULL;
            inbox->rear= NULL;
        }
        else{

            MessageNode* temp = inbox->front;

            inbox->front = inbox->front->getNext();
            inbox->rear->setNext(inbox->front);
            delete temp;
        }
        
    }

    void displayAllMessages(Inbox* inbox){
        if(inbox->front != NULL){
            cout<<"Inbox is Empty.."<<endl;
        }
        else{
            MessageNode* temp = inbox->front;
            while(temp->getNext() != inbox->front){

                cout<<"**** ______________________________________________________________________****"<<endl;
                cout<<"________From : "<<temp->getFrom()<<"_______________________________________"<<endl;
                cout<<"Message : _________________________________________________________________"<<endl;
                cout<<temp->getMessage()<<endl;
                cout<<"___________________________________________________________________________"<<endl;
                temp = temp->getNext();
            }
            cout<<"**** ______________________________________________________________________****"<<endl;
            cout<<"________From : "<<temp->getFrom()<<"_______________________________________"<<endl;
            cout<<"Message : _________________________________________________________________"<<endl;
            cout<<temp->getMessage()<<endl;
            cout<<"___________________________________________________________________________"<<endl;
        }
    }

};

class Message{
    Inbox ibox;
    string messageBody;
    
public:
    Message(): messageBody(""){}
    Message( string messageBody){
        this->messageBody= messageBody;
    }
    void sendMessage(string meassage, UserProfile &to){
        
    }

};
///////////////////////////////////////////////////////////////////////////////////////////////////////////
class Job{
    LinkedInJobs lJobs;
public:

};

class JobHistory{
public:


};

class Certification{

public:

};

class UserProfile{

    Message msg;
    UserDetails user;
    Certification certif;
    Job job;
    JobHistory jobHist;
    LinkedInProfiles* linkedinProfiles; 

public:
    UserProfile(){}
    UserProfile(string name, int age, char gender, string email, double userId) 
                : user(name, age, gender, email, userId){}
        // friend ostream& operator<<(ostream &out, const UserProfile &user) {}
    void displayData()
    {
        cout<<" ___________________________________________________________________________________"<<endl;
        cout<<"|  User Name : "<<endl;
    }

    void dashBoard(){

    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////

class UserNode{
    UserProfile userPro;
    UserNode* next;
public:
    UserNode(): userPro(), next(NULL){}
    UserNode(string name, int age, char gender, string email, double userId)
        :userPro(name, age, gender, email, userId), next(NULL){}

    UserProfile getUser(){
        return userPro;
    }
    void setNext(UserNode* next){
        this->next = next;
    }
    UserNode* getNext(){
        return next;
    }

};

class LinkedInProfiles{
    UserNode **arr;
    int size;
public:
    LinkedInProfiles(){}
    LinkedInProfiles(int size): size(size){
        //Filling empty array with NULL, just for Operational purpose
        for(int i=0; i<size;i++){
            arr[i] = NULL;
        }
    }

    int HashFunction(int key, int size){
        return key%size;
    }

    void createAccount(string name, int age, char gender, string email, double ID){

        //rehashing occurs when size reaches to 85% of it self.
        if(size == (size/100)*85)
            size = size + ((size/100)*25);
        
        int hashIndex = HashFunction(ID, size);
        UserNode* temp = arr[hashIndex];
        if(temp == NULL)
            temp = new UserNode(name, age, gender, email, ID);
        else{    
            while(temp!= NULL)
                temp = temp->getNext();
            temp->setNext(new UserNode(name, age, gender, email, ID));
        }
    }

    UserNode* searchById(double ID){
        return arr[0];
    }


};
class LinkedInPosts{

public:

};

class LinkedInJobs{

public:

};

///////////////////////////////////////////////////////////////////////////////////////////////////////////
class LinkedIn{

    LinkedInProfiles* linkedinProfiles;
    LinkedInPosts* lPosts;
    LinkedInJobs* lJobs;
    UserProfile* user;

public:
    LinkedIn(){}
    
    void login(double ID){
        UserNode* Status = linkedinProfiles->searchById(ID);
        if(Status != NULL)
            cerr<<"___________xxxx  User Not Found On LinkedIn   xxxx________"<<endl;
        else{
            //Copy Constructor is Called...........
            UserProfile LoggedIn = Status->getUser();
            LoggedIn.dashBoard();
        }
    }

    
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(){

    

    return 0;
}