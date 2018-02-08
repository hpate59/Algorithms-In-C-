//
//  classes.h
//  Project-2
//
//  Created by Harshil Patel on 2/1/18.
//  Copyright © 2018 UIC. All rights reserved.
//

#ifndef classes_h
#define classes_h


#endif /* classes_h */

/*classes.h*/

//
// Classes for use with Chicago Crime Analysis program, e.g. "CrimeReport"
// and "CrimeCode".
//
// << Harshil Patel >>
// U. of Illinois, Chicago
// CS 341: Spring 2018
// Project 02
//

#pragma once

#include <iostream>
#include <string>

using namespace std;

class CrimeCode
{
public:
    string IUCR;
    string Primary_Description;
    string Secondry_Description;
    int count = 0 ;
    
public:
    CrimeCode(string iucr, string pd, string sd, int x)
    :IUCR(iucr), Primary_Description(pd), Secondry_Description(sd), count(x)
    {}
    
    string getIUCRcrime() const{
        return IUCR;
    }
    
    string getPrimaryDes() const{
        return Primary_Description;
    }
    
    string getSecondaryDes() const{
        return Secondry_Description;
    }
    
    int getCount() const{
        return count;
    }
    
    void setCount() {
        count++;
    }
    
};

class CrimeReport
{
private:
    string dateNtime;
    string IUCR;
    string Arrest;
    string DomesticViolence;
    int Beat;
    int District;
    int Ward;
    int Community;
    int Year;

public:
    CrimeReport(string dt, string iucr, string arr, string dv, int beat, int dis, int wrd, int comm, int year)
    : dateNtime(dt), IUCR(iucr), Arrest(arr), DomesticViolence(dv), Beat(beat),
      District(dis), Ward(wrd), Community(comm), Year(year)
    {}
    
    string getDateNtime() const{
        return dateNtime;
    }
    
    string getIUCR() const{
        return IUCR;
    }
    
    string getArrest() const{
        return Arrest;
    }
    
    string getDV() const{
        return DomesticViolence;
    }
    
    int getBeat() const{
        return Beat;
    }
    
    int getDistrict() const{
        return District;
    }
    
    int getWard() const{
        return Ward;
    }
    
    int getCommunity() const{
        return Community;
    }
    
    int getYear() const{
        return Year;
    }
};
