#include "Data.h"

#include <iostream>

using namespace std;

Data::Data(){
    this->input_cnt = 0;
    this->replace_cnt = 0;
    this->resize_cnt = 0;
}

int Data::getInputCnt(){
    return input_cnt;
}

int Data::getReplaceCnt(){
    return replace_cnt;
}

int Data::getResizeCnt(){
    return resize_cnt;
}

void Data::increaseInputCnt(){
    input_cnt++;
}

void Data::increaseReplaceCnt(){
    replace_cnt++;
}

void Data::increaseResizeCnt(){
    resize_cnt++;
}

void Data::reset(){
    input_cnt = replace_cnt = 0;
}

void Data::print(int size, int capacity){
    int num = 21;
    cout.width(110); cout.fill('='); cout << "" << endl;

    // SIZE // CAPACITY // input // replace // resize
    cout.width(num); cout.fill(' '); cout.flags(ios::left);
    cout << "SIZE" << "|";
    cout.width(num); cout.fill(' '); cout.flags(ios::left);
    cout << "CAPACITY" << "|";
    cout.width(num); cout.fill(' '); cout.flags(ios::left);
    cout << "INPUT" << "|";
    cout.width(num); cout.fill(' '); cout.flags(ios::left);
    cout << "REPLACE" << "|";
    cout.width(num); cout.fill(' '); cout.flags(ios::left);
    cout << "RESIZE" << "|\n\r";

    cout.width(110); cout.fill('='); cout << "" << endl;

    cout.width(num); cout.fill(' '); cout << size << "|";
    cout.width(num); cout.fill(' '); cout << capacity << "|";
    cout.width(num); cout.fill(' '); cout << input_cnt << "|";
    cout.width(num); cout.fill(' '); cout << replace_cnt << "|";
    cout.width(num); cout.fill(' '); cout << resize_cnt << "|\n\r";

    cout.width(110); cout.fill('='); cout << "" << endl;
}