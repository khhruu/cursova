#include <iostream>
#include "Interface.h"

using namespace std;

int main()
{
    system("chcp 1251 > null");

    Interface UI;
    UI.Menu();
    return 0;
}
#ifndef DATABANK_H
#define DATABANK_H

#include <conio.h>
#include <ctime>
#include <fstream>
#include <list>

#include "Cart.h"
#include "Human.h"
#include "Credit.h"
#include "Cart.h"
#include "Investment.h"

class DataBank
{
    public:
        DataBank();
        virtual ~DataBank();
        list<Human> & GetHuman();
        list<Investment> & GetInvestment();
        list<Credit> & GetCredit();
        list<Cart> & GetCart();
        void PrintHumans();
        void PrintInvestments();
        void PrintCredits();
        void PrintCarts();
        void CreateHuman();
        list<Human>::iterator SearchByInitial(string SearchInitial);
        list<Human>::iterator SearchByID(int SearchID);
        list<Cart>::iterator SearchCartByNumber(string Number);
        list<Cart>::iterator SearchCartByID(int SearchID);
        void DeleteHuman_By_Initials(string Delete_Initial);
        void DeleteHuman_By_ID(int Delete_ID);
        void Edit_DataC(list<Cart>::const_iterator it, Cart& edit_obj);
        void SaveAllData();

    private:
        list<Cart> cart;
        list<Human> humans;
        list<Credit> credits;
        list<Investment> investment;

        void InitAllData();
};

#endif // DATABANK_H
#include "DataBank.h"


DataBank::DataBank()
{
    InitAllData();
}

DataBank::~DataBank()
{
    humans.clear();
    credits.clear();
    investment.clear();
    cart.clear();
}


list<Human>& DataBank::GetHuman()
{
    return *& humans;
}

list<Investment>& DataBank::GetInvestment()
{
    return *& investment;
}

list<Credit>& DataBank::GetCredit()
{
    return *& credits;
}

void DataBank::PrintHumans()
{
    if(humans.empty())
        std::cout<<" ������ ����� �������!"<<std::endl;
    else{
        for(auto it = humans.begin(); it != humans.end(); it++){
            Human human = *it;
            human.Print();
        }
    }
}

void DataBank::PrintInvestments()
{
    if(investment.empty())
        std::cout<<" ������ ���������� �������!"<<std::endl;
    else{
        for(auto it = investment.begin(); it != investment.end(); it++){
            Investment inv = *it;
            cout<<endl<<" ----- ������� �������ֲ� -----"<<endl<<endl;
            (*SearchByID(inv.Get_ID_Human())).Print();
            cout<<endl<<" ----- ��Ͳ �������ֲ� -----"<<endl;
            inv.Print();
            cout<<endl<<" -----=================-----"<<endl;
        }
    }
}

void DataBank::PrintCredits()
{
    if(credits.empty())
        std::cout<<" ������ ������� �������!"<<std::endl;
    else{
        for(auto it = credits.begin(); it != credits.end(); it++){
            Credit credit = *it;

            cout<<endl<<" ----- ������� ������� -----"<<endl<<endl;
            (*SearchByID(credit.Get_ID_Cart())).Print();
            cout<<endl<<" ----- ��Ͳ ������� -----"<<endl;
            credit.Print();
            cout<<endl<<" -----=================-----"<<endl;
        }
    }
}

void DataBank::CreateHuman()
{
    cout<<" ��������� ���������� ����� � �������"<<endl<<endl;
    string _string;
    Human newHuman;
    newHuman.Set_ID(humans.size()+1);
    cout<<" ������ ������� ������"<<endl<<" >";
    getline(cin, _string);
    newHuman.Set_Initial(_string);
    cout<<" ������ �������� ���"<<endl<<" >";
    getline(cin, _string);
    newHuman.Set_Passport(_string);
    cout<<" ������ ����� ��������"<<endl<<" >";
    getline(cin, _string);
    newHuman.Set_Phone(_string);
    cout<<" ������ ���������� �����"<<endl<<" >";
    getline(cin, _string);
    newHuman.Set_Email(_string);

    humans.push_back(newHuman);
}

list<Human>::iterator DataBank::SearchByInitial(string SearchInitial)
{
    auto null = humans.begin();
    if(!humans.empty()){
        for(auto it = humans.begin(); it != humans.end(); it++){
            Human searchHuman = *it;
            if(searchHuman.Get_Initial() == SearchInitial){
                return it;
            }
        }
        cout<<" �� �������� ��� ������ = "<<SearchInitial<<endl;
        return null;
    }
    else {
        cout<<" ��� ������!"<<endl;
        return null;
    }
}

list<Human>::iterator DataBank::SearchByID(int SearchID)
{
    auto null = humans.begin();
    if(!humans.empty()){
        for(auto it = humans.begin(); it != humans.end(); it++){
            Human searchHuman = *it;
            if(searchHuman.Get_ID() == SearchID){
                return it;
            }
        }
        cout<<" �� �������� ��� ������ = "<<SearchID<<endl;
        return null;
    }
    else {
        cout<<" ��� ������!"<<endl;
        return null;
    }
}
void DataBank::Edit_DataC(list<Cart>::const_iterator it, Cart& edit_obj)
{
    cart.insert(it, edit_obj);
    cart.erase(it);
}

void DataBank::DeleteHuman_By_Initials(string Delete_Initial)
{
    auto it = SearchByInitial(Delete_Initial);
    Human deleteHuman = *it;
    if(deleteHuman.Get_Initial() != Delete_Initial){
        cout<<endl<<" ��������� �� �������!"<<endl;
    }
    else {
        humans.erase(it);
        cout<<endl<<" ������ ���������!"<<endl;
    }
}

void DataBank::DeleteHuman_By_ID(int Delete_ID)
{
    auto it = SearchByID(Delete_ID);
    Human deleteHuman = *it;
    if(deleteHuman.Get_ID() != Delete_ID){
        cout<<endl<<" ��������� �� �������!"<<endl;
    }
    else {
        humans.erase(it);
        cout<<endl<<" ������ ���������!"<<endl;
    }
}

void DataBank::SaveAllData()
{
    fstream file; bool next = false;
    Human human; Credit credit; Investment invest; Cart _cart;


    file.open("File\\Carts.txt", fstream::out);
    if(!file.is_open())
        cout<<"���� File\\Carts.txt �� ��������!"<<endl;
    else{ //������
    for(auto it = cart.begin(); it!=cart.end(); it++){
        _cart = *it;
        if(next == true){file <<endl;}
        file <<  _cart.Get_ID();
        file <<endl <<  _cart.Get_ID_Human();
        file <<endl <<  _cart.Get_Number();
        file <<endl <<  _cart.Get_Balance();
        file <<endl <<  _cart.Get_ValidTo();
        next = true;
        }
    }
    next = false;
    file.close();
    file.open("File\\Humans.txt", fstream::out);
    if(!file.is_open())
        cout<<"���� File\\Humans.txt �� ��������!"<<endl;
    else{ //������
    for(auto it = humans.begin(); it!=humans.end(); it++){
        human = *it;
        if(next == true){file <<endl;}
        file <<  human.Get_ID();
        file <<endl <<  human.Get_Initial();
        file <<endl <<  human.Get_Passport();
        file <<endl <<  human.Get_Phone();
        file <<endl <<  human.Get_Email();
        next = true;
        }
    }
    next = false;
    file.close();


    file.open("File\\Credits.txt", fstream::out);
    if(!file.is_open())
        cout<<"���� File\\Credits.txt �� ��������!"<<endl;
    else{
        for(auto it = credits.begin(); it!=credits.end(); it++){
            credit = *it;
            if(next == true){file <<endl;}
            file <<  credit.Get_ID();
            file <<endl <<  credit.Get_ID_Cart();
            file <<endl <<  credit.Get_TypeCredit();
            file <<endl <<  credit.Get_Money();
            file <<endl <<  credit.Get_Monthly_Fee();
            file <<endl <<  credit.Get_Date_Taken();
            file <<endl <<  credit.Get_Term();
            file <<endl <<  credit.Get_Percentage();
            next = true;
            }
    }
    file.close();
    next = false;

    file.open("File\\Investment.txt", fstream::out);
    if(!file.is_open())
        cout<<"���� File\\Investment.txt �� ��������!"<<endl;
    else{
        for(auto it = investment.begin(); it!=investment.end(); it++){
            invest = *it;
            if(next == true){file <<endl;}
            file <<  invest.Get_ID();
            file <<endl <<  invest.Get_ID_Human();
            file <<endl <<  invest.Get_TypeDeposit();
            file <<endl <<  invest.Get_Deposit();
            file <<endl <<  invest.Get_Supplement();
            file <<endl <<  invest.Get_DateDeposit();
            file <<endl <<  invest.Get_DateAddSupplement();
            next = true;
        }
    }
    file.close();
}
list<Cart>& DataBank::GetCart()
{
    return cart;
}

void DataBank::PrintCarts()
{
    if(cart.empty())
        std::cout<<" ������ ���� �������!"<<std::endl;
    else{
        for(auto it = cart.begin(); it != cart.end(); it++){
            Cart tmpCart = *it;

            cout<<endl<<" ----- ������� ����� -----"<<endl<<endl;
            (*SearchByID(tmpCart.Get_ID_Human())).Print();
            cout<<endl<<" ----- ��Ͳ ����� -----"<<endl;
            tmpCart.Print();
            cout<<endl<<" -----=================-----"<<endl;
        }
    }
}


list<Cart>::iterator DataBank::SearchCartByNumber(string Number)
{
    auto null = cart.begin();
    if(!cart.empty()){
        for(auto it = cart.begin(); it != cart.end(); it++){
            Cart searchCart = *it;
            if(searchCart.Get_Number() == Number){
                return it;
            }
        }
        cout<<" �� �������� ��� ����� = "<<Number<<endl;
        return null;
    }
    else {
        cout<<" ��� ������!"<<endl;
        return null;
    }
}

list<Cart>::iterator DataBank::SearchCartByID(int SearchID)
{
    auto null = cart.begin();
    if(!cart.empty()){
        for(auto it = cart.begin(); it != cart.end(); it++){
            Cart searchCart = *it;
            if(searchCart.Get_ID() == SearchID){
                return it;
            }
        }
        cout<<" �� �������� ��� ����� = "<<SearchID<<endl;
        return null;
    }
    else {
        cout<<" ��� ������!"<<endl;
        return null;
    }
}

void DataBank::InitAllData()
{
    string _string;
    double _double = 0;
    int _int = 0;
    fstream file;

    file.open("File\\Humans.txt", fstream::in);
    if(!file.is_open())
        cout<<"���� File\\Humans.txt �� ��������!"<<std::endl;
    else{
        Human human;

        while(!file.eof()){
            file >> _int;
            human.Set_ID(_int);
            file.ignore();
            getline(file, _string);
            human.Set_Initial(_string);
            getline(file, _string);
            human.Set_Passport(_string);
            getline(file, _string);
            human.Set_Phone(_string);
            getline(file, _string);
            human.Set_Email(_string);

            humans.push_back(human);
        }
        file.close();
    }

    file.open("File\\Credits.txt", fstream::in);
    if(!file.is_open()){
        cout<<"���� File\\Credits.txt �� ��������!"<<std::endl;
    }
    else{
        Credit credit;
        while(!file.eof()){
            file >> _int;
            credit.Set_ID(_int);

            file >> _int;
            credit.Set_ID_Cart(_int);
            file.ignore();

            getline(file, _string);
            credit.Set_TypeCredit(_string);

            //file.ignore();
            file >> _double;
            credit.Set_Money(_double);
            file >> _double;
            credit.Set_Monthly_Fee(_double);

            file.ignore();

            getline(file, _string);
            credit.Set_Date_Taken(_string);
            getline(file, _string);
            credit.Set_Term(_string);
            file.ignore();
            file >> _double;
            credit.Set_Percentage(_double);
            file.ignore();
            credits.push_back(credit);
        }
        file.close();
    }


    file.open("File\\Investment.txt", fstream::in);
    if(!file.is_open()){
    cout<<"���� File\\Investment.txt �� ��������!"<<std::endl;
    }
    else{
    Investment invest;

    while(!file.eof()){
        file >> _int;
            invest.Set_ID(_int);

            file >> _int;
            invest.Set_ID_Cart(_int);
            file.ignore();

            getline(file, _string);
            invest.Set_TypeDeposit(_string);

            file >> _double;
            invest.Set_Deposit(_double);
            file >> _double;
            invest.Set_Supplement(_double);

            file.ignore();

            getline(file, _string);
            invest.Set_DateDeposit(_string);
            getline(file, _string);
            invest.Set_DateAddSupplement(_string);
            investment.push_back(invest);
    }
    file.close();
    }

    file.open("File\\Carts.txt", fstream::in);
    if(!file.is_open()){
    cout<<"���� File\\Carts �� ��������!"<<std::endl;
    }
    else{
    Cart _cart;

    while(!file.eof()){
        file >> _int;
        _cart.Set_ID(_int);

        file >> _int;
        _cart.Set_ID_Human(_int);
        file.ignore();

        getline(file, _string);
        _cart.Set_Number(_string);

        file >> _double; file.ignore();
        _cart.Set_Balance(_double);
       getline(file, _string);
        _cart.Set_ValidTo(_string);

        cart.push_back(_cart);
    }
    file.close();
    }
}
#ifndef INVESTMENT_H
#define INVESTMENT_H

#include<string>
#include<iostream>
using namespace std;

class Investment
{
    public:
        Investment(int ID = 0, int ID_Cart = 0, string TypeDeposit = "",
                    double Deposit = 0, double Supplement = 0, string DateDeposit = "", string DateAddSupplement = "");
        int Get_ID(){return ID;}
        int Get_ID_Human(){return ID_Cart;}
        string Get_TypeDeposit(){return TypeDeposit;}
        double Get_Deposit(){return Deposit;}
        double Get_Supplement(){return Supplement;}
        string Get_DateDeposit(){return DateDeposit;}
        string Get_DateAddSupplement(){return DateAddSupplement;}

        void Print();

        void Set_ID(int ID);
        void Set_ID_Cart(int ID_Cart);
        void Set_TypeDeposit(string TypeDeposit);
        void Set_Deposit(double Deposit);
        void Set_Supplement(double Supplement);
        void Set_DateDeposit(string DateDeposit);
        void Set_DateAddSupplement(string DateAddSupplement);

    private:
        int ID;
        int ID_Cart;
        string TypeDeposit;
        double Deposit;
        double Supplement;
        string DateDeposit;
        string DateAddSupplement;

};

#endif // INVESTMENT_H
#include "Investment.h"

Investment::Investment(int ID, int ID_Cart, string TypeDeposit, double Deposit, double Supplement, string DateDeposit, string DateAddSupplement)
{
    this->ID = ID;
    this->ID_Cart = ID_Cart;
    this->TypeDeposit = TypeDeposit;
    this->Deposit = Deposit;
    this->Supplement = Supplement;
    this->DateDeposit = DateDeposit;
    this->DateAddSupplement = DateAddSupplement;
}


void Investment::Print()
{
    cout
    <<"     ��� - "<<ID<<endl
    <<"     ��� ������ - "<<ID_Cart <<endl
    <<"     ��� �������� - "<<TypeDeposit <<endl
    <<"     ���� ������ - "<<Deposit <<endl
    <<"     г���� ������� - "<<Supplement <<endl
    <<"     ���� ������ - "<<DateDeposit <<endl
    <<"     ���� �������� - "<<DateAddSupplement<<endl<<endl;
}

void Investment::Set_ID(int ID)
{
    this->ID = ID;
}

void Investment::Set_ID_Cart(int ID_Cart)
{
    this->ID_Cart = ID_Cart;
}

void Investment::Set_TypeDeposit(string TypeDeposit)
{
    this->TypeDeposit = TypeDeposit;
}

void Investment::Set_Deposit(double Deposit)
{
    this->Deposit = Deposit;
}

void Investment::Set_Supplement(double Supplement)
{
    this->Supplement = Supplement;
}

void Investment::Set_DateDeposit(string DateDeposit)
{
    this->DateDeposit = DateDeposit;
}

void Investment::Set_DateAddSupplement(string DateAddSupplement)
{
    this->DateAddSupplement = DateAddSupplement;
}
#ifndef CART_H
#define CART_H

#include<string>
#include<iostream>
using namespace std;

class Cart
{
    public:
        Cart(int ID  = 0, int ID_Human  = 0, string Number = "", double Balance=0, string ValidTo="");

        int Get_ID(){return ID;}
        int Get_ID_Human(){return ID_Human;}
        string Get_Number(){return Number;}
        double Get_Balance(){return Balance;}
        string Get_ValidTo(){return ValidTo;}

        void Set_ID_Human(int ID_Human);
        void Set_ID(int ID);
        void Set_Number(string Number);
        void Set_Balance(double Balance);
        void Set_ValidTo(string ValidTo);

        void Print();

    private:
        int ID;
        int ID_Human;
        string Number;
        double Balance;
        string ValidTo;
};

#endif // CART_H
#include "Cart.h"

Cart::Cart(int ID, int ID_Human, string Number, double Balance, string ValidTo)
{
    this->ID = ID;
    this->ID_Human = ID_Human;
    this->Number = Number;
    this->Balance = Balance;
    this->ValidTo = ValidTo;
}
void Cart::Set_ID_Human(int ID_Human)
{
    this->ID_Human = ID_Human;
}

void Cart::Set_ID(int ID)
{
    this->ID = ID;
}

void Cart::Set_Number(string Number)
{
    this->Number = Number;
}

void Cart::Set_Balance(double Balance)
{
    this->Balance = Balance;
}

void Cart::Set_ValidTo(string ValidTo)
{
    this->ValidTo = ValidTo;
}

void Cart::Print()
{
    cout<<"     ��� ����� = "<< ID<<endl
    <<"     ����� ����� = "<< Number<<endl
    <<"     ������ = "<< Balance<< endl
    <<"     ĳ���� �� = "<< ValidTo<<endl;
}
#ifndef INTERFACE_H
#define INTERFACE_H

#include "DataBank.h"
#include "Credit.h"
#include "Investment.h"
#include "Human.h"

class Interface
{
    public:
        Interface(){}
        void Menu();
        void CreateCart();
        void CreateCredit();
        void CreateInvestment();

        void CartInfo();
        void HumansInfo();

    private:
        int Action;
        DataBank myBank;
};

#endif // INTERFACE_H
#include "Interface.h"
void Interface::HumansInfo()
{
    while(true){
        cout
        <<"#########  ²�²����ײ  ##########"<<endl<<endl<<endl
        <<" 1  - ����������� ��� ����������."<<endl
        <<" 2  - ������������ ������ ���������."<<endl
        <<" 3  - ��������� ��� ����������. "<<endl
        <<" 4  - ����� ���������."<<endl<<endl
        <<" 5  - ��������� ����� ���������."<<endl<<endl

        <<" 6  - ����������� � ������� ����."<<endl<<endl
        <<"__________________________________"<<endl<<endl<<endl
        <<" ������ ����� ������!    --> ";
        cin>>Action;

        switch(Action){
            case 1  :{
                system("cls");
                cout<<endl<<endl
                <<"########## ²�²����ײ ##########"<<endl<<endl<<endl;
                myBank.PrintHumans();
                cout
                <<"________________________________"<<endl<<endl<<endl
                <<endl<<endl<<" �������� ������, ��� ����������� �����"<<endl;
                getch();
                system("cls");
                break;}
            case 2  :{
                system("cls");
                cin.ignore();
                myBank.CreateHuman();
                cout<<endl<<" ��² ��Ͳ ��ֲ����� ��ϲ��� �������� !!!";
                cout<<endl<<endl<<" �������� ������, ��� ����������� �����"<<endl;
                getch();
                system("cls");

                break;}
            case 3  :{
                bool work_sort =  true;
                while(work_sort){
                system("cls");
                cout<<endl<<endl
                <<"##### ���������� ����� ²�²������ #####"<<endl<<endl<<endl
                <<" 1 ��������� �� ����."<<endl
                <<" 2 ��������� �� ��������."<<endl<<endl
                <<" 3 �����."<<endl
                <<"________________________________________"<<endl<<endl<<endl
                <<" ������ ����� ������!    --> ";
                cin>>Action;

                switch(Action){
                    case 1: {
                        myBank.GetHuman().sort([](Human &ob1, Human &ob2){
                                return ob1.Get_ID() < ob2.Get_ID();
                                });
                        cout<<endl<<" ��Ͳ ���� ���������Ͳ �� ���� !!!";
                        cout<<endl<<endl<<" �������� ������, ��� ����������� �����"<<endl;
                        getch();
                        break;}
                    case 2: {
                        myBank.GetHuman().sort([](Human &ob1, Human &ob2){
                                return ob1.Get_Initial() < ob2.Get_Initial();
                                });
                        cout<<endl<<" ��Ͳ ���� ���������Ͳ �� �Ͳֲ���� !!!";
                        cout<<endl<<endl<<" �������� ������, ��� ����������� �����"<<endl;
                        getch();
                        break;}
                    default: {
                        work_sort = false;
                        system("cls");
                        break;}

                }
                }

                break;}
            case 4  :{
                bool _search =  true;
                while(_search){
                system("cls");
                cout<<endl<<endl
                <<"_____ ����� ����� ²�²������ _____"<<endl<<endl<<endl
                <<" 1 ����� �� ����."<<endl
                <<" 2 ����� �� ��������."<<endl<<endl
                <<" 3 �����."<<endl
                <<"___________________________________"<<endl<<endl<<endl
                <<" ������ ����� ������!    --> ";
                cin>>Action;
                switch(Action){
                    case 1:{
                        system("cls");
                        int search_ID;
                        cout<<endl<<" ������ ��� > ";
                        cin>>search_ID;
                        Human it = *myBank.SearchByID(search_ID);
                        if(it.Get_ID() == search_ID){
                            it.Print();
                        }
                        cout<<endl<<endl<<" �������� ������, ��� ����������� �����"<<endl;
                        getch();
                        system("cls");
                        break;}
                    case 2:{
                        system("cls");
                        cin.ignore();
                        string search_Initial;
                        cout<<endl<<" ������ ������� > ";
                        getline (cin, search_Initial);
                        Human it = *myBank.SearchByInitial(search_Initial);
                        if(it.Get_Initial() == search_Initial){
                            it.Print();
                        }
                        cout<<endl<<endl<<" �������� ������, ��� ����������� �����"<<endl;
                        getch();
                        system("cls");
                        break;}
                    default :{
                        _search = false;
                        system("cls");
                        break;}
                }
                }
                system("cls");
                break;}
            case 5  :{
                bool _delete =  true;
                while(_delete){
                system("cls");
                cout<<endl<<endl
                <<"##### ��������� ����� ²�²������ #####"<<endl<<endl<<endl
                <<""<<endl<<endl
                <<" 1 ��������� �� ����."<<endl
                <<" 2 ��������� �� ��������."<<endl
                <<" 3 �����."<<endl
                <<"_______________________________________"<<endl<<endl<<endl
                <<" ������ ����� ������!    --> ";
                cin>>Action;
                switch(Action){
                    case 1:{
                        int delete_ID;
                        cout<<" ������ ��� > ";
                        cin>>delete_ID;
                        myBank.DeleteHuman_By_ID(delete_ID);
                        cout<<endl<<endl<<" �������� ������, ��� ����������� �����"<<endl;
                        getch();
                        system("cls");
                        break;}
                    case 2:{
                        cin.ignore();
                        string delete_Initial;
                        cout<<" ������ ������� > ";
                        getline (cin, delete_Initial);
                        myBank.DeleteHuman_By_Initials(delete_Initial);
                        cout<<endl<<endl<<" �������� ������, ��� ����������� �����"<<endl;
                        getch();
                        system("cls");
                        break;}
                    default :{

                        _delete = false;
                        system("cls");
                        break;}
                }
                }
                system("cls");
                break;}
            default :{
                system("cls");
                return;
                break;}
        }
    }
}

void Interface::Menu()
{
    while(true){

        cout
        <<"##########         ����        ##########"<<endl<<endl<<endl
        <<" 0  - ������� �����."<<endl
        <<" 1  - ³��������."<<endl
        <<" 2  - ������ ����������. "<<endl
        <<" 3  - ������ �������."<<endl<<endl
        <<" 4  - ���������� �������."<<endl
        <<" 5  - ���������� �����������."<<endl<<endl
        <<" 6  - �������� �� ��� � ���� �����."<<endl<<endl
        <<" 7  - �����."<<endl<<endl
        <<"________________________________________"<<endl<<endl<<endl
        <<" ������ ����� ������!    --> ";
        cin>>Action;

        switch(Action){
            case 0:{
                system("cls");
                CartInfo();
                system("cls");
                break;}
            case 1:{
                system("cls");
                HumansInfo();
                system("cls");
                break;}
            case 2:{
                system("cls");
                cout<<"            I������ֲ�"<<endl<<endl;
                myBank.PrintInvestments();
                cout<<endl<<" �������� ������, ��� ����������!"<<endl;
                getch();
                system("cls");
                break;}
            case 3:{
                system("cls");
                cout<<"               �������"<<endl<<endl;
                myBank.PrintCredits();
                cout<<endl<<" �������� ������, ��� ����������!"<<endl;
                getch();
                system("cls");
                break;}
            case 4:{
                system("cls");
                CreateCredit();
                system("cls");
                break;}
            case 5:{
                system("cls");
                CreateInvestment();
                break;}
            case 6:{
                system("cls");
                myBank.SaveAllData();
                cout<<endl<<endl<<" ��� ������ ��������!!!"<<endl;
                cout<<endl<<endl<<" �������� ������, ��� ����������!"<<endl;
                getch();
                system("cls");
                break;}

            default : {
                system("cls");
                cout<<endl<<endl<<"�������� ��������� ���� ������ !"<<endl<<endl;
                return;
                break;}
        }
    }
}

void Interface::CreateCredit()
{
    int _int = 0, tmpAction; double _double = 0;
    string _string;
    system("cls");
    Credit tempC;
    tempC.Set_ID(myBank.GetHuman().size() + 1);
    cout<<"=========== ���������� ������� ==========="<<endl<<endl
    <<" ������ �����"<<endl<<endl
    <<" 1. ������ ��� ����� ���������."<<endl
    <<" 2. ������������ ����� ���������."<<endl
    <<" 3. ���������."<<endl<<endl<<" >";
    cin>>tmpAction;
    switch(tmpAction){
        case 1: {
            if(myBank.GetCart().size() == 0){
                cout<<" ������ ���� ���������� �������, ������� �� ! "<<endl
                <<endl<<" �������� ������, ��� ����������!"<<endl;
                getch();
                system("cls");
            return;
            }
            myBank.PrintCarts();
            while(true){

                cout<<endl<<" ������ ��� ����� ���������"<<endl<<" >";
                cin>>tmpAction;
                if(tmpAction <= myBank.GetCart().size() && tmpAction > 0)
                    break;
                else{
                    cout<<endl<<" �� ������ ������� ���, ��������� �� ���"<<endl;
                }
            }
            tempC.Set_ID_Cart(tmpAction);
            break;}
        case 2: {
            system("cls"); cin.ignore();
            CreateCart();
            system("cls");
            tempC.Set_ID_Cart(myBank.GetCart().size());
            break;}
        default: {
            cout<<" ���������� ���������! "<<endl
            <<endl<<" �������� ������, ��� ����������!"<<endl;
                getch();
                system("cls");
            return;}
    }
    system("cls");

    cout<<endl<<" ����������� �Ū����ֲ� ������� "<<endl
    <<" ������ ��� �������"<<endl<<" >"; cin.ignore();
    getline(cin, _string);
    tempC.Set_TypeCredit(_string);
    cout<<endl<<" ������ ���� ����� (��������� ���)"<<endl<<" >";
    cin>>_double;
    tempC.Set_Money(_double);
    cout<<endl<<" ������ ���� �������� ������ (��������� ���)"<<endl<<" >";
    cin>>_double;
    tempC.Set_Monthly_Fee(_double); cin.ignore();
    cout<<endl<<" ������ ���� ������ �������"<<endl<<" >";
    getline(cin, _string);
    tempC.Set_Date_Taken(_string);
    cout<<endl<<" ������ ����� ������ �������"<<endl<<" >";
    getline(cin, _string);
    tempC.Set_Term(_string);
    cout<<endl<<" ������ ������� ������� (��������� ���)"<<endl<<" >";
    cin>>_double;
    tempC.Set_Percentage(_double);
    cin.ignore();
    myBank.GetCredit().push_back(tempC);

    system("cls");
    cout<<endl<<endl<<" ������ ��ϲ��� ����������!!!"<<endl;
    cout<<endl<<endl<<" �������� ������, ��� ����������!"<<endl;
    getch();
    system("cls");
}

void Interface::CreateInvestment()
{
    int _int = 0, tmpAction; double _double = 0;
    string _string;
    system("cls");
    Investment tempI;
    tempI.Set_ID(myBank.GetCredit().size() + 1);
    cout<<"=========== ����� ������ (�������ֲ�) ==========="<<endl<<endl
    <<" ������ �����"<<endl<<endl
    <<" 1. ������ ��� ����� ���������."<<endl
    <<" 2. ������������ ����� ��� ���������."<<endl
    <<" 3. ���������."<<endl<<endl<<" >";
    cin>>tmpAction;
    switch(tmpAction){
        case 1: {
            if(myBank.GetCart().size() == 0){
                cout<<" ������ ���� �������, ������� �� ! "<<endl
                <<endl<<" �������� ������, ��� ����������!"<<endl;
                getch();
                system("cls");
            return;
            }
            myBank.PrintCarts();
            while(true){

                cout<<endl<<" ������ ��� ���������"<<endl<<" >";
                cin>>tmpAction;
                if(tmpAction <= myBank.GetCart().size() && tmpAction > 0)
                    break;
                else{
                    cout<<endl<<" �� ������ ������� ���, ��������� �� ���"<<endl;
                }
            }
            tempI.Set_ID_Cart(tmpAction);
            break;}
        case 2: {
            system("cls"); cin.ignore();
            CreateCart();
            system("cls");
            tempI.Set_ID_Cart(myBank.GetCart().size());
            break;}
        default: {
            cout<<" ���������� ���������! "<<endl
            <<endl<<" �������� ������, ��� ����������!"<<endl;
                getch();
                system("cls");
            return;}
    }
    system("cls");
cin.ignore();
    cout<<endl<<" ����������� �Ū����ֲ� �������ֲ� "<<endl
    <<" ������ ��� ����������"<<endl<<" >";
    getline(cin, _string);
    tempI.Set_TypeDeposit(_string);
    cout<<endl<<" ������ ���� �������� (��������� ���)"<<endl<<" >";
    cin>>_double;
    tempI.Set_Deposit(_double);
    cout<<endl<<" ������ ���� ���� �������� (��������� ���)"<<endl<<" >";
    cin>>_double;
    tempI.Set_Supplement(_double); cin.ignore();
    cout<<endl<<" ������ ���� ����������"<<endl<<" >";
    getline(cin, _string);
    tempI.Set_DateDeposit(_string);
    cout<<endl<<" ������ ���� ���������� ����������� ��������"<<endl<<" >";
    getline(cin, _string);
    tempI.Set_DateAddSupplement(_string);

    myBank.GetInvestment().push_back(tempI);

    system("cls");
    cout<<endl<<endl<<" �������ֲ� ��ϲ��� ���Ū��������!!!"<<endl;
    cout<<endl<<endl<<" �������� ������, ��� ����������!"<<endl;
    getch();
    system("cls");
}
void Interface::CartInfo()
{
    while(true){
        cout
        <<"#########  ������Ͳ �����  ##########"<<endl<<endl<<endl
        <<" 1  - ����������� ��� ����."<<endl
        <<" 2  - ������������ ���� �����."<<endl
        <<" 3  - ����� �����."<<endl<<endl
        <<" 4  - ���������� ������� �����."<<endl<<endl
        <<" 5  - ����������� � ������� ����."<<endl<<endl
        <<"__________________________________"<<endl<<endl<<endl
        <<" ������ ����� ������!    --> ";
        cin>>Action;

        switch(Action){
            case 1  :{
                system("cls");
                cout<<endl<<endl
                <<"########## ������Ͳ ����� ##########"<<endl<<endl<<endl;
                myBank.PrintCarts();
                cout
                <<"________________________________"<<endl<<endl<<endl
                <<endl<<endl<<" �������� ������, ��� ����������� �����"<<endl;
                getch();
                system("cls");
                break;}
            case 2  :{
                system("cls");
                cin.ignore();
                CreateCart();
                cout<<endl<<" ��² ��Ͳ ����� ��ϲ��� �������� !!!";
                cout<<endl<<endl<<" �������� ������, ��� ����������� �����"<<endl;
                getch();
                system("cls");

                break;}

            case 3  :{
                bool _search =  true;
                while(_search){
                system("cls");
                cout<<endl<<endl
                <<"_____ ����� ����� ����� _____"<<endl<<endl<<endl
                <<" 1 ����� �� ����."<<endl
                <<" 2 ����� �� ������ �����."<<endl<<endl
                <<" 3 �����."<<endl
                <<"___________________________________"<<endl<<endl<<endl
                <<" ������ ����� ������!    --> ";
                cin>>Action;
                switch(Action){
                    case 1:{
                        system("cls");
                        int search_ID;
                        cout<<endl<<" ������ ��� > ";
                        cin>>search_ID;
                        Cart it = *myBank.SearchCartByID(search_ID);
                        if(it.Get_ID() == search_ID){
                            it.Print();
                        }
                        cout<<endl<<endl<<" �������� ������, ��� ����������� �����"<<endl;
                        getch();
                        system("cls");
                        break;}
                    case 2:{
                        system("cls");
                        cin.ignore();
                        string search_;
                        cout<<endl<<" ������ ����� ����� > ";
                        getline (cin, search_);
                        Cart it = *myBank.SearchCartByNumber(search_);
                        if(it.Get_Number() == search_){
                            it.Print();
                        }
                        cout<<endl<<endl<<" �������� ������, ��� ����������� �����"<<endl;
                        getch();
                        system("cls");
                        break;}
                    default :{
                        _search = false;
                        system("cls");
                        break;}
                }
                }
                system("cls");
                break;}
                case 4: {
                    string tmp;
                    system("cls"); cin.ignore();
                    cout<<"++++++++ ���������� ����� +++++++++"<<endl<<endl
                    <<" ������ ����� ����� "<<endl<<" >";
                    getline(cin, tmp);
                    auto it = *myBank.SearchCartByNumber(tmp);
                    Cart cc = it;
                    if(cc.Get_Number() != tmp)
                        cout<<"��� ����� �� ��������!"<<endl;
                    else{
                        double tmpD;
                        cout<<" ������ ���� ����������"<<endl<<" >";
                        cin>>tmpD;
                        cc.Set_Balance(it.Get_Balance() + tmpD);
                        myBank.Edit_DataC(myBank.SearchCartByNumber(tmp), cc);
                        cout<<"������ ��������� �������!"<<endl;
                    }
                    cout<<endl<<endl<<" �������� ������, ��� ����������� �����"<<endl;
                    getch();
                    system("cls");
                break;}
            default :{
                system("cls");
                return;
                break;}
        }
    }
}

void Interface::CreateCart()
{
    int _int = 0, tmpAction; double _double = 0;
    string _string;
    system("cls");
    Cart tempC;
    tempC.Set_ID(myBank.GetCart().size() + 1);
    cout<<"=========== ���������� ����� ==========="<<endl<<endl
    <<" ������ �����"<<endl<<endl
    <<" 1. ������ ��� �������������� ���������."<<endl
    <<" 2. ������������ ���������."<<endl
    <<" 3. ���������."<<endl<<endl<<" >";
    cin>>tmpAction;
    switch(tmpAction){
        case 1: {
            if(myBank.GetHuman().size() == 0){
                cout<<" ������ ���������� �������, ������� �� ! "<<endl
                <<endl<<" �������� ������, ��� ����������!"<<endl;
                getch();
                system("cls");
                return;
            }
            myBank.PrintHumans();
            while(true){

                cout<<endl<<" ������ ��� ���������"<<endl<<" >";
                cin>>tmpAction;
                if(tmpAction <= myBank.GetHuman().size() && tmpAction > 0)
                    break;
                else{
                    cout<<endl<<" �� ������ ������� ���, ��������� �� ���"<<endl;
                }
            }
            tempC.Set_ID_Human(tmpAction);
            break;}
        case 2: {
            system("cls"); cin.ignore();
            CreateCart();
            system("cls");
            tempC.Set_ID_Human(myBank.GetHuman().size());
            break;}
        default: {
            cout<<" ���������� ���������! "<<endl
            <<endl<<" �������� ������, ��� ����������!"<<endl;
                getch();
                system("cls");
            return;
            }
    }
    system("cls");
    cin.ignore();
    cout<<endl<<" ����������� �Ū����ֲ� ����� "<<endl
    <<" ������ ����� �����"<<endl<<" >";
    getline(cin, _string);

    tempC.Set_Number(_string);
    cout<<endl<<" ������, ����� ����� ��:"<<endl<<" >";
    getline(cin, _string);
    tempC.Set_ValidTo(_string);

    myBank.GetCart().push_back(tempC);

    system("cls");
}
