#include <bits/stdc++.h>
#include <fstream>
using namespace std;
#define size1 26

struct sales_info{
    string fname;
    string lname;
    int age;
    int quantity;
    struct sales_info* next;
};


struct medic_name{
    string name;
    medic_name *next;
};

struct diseases{
    string d_name;
    medic_name* medics;
    diseases* next;
};


struct info{
    string med_name;
    string mfd;
    int quantity;
    string expiry_date;
    int cost;
    info* next;
};

diseases* data = NULL;

struct Node{
    Node *name[size1];
    info*m;
    sales_info*k;
    bool isend;
};

Node* createNode() {
     Node*tmp=new Node;
     tmp->isend=false;
     for(int i=0;i<size1;i++){
        tmp->name[i]=NULL;
     }
     return tmp;
}

info* insert_med_info(string name,int q,string mfg,string expiry,int c){
    info*m=new info;
    m->med_name=name;
    m->quantity=q;
    m->mfd=mfg;
    m->expiry_date=expiry;
    m->cost=c;
    return m;
}

sales_info* insert_sales_info(struct sales_info*root,string f, string l, int age, int q){

    sales_info* m=new sales_info;
    m->age = age;
    m->fname = f;
    m->lname = l;
    m->quantity=q;
    if(root==NULL){
        root=m;
        root->next=NULL;
    }
    else{
        m->next=root;
        root=m;
    }
    return root;
}

Node* Insert(struct Node*root,struct info*node,string key){

    Node* tmp=root;
    for(int i=0;i<key.length();i++) {
        int index=key[i]-'a';
        if(!tmp->name[index])
            tmp->name[index]=createNode();
        tmp=tmp->name[index];
    }
       tmp->isend=true;
       tmp->m=node;
}

void print_info(info* root, sales_info* sroot){
    cout<<"Name Of Medicine"<<"-"<<root->med_name<<'\n';
    cout<<"Cost"<<"-"<<root->cost<<'\n';
    while(sroot){
        cout<<"Name Of Person  "<<sroot->fname<<" "<<sroot->lname<<'\n';
        cout<<"Age Of Person "<<sroot->age<<endl;
        cout<<"Quantity"<<"  "<<sroot->quantity<<'\n';
        sroot=sroot->next;
    }
}

void print_med_info(struct info*root){
   cout<<"Name Of Medicine"<<"-"<<root->med_name<<'\n';
   cout<<"Cost"<<"-"<<root->cost<<'\n';
   cout<<"Manufacturing Date"<<"-"<<root->mfd<<'\n';
   cout<<"Expiry Date"<<"-"<<root->expiry_date<<'\n';
   cout<<"Quantity"<<"-"<<root->quantity<<'\n';
}

Node* is_present(struct Node *root,string key){
    Node*tmp=root;
    for(int i=0;i<key.length();i++){
        int index=key[i]-'a';
        if(!tmp->name[index])
            return NULL;
         tmp=tmp->name[index];
    }
    if(tmp!=NULL&&tmp->isend)
        return tmp;
    else
       return NULL;
}


//loads data from file and makes a multilinkedlist;
void loadData(){
    ifstream dfile;
    dfile.open("diseases.txt");
    string str;
    while (getline(dfile, str)) {
        char temp[20];
        vector<string> s;
        int k=0;
        for(int i=0; i<str.length(); i++){
            k=0;
            while(str[i]!=' ' && i<str.length()){
                temp[k] = str[i];
                i++;
                k++;
            }
            temp[k] = '\0';
            s.push_back(string(temp));
        }
        diseases* ptr = new diseases;
        medic_name *med = new medic_name;
        med->name = s[1];
        med->next = NULL;
        ptr->d_name = s[0];
        ptr->next = NULL;
        ptr->medics = med;
        if(data==NULL)
            data = ptr;
        else{
            diseases* temp = data;
            while(temp->next!=NULL)
                temp = temp->next;
            temp->next = ptr;
        }

        for(int i=2; i<s.size(); i++){
           medic_name *ptr2 = new medic_name;
           ptr2->name = s[i];
           ptr2->next=  NULL;
           med->next = ptr2;
           med = med->next;
        }
    }

}

//prints data from multilinkedlist;
void printalldata(){
diseases *ptr = data;
medic_name *ptr2;
while(ptr!=NULL){
    ptr2 = ptr->medics;
    cout<<ptr->d_name<<" ";
    while(ptr2!=NULL){
        cout<<ptr2->name<<" ";
        ptr2 = ptr2->next;
    }
    cout<<endl;
    ptr= ptr->next;
}
}



bool loginCustomer(){
    FILE *loginfile = fopen("login.txt", "r");
    char loginid[20], password[20], fname[20], lname[20];
    int age, quantity;
    string tempid, temppass;
    cout<<"Enter your user name:"<<endl;
    cin>>tempid;
    cout<<"Enter your password:"<<endl;
    cin>>temppass;
    if (loginfile==NULL) {
        cout << "Unable to open file login.txt"<<endl;
        return false;
    }
    bool flag = true;
    while (!feof(loginfile)) {
        fscanf(loginfile, "%s %s %s %s %d %d\n", loginid, password, fname, lname, &age, &quantity);
        if(tempid==loginid && temppass==password){
            flag = false;
            break;
        }
    }
    if(flag==false){
        cout<<"Hello, "<<tempid<<endl;
    }
    else{
        cout<<"User not found!!"<<endl;
        fclose(loginfile);
        return false;
    }
    fclose(loginfile);
    return true;
}

bool registerCustomer(){

    FILE *loginfile = fopen("login.txt", "a");
    char loginid[20], password[20], fname[20], lname[20];
    int age, quantity;
    cout<<"Enter your user name:"<<endl;
    cin>>loginid;
    cout<<"Enter your password:"<<endl;
    cin>>password;
    cout<<"Enter your First Name:"<<endl;
    cin>>fname;
    cout<<"Enter your Last Name:"<<endl;
    cin>>lname;
    cout<<"Enter your Age:"<<endl;
    cin>>age;
    cout<<"Enter quantity of medicine required:"<<endl;
    cin>>quantity;
    if (loginfile==NULL) {
        cout << "Unable to open file login.txt"<<endl;
        return false;
    }
    fprintf(loginfile, "%s %s %s %s %d %d\n", loginid, password, fname, lname, age, quantity);
    fclose(loginfile);
    return true;
}

bool loginSeller(){
    FILE *loginfile = fopen("loginseller.txt", "r");
    char loginid[20], password[20], fname[20], lname[20];
    int age;
    string tempid, temppass;
    cout<<"Enter your user name:"<<endl;
    cin>>tempid;
    cout<<"Enter your password:"<<endl;
    cin>>temppass;
    if (loginfile==NULL) {
        cout << "Unable to open file login.txt"<<endl;
        return false;
    }
    bool flag = true;
    while (!feof(loginfile)) {
        fscanf(loginfile, "%s %s %s %s %d\n", loginid, password, fname, lname, &age);
        if(tempid==loginid && temppass==password){
            flag = false;
            break;
        }
    }
    if(flag==false){
        cout<<"Hello, "<<tempid<<endl;
    }
    else{
        cout<<"User not found!!"<<endl;
        fclose(loginfile);
        return false;
    }
    fclose(loginfile);
    return true;
}

bool registerSeller(){

    FILE *loginfile = fopen("loginseller.txt", "a");
    char loginid[20], password[20], fname[20], lname[20];
    int age;
    cout<<"Enter your user name:"<<endl;
    cin>>loginid;
    cout<<"Enter your password:"<<endl;
    cin>>password;
    cout<<"Enter your First Name:"<<endl;
    cin>>fname;
    cout<<"Enter your Last Name:"<<endl;
    cin>>lname;
    cout<<"Enter your Age:"<<endl;
    cin>>age;

    if (loginfile==NULL) {
        cout << "Unable to open file login.txt"<<endl;
        return false;
    }
    bool flag = true;
    fprintf(loginfile, "%s %s %s %s %d\n", loginid, password, fname, lname, age);
    fclose(loginfile);
    return true;
}

int main() {
    loadData();
    cout<<"WELCOME TO INDIGO PHARMACY!!"<<endl<<endl;
    char input;
    sellorcust:
    cout<<"Press 'q' at any state of program to exit"<<endl<<endl;
    cout<<"Are u a customer or a seller:"<<endl;
    cout<<"Press '1' for CUSTOMER or '2' for SELLER"<<endl;
    cin>>input;
    if(input=='1'){
        // customer
        accoutinfo1:
        char haveAnAccount  = 'y';
        cout<<"Do u have an account? (y/n)"<<endl;
        cin>>haveAnAccount;
        if(haveAnAccount=='y'){
            // customer has an account;
            bool res = loginCustomer();
            if(res==false){
                goto accoutinfo1;
            }
        }
        else if(haveAnAccount=='n'){
            // customer does not have an account;
            bool res = registerCustomer();
            if(res==false)
                goto accoutinfo1;
        }
        else if(haveAnAccount=='q')
            exit(0);
        else{
            goto accoutinfo1;
        }

        //asking for customer diseases;
        askingDisease:
        cout<<"Tell us about your disease we will offer you some medicines"<<endl;
        string d;
        cin>>d;
        diseases *ptr = data;
        while(ptr!=NULL && ptr->d_name!=d)
            ptr = ptr->next;
        if(ptr!=NULL){
            medic_name *ptr2 = ptr->medics;
            while(ptr2!=NULL){
                cout<<ptr2->name<<" ";
                ptr2 = ptr2->next;
            }
            cout<<endl;
            cout<<"Type the medicine name you want and its quantity: "<<endl;
            string medname;
            int q;
            cin>>medname>>q;
            /*
            Now we have to update the data in the trie to change the quantity and then upload updated quantity in the file;

            */
            cout<<"Transaction was a success!! Your order will be delivered soon"<<endl;

        }
        else{
            cout<<"Sorry your disease is not listed in our database try again!!"<<endl;
            goto askingDisease;
        }


    }
    else if(input=='2'){
        // seller
        accoutinfo2:
        char haveAnAccount  = 'y';
        cout<<"Do u have an account? (y/n)"<<endl;
        cin>>haveAnAccount;
        if(haveAnAccount=='y'){
            // seller has an account;
            bool res = loginSeller();
            if(res ==false)
                goto accoutinfo2;
        }
        else if(haveAnAccount=='n'){
            // seller does not have an account;
            bool res = registerSeller();
            if(res ==false)
                goto accoutinfo2;
        }
        else if(haveAnAccount=='q')
            exit(0);
        else{
            goto accoutinfo2;
        }

    }
    else if(input=='q')
        exit(0);
    else
        goto sellorcust;






    /*
   string s[]={"abc","bde","abdec"};
   string s1;
   struct Node*root=createNode();
   for(int i=0;i<3;i++){
    struct info*tmp=NULL;
    tmp=insert_med_info(s[i],10,"12-03-1999","12-03-2005",40);
    Insert(root,tmp,s[i]);
   }string name;
   for(int i=0;i<3;i++){
        cout<<"Enter The Name Of Medicine"<<'\n';
        cin>>s1;
    struct Node*m1=is_present(root,s1);
    if(m1){ print_med_info(m1->m);
    cout<<"1)-Want To Buy"<<'\n';
    cout<<"2)-Quit"<<'\n';
    int c;cin>>c;
    if(c){
    cout<<"Enter Your Name"<<'\n';
    cin>>name;
    struct sales_info*tmp=NULL;
    tmp=insert_sales_info(tmp,name,m1->m->quantity);
    m1->k=tmp;
      }
    cout<<"Thank You For Buying"<<'\n';
    cout<<"1)-To Search Another Medicine"<<'\n';
    cout<<"2)-To Quit"<<'\n';
    cin>>c;
    if(c==1)
        continue;
    else
        break;
    }
   else{ int c;
    cout<<"This Medicine Is Not Available"<<'\n';
    cout<<"1)-To Search Another Medicine"<<'\n';
    cout<<"2)-To Quit"<<'\n';
    cin>>c;
    if(c==1)
        continue;
    else
        break;
   }
   }
   string s2;
   cout<<"Enter Name Of Medicine To See Sales Record"<<'\n';
   cin>>s2;
   struct Node*tmp=is_present(root,s2);
   print_info(tmp->m,tmp->k);

   */
}
