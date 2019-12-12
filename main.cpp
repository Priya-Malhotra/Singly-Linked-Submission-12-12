#include <iostream>
#include <fstream>
#include <cmath>
#include "slist.h"

#include <stdlib.h>
using namespace std;
//the one in the lib

void mergeSort(slist* arr, int l, int r);
double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d);
void merge(slist* arr, int l, int m, int r);


int main(){
 ifstream infile;
 int i=0;
 char cNum[10] ;
 slist* airportList = new slist();
 int airportCount = 0;

 infile.open ("USAirportCodes.csv", ifstream::in);
 if (infile.is_open()){
 //int c=0;
 while (infile.good()){


 Airport* current = new Airport();
 infile.getline(current->code, 256, ',');
 infile.getline(cNum, 256, ',');
 current->longitude = atof(cNum);
 infile.getline(cNum, 256, '\n');
 current->latitude = atof(cNum);
 airportList->add(*current);
 airportCount++;

 delete current;
 i++ ;

 }
 
 infile.close();

 }
 else
 {
 cout << "Error opening file";
 }


 cout << "List of Airports 100 miles from Austin" << endl;
 
 
 int countNum = 1;
 for(int i = 0; i < 13430; i++) {
 if(distanceEarth(airportList->get(i).latitude, airportList->get(i).longitude, 97.6664, 30.1975) <=160.934) {
 cout << countNum << ": code: " << airportList->get(i).code << " long: " << airportList->get(i).longitude << " lat: " << airportList->get(i).latitude << " Distance: " << distanceEarth(airportList->get(i).latitude, airportList->get(i).longitude, 97.6664, 30.1975) << endl;
  countNum++;
 }
 }


 cout << "--------------------------" << endl;
 cout << "Unsorted List" << endl;
 //airportList->toString();


 //don't want to print out everything so commenting out this chunk
 ///farthest airport area
 cout << "--------------------------" << endl;
 cout << "Sorted List" << endl;
 mergeSort(airportList, 0, 13430);
 airportList->toString(); //1: ADK 176.646 51.8781 //13429: WRL 107.951 43.9658
 cout << "--------------------------" << endl;
 cout << "farthest distance " << endl;
 cout << "code " << airportList->get(1).code << " lat: " << airportList->get(1).latitude << " long: " << airportList->get(1).longitude << " Distance:" << distanceEarth(airportList->get(0).latitude, airportList->get(0).longitude, 30.1975, 97.6664) << endl;


}

#define pi 3.14159265358979323846
#define earthRadiusKm 6371.0

// This function converts decimal degrees to radians
double deg2rad(double deg) {
 return (deg * pi / 180);
}

// This function converts radians to decimal degrees
double rad2deg(double rad) {
 return (rad * 180 / pi);
}


/**
 * Returns the distance between two points on the Earth.
 * Direct translation from http://en.wikipedia.org/wiki/Haversine_formula
 * @param lat1d Latitude of the first point in degrees
 * @param lon1d Longitude of the first point in degrees
 * @param lat2d Latitude of the second point in degrees
 * @param lon2d Longitude of the second point in degrees
 * @return The distance between the two points in kilometers
 */
double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d) {
 double lat1r, lon1r, lat2r, lon2r, u, v;
 lat1r = deg2rad(lat1d);
 lon1r = deg2rad(lon1d);
 lat2r = deg2rad(lat2d);
 lon2r = deg2rad(lon2d);
 u = sin((lat2r - lat1r)/2);
 v = sin((lon2r - lon1r)/2);
 return 2.0 * earthRadiusKm * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));
}
//one that is in the static lib


/*
	Provide sort routine on linked list
*/

void merge(slist* arr, int l, int m, int r) {
 int i, j, k;
 int n1 = m - l + 1;
 int n2 = r - m;


 slist* L = new slist();
 slist* R = new slist();


 for (i = 0; i < n1; i++){
 L->get(i) = arr->get(l + i);
 }
 for (j = 0; j < n2; j++) {
 R->get(j) = arr->get(m + 1 + j);
 }

 i = 0;
 j = 0;
 k = l;
 while (i < n1 && j < n2){

 if ( distanceEarth(L->get(i).latitude, L->get(i).longitude, 30.1975, 97.6664) <= distanceEarth( R->get(j).latitude, R->get(j).longitude, 30.1975, 97.6664 )){
 arr->get(k) = L->get(i);
 i++;
 }
 else
 {
 arr->get(k) = R->get(j);
 j++;
 }
 k++;
 }


 while (i < n1) {
 arr->get(k) = L->get(i);
 i++;
 k++;
 }


 while (j < n2){
 arr->get(k) = R->get(j);
 j++;
 k++;
 }
}

void mergeSort(slist* arr, int l, int r) {
 if (l < r) {

 int m = l+(r-l)/2;


 mergeSort(arr, l, m);
 mergeSort(arr, m+1, r);

 merge(arr, l, m, r);
 }
}