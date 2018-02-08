//
//  main.cpp
//  Project-2
//
//  Created by Harshil Patel on 2/1/18.
//  Copyright © 2018 UIC. All rights reserved.
//

/*main.cpp*/

//
// Chicago Crime Analysis program in modern C++.
//
// <<Harshil Patel>>
// U. of Illinois, Chicago
// CS 341: Spring 2018
// Project 02
//

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>

#include "classes.h"

using namespace std;

/*
 * The function sorts the vector inorder by
 * the IUCR codes so that the smallest IUCR
 * code is not the top. The function uses an
 * inbuilt sort algorithm.
 */
vector<CrimeCode> SortByIUCR(vector<CrimeCode> &codes){
    
    //call the sort algorithm
    
    sort(codes.begin(), codes.end(),
    [](CrimeCode &c1, CrimeCode &c2){
        if(c1.getIUCRcrime() < c2.getIUCRcrime()){
            return true;
        }else{
            return false;
        }
    }); //end of sort
    
    //return the sorted vector.
    return codes;
}//end of fucntion

/*
 * Function takes in  a map and converts it into
 * map into a muktimap with key of type int and value of type
 * CrimeCode and transfers data accrodinly
 */
multimap<int, CrimeCode> MapToMultimap(map<string, CrimeCode> &M){
    
    std:: multimap<int, CrimeCode> newMap;
    
    for(std:: pair<string, CrimeCode> keyvaluepair: M){
        auto key = keyvaluepair.second.getCount();
        auto value = keyvaluepair.second;
        
        auto newKeyvaluepair = pair<int, CrimeCode>(key, value);
        newMap.insert(newKeyvaluepair);
    }
    
    return newMap;
}//end of function

/*
 * A function which converts a vector to a map
 * with key as a string(IUCR) and value of type CrimeCode
 * the fucntion aslo transfers data from vector to map.
 */
 map<string, CrimeCode> Vector2iucr(const vector<CrimeCode> &codes){
    
     // make a map
    std:: map<string, CrimeCode> transfer;
    
     //loop thriugh the vector and insert key and value into map.
    for(const CrimeCode &c1 : codes ){
        auto keyValPair = pair<string, CrimeCode>(c1.getIUCRcrime(), c1);
        
        transfer.insert(keyValPair);
    }
    //ordered by string i.e IUCR
    return transfer;
}//end of function

/*
 * A function which uses a map to lookup
 * iucr in the map and then increment the count
 * accordingly.
 */
void lookUp(map<string, CrimeCode> &M, string iucr){
    
    //finds the IUCR
    auto itr = M.find(iucr);
    
    //Set the count.
    itr->second.setCount();
}//end of function

int main()
{
    string  crimeCodesFilename, crimesFilename;
    
    cin >> crimeCodesFilename;
    cout << crimeCodesFilename << endl;
    
    cin >> crimesFilename;
    cout << crimesFilename << endl;
    
    ifstream  codesFile(crimeCodesFilename);
    ifstream  crimesFile(crimesFilename);
    
    cout << std::fixed;
    cout << std::setprecision(2);
    
    //check if the file opened correctly or the file name is valid
    if (!codesFile.good())
    {
        cout << "**ERROR: cannot open crime codes file: '" << crimeCodesFilename << "'" << endl;
        return -1;
    }
    if (!crimesFile.good())
    {
        cout << "**ERROR: cannot open crimes file: '" << crimesFilename << "'" << endl;
        return -1;
    }
    
    //Lets parse the crimeCodesFile first:
    string iucr, pd, sd, line;
    
    vector<CrimeCode> codes;
    
    getline(codesFile, line);
    while(getline(codesFile, line)){
        stringstream ss(line);
        
        //parse the line
        getline(ss, iucr, ',');
        getline(ss, pd, ',');
        getline(ss, sd, ',');
        
        CrimeCode info(iucr, pd, sd,0);
        
        //push the data into vector
        codes.push_back(info);
    }//end of while
    
    //Conveert the vector to map with iucr as key and CrimeCodes as value
    auto M = Vector2iucr(codes);

    //Parse the CrimesFile
    
    string iucrCrimes, dt;
    string arr,domestic;
    string beat,dis,ward,comm,year;
    
    vector<CrimeReport> crimes;
    
    getline(crimesFile,line);
    while(getline(crimesFile, line)){
        stringstream ss(line);
        
        //parse the data
        getline(ss, dt, ',');
        getline(ss, iucrCrimes, ',');
        getline(ss, arr, ',');
        getline(ss, domestic, ',');
        getline(ss, beat, ',');
        getline(ss, dis, ',');
        getline(ss, ward, ',');
        getline(ss, comm, ',');
        getline(ss, year, ',');
        
        CrimeReport info(dt, iucrCrimes, arr, domestic, stoi(beat), stoi(dis), stoi(ward), stoi(comm), stoi(year));
        
        /*
         * A lookUp function which takes a map and the iucr
         * and then looks up that IUCR in the map and if found
         * we increment the count accordingly
         */
        lookUp(M, iucrCrimes);
        
        crimes.push_back(info);
    }
    
    cout << "** Crime Analysis **" << endl << endl;
    
    //print out the range of dates from the crimes report file.
    //it is the first and the last entrile in the crimes file.
    cout<< "Date range: " << crimes[0].getDateNtime() << " - " << crimes[crimes.size()-1].getDateNtime() << endl <<endl;
    
    /*
     * sort the customes by iucr codes by
     * the IUCR so that the smallest IUCR is
     * displayed first.
     */
    codes = SortByIUCR(codes);
    
    /*
     * print out thr first and the last three
     * entries int the crimes file and also print the
     * total numbe of codes in the file.
     */
    cout << "# of crime codes: " << codes.size() << endl;
    int count = 0;
    for(CrimeCode &c1 : codes){
        if( count < 3 || count > codes.size() - 4){
        cout << c1.getIUCRcrime() << ":  " << c1.getPrimaryDes() << ":" << c1.getSecondaryDes() << endl;
        }
        if(count == 4){
            cout << "..." << endl;
        }
        count ++;
    }
    
    cout << endl;
    
    //print the total number of crimes.
    cout << "# of crimes: " << crimes.size() << endl;
    
    int count2 = 0;
    
    /*
     * print out thr first and the last three
     * entries int the crime report file.
     */
    for(CrimeReport &c2 : crimes){
        if(count2 < 3 || count2 > crimes.size() - 4){
           
            cout << c2.getIUCR() << ":  " << c2.getDateNtime() <<
            ", " << c2.getBeat() << ", " << c2.getDistrict() <<
            ", " << c2.getWard() << ", " << c2.getCommunity() ;
            if(c2.getArrest() == "TRUE" || c2.getArrest() == "true"){
                cout << ", arrested";
            }
            if(c2.getDV() == "TRUE" || c2.getDV() == "true"){
                cout << ", domestic violence";
            }
            cout << endl;
        }
    
        if(count2 == 4){
            cout << "..." << endl;
        }
        count2++;
    }//end of for
    
    /*
     * Now we print the Top-5 crimes
     */
    cout << endl ;
    cout << "** Top-5 Crimes **" << endl << endl;
    
    cout<< "Code:   Total, Description "<< endl;
    auto codesByCrimes = MapToMultimap(M);
    int count3 = 0;
    /*
     * As the multi map is sorted by the asceding order of the
     * number of crimes we tend to print it in reverse order using the
     * the reverse iterator and then we only print out the first 5 elemnts
     * to show the top 5 crimes.
     */
    std:: multimap<int,CrimeCode> :: reverse_iterator itr;
    for(itr = codesByCrimes.rbegin(); itr != codesByCrimes.rend(); ++itr){
        
        auto key = itr->first;
        auto value = itr->second;
        
        //print the required output
        cout << value.getIUCRcrime() << ":   " << key <<", "<< value.getPrimaryDes()<< ": " << value.getSecondaryDes() << endl;
        
        //since we have to print only the top 5
        if(count3 == 4){
            break;
        }
        count3++;
    }// end of for
    
    //done
    cout << endl;
    cout<< "** Done **" << endl;
    return 0;
}//end of main
