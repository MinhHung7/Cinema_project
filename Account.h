#pragma once
#include<iostream>
using namespace std;
class Account{
    private:
        string name, phone, email, password, dob, gender;
    public:
        Account(){
            name="";
            phone="";
            email="";
            password="";
            dob="";
            gender="";
        }
        Account(string name,string phone,string email,string password,string dob, string gender){
            this->name=name;
            this->phone=phone;
            this->email=email;
            this->password=password;
            this->dob=dob;
            this->gender=gender;
        }
        void setName(string name){
            this->name=name;
        }
        string getName(){
            return name;
        }
        void setPhone(string phone){
            this->phone=phone;
        }
        string getPhone(){
            return phone;
        }
        void setEmail(string email){
            this->email=email;
        }
        string getEmail(){
            return email;
        }
        void setPassword(string password){
            this->password = password;
        }
        string getPassword(){
            return password;
        }
        void setDob(string dob){
            this->dob=dob;
        }
        string getDob(){
            return dob;
        }
        void setGender(string gender){
            this->gender = gender;
        }
        string getGender(){
            return gender;
        }
};