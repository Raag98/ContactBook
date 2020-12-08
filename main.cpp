#include<bits/stdc++.h>
using namespace std;

string upperToLower(string S) {
  for(auto i = S.begin(); i != S.end(); i++) {
    if(*i >= 65 && *i <= 90)
      *i += 32;
  }
  return S;
}

class Contact {
  string fname, lname, email, address, bday;
  vector<string> phone_numbers;

public:

  // Constructor 
  Contact(string fname, string lname, string pno, string email, string address, string bday) {
    this->fname = fname;
    this->lname = lname;
    this->phone_numbers.push_back(pno);
    this->email = email;
    this->address = address;
    this->bday = bday;
  }

  // string getfName() {
  //   return fname;
  // }

  // string getlName() {
  //   return lname;
  // }

  // string geteMail() {
  //   return email;
  // }  

  // string getaddress() {
  //   return address;
  // }

  // string getbDay() {
  //   return bday;
  // }

  vector<string> getPNo() {
    return phone_numbers;
  }

//  Updates Phone No.
  void updatePNo(string S) {
    // if(phone_numbers.empty()) 
    //   phone_numbers.push_back(S);
    // else 
    phone_numbers[0] = S;
  }

  
  // Add another Phone No.
  void addPhone(string pno){
    phone_numbers.push_back(pno);
  }

  // Prints All Details
  void printDetails(){
    cout << "Name : " << fname << " " << lname << endl;
    cout << "Phone Number : ";
    for(auto pno : phone_numbers)
      cout << pno << ", ";
    cout << endl;
    cout << "E-Mail : " << email << endl;
    cout << "Address : " << address << endl;
    cout << "Birthday : " << bday << endl;
    cout << endl;
  }
};



class Node{

public:
  char data;
  map<char, Node*> children;
  Contact* person;  // acts as bool terminal

  Node(char d){
    data = d;
    person = NULL;
  }
};



class Trie{
  Node* root;
  int count;

public:
  Trie() { 
    root = new Node('\0');
    count = 0;
  }

  Contact* insert(string fname, string lname, string pno, string email, string address, string bday) {
    string w = fname + lname;
    w = upperToLower(w);
    Node* temp = root;
    for(auto ch : w) {
      if(temp->children.count(ch)){
        temp = temp->children[ch];
      }
      else{
        Node* n = new Node(ch);
        temp->children[ch] = n;
        temp = n;
      }
    }
    temp->person = new Contact(fname, lname, pno, email, address, bday);
    return temp->person;
  }

  void printAllBelow(Node* root){
    if(root == NULL) root = this->root; 

    if(root->person) root->person->printDetails();

    for(auto pair : root->children){
      if(pair.second) printAllBelow(pair.second);
    }
  }

  void find(string w){
    Node* temp = root;
    w = upperToLower(w);
    for(auto ch : w){
      if(temp->children.count(ch) == 0) {
        cout << "Contact Not Found" << endl;
        return;
      }
      else 
        temp = temp->children[ch];
    }
    printAllBelow(temp);
    // if(temp->person != NULL) temp->person->printDetails();
  }

  // Update Phone Number Function
  Contact* update(string w1, string w2, string new_pno) {
    string w = w1 + w2;
    w = upperToLower(w);
    Node* temp = root;
    for(auto ch : w){
      if(temp->children.count(ch) == 0) {
        cout << "Contact Does not Exist" << endl;
        return NULL;
      }
      else temp = temp->children[ch];        
    }
    if(temp->person) temp->person->updatePNo(new_pno);

    return temp->person;
  }

  Contact* addPhoneNumber(string w1, string w2, string new_pno) {
    string w = w1 + w2;
    w = upperToLower(w);
    Node* temp = root;
    for(auto ch : w) {
      if(temp->children.count(ch) == 0){
        cout << "Contact Does not Exist." << endl;
        return NULL;
      }
      else temp = temp->children[ch];        
    }
    if(temp->person) temp->person->addPhone(new_pno);

    return temp->person;
  }
};



class Trie2 {
  Node* root;
  int count;

public:

  Trie2() {
    root = new Node('x');
    count = 0;
  } 

  void insert(string pno, Contact* s) {
    string w = pno;
    Node* temp = root;
    for(auto ch : w) {
      if(temp->children.count(ch))
        temp = temp->children[ch];
      else {
        Node* n = new Node(ch);
        temp->children[ch] = n;
        temp = n;
      }
    }
    temp->person = s;
  }

  void printAllBelow(Node *root){
    if(root->person)
      root->person->printDetails();

    for(auto pair : root->children){
      if(pair.second)
        printAllBelow(pair.second);
    }

    cout<<"No More Contacts exists." << endl;
  }

  void find(string w) {
    Node* temp = root;
    for(auto ch : w) {
      if(temp->children.count(ch) == 0) {
        cout << "Contact Not found" << endl;
        return;
      }
      else{
        temp = temp->children[ch];
      }
    }
    printAllBelow(temp);
    // if(temp->person != NULL){
    //   temp->person->printDetails();
    // }
  }

  bool isEmpty(Node* root) 
  { 
    for (int i = 0; i < 10; i++) 
      if (root->children[i]) 
        return false; 
    return true; 
  } 

  void breakLink(string w){
    Node *temp = root;
    for(auto ch : w){
      if(temp->children.count(ch) == 0){
        cout<<"Contact Not Found!!"<<endl;
        return;
      }
      else{
        temp = temp->children[ch];
      }
    }
    temp->person = NULL;
  }

  void update(string oldNo, string newNo, Contact *s){
      breakLink(oldNo);
      insert(newNo, s);
   }      
};

class ContactBook {
  Trie T;
  Trie2 T2;

public:

  void insert(string fname, string lname, string pno, string email, string address, string bday) {
    Contact *x = T.insert(fname, lname, pno, email, address, bday);
    T2.insert(pno, x);
  }

  void update(string fname, string lname, string oldpno, string newpno) {
    Contact *x = T.update(fname, lname, newpno);
    T2.update(oldpno, newpno, x);
  }

  void findByName(string w) {
    T.find(w);
  }

  void findByPhoneNumber(string w) {
    T2.find(w);
  }

  void addPhoneNumber(string fname, string lname, string pno) {
    Contact *x = T.addPhoneNumber(fname, lname, pno);
    if(x != NULL){
      T2.insert(pno, x);
    }
  }

  void printAllContacts(){
    T.printAllBelow(NULL);
  }
};


// Driver Code
int main(){

  // string fname1 = "Anurag";
  // string lname1 = "Rai";
  // string phone1 = "99887766";
  // string email1 = "anumeraraag@gmail.com";
  // string add1 = "123-/35 B";
  
  // string fname2 = "Gautam";
  // string lname2 = "Sir";
  // string phone2 = "999888888";
  // string email2 = "gautamsir@gmail.com";
  // string add2 = "111-/22222 B";
  
  // string fname3 = "Paras";
  // string lname3 = "Aghija";
  // string phone3 = "111111111";
  // string email3 = "paras@gmail.com";
  // string add3 = "3333-/6666 B";

  // string fname4 = "Shaan";
  // string lname4 = "Chu";
  // string phone4 = "666666999999";
  // string email4 = "shaanthegandu@gmail.com";
  // string add4 = "Kotha 69, GB Road";

  // string fname5 = "Shaan";
  // string lname5 = "lodu";
  // string phone5 = "2222222222222";
  // string email5 = "shaanlodulalit@gmail.com";
  // string add5 = "Kotha 96, GB Road";
  


  

  // Trie t;
  // Trie2 t2;

  // Contact *a1 = t.insert(fname1,lname1,phone1,email1);
  // Contact *a2 = t.insert(fname2,lname2,phone2,email2);
  // Contact *a3 = t.insert(fname3,lname3,phone3,email3);
  // Contact *a4 = t.insert(fname4,lname4,phone4,email4);
  // Contact *a5 = t.insert(fname5,lname5,phone5,email5);

  // t2.insert(phone1,a1);
  // t2.insert(phone2,a2);
  // t2.insert(phone3,a3);
  // t2.insert(phone4,a4);
  // t2.insert(phone5,a5);

  // t.find("Shaan");
  
  // t.find("Anurag");

  // t.update("Anurag", "Rai", "9807075828");

  // t.find("Anurag");

  // t.addPhoneNumber("Anurag", "Rai", "1111111111");

  // t.find("Anurag");

  // string st = "AnUrAg";
  // string st2 = upperToLower(st);
  // cout << st2;

  // t2.find("111111111");
  // Contact *x = t.update("Paras", "Aghija", "0000000000");
  // t2.update("111111111","0000000000", x);
  // t.find("Paras");
  // t2.find("111111111");

  // y.findByName("Anurag");
  // y.findByPhoneNumber("666666999999");
  // y.findByPhoneNumber("99887766");

  // y.update("Anurag", "Rai", "99887766", "0000000000");

  // y.findByName("Anur");
  // y.findByPhoneNumber("0000000000");

  // y.addPhoneNumber("Anurag", "Rai", "9807075828");
  // y.findByName("Anu");
  // y.findByPhoneNumber("0000000000");

  // contactBook.printAllContacts();

  ContactBook contactBook;
  contactBook.insert("Paras", "Aghija", "9999988888", "aghija.paras@gmail.com", "Delhi", "19 August");
  contactBook.insert("Gautam", "Sachdeva", "7777788888", "sachdeva.gautam@gmail.com", "Allahabad", "23 June"); // Update DOB
  contactBook.insert("Anurag", "Rai", "7777766666", "rai.anurag@gmail.com", "Varanasi", "9 August");
  contactBook.insert("Shaan", "Grover", "5555566666", "grover.shaan@gmail.com", "Delhi", "9 August");


  cout << "***************************" << endl << " CONTACT MANAGEMENT SYSTEM" << endl << "***************************" << endl;

  while(1) {
    int opt;
    cout << endl << "Features:\n 1 - Add Contact \n 2 - Delete Contact \n 3 - Search Contact \n 4 - Update Contact \n 5 - All Contacts \n 6 - Exit" << endl;
    cout << "Enter your Choice: ";
    cin >> opt; 

    switch(opt) {
      case 1: {
        string cont[6];
        cout << "Enter First Name: ";
        cin >> cont[0];
        cout << "Enter Last Name: ";
        cin >> cont[1];
        cout << "Enter Phone Number: ";
        cin >> cont[2];
        cout << "Enter E-Mail: ";
        cin >> cont[3];
        cout << "Enter Address: ";
        cin >> cont[4];
        cout << "Enter First Name: ";
        cin >> cont[5];
        contactBook.insert(cont[0], cont[1], cont[2], cont[3], cont[4], cont[5]);
        cout << "Contact Created Successfully!";
        break; 
      }

      case 2: {
        // Contact Deletion
        break;
      }

      case 3: { // Working
        string findCont_fname,findCont_lname;
        cout << "Enter First Name of Contact: ";
        cin >> findCont_fname;
        cout << "Enter Last Name of Contact: ";
        cin >> findCont_lname;
        findCont_fname += findCont_lname;
        contactBook.findByName(findCont_fname);
        break;
      }

      case 4: {
        string findCont_fname,findCont_lname, newPno;
        cout << "Enter First Name of Contact: ";
        cin >> findCont_fname;
        cout << "Enter Last Name of Contact: ";
        cin >> findCont_lname;
        findCont_fname += findCont_lname;
        cout << "Enter New Phone Number";
        cin >> newPno;
        
        break;
      }

      case 5: { // Working
        contactBook.printAllContacts();
        break;
      }

      case 6: { // Project Credits
        // Group Members.
        break;
      }

      case 7: { // Working
        cout << "Thank You!!";
        exit(0);
        break;
      }

      default: {
        cout << "Enter Valid Option";
        break;
      }
    }


  }

  return 0;
}

/*

TODO: Choice, 
      Contact Delete,
*/