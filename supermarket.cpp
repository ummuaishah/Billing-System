#include<iostream>
#include<windows.h>
#include<conio.h>
#include<fstream>
#include<cstring>
#include<cstdio>
#include<cstdlib>
#include<iomanip>
using namespace std;

int k=7,r=0,flag=0;
COORD coord = {0, 0};

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
struct date
{
    int month,day,year;
};

ofstream fout;
ifstream fin;

class item
{
    int itemNumber;
    char fullname[25];
    date d;
public:
    void add_items()
    {
        cout<<"\n\n\tItem No: ";
        cin>>itemNumber;
        cout<<"\n\n\tName of the item: ";
        cin>>fullname;

        cout<<"\n\n\tManufacturing Date(dd-mm-yy): ";
        cin>>d.month>>d.day>>d.year;
    }
    void show_items()
    {
        cout<<"\n\tItem No: ";
        cout<<itemNumber;
        cout<<"\n\n\tName of the item: ";
        cout<<fullname;
        cout<<"\n\n\tDate : ";
        cout<<d.month<<"-"<<d.day<<"-"<<d.year;
    }
    void report_of_items()
    {
        gotoxy(3,k);
        cout<<itemNumber;
        gotoxy(13,k);
        puts(fullname);
    }
    int retno()
    {
        return(itemNumber);

    }

};

class amount: public item
{
    float item_price,item_quantity,item_tax,item_gross,item_discount,item_net_amount;
public:
    void add_items();
    void show_items();
    void report_of_items();
    void calculate_items();
    void payment_window();
    float retnetamt()
    {
        return(item_net_amount);
    }
} amounts;

void amount::add_items()
{
    item::add_items();
    cout<<"\n\n\tPrice: ";
    cin>>item_price;
    cout<<"\n\n\tQuantity: ";
    cin>>item_quantity;
    cout<<"\n\n\tTax percent: ";
    cin>>item_tax;
    cout<<"\n\n\tDiscount percent: ";
    cin>>item_discount;
    calculate_items();
    fout.write((char *)&amounts,sizeof(amounts));
    fout.close();
}
void amount::calculate_items()
{
    item_gross=item_price+(item_price*(item_tax/100));
    item_net_amount=item_quantity*(item_gross-(item_gross*(item_discount/100)));
}
void amount::show_items()
{
    fin.open("itemstore.dat",ios::binary);
    fin.read((char*)&amounts,sizeof(amounts));
    item::show_items();
    cout<<"\n\n\tNet amount: ";
    cout<<item_net_amount;
    fin.close();
}

void amount::report_of_items()
{
    item::report_of_items();
    gotoxy(23,k);
    cout<<item_price;
    gotoxy(33,k);
    cout<<item_quantity;
    gotoxy(44,k);
    cout<<item_tax;
    gotoxy(52,k);
    cout<<item_discount;
    gotoxy(64,k);
    cout<<item_net_amount;
    k=k+1;
    if(k==50)
    {
        gotoxy(25,50);
        cout<<"PRESS ANY KEY TO CONTINUE...";
        getch();
        k=7;
        system("cls");
        gotoxy(30,3);
        cout<<" ITEM DETAILS ";
        gotoxy(3,5);
        cout<<"NUMBER";
        gotoxy(13,5);
        cout<<"NAME";
        gotoxy(23,5);
        cout<<"PRICE";
        gotoxy(33,5);
        cout<<"QUANTITY";
        gotoxy(44,5);
        cout<<"TAX";
        gotoxy(52,5);
        cout<<"DEDUCTION";
        gotoxy(64,5);
        cout<<"NET AMOUNT";
    }
}

void amount::payment_window()
{
    show_items();
    cout<<"\n\n\n\t\t[+][+][+][+][+][+][+][+][+][+][+][+][+][+][+][+]";
    cout<<"\n\t\t                 DETAILS                  ";
    cout<<"\n\t\t[+][+][+][+][+][+][+][+][+][+][+][+][+][+][+][+]";
    cout<<"\n\n\t\tPRICE                     :"<<item_price;
    cout<<"\n\n\t\tQUANTITY                  :"<<item_quantity;
    cout<<"\n\t\tTAX PERCENTAGE              :"<<item_tax;
    cout<<"\n\t\tDISCOUNT PERCENTAGE         :"<<item_discount;
    cout<<"\n\n\n\t\tNET AMOUNT              :Rs."<<item_net_amount;
    cout<<"\n\t\t[+][+][+][+][+][+][+][+][+][+][+][+][+][+][+][+]";
}

int main()
{
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout<<setprecision(2);
    fstream tmp("temp.dat",ios::binary|ios::out);
menu:
    system("cls");
    gotoxy(25,2);
    cout<<"Super Market Billing ";
    gotoxy(25,3);
    cout<<"[+][+][+][+][+][+][+][+]\n\n";
    cout<<"\n\t\t1.Bill Report\n\n";
    cout<<"\t\t2.Add/Remove/Edit Item\n\n";
    cout<<"\t\t3.Show Item Details\n\n";
    cout<<"\t\t4.Exit\n\n";
    cout<<"\t\tPlease Enter Required Option: ";
    int ch,ff;
    float gtotal;
    cin>>ch;
    switch(ch)
    {
    case 1:
ss:
        system("cls");
        gotoxy(25,2);
        cout<<"Bill Details";
        gotoxy(25,3);
        cout<<"[+][+][+][+][+][+][+][+][+][+][+][+][+][+][+][+]\n\n";
        cout<<"\n\t\t1.All Items\n\n";
        cout<<"\t\t2.Back to Main menu\n\n";
        cout<<"\t\tPlease Enter Required Option: ";
        int cho;
        cin>>cho;
        if(cho==1)
        {
            system("cls");
            gotoxy(30,3);
            cout<<" BILL DETAILS ";
            gotoxy(3,5);
            cout<<"ITEM NO";
            gotoxy(13,5);
            cout<<"NAME";
            gotoxy(23,5);
            cout<<"PRICE";
            gotoxy(33,5);
            cout<<"QUANTITY";
            gotoxy(44,5);
            cout<<"TAX %";
            gotoxy(52,5);
            cout<<"DISCOUNT %";
            gotoxy(64,5);
            cout<<"NET AMOUNT";
            fin.open("itemstore.dat",ios::binary);
            if(!fin)
            {
                cout<<"\n\nFile Not Found...";
                goto menu;
            }
            fin.seekg(0);
            gtotal=0;
            while(!fin.eof())
            {
                fin.read((char*)&amounts,sizeof(amounts));
                if(!fin.eof())
                {
                    amounts.report_of_items();
                    gtotal+=amounts.retnetamt();
                    ff=0;
                }
                if(ff!=0) gtotal=0;
            }
            gotoxy(17,k);
            cout<<"\n\n\n\t\t\tGrand Total="<<gtotal;
            getch();
            fin.close();
        }
        if(cho==2)
        {
            goto menu;
        }
        goto ss;
    case 2:
db:
        system("cls");
        gotoxy(25,2);
        cout<<"Bill Editor";
        gotoxy(25,3);
        cout<<"[+][+][+][+][+][+][+][+][+][+][+][+][+][+][+][+]\n\n";
        cout<<"\n\t\t1.Add Item Details\n\n";
        cout<<"\t\t2.Edit Item Details\n\n";
        cout<<"\t\t3.Delete Item Details\n\n";
        cout<<"\t\t4.Back to Main Menu ";
        int apc;
        cin>>apc;
        switch(apc)
        {
        case 1:
            fout.open("itemstore.dat",ios::binary|ios::app);
            amounts.add_items();
            cout<<"\n\t\tItem Added Successfully!";
            getch();
            goto db;

        case 2:
            int ino;
            flag=0;
            cout<<"\n\n\tEnter Item Number to be Edited :";
            cin>>ino;
            fin.open("itemstore.dat",ios::binary);
            fout.open("itemstore.dat",ios::binary|ios::app);
            if(!fin)
            {
                cout<<"\n\nFile Not Found...";
                goto menu;
            }
            fin.seekg(0);
            r=0;
            while(!fin.eof())
            {
                fin.read((char*)&amounts,sizeof(amounts));
                if(!fin.eof())
                {
                    int x=amounts.item::retno();
                    if(x==ino)
                    {
                        flag=1;
                        fout.seekp(r*sizeof(amounts));
                        system("cls");
                        cout<<"\n\t\tCurrent Details are\n";
                        amounts.show_items();
                        cout<<"\n\n\t\tEnter New Details\n";
                        amounts.add_items();
                        cout<<"\n\t\tItem Details editted";
                    }
                }
                r++;
            }
            if(flag==0)
            {
                cout<<"\n\t\tItem No does not exist...Please Retry!";
                getch();
                goto db;
            }
            fin.close();
            getch();
            goto db;

        case 3:
            flag=0;
            cout<<"\n\n\tEnter Item Number to be deleted :";
            cin>>ino;
            fin.open("itemstore.dat",ios::binary);
            if(!fin)
            {
                cout<<"\n\nFile Not Found...";
                goto menu;
            }

            fin.seekg(0);
            while(fin.read((char*)&amounts, sizeof(amounts)))
            {
                int x=amounts.item::retno();
                if(x!=ino)
                    tmp.write((char*)&amounts,sizeof(amounts));
                else
                {
                    flag=1;
                }
            }
            fin.close();
            tmp.close();
            fout.open("itemstore.dat",ios::trunc|ios::binary);
            fout.seekp(0);
            tmp.open("temp.dat",ios::binary|ios::in);
            if(!tmp)
            {
                cout<<"Error in File";
                goto db;
            }
            while(tmp.read((char*)&amounts,sizeof(amounts)))
                fout.write((char*)&amounts,sizeof(amounts));
            tmp.close();
            fout.close();
            if(flag==1)
                cout<<"\n\t\tItem Succesfully Deleted";
            else if (flag==0)
                cout<<"\n\t\tItem does not Exist! Please Retry";
            getch();
            goto db;
        case 4:
            goto menu;
        default:
            cout<<"\n\n\t\tWrong Choice!!! Retry";
            getch();
            goto db;
        }
    case 3:
        system("cls");
        flag=0;
        int ino;
        cout<<"\n\n\t\tEnter Item Number :";
        cin>>ino;
        fin.open("itemstore.dat",ios::binary);
        if(!fin)
        {
            cout<<"\n\nFile Not Found...\nProgram Terminated!";
            goto menu;
        }
        fin.seekg(0);
        while(fin.read((char*)&amounts,sizeof(amounts)))
        {
            int x=amounts.item::retno();
            if(x==ino)
            {
                amounts.payment_window();
                flag=1;
                break;
            }
        }
        if(flag==0)
            cout<<"\n\t\tItem does not exist....Please Retry!";
        getch();
        fin.close();
        goto menu;
    case 4:
        system("cls");
        gotoxy(20,20);
        cout<<"ARE YOU SURE, YOU WANT TO EXIT (Y/N)?";
        char yn;
        cin>>yn;
        if((yn=='Y')||(yn=='y'))
        {
            gotoxy(12,20);
            system("cls");
            cout<<"[+][+][+][+][+][+][+][+][+][+][+][+][+][+][+][+] THANKS [+][+][+][+][+][+][+][+][+][+][+][+][+][+][+][+]";
            getch();
            exit(0);
        }
        else if((yn=='N')||(yn=='n'))
            goto menu;
        else
        {
            goto menu;
        }
    default:
        cout<<"\n\n\t\tWrong Choice....Please Retry!";
        getch();
        goto menu;
    }
    return 0;
}
