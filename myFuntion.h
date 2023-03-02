#include<iostream>
#include<vector>
#include<iomanip>
#include<windows.h>
#include<exception>
#include"Account.h"
#include<string>
#include<fstream>
#include"Movie.h"
#include<stdlib.h>
#include<time.h>

using namespace std;

void homePage(Account);
void signInUpPage(Account);

int checkAndReturnYourChoose(Account user, string buffer, int status, const vector<string>menu){
    int choose;
    try{
        choose = stoi(buffer);
        if(choose<0 || choose > menu.size()){
            throw(0);
        }
        return choose;
    }
    catch(int n){
        cout<<"PLEASE ENTER A NUMBER FROM 0 TO "<<menu.size()<<"!!!";
        Sleep(1000);
        system("cls");
        if(status == 1) homePage(user);
        else if(status == 2) signInUpPage(user);
    }
    catch(exception e){
        cout<<"PLEASE ENTER A NUMBER!!!";
        Sleep(1000);
        system("cls");
        if(status == 1) homePage(user);
        else if(status == 2) signInUpPage(user);
    }
}

void makeMenu(string tittle,vector<string>vt,string footText){
    int maxLength=tittle.size();
    for(string x:vt){
        if(x.size() > maxLength) maxLength=x.size();
    }
    maxLength+=20;
    cout<<"+"<<setfill('-')<<setw(maxLength)<<right<<"+"<<"\n";
    int spaceLeft = (int)(maxLength-tittle.size())/2;
    cout<<setfill(' ')<<setw(spaceLeft)<<left<<"|"<<setw(maxLength-spaceLeft)<<left<<tittle; cout<<"|"<<"\n";
    cout<<"+"<<setfill('-')<<setw(maxLength)<<right<<"+"<<"\n";

    for(int i=0;i<=vt.size();++i){
        if(i==vt.size()){
            cout<<"| "<<i<<". "<<setfill(' ')<<setw(maxLength-5)<<left<<footText<<"|\n";
        }
        else cout<<"| "<<i<<". "<<setfill(' ')<<setw(maxLength-5)<<left<<vt[i]<<"|\n";
    }
     cout<<"+"<<setfill('-')<<setw(maxLength)<<right<<"+"<<"\n";
}

bool checkValidDob(string& dob){
    int dateInMonth[13]= {0,31,28,31,30,31,30,31,31,30,31,30,31};

    int date, month, year;
    date = stoi(dob.substr(0,2));
    month = stoi(dob.substr(3,2));
    year = stoi(dob.substr(6,4));
    if(year % 400==0 || (year %4==0 && year %100 !=0 && year %400!=0)){
        dateInMonth[2]=29;
    }
    if(date>dateInMonth[month]){
        return false;
    }
    else if(year < 1000){
        return false;
    }
    return true;
}

bool checkDob(string &dob){
    if(dob.size()!=10){
        return false;
    }
    for(int i=0;i<dob.size();++i){
        if(i==2 || i==5){
            if(dob[i]!='/'){
                return false;
            }
        }
        else if(dob[i] <'0' || dob[i]>'9'){
            return false;
        }
    }
    return checkValidDob(dob);
}

bool checkPhone(string& phone){
    if(phone.size()!=10  && phone.size()!=11){
        return false;
    }

    for(int i=0;i<phone.size();++i){
        if(phone[i]<'0' && phone[i]>'9'){
            return false;
        }
    }
    return true;
}

void signInUpPage(Account user){
    string tittle="Dang nhap/Dang ki";
    vector<string>menu={"Sign in","Sign up"};
    string footText = "Back";
    makeMenu(tittle,menu,footText);
    cout<<"| Enter your choose: ";
    string buffer; getline(cin,buffer);

    int choose = checkAndReturnYourChoose(user, buffer, 2, menu);
    switch(choose){
        case 0:{
            system("cls");
            cout<<"\t\tSIGN IN\n";
            string email;
            do{
                cout<<"Enter your email: ";
                email=""; getline(cin,email);
            }
            while(email.find("@gmail.com") <= 0 || email.find("@gmail.com") >= email.size());

            string password;
            do{
                cout<<"Enter your password: ";
                password=""; getline(cin,password);
            }
            while(password.size() < 8);

            if(email != user.getEmail() || password != user.getPassword()){
                cout<<"Warning: Unsuccessfullly sign in!!!";
                Sleep(2000);
                system("cls");
                signInUpPage(user);
            }
            break;
        }
        case 1:{
            system("cls");
            cout<<"\t\t SIGN UP\n";
            cout<<"Enter your name: ";
            string name; getline(cin, name);
            string dob;
            do{
                cout<<"Enter your date of birth (01/02/2022): ";
                getline(cin,dob);
            }
            while(checkDob(dob)==false);
            string phone;
            do{
                cout<<"Enter your phone: ";
                getline(cin,phone);
            }
            while(checkPhone(phone)==false);
            string gender;
            do{
                cout<<"Enter your gender (Male/Female): ";
                getline(cin,gender);
            }
            while(gender!="Male" && gender!="Female");

            string email;
            do{
                cout<<"Enter your email: ";
                email=""; getline(cin,email);
            }
            while(email.find("@gmail.com") <= 0 || email.find("@gmail.com") >= email.size());

            string password;
            do{
                cout<<"Enter your password: ";
                password=""; getline(cin,password);
            }
            while(password.size() < 8);

            user.setName(name);
            user.setEmail(email);
            user.setPassword(password);
            user.setDob(dob);
            user.setGender(gender);
            user.setPhone(phone);
            system("cls");
            homePage(user);
            break;
        }
        default:{
            system("cls");
            homePage(user);
        }
    }

}
void typeGenes(string genres, Movie& movie){
    for(int i=0;i<genres.size();++i){
        if(genres[i]=='|'){
            genres[i]= ' ';
        }
    }
    string genre;
    stringstream ss(genres);
    while(ss >> genre){
        movie.addGenre(genre);
    }
}
void handle(const string line, vector<Movie>&movies){
    Movie movie;
    int beginPoint = line.find_first_of(',',0);
    int endPoint = line.find_first_of(',',beginPoint+1);
    int i=0;
    while(endPoint<line.size()){
        switch(i){
            case 0:{
                string genres = line.substr(beginPoint+1, endPoint-beginPoint-1);
                typeGenes(genres, movie);
                beginPoint = endPoint+1;
                endPoint = line.find_first_of(',',beginPoint);
                ++i;
                break;
            }
            case 1:{
                int posQuota = line.find_first_of('"');
                if(posQuota<line.size()){
                    beginPoint = posQuota+1;
                    endPoint = line.find_first_of('"',beginPoint);
                }
                string name = line.substr(beginPoint,endPoint-beginPoint);
                movie.setName (name);
                ++i;
                if(posQuota<line.size()) beginPoint = endPoint+2;
                else beginPoint=endPoint+1;
                endPoint = line.find_first_of(',',beginPoint);
                break;
            }
            case 2:{
                string date = line.substr(beginPoint,endPoint-beginPoint);
                movie.setDate(date);
                ++i;
                beginPoint = endPoint+1;
                endPoint = line.find_first_of(',',beginPoint);
                break;
            }
            case 3:{
                string time = line.substr(beginPoint,endPoint-beginPoint);
                movie.setTime(time);
                ++i;
                beginPoint = endPoint+1;
                endPoint = line.find_first_of(',',beginPoint);
                break;
            }
            case 4:{
                string period = line.substr(beginPoint,endPoint-beginPoint);
                movie.setPeriod(period);
                ++i;
                beginPoint = endPoint+1;
                endPoint = line.find_first_of(',',beginPoint);
                break;
            }
            default:{
                break;
            }
        }
    }
    string price = line.substr(beginPoint);
    movie.setPrice(price);
    movies.push_back(movie);
}
void show(vector<Movie>movies){
    system("cls");
    srand((int)time(0));
    int countShow=5;
    int firstMovie = rand()%(movies.size()-countShow-1);
    int lastMovie = firstMovie+countShow;
    for(int i=firstMovie;i<=lastMovie;++i){

        string tittle = movies[i].getName();
        vector<string>information;
        string genres="";
        for(int j=0;j<movies[i].getGenres().size();++j){
            if(j>0){
                genres += ", "+movies[i].getGenres()[j];
            }
            else{
                genres += movies[i].getGenres()[j];
            }
        }
        information.push_back("Genres: "+genres);
        information.push_back("Date: "+movies[i].getDate());
        information.push_back("Time: "+movies[i].getTime());
        information.push_back("Period: "+movies[i].getPeriod());
        information.push_back("Price: "+movies[i].getPrice());
        string footText = "";
        makeMenu(tittle, information, footText);
    }
}

void moviePage(const Account user){
    vector<Movie>movies;
    ifstream openToRead;
    openToRead.open("MovieData.txt",ios::in);
    if(openToRead.is_open()){
        while(!openToRead.eof()){
            string line;
            getline(openToRead,line);
            handle(line, movies);
        }
        openToRead.close();
        show(movies);
    }
    else{
        cout<<"Something went wrong!!!";
    }
}

void homePage(Account user){
    string tittle = "CINEMA (M.Hung)";
    vector<string>menu={"Dang nhap/Dang ki","Phim","Thanh vien","Dich vu"};
    string footText = "THOAT";
    makeMenu(tittle, menu, footText);
    cout<<"| Enter your choose: ";
    int choose=0;
    string buffer; getline(cin,buffer);

    choose = checkAndReturnYourChoose( user,  buffer,  1, menu);

    switch(choose){
        case 0:{
            system("cls");
            signInUpPage(user);
            break;
        }
        case 1:{
            system("cls");
            moviePage(user);
            break;
        }
        default:{
            return ;
        }
    }
    
}
