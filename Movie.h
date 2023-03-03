#pragma once
#include<iostream>
#include<vector>
using namespace std;
class Movie{ // genres {ten, thoigian, ngay, thoi luong, gia}
    private:
        vector<string> genres;
        string name;
        string time;
        string date;
        string period;
        string price;
    public:
    vector<string> getGenres(){
        return this->genres;
    }
    void addGenre(string genre){
        this->genres.push_back(genre);
    }
    void setName(string name){
        this->name=name;
    }
    void setDate(string date){
        this->date = date;
    }
    void setTime(string time){
        this->time= time;
    }
    void setPeriod(string period){
        this->period = period;
    }
    void setPrice(string price){
        this->price = price;
    }
    string getName(){
        return this->name;
    }
    string getDate(){
        return this->date;
    }
    string getTime(){
        return this->time;
    }
    string getPeriod(){
        return this->period;
    }
    string getPrice(){
        return this->price;
    }
};