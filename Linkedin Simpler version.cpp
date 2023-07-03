///////////////////////////////////////////////////////////////////////////////////////////////////////////
#include<iostream>
#include<queue>
#include<string>
#include<fstream>
using namespace std;

///////////////////////////////////////// LINKEDIN - DSA PROJECT /////////////////////////////////////////
//------------------------------------- Author : SYED FAISAL ABRAR ---------------------------------------
///////////////////////////////////////////// IN PROGRESS   ///////////////////////////////////////////////
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

///////////////////////////////////////////////////////////////////////////////////////////////////

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
    MessageNode* prev;
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
    void setPrev(MessageNode* prv){
        this->prev = prv;
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
    MessageNode* getPrev(){
        return prev;
    }

};
class Inbox{
    MessageNode* head;
    MessageNode* tail;
    LinkedInProfiles* pro;
public:

    Inbox(): head(NULL), tail(NULL){}
    void addMessage(string msg, string from){

        MessageNode* NewMsg = new MessageNode(msg, from);

        if(head == NULL){
                head = NewMsg;
                tail = NewMsg;
            }
        else    
        {
            MessageNode* temp = tail;
            tail->setNext(NewMsg);
            NewMsg->setPrev(tail);
            tail = NewMsg;
        }  
    }
    // pro->searchByName(from);
    
    void deleteMessage(MessageNode* inboxHead, string from){

        if(inboxHead == NULL){
            cout<<"Inbox Is Empty!"<<endl;
        }
        else{
            MessageNode* head = inboxHead;
            while(head != NULL){

                if(head->getFrom() == from){
                    MessageNode* temp = head->getNext();
                    head->setNext(head->getNext()->getNext());
                    head->getNext()->setPrev(head);
                    delete temp;
                    break;
                }
                else
                    head = head->getNext();
            }
        }
    }

    void displayAllMessages(){
        if(head == NULL){
            cout<<"Inbox is Empty.."<<endl;
        }
        else{

            MessageNode* temp = head;
            while(temp != NULL){

                cout<<"**** ______________________________________________________________________****"<<endl;
                cout<<"________From : "<<temp->getFrom()<<"_______________________________________"<<endl;
                cout<<"Message : _________________________________________________________________"<<endl;
                cout<<temp->getMessage()<<endl;
                cout<<"___________________________________________________________________________"<<endl;

                temp = temp->getNext();
            }
        }

        int choice=0;
        cout<<"Press 1 if you want to go to User Profile , and 0 to exit : ";
        cin>>choice;
        while(1){
            if(choice == 1)
                {
                    string userName = "";
                    cout<<"  Enter User Name from Above to Search : ";
                    cin>>userName;

                    //Searching User In Hash Table......................
                    pro->searchByName(userName);
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

class Message{

public:
    Inbox ibox;
    
    Message(){}
    
    void sendMessage(string message, UserProfile &to){
        if(message != ""){
            to.msg.ibox.addMessage(message, to.user.getName());
        }
        else{
            cout<<"Can't Send.Message Body Is Empty!"<<endl;
        }
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
//////////////////////////////////////////////////////////////////////////////////////////////////
class pNode{
    string publisher;
    string content;
    double postId;
    pNode* next;
public:
    pNode():publisher(""), content(""), postId(0){next=NULL;}
    pNode(string pub, string cont, double ID):publisher(pub), content(cont), postId(ID){next=NULL;}

    string getPublisher(){return publisher;}
    string getContent(){return content;}
    double getID(){return postId;}

    void setNext(pNode* n){
        next = n;
    }
    pNode* getNext(){return next;}
};
class Posts{
    pNode **postArray;
    int size;
    pNode* pn;
    LinkedInPosts* linkPost;
public:
    Posts():size(0){}
    Posts(int size): size(size){
            //Filling empty array with NULL, just for Operational purpose
        for(int i=0; i<size;i++){
            postArray[i] = NULL;
        }
    }
        int HashFunction(int key, int size){
        return key%size;
    }
    void createPost(string publisher, string content, double postId){
        //rehashing occurs when size reaches to 85% of it self.
        if(size == (size/100)*85)
            size = size + ((size/100)*25);
        
        int hashIndex = HashFunction(postId, size);
        pNode* temp = postArray[hashIndex];
        if(temp == NULL)
            temp = new pNode(publisher, content,  postId);
        else{    
            while(temp!= NULL)
                temp = temp->getNext();
            temp->setNext(new pNode(publisher, content,  postId));
        }
        linkPost->postToDatabase(publisher, content, postId);
    }

    void displayPosts(){

    }
    
};
class UserProfile{

public:
    Message msg;
    UserDetails user;
    Certification certif;
    Job job;
    JobHistory jobHist;
    Posts post;
    LinkedInProfiles* linkedinProfiles; 

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
    UserNode **ProfileArr;
    int size;
public:
    LinkedInProfiles(){}
    LinkedInProfiles(int size): size(size){
        //Filling empty array with NULL, just for Operational purpose
        for(int i=0; i<size;i++){
            ProfileArr[i] = NULL;
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
        UserNode* temp = ProfileArr[hashIndex];
        if(temp == NULL)
            temp = new UserNode(name, age, gender, email, ID);
        else{    
            while(temp!= NULL)
                temp = temp->getNext();
            temp->setNext(new UserNode(name, age, gender, email, ID));
        }
    }

    UserNode* searchById(double ID){
        return ProfileArr[0];
    }

    void searchByName(string name){

    }

};
/////////////////////////////////////////////////////////////////////////////////////////////
class postsNode{
    string publisher;
    string content;
    double ID;
    postsNode* next;
public:
    postsNode(){}
    postsNode(string pub, string content, double postID) 
        : publisher(pub), content(content), ID(postID){next=NULL;}
    string getPublisher(){
        return publisher;
    }
    string getContent(){
        return content;
    }
    double getPostId(){
        return ID;
    }
    postsNode* getNext(){
        return next;
    }
    void setNext(postsNode* n){next = n;}
};
class LinkedInPosts{

    postsNode **PostsArr;
    int size;
public:
    LinkedInPosts(){}
    LinkedInPosts(int size): size(size){
        //Filling empty array with NULL, just for Operational purpose
        for(int i=0; i<size;i++){
            PostsArr[i] = NULL;
        }
    }

    int HashFunction(int key, int size){
        return key%size;
    }

    void postToDatabase(string publisher, string content, double postID){

        //rehashing occurs when size reaches to 85% of it self.
        if(size == (size/100)*85)
            size = size + ((size/100)*25);
        
        int hashIndex = HashFunction(postID, size);
        postsNode* temp = PostsArr[hashIndex];
        if(temp == NULL)
            temp = new postsNode(publisher, content, postID);
        else{    
            while(temp!= NULL)
                temp = temp->getNext();
            temp->setNext(new postsNode(publisher, content, postID));
        }
    }

    postsNode* searchById(double ID){
        postsNode* required = PostsArr[int(ID)];

        while(required != NULL){
            if(required->getPostId() == ID){
                return required;
            }
            else
                required->getNext();
        }

        return NULL;
    }
};
////////////////////////////////////////////////////////////////////////////////////////////////////////

class jobsNode{
    string publisher;
    string content;
    double ID;
    jobsNode* next;
public:
    jobsNode(){}
    jobsNode(string pub, string content, double postID) 
        : publisher(pub), content(content), ID(postID){next=NULL;}
    string getPublisher(){
        return publisher;
    }
    string getContent(){
        return content;
    }
    double getJobId(){
        return ID;
    }
    jobsNode* getNext(){
        return next;
    }
    void setNext(jobsNode* n){next = n;}
};
class LinkedInJobs{
jobsNode **JobsArr;
    int size;
public:
    LinkedInJobs(){}
    LinkedInJobs(int size): size(size){
        //Filling empty array with NULL, just for Operational purpose
        for(int i=0; i<size;i++){
            JobsArr[i] = NULL;
        }
    }

    int HashFunction(int key, int size){
        return key%size;
    }

    void postToDatabase(string publisher, string content, double postID){

        //rehashing occurs when size reaches to 85% of it self.
        if(size == (size/100)*85)
            size = size + ((size/100)*25);
        
        int hashIndex = HashFunction(postID, size);
        jobsNode* temp = JobsArr[hashIndex];
        if(temp == NULL)
            temp = new jobsNode(publisher, content, postID);
        else{    
            while(temp!= NULL)
                temp = temp->getNext();
            temp->setNext(new jobsNode(publisher, content, postID));
        }
    }

    jobsNode* searchById(double ID){
        jobsNode* required = JobsArr[int(ID)];

        while(required != NULL){
            if(required->getJobId() == ID){
                return required;
            }
            else
                required->getNext();
        }
        return NULL;
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////
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