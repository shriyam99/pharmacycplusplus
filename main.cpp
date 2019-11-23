#include<bits/stdc++.h>
using namespace std;
#define size 26

struct sales_info{
string person_name;
int quantity;
struct sales_info*next;
};
struct info{
string med_name;
string mfd;
int quantity;
string expiry_date;
int cost;
string date;
struct info*next;
};
struct Node{
struct Node *name[size];
struct info*m;
struct sales_info*k;
bool isend;
};

struct Node*createNode(void)
{
 struct Node*tmp=new Node;
 tmp->isend=false;
 for(int i=0;i<size;i++){
    tmp->name[i]=NULL;
 }
 return tmp;
}
struct info*insert_med_info(string name,int q,string mfg,string expiry,int c){
      struct info*m=new info;
      m->med_name=name;
      m->quantity=q;
      m->mfd=mfg;
      m->expiry_date=expiry;
      m->cost=c;
    return m;
}
struct sales_info*insert_sales_info(struct sales_info*root,string n,int q){

    struct sales_info*m=new sales_info;
    m->person_name=n;
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
struct Node*Insert(struct Node*root,struct info*node,string key){
struct Node*tmp=root;
for(int i=0;i<key.length();i++)
{
    int index=key[i]-'a';
    if(!tmp->name[index])
        tmp->name[index]=createNode();
    tmp=tmp->name[index];
}
   tmp->isend=true;
   tmp->m=node;

}
void print_info(struct info*root,struct sales_info*sroot){
    cout<<"Name Of Medicine"<<"-"<<root->med_name<<'\n';
    cout<<"Cost"<<"-"<<root->cost<<'\n';
    while(sroot){
        cout<<"Name Of Person"<<"  "<<sroot->person_name<<'\n';
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
struct Node*is_present(struct Node *root,string key){
struct Node*tmp=root;
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

int main()
{
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
}
