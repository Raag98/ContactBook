#include<bits/stdc++.h>
using namespace std;

void printStars() {
  cout << "***************************" << endl;
}

void projCredits() {
  cout << endl << "Project: CONTACT MANAGEMENT SYSTEM \n Made by:\n 1. Paras Aghija (191030) \n 2. Gautam Sachdeva(19103084) \n 3. Anurag Rai(19103065)" << endl;
}

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
  void updatePNo(string old_pno, string new_pno) {
    // if(phone_numbers.empty()) 
    //   phone_numbers.push_back(S);
    // else 
    auto it = find(phone_numbers.begin(), phone_numbers.end(), old_pno);
    *it = new_pno;
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
  Contact* update(string w1, string w2, string old_pno, string new_pno) {
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
    if(temp->person) temp->person->updatePNo(old_pno, new_pno);

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
    Contact *x = T.update(fname, lname,oldpno, newpno);
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

  
  // Trie t;
  // Trie2 t2;

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

  ContactBook contactBook;
  contactBook.insert("Paras", "Aghija", "9999988888", "aghija.paras@gmail.com", "Delhi", "19 August");
  contactBook.insert("Gautam", "Sachdeva", "7777788888", "sachdeva.gautam@gmail.com", "Allahabad", "23 June"); // Update DOB
  contactBook.insert("Anurag", "Rai", "7777766666", "rai.anurag@gmail.com", "Varanasi", "9 August");
  contactBook.insert("Shaan", "Grover", "5555566666", "grover.shaan@gmail.com", "Delhi", "9 August");

  printStars();
  cout << " CONTACT MANAGEMENT SYSTEM" << endl;
  printStars();

  while(1) {
    int opt;
    cout << endl << "Features:\n 1 - Add Contact \n 2 - Delete Contact \n 3 - Search Contact \n 4 - Update Contact \n 5 - All Contacts \n 6 - Project Details \n 7 - Exit" << endl;
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

      case 2: { // Contact Deletion
        string newPno;
        cin >> newPno;
        contactBook.addPhoneNumber("Shaan", "Grover", newPno);
        break;
      }

      case 3: { // Working
        int ch;
        cout << "\t1 - Search by Name\n\t2 - Search by Phone Number\nEnter your choice: ";
        cin >> ch;
        if(ch == 1) {
          string findCont_name;
          cout << "Enter Name of Contact: ";
          cin >> findCont_name;
          // cout << "Enter Last Name of Contact: ";
          // cin >> findCont_lname;
          // findCont_fname += findCont_lname;
          contactBook.findByName(findCont_name);
        }
        else if(ch == 2) {
          string findCont_pno;
          cout << "Enter Phone Number of Contact: ";
          cin >> findCont_pno;
          contactBook.findByPhoneNumber(findCont_pno);
        }
        break;
      }

      case 4: { // Working
        string findCont_fname,findCont_lname, oldPno, newPno;
        cout << "Enter First Name of Contact: ";
        cin >> findCont_fname;
        cout << "Enter Last Name of Contact: ";
        cin >> findCont_lname;

        cout << "Enter Old Phone Number";
        cin >> oldPno;
        cout << "Enter New Phone Number";
        cin >> newPno;

        contactBook.update(findCont_fname, findCont_lname, oldPno, newPno);

        // findCont_fname += findCont_lname;        
        cout << "Contact Updated Successfully!" << endl; 
        contactBook.findByName(findCont_fname);

        break;
      }

      case 5: { // Working
        contactBook.printAllContacts();
        break;
      }

      case 6: { // Working
        projCredits();
        break;
      }

      case 7: { // Working
        cout << "Thank You!!";
        exit(0);
        break;
      }

      default: {
        cout << "Enter a Valid Option";
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