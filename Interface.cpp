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

