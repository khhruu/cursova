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
        std::cout<<" Список людей порожній!"<<std::endl;
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
        std::cout<<" Список інвестицій порожній!"<<std::endl;
    else{
        for(auto it = investment.begin(); it != investment.end(); it++){
            Investment inv = *it;
            cout<<endl<<" ----- ВЛАСНИК ІНВЕСТИЦІЇ -----"<<endl<<endl;
            (*SearchByID(inv.Get_ID_Human())).Print();
            cout<<endl<<" ----- ДАНІ ІНВЕСТИЦІЇ -----"<<endl;
            inv.Print();
            cout<<endl<<" -----=================-----"<<endl;
        }
    }
}

void DataBank::PrintCredits()
{
    if(credits.empty())
        std::cout<<" Список кредитів порожній!"<<std::endl;
    else{
        for(auto it = credits.begin(); it != credits.end(); it++){
            Credit credit = *it;

            cout<<endl<<" ----- ВЛАСНИК КРЕДИТУ -----"<<endl<<endl;
            (*SearchByID(credit.Get_ID_Cart())).Print();
            cout<<endl<<" ----- ДАНІ КРЕДИТУ -----"<<endl;
            credit.Print();
            cout<<endl<<" -----=================-----"<<endl;
        }
    }
}

void DataBank::CreateHuman()
{
    cout<<" Реєстрація відвідуючого банку в систему"<<endl<<endl;
    string _string;
    Human newHuman;
    newHuman.Set_ID(humans.size()+1);
    cout<<" Введіть ініціали людини"<<endl<<" >";
    getline(cin, _string);
    newHuman.Set_Initial(_string);
    cout<<" Введіть паспортні дані"<<endl<<" >";
    getline(cin, _string);
    newHuman.Set_Passport(_string);
    cout<<" Введіть номер телефону"<<endl<<" >";
    getline(cin, _string);
    newHuman.Set_Phone(_string);
    cout<<" Введіть електронну пошту"<<endl<<" >";
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
        cout<<" Не знайдено дані людини = "<<SearchInitial<<endl;
        return null;
    }
    else {
        cout<<" Дані відсутні!"<<endl;
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
        cout<<" Не знайдено дані людини = "<<SearchID<<endl;
        return null;
    }
    else {
        cout<<" Дані відсутні!"<<endl;
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
        cout<<endl<<" Видалення не вдалося!"<<endl;
    }
    else {
        humans.erase(it);
        cout<<endl<<" Успішно видалений!"<<endl;
    }
}

void DataBank::DeleteHuman_By_ID(int Delete_ID)
{
    auto it = SearchByID(Delete_ID);
    Human deleteHuman = *it;
    if(deleteHuman.Get_ID() != Delete_ID){
        cout<<endl<<" Видалення не вдалося!"<<endl;
    }
    else {
        humans.erase(it);
        cout<<endl<<" Успішно видалений!"<<endl;
    }
}

void DataBank::SaveAllData()
{
    fstream file; bool next = false;
    Human human; Credit credit; Investment invest; Cart _cart;


    file.open("File\\Carts.txt", fstream::out);
    if(!file.is_open())
        cout<<"Файл File\\Carts.txt не знайдено!"<<endl;
    else{ //Людина
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
        cout<<"Файл File\\Humans.txt не знайдено!"<<endl;
    else{ //Людина
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
        cout<<"Файл File\\Credits.txt не знайдено!"<<endl;
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
        cout<<"Файл File\\Investment.txt не знайдено!"<<endl;
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
        std::cout<<" Список карт порожній!"<<std::endl;
    else{
        for(auto it = cart.begin(); it != cart.end(); it++){
            Cart tmpCart = *it;

            cout<<endl<<" ----- ВЛАСНИК КАРТИ -----"<<endl<<endl;
            (*SearchByID(tmpCart.Get_ID_Human())).Print();
            cout<<endl<<" ----- ДАНІ КАРТИ -----"<<endl;
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
        cout<<" Не знайдено дані карти = "<<Number<<endl;
        return null;
    }
    else {
        cout<<" Дані відсутні!"<<endl;
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
        cout<<" Не знайдено дані карти = "<<SearchID<<endl;
        return null;
    }
    else {
        cout<<" Дані відсутні!"<<endl;
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
        cout<<"Файл File\\Humans.txt не знайдено!"<<std::endl;
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
        cout<<"Файл File\\Credits.txt не знайдено!"<<std::endl;
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
    cout<<"Файл File\\Investment.txt не знайдено!"<<std::endl;
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
    cout<<"Файл File\\Carts не знайдено!"<<std::endl;
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
    <<"     Код - "<<ID<<endl
    <<"     Код людини - "<<ID_Cart <<endl
    <<"     Тип депозиту - "<<TypeDeposit <<endl
    <<"     Сума вкладу - "<<Deposit <<endl
    <<"     Річний відсоток - "<<Supplement <<endl
    <<"     Дата вкладу - "<<DateDeposit <<endl
    <<"     Дата надбавки - "<<DateAddSupplement<<endl<<endl;
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
    cout<<"     Код карти = "<< ID<<endl
    <<"     Номер карти = "<< Number<<endl
    <<"     Баланс = "<< Balance<< endl
    <<"     Дійсна до = "<< ValidTo<<endl;
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
        <<"#########  ВІДВІДУВАЧІ  ##########"<<endl<<endl<<endl
        <<" 1  - Переглянути дані відвідувачів."<<endl
        <<" 2  - Зареєструвати нового відвідувача."<<endl
        <<" 3  - Сортувати дані відвідувачів. "<<endl
        <<" 4  - Пошук відвідувача."<<endl<<endl
        <<" 5  - Видалення даних відвідувача."<<endl<<endl

        <<" 6  - Повернутись в головне меню."<<endl<<endl
        <<"__________________________________"<<endl<<endl<<endl
        <<" Введіть номер пункту!    --> ";
        cin>>Action;

        switch(Action){
            case 1  :{
                system("cls");
                cout<<endl<<endl
                <<"########## ВІДВІДУВАЧІ ##########"<<endl<<endl<<endl;
                myBank.PrintHumans();
                cout
                <<"________________________________"<<endl<<endl<<endl
                <<endl<<endl<<" Натисніть клавішу, щоб повернутися назад"<<endl;
                getch();
                system("cls");
                break;}
            case 2  :{
                system("cls");
                cin.ignore();
                myBank.CreateHuman();
                cout<<endl<<" НОВІ ДАНІ ПАЦІВНИКА УСПІШНО СТВОРЕНО !!!";
                cout<<endl<<endl<<" Натисніть клавішу, щоб повернутися назад"<<endl;
                getch();
                system("cls");

                break;}
            case 3  :{
                bool work_sort =  true;
                while(work_sort){
                system("cls");
                cout<<endl<<endl
                <<"##### СОРТУВАННЯ ДАНИХ ВІДВІДУВАЧА #####"<<endl<<endl<<endl
                <<" 1 Сортувати по коду."<<endl
                <<" 2 Сортувати по ініціалах."<<endl<<endl
                <<" 3 Вийти."<<endl
                <<"________________________________________"<<endl<<endl<<endl
                <<" Введіть номер пункту!    --> ";
                cin>>Action;

                switch(Action){
                    case 1: {
                        myBank.GetHuman().sort([](Human &ob1, Human &ob2){
                                return ob1.Get_ID() < ob2.Get_ID();
                                });
                        cout<<endl<<" ДАНІ БУЛИ ПОСОРТОВАНІ ПО КОДУ !!!";
                        cout<<endl<<endl<<" Натисніть клавішу, щоб повернутися назад"<<endl;
                        getch();
                        break;}
                    case 2: {
                        myBank.GetHuman().sort([](Human &ob1, Human &ob2){
                                return ob1.Get_Initial() < ob2.Get_Initial();
                                });
                        cout<<endl<<" ДАНІ БУЛИ ПОСОРТОВАНІ ПО ІНІЦІАЛАХ !!!";
                        cout<<endl<<endl<<" Натисніть клавішу, щоб повернутися назад"<<endl;
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
                <<"_____ ПОШУК ДАНИХ ВІДВІДУВАЧА _____"<<endl<<endl<<endl
                <<" 1 Пошук по коду."<<endl
                <<" 2 Пошук по ініціалах."<<endl<<endl
                <<" 3 Вийти."<<endl
                <<"___________________________________"<<endl<<endl<<endl
                <<" Введіть номер пункту!    --> ";
                cin>>Action;
                switch(Action){
                    case 1:{
                        system("cls");
                        int search_ID;
                        cout<<endl<<" Введіть код > ";
                        cin>>search_ID;
                        Human it = *myBank.SearchByID(search_ID);
                        if(it.Get_ID() == search_ID){
                            it.Print();
                        }
                        cout<<endl<<endl<<" Натисніть клавішу, щоб повернутися назад"<<endl;
                        getch();
                        system("cls");
                        break;}
                    case 2:{
                        system("cls");
                        cin.ignore();
                        string search_Initial;
                        cout<<endl<<" Введіть ініціали > ";
                        getline (cin, search_Initial);
                        Human it = *myBank.SearchByInitial(search_Initial);
                        if(it.Get_Initial() == search_Initial){
                            it.Print();
                        }
                        cout<<endl<<endl<<" Натисніть клавішу, щоб повернутися назад"<<endl;
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
                <<"##### ВИДАЛЕННЯ ДАНИХ ВІДВІДУВАЧА #####"<<endl<<endl<<endl
                <<""<<endl<<endl
                <<" 1 Видалення по коду."<<endl
                <<" 2 Видалення по ініціалах."<<endl
                <<" 3 Вийти."<<endl
                <<"_______________________________________"<<endl<<endl<<endl
                <<" Введіть номер пункту!    --> ";
                cin>>Action;
                switch(Action){
                    case 1:{
                        int delete_ID;
                        cout<<" Введіть код > ";
                        cin>>delete_ID;
                        myBank.DeleteHuman_By_ID(delete_ID);
                        cout<<endl<<endl<<" Натисніть клавішу, щоб повернутися назад"<<endl;
                        getch();
                        system("cls");
                        break;}
                    case 2:{
                        cin.ignore();
                        string delete_Initial;
                        cout<<" Введіть ініціали > ";
                        getline (cin, delete_Initial);
                        myBank.DeleteHuman_By_Initials(delete_Initial);
                        cout<<endl<<endl<<" Натисніть клавішу, щоб повернутися назад"<<endl;
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
        <<"##########         БАНК        ##########"<<endl<<endl<<endl
        <<" 0  - Кредитні карти."<<endl
        <<" 1  - Відвідувачі."<<endl
        <<" 2  - Список Інвестицій. "<<endl
        <<" 3  - Список Кредитів."<<endl<<endl
        <<" 4  - Оформлення кредиту."<<endl
        <<" 5  - Оформлення інвестиціїй."<<endl<<endl
        <<" 6  - Зберегти всі дані в базу даних."<<endl<<endl
        <<" 7  - Вийти."<<endl<<endl
        <<"________________________________________"<<endl<<endl<<endl
        <<" Введіть номер пункту!    --> ";
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
                cout<<"            IНВЕСТИЦІЇ"<<endl<<endl;
                myBank.PrintInvestments();
                cout<<endl<<" Натисніть клавішу, щоб продовжити!"<<endl;
                getch();
                system("cls");
                break;}
            case 3:{
                system("cls");
                cout<<"               КРЕДИТИ"<<endl<<endl;
                myBank.PrintCredits();
                cout<<endl<<" Натисніть клавішу, щоб продовжити!"<<endl;
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
                cout<<endl<<endl<<" Дані успішно збережені!!!"<<endl;
                cout<<endl<<endl<<" Натисніть клавішу, щоб продовжити!"<<endl;
                getch();
                system("cls");
                break;}

            default : {
                system("cls");
                cout<<endl<<endl<<"Програма завершила свою роботу !"<<endl<<endl;
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
    cout<<"=========== ОФОРМЛЕННЯ КРЕДИТУ ==========="<<endl<<endl
    <<" Оберіть пункт"<<endl<<endl
    <<" 1. Обрати дані карти відвідувача."<<endl
    <<" 2. Зареєструвати карту відвідувачу."<<endl
    <<" 3. Скасувати."<<endl<<endl<<" >";
    cin>>tmpAction;
    switch(tmpAction){
        case 1: {
            if(myBank.GetCart().size() == 0){
                cout<<" Список карт відвідувачів порожній, додайте їх ! "<<endl
                <<endl<<" Натисніть клавішу, щоб продовжити!"<<endl;
                getch();
                system("cls");
            return;
            }
            myBank.PrintCarts();
            while(true){

                cout<<endl<<" Введіть код карти відвідувача"<<endl<<" >";
                cin>>tmpAction;
                if(tmpAction <= myBank.GetCart().size() && tmpAction > 0)
                    break;
                else{
                    cout<<endl<<" Ви введли невірний код, спробуйте ще раз"<<endl;
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
            cout<<" ОФОРМЛЕННЯ СКАСОВАНО! "<<endl
            <<endl<<" Натисніть клавішу, щоб продовжити!"<<endl;
                getch();
                system("cls");
            return;}
    }
    system("cls");

    cout<<endl<<" ПРОДОВЖЕННЯ РЕЄСТРАЦІЇ КРЕДИТУ "<<endl
    <<" Введіть тип кредиту"<<endl<<" >"; cin.ignore();
    getline(cin, _string);
    tempC.Set_TypeCredit(_string);
    cout<<endl<<" Введіть суму займу (Чисельний ввід)"<<endl<<" >";
    cin>>_double;
    tempC.Set_Money(_double);
    cout<<endl<<" Введіть суму щомісячної оплати (Чисельний ввід)"<<endl<<" >";
    cin>>_double;
    tempC.Set_Monthly_Fee(_double); cin.ignore();
    cout<<endl<<" Введіть дату взяття кредиту"<<endl<<" >";
    getline(cin, _string);
    tempC.Set_Date_Taken(_string);
    cout<<endl<<" Введіть термін оплати кредиту"<<endl<<" >";
    getline(cin, _string);
    tempC.Set_Term(_string);
    cout<<endl<<" Введіть відсоток доплати (Чисельний ввід)"<<endl<<" >";
    cin>>_double;
    tempC.Set_Percentage(_double);
    cin.ignore();
    myBank.GetCredit().push_back(tempC);

    system("cls");
    cout<<endl<<endl<<" КРЕДИТ УСПІШНО ОФОРМЛЕНИЙ!!!"<<endl;
    cout<<endl<<endl<<" Натисніть клавішу, щоб продовжити!"<<endl;
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
    cout<<"=========== ВКЛАД ГРОШЕЙ (ІНВЕСТИЦІЯ) ==========="<<endl<<endl
    <<" Оберіть пункт"<<endl<<endl
    <<" 1. Обрати дані карти відвідувача."<<endl
    <<" 2. Зареєструвати карту для відвідувача."<<endl
    <<" 3. Скасувати."<<endl<<endl<<" >";
    cin>>tmpAction;
    switch(tmpAction){
        case 1: {
            if(myBank.GetCart().size() == 0){
                cout<<" Список карт порожній, додайте їх ! "<<endl
                <<endl<<" Натисніть клавішу, щоб продовжити!"<<endl;
                getch();
                system("cls");
            return;
            }
            myBank.PrintCarts();
            while(true){

                cout<<endl<<" Введіть код відвідувача"<<endl<<" >";
                cin>>tmpAction;
                if(tmpAction <= myBank.GetCart().size() && tmpAction > 0)
                    break;
                else{
                    cout<<endl<<" Ви введли невірний код, спробуйте ще раз"<<endl;
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
            cout<<" ОФОРМЛЕННЯ СКАСОВАНО! "<<endl
            <<endl<<" Натисніть клавішу, щоб продовжити!"<<endl;
                getch();
                system("cls");
            return;}
    }
    system("cls");
cin.ignore();
    cout<<endl<<" ПРОДОВЖЕННЯ РЕЄСТРАЦІЇ ІНВЕСТИЦІЇ "<<endl
    <<" Введіть тип інвестиції"<<endl<<" >";
    getline(cin, _string);
    tempI.Set_TypeDeposit(_string);
    cout<<endl<<" Введіть суму депозиту (Чисельний ввід)"<<endl<<" >";
    cin>>_double;
    tempI.Set_Deposit(_double);
    cout<<endl<<" Введіть суму річної надбавки (Чисельний ввід)"<<endl<<" >";
    cin>>_double;
    tempI.Set_Supplement(_double); cin.ignore();
    cout<<endl<<" Введіть дату інвестиції"<<endl<<" >";
    getline(cin, _string);
    tempI.Set_DateDeposit(_string);
    cout<<endl<<" Введіть дату наступного нарахування надбавки"<<endl<<" >";
    getline(cin, _string);
    tempI.Set_DateAddSupplement(_string);

    myBank.GetInvestment().push_back(tempI);

    system("cls");
    cout<<endl<<endl<<" ІНВЕСТИЦІЯ УСПІШНО ЗАРЕЄСТРОВАНА!!!"<<endl;
    cout<<endl<<endl<<" Натисніть клавішу, щоб продовжити!"<<endl;
    getch();
    system("cls");
}
void Interface::CartInfo()
{
    while(true){
        cout
        <<"#########  КРЕДИТНІ КАРТИ  ##########"<<endl<<endl<<endl
        <<" 1  - Переглянути дані карт."<<endl
        <<" 2  - Зареєструвати нову карту."<<endl
        <<" 3  - Пошук карти."<<endl<<endl
        <<" 4  - Поповнення балансу карти."<<endl<<endl
        <<" 5  - Повернутись в головне меню."<<endl<<endl
        <<"__________________________________"<<endl<<endl<<endl
        <<" Введіть номер пункту!    --> ";
        cin>>Action;

        switch(Action){
            case 1  :{
                system("cls");
                cout<<endl<<endl
                <<"########## КРЕДИТНІ КАРТИ ##########"<<endl<<endl<<endl;
                myBank.PrintCarts();
                cout
                <<"________________________________"<<endl<<endl<<endl
                <<endl<<endl<<" Натисніть клавішу, щоб повернутися назад"<<endl;
                getch();
                system("cls");
                break;}
            case 2  :{
                system("cls");
                cin.ignore();
                CreateCart();
                cout<<endl<<" НОВІ ДАНІ КАРТИ УСПІШНО СТВОРЕНО !!!";
                cout<<endl<<endl<<" Натисніть клавішу, щоб повернутися назад"<<endl;
                getch();
                system("cls");

                break;}

            case 3  :{
                bool _search =  true;
                while(_search){
                system("cls");
                cout<<endl<<endl
                <<"_____ ПОШУК ДАНИХ КАРТИ _____"<<endl<<endl<<endl
                <<" 1 Пошук по коду."<<endl
                <<" 2 Пошук по номеру карти."<<endl<<endl
                <<" 3 Вийти."<<endl
                <<"___________________________________"<<endl<<endl<<endl
                <<" Введіть номер пункту!    --> ";
                cin>>Action;
                switch(Action){
                    case 1:{
                        system("cls");
                        int search_ID;
                        cout<<endl<<" Введіть код > ";
                        cin>>search_ID;
                        Cart it = *myBank.SearchCartByID(search_ID);
                        if(it.Get_ID() == search_ID){
                            it.Print();
                        }
                        cout<<endl<<endl<<" Натисніть клавішу, щоб повернутися назад"<<endl;
                        getch();
                        system("cls");
                        break;}
                    case 2:{
                        system("cls");
                        cin.ignore();
                        string search_;
                        cout<<endl<<" Введіть номер карти > ";
                        getline (cin, search_);
                        Cart it = *myBank.SearchCartByNumber(search_);
                        if(it.Get_Number() == search_){
                            it.Print();
                        }
                        cout<<endl<<endl<<" Натисніть клавішу, щоб повернутися назад"<<endl;
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
                    cout<<"++++++++ ПОПОВНЕННЯ КАРТИ +++++++++"<<endl<<endl
                    <<" Введіть номер карти "<<endl<<" >";
                    getline(cin, tmp);
                    auto it = *myBank.SearchCartByNumber(tmp);
                    Cart cc = it;
                    if(cc.Get_Number() != tmp)
                        cout<<"Дані карти не знайдено!"<<endl;
                    else{
                        double tmpD;
                        cout<<" Введіть суму поповнення"<<endl<<" >";
                        cin>>tmpD;
                        cc.Set_Balance(it.Get_Balance() + tmpD);
                        myBank.Edit_DataC(myBank.SearchCartByNumber(tmp), cc);
                        cout<<"Успішно поповнено рахунок!"<<endl;
                    }
                    cout<<endl<<endl<<" Натисніть клавішу, щоб повернутися назад"<<endl;
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
    cout<<"=========== ОФОРМЛЕННЯ КАРТИ ==========="<<endl<<endl
    <<" Оберіть пункт"<<endl<<endl
    <<" 1. Обрати дані зареєстрованого відвідувача."<<endl
    <<" 2. Зареєструвати відвідувача."<<endl
    <<" 3. Скасувати."<<endl<<endl<<" >";
    cin>>tmpAction;
    switch(tmpAction){
        case 1: {
            if(myBank.GetHuman().size() == 0){
                cout<<" Список відвідувачів порожній, додайте їх ! "<<endl
                <<endl<<" Натисніть клавішу, щоб продовжити!"<<endl;
                getch();
                system("cls");
                return;
            }
            myBank.PrintHumans();
            while(true){

                cout<<endl<<" Введіть код відвідувача"<<endl<<" >";
                cin>>tmpAction;
                if(tmpAction <= myBank.GetHuman().size() && tmpAction > 0)
                    break;
                else{
                    cout<<endl<<" Ви введли невірний код, спробуйте ще раз"<<endl;
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
            cout<<" ОФОРМЛЕННЯ СКАСОВАНО! "<<endl
            <<endl<<" Натисніть клавішу, щоб продовжити!"<<endl;
                getch();
                system("cls");
            return;
            }
    }
    system("cls");
    cin.ignore();
    cout<<endl<<" ПРОДОВЖЕННЯ РЕЄСТРАЦІЇ КАРТИ "<<endl
    <<" Введіть номер карти"<<endl<<" >";
    getline(cin, _string);

    tempC.Set_Number(_string);
    cout<<endl<<" Введіть, карта дійсна до:"<<endl<<" >";
    getline(cin, _string);
    tempC.Set_ValidTo(_string);

    myBank.GetCart().push_back(tempC);

    system("cls");
}
