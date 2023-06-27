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

