#include <iostream>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>
using namespace std;

//Number of employees engaged with the callers
int fre=0;

//Total number of employees
int total_employees=16;

//Employee information
class Employee
{
    public:
        string name;
        int age;
        string address;
        Employee()
        {
            name="\0";
            age=0;
            address="\0";
        }
        Employee(string Name,int Age,string Address)
        {
            name=Name;
            age=Age;
            address= Address;
        }
        void Display_Employee();

};
void Employee::Display_Employee()
{
    cout<<"\nName: "<<name;
    cout<<"\nAge: "<<age;
    cout<<"\nAddress: "<<address;
    cout<<endl;
}

//Respondent
class Respondent:public Employee
{
    int rank;
   public :
     Respondent()
   {
      cout << "Respondent class default constructor\n";
   }
    Respondent(string Name,int Age,string Address):Employee(Name,Age,Address)
   {
        int rank=0;
   }
   void Display()
   {
       cout<<"\nOccupation: Respondent";
       Display_Employee();
   }
};

//Manager
class Manager:public Employee
{
    int rank;
   public:
    Manager()
   {
      cout << "Manager class default constructor\n";
   }
   Manager(string Name,int Age,string Address):Employee(Name,Age,Address)
   {
        int rank=1;
   }
   void Display()
   {
       cout<<"\nOccupation: Manager";
       Display_Employee();
   }
};

//Director
class Director:public Employee
{
    int rank;
   public:
    Director()
   {
      cout << "Director class default constructor\n";
   }
    Director(string Name,int Age,string Address):Employee(Name,Age,Address)
   {
        int rank=2;
   }
   void Display()
   {
       cout<<"\nOccupation: Director";
       Display_Employee();
   }
};

//Caller information
class Caller
{
    public:
    string name;
    string phone;
    string address;
        Caller()
        {
            name="\0";
            address="\0";
            phone="\0";
        }
        void Assign(string,string,string);
        void display();
};
void Caller::Assign(string Name,string ph,string Address)
{
      name=Name;
      address=Address;
      phone=ph;
}
void Caller::display()
{
    cout<<"\n\t\tName: "<<name;
    cout<<"\n\t\tPhone number: "<<phone;
    cout<<"\n\t\tAddress: "<<address;
}

// call information
class Call:public Caller
{
public:
        string query;
        void Caller_details(string Query,string Name,string ph,string Address)
        {
            query=Query;
            Assign(Name,ph,Address);
        }
        void Display()
        {
            display();
            cout<<"\n\t\tQuery is "<<query;

        }

};
//Waiting list contains waiting call objects
struct node
{
    Call *object;
    struct node *next;
};
typedef struct node *waitingL;

//Respondent list contains all the respondents information with assigned call objects
struct node1
{
    Respondent *receiving;
    Call *calling;
    struct node1 *next;
};
typedef struct node1 *RespondentL;
//Manager list contains all the managers information with assigned call objects
struct node2
{
    Manager *receiving;
    Call *calling;
    struct node2 *next;
};
typedef struct node2 *ManagerL;
//Director list contains all the Directors information with assigned call objects
struct node3
{
    Director *receiving;        // director object
    Call *calling;              // call object
    struct node3 *next;
};
typedef struct node3 *DirectorL;

//Handling of calls which has call object with assigned call and end call function
class Callhandler
{
  public:
      Call *obj;
      waitingL Assign_Call(RespondentL res, ManagerL man,DirectorL dir,waitingL wait);
      waitingL Endcall(string ph,RespondentL res,ManagerL man,DirectorL dir,waitingL wait);
};
// assigned to respondent or manager or director based on avaliability
waitingL Callhandler ::Assign_Call(RespondentL res, ManagerL man,DirectorL dir,waitingL wait)
{
        waitingL wait12 = wait;
        RespondentL tempo=res;
        // Respondent or manager or director is not free then assigned to waiting list
        if(fre==total_employees || fre>total_employees)
        {
            if(wait!=NULL)
            {
           waitingL wait_call = (struct node*) malloc(sizeof(struct node));
            wait_call->object=obj;
            wait_call->next=NULL;
            while(1)
            {
                if(wait->next==NULL)
                {
                    wait->next=wait_call;
                    break;
                }
                else
                {
                    wait=wait->next;
                }
            }
            return wait12;
            }
            else
            {
                waitingL temp=(struct node*)malloc(sizeof(struct node));
                wait=temp;
                wait->object=obj;
                wait->next=NULL;
                return wait;
            }
        }
        else
        {
            // assigned to respondent if any one respondent is free
            int z=0;
            while(res->next!=NULL)
            {
                if(res->calling==NULL)
                {
                    z++;
                    res->calling=obj;
                    break;
                }
                else
                {
                    res=res->next;
                }
            }
            if(z==0)
            {
                 //assigned to manager if all respondents are handling the calls
                while(man->next!=NULL)
                {
                    if(man->calling==NULL)
                    {
                        z++;
                        man->calling=obj;
                        break;
                    }
                    else
                    {
                        man=man->next;
                    }
                }
            }
            if(z==0)
            {
                //assigned to director if all respondents and managers are handling the calls
                while(dir->next!=NULL)
                {
                    if(dir->calling==NULL)
                    {
                        z++;
                        dir->calling=obj;
                        break;
                    }
                    else
                    {
                        dir=dir->next;
                    }
                }
            }
            fre++;
                 // Printing the assigned call information after each assignment
            for(int i=0;i<fre;i++)
            {
              cout<<(*(tempo->calling)).phone<<endl;
              cout<<(*(tempo->calling)).name<<endl;
              cout<<(*(tempo->calling)).address<<endl;
              cout<<(tempo->calling)->query<<endl;
              if((tempo->next)!=NULL)
                tempo=tempo->next;
              cout<<endl;
            }
            return wait;
        }
}

//Ending the appropriate calls based on the phone number request
waitingL Callhandler::Endcall(string ph,RespondentL res,ManagerL man,DirectorL dir,waitingL wait)
{
        int z=0;
        RespondentL res1=res;
        ManagerL man1=man;
        DirectorL dir1=dir;

        // search the call in respondents and if available end the call.

        while(res1!=NULL)
        {
            if((res1->calling!=NULL) && ((*(res1->calling)).phone)==ph)
            {
                res1->calling=NULL;

                if(wait!=NULL)
                {
                waitingL t1=wait;
                Call *t2=wait->object;
                obj=t2;
                if(wait->next!=NULL)
                   { wait=wait->next;
                    wait=Assign_Call(res,man,dir,wait);
                   }
                else
                    wait=NULL;
                free(t1);
                }
                else
                {
                    fre--;
                    cout<<fre;
                }
                return wait;
            }
            else
            {
                if(res1->next!=NULL)
                    res1=res1->next;
                else
                    res1=NULL;
            }
        }
        // if the call is assigned to manager then end the call
       while(man1!=NULL)
        {
            if((man1->calling!=NULL) && (*(man1->calling)).phone==ph)
            {
                man1->calling=NULL;
                if(wait!=NULL)
                {
                waitingL t1=wait;
                Call *t2=wait->object;
                if(wait->next!=NULL)
                {
                    wait=wait->next;
                     obj=t2;
                    wait=Assign_Call(res,man,dir,wait);
                }
                else
                    wait=NULL;
                free(t1);
                }
                else
                {
                    fre--;
                }
                return wait;
            }
            else
            {
                if(man1->next!=NULL)
                    man1=man1->next;
                else
                    man1=NULL;
            }
        }
                // if the call is assigned to director then search and delete the call
        while(dir1!=NULL)
        {
            if((dir1->calling!=NULL) && (*(dir1->calling)).phone==ph)
            {
                dir1->calling=NULL;
                if(wait!=NULL){
                waitingL t1=wait;
                Call *t2=wait->object;
                if(wait->next!=NULL)
                {
                    wait=wait->next;
                    obj=t2;
                    wait=Assign_Call(res,man,dir,wait);
                }
                else
                    wait=NULL;
                free(t1);
                }
                else
                {
                    fre--;
                }
                return wait;
            }
            else
            {
                if(dir1->next!=NULL)
                    dir1=dir1->next;
                else
                    dir1=NULL;
            }
        }
        cout<<"\n\tThe requested number is not engaged with the call center"<<endl<<endl<<endl;
        return wait;
}



int main()
{
    //Storing the respondent informations into the respondent list.

    Respondent a("Sukesh",23,"Rajapalayam");
    RespondentL res_head=(RespondentL)malloc(sizeof(struct node1));
    res_head->receiving=&a;
    res_head->calling=NULL;
    Respondent b("Sharu",19,"Sivakasi");
    RespondentL resp=(RespondentL)malloc(sizeof(struct node1));
    res_head->next=resp;
    resp->receiving=&b;
    resp->calling=NULL;
    Respondent c("Kishore",19,"Madurai");
    RespondentL resp1=(RespondentL)malloc(sizeof(struct node1));
    resp->next=resp1;
    resp1->receiving=&c;
    resp1->calling=NULL;
    Respondent d("SriVani",19,"Theni");
    RespondentL resp2=(RespondentL)malloc(sizeof(struct node1));
    resp1->next=resp2;
    resp2->receiving=&d;
    resp2->calling=NULL;
    Respondent e("Sanjita",19,"Rajapalayam");
    RespondentL resp3=(RespondentL)malloc(sizeof(struct node1));
    resp2->next=resp3;
    resp3->receiving=&e;
    resp3->calling=NULL;
    Respondent f("Krithika",21,"Dindigul");
    RespondentL resp4=(RespondentL)malloc(sizeof(struct node1));
    resp3->next=resp4;
    resp4->receiving=&f;
    resp4->calling=NULL;
    Respondent g("Venkatesh",22,"California");
    RespondentL resp5=(RespondentL)malloc(sizeof(struct node1));
    resp4->next=resp5;
    resp5->receiving=&g;
    resp5->calling=NULL;
    Respondent h("Kavin",50,"Neyveli");
    RespondentL resp6=(RespondentL)malloc(sizeof(struct node1));
    resp5->next=resp6;
    resp6->receiving=&h;
    resp6->calling=NULL;
    Respondent i("Harish",36,"Chennai");
    RespondentL resp7=(RespondentL)malloc(sizeof(struct node1));
    resp6->next=resp7;
    resp7->receiving=&i;
    resp7->calling=NULL;
    Respondent j("Thilak",31,"Coimbatore");
    RespondentL resp8=(RespondentL)malloc(sizeof(struct node1));
    resp7->next=resp8;
    resp8->receiving=&j;
    resp8->calling=NULL;
    resp8->next=NULL;

    //Storing the managers informations into the manager list.
    Manager k("Rithick",28,"Salem");
    ManagerL man_head=(ManagerL)malloc(sizeof(struct node2));
    man_head->receiving=&k;
    man_head->calling=NULL;
    Manager l("Sailaja",24,"Bangalore");
    ManagerL mana=(ManagerL)malloc(sizeof(struct node2));
    man_head->next=mana;
    mana->receiving=&l;
    mana->calling=NULL;
    Manager m("Avanthika",35,"Erode");
    ManagerL mana1=(ManagerL)malloc(sizeof(struct node2));
    mana->next=mana1;
    mana1->receiving=&m;
    mana1->calling=NULL;
    Manager n("Poongodhai",40,"Kovilpatti");
    ManagerL mana2=(ManagerL)malloc(sizeof(struct node3));
    mana1->next=mana2;
    mana2->receiving=&n;
    mana2->calling=NULL;
    mana2->next=NULL;

    //Storing the Directors informations into the Director list.
    Director o("Srinivasan",53,"Rajapalayam");
    DirectorL dir_head=(DirectorL)malloc(sizeof(DirectorL));
    dir_head->receiving=&o;
    dir_head->calling=NULL;
    Director p("Vijayalakshmi",47,"Rajapalayam");
    DirectorL dire=(DirectorL)malloc(sizeof(DirectorL));
    dir_head->next=dire;
    dire->receiving=&p;
    dire->calling=NULL;
    dire->next=NULL;

    // waiting list
    waitingL wait_head=NULL;

    //Display
    cout<<"\n\t\t\t\t\t\tWELCOME TO CALL CENTER\n";
    cout<<endl<<endl;
    cout<<"\t\t**Description"<<endl;
    cout<<"\t\t\tA call centre or call center is a centralised office used for receiving or transmitting a large volume of enquiries by telephone. An inbound call centre is operated by a company to administer incoming product or service support or information enquiries from consumers.";
    cout<<endl<<endl<<endl<<endl;
    int option,pk;
    string nme,phno,add,que;
    Call cl[100];
    int y=0,xy;
    while(1)
    {
    aa :cout<<"\t\t**Services Provided:";
    cout<<"\n\t\t\t 1.Clearing the Querires";
    cout<<"\n\t\t\t 2.Query cleared..End call";
    cout<<"\n\t\t\t 3.Display the Full employee list";
    cout<<"\n\t\t\t 4.Display the passive callers(Waiting callers)";
    cout<<"\n\t\t\t 5.Display the active callers info";
    cout<<"\n\t\t\t 6.Exit";
    cout<<"\n\n\t\tEnter your option(1/2/3/4/5/6)";
    try
    {
            if(!(cin>>option))
               {
                throw 10;
                }
    }
       catch(int x)
       {
         cin.clear();
         cin.ignore(123,'\n');
         cout<<" \n Enter a digit value\n";
         goto aa;
       }
    switch(option)
    {
    case 1:  // Assigning the calls
           cout<<"Enter your name:";
           cin>>nme;
           cout<<"Enter your phone number:";
           cin>>phno;
           cout<<"Enter your address:";
           cin>>add;
           cout<<"Enter your query:";
           cin>>que;
          cl[y].Caller_details(que,nme,phno,add);
           Callhandler f;
           f.obj=&cl[y];
           wait_head=f.Assign_Call(res_head,man_head,dir_head,wait_head);
           y++;

           break;
    case 2:  // ending the calls
           cout<<"\n\n\t\tEnter the phone number whose query has been successfully cleared";
           cin>>phno;
           Callhandler f1;
           wait_head=f1.Endcall(phno,res_head,man_head,dir_head,wait_head);
           break;
    case 3: // Display the all respondents, directors and managers information
    {
           cout<<"\n\n\tList of Employees and their info";
           RespondentL r_head=res_head;
           ManagerL m_head=man_head;
           DirectorL d_head=dir_head;
           cout<<"\n\n\tRESPONDENTS";
           pk=1;
           while(r_head!=NULL)
            {
                    cout<<"\n\nNumber:"<<pk;
                    pk++;
                    (r_head->receiving)->Display();
                    cout<<endl;
                    if(r_head->next!=NULL)
                    {
                        r_head=r_head->next;
                    }
                    else
                    {
                        r_head=NULL;
                    }

            }
            cout<<"\n\n\tMANAGERS";
           pk=1;
           while(m_head!=NULL)
            {
                    cout<<"\n\nNumber:"<<pk;
                    pk++;
                    (m_head->receiving)->Display();
                    cout<<endl;
                    if(m_head->next!=NULL)
                    {
                        m_head=m_head->next;
                    }
                    else
                    {
                        m_head=NULL;
                    }

            }
            cout<<"\n\n\tDIRECTORS";
           pk=1;
           while(d_head!=NULL)
            {
                    cout<<"\n\nHead of department: "<<pk;
                    pk++;
                    (d_head->receiving)->Display();
                    cout<<endl;
                    if(d_head->next!=NULL)
                    {
                        d_head=d_head->next;
                    }
                    else
                    {
                        d_head=NULL;
                    }

            }
            cout<<endl<<endl;
           break;
    }
    case 4:  // display waiting list callers
           if(wait_head==NULL)
           {
               cout<<"\n\t\tNo callers are waiting\n\n";
           }
           else
            {
                cout<<"\n\nWaiting list caller info\n\n";
                waitingL w_head=wait_head;
                while(w_head!=NULL)
                {
                    (w_head->object)->Display();
                    cout<<endl;
                    if(w_head->next!=NULL)
                    {
                        w_head=w_head->next;
                    }
                    else
                    {
                        w_head=NULL;
                    }

                }
            }
           break;
    case 5://  Display Active callers with assigned information
    {
            xy=1;
            RespondentL r1=res_head;
            ManagerL m1=man_head;
            DirectorL d1=dir_head;
            while(r1!=NULL)
            {
                if((r1->calling)!=NULL)
                {
                    cout<<endl<<"\tCaller: "<< xy<<endl;
                    xy++;
                    (r1->calling)->Display();
                    cout<<"\n\tAttender info:";
                    (r1->receiving)->Display();
                    cout<<endl<<endl;
                }
                if(r1->next!=NULL)
                {
                     r1=r1->next;
                }
                else
                {
                    r1=NULL;
                }
            }
            while(m1!=NULL)
            {
                if((m1->calling)!=NULL)
                {
                    cout<<endl<<"\tCaller: "<< xy<<endl;
                    xy++;
                    (m1->calling)->Display();
                    cout<<"\nAttender info:";
                    (m1->receiving)->Display();
                    cout<<endl<<endl;
                }
                if(m1->next!=NULL)
                {
                    m1=m1->next;
                }
                else
                {
                    m1=NULL;
                }
            }
            while(d1!=NULL)
            {
                if((d1->calling)!=NULL)
                {
                    cout<<endl<<"\tCaller: "<< xy<<endl;
                    xy++;
                    (d1->calling)->Display();
                    cout<<"\nAttender info:";
                    (d1->receiving)->Display();
                    cout<<endl<<endl;
                }
                if(d1->next!=NULL)
                {
                    d1=d1->next;
                }
                else
                {
                    d1=NULL;
                }

            }
            break;
    }
    case 6:
           exit(0);
    default:
            cout<<"\nGive correct option";

    }
    }

}

