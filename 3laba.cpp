#include<bits/stdc++.h>
#include<string>
#include<iostream>
#include<algorithm>
#include "pugixml.cpp"
using namespace std;
struct Station_info
{
    string type_of_vehicle;
    string object_type;
    string name_stopping;
    string the_official_name;
    string location;
    vector <string> routes;
    double coordinate_x, coordinate_y;
};
int stoi(const string &S)
{
    int i = 0;
    for(int s = 0; s < S.length(); s++)
    {
        i *= 10;
        i += S[s] - '0';
    }
    return i;
}
double stod(const string &S)
{
    double d_int = 0, d_double = 0;
    int dot_place;
    for(int s = 0; s < S.length(); s++) if(S[s] == '.') dot_place = s;
    for(int s = dot_place - 1; s >= 0; s--)
    {
        d_int *= 10;
        d_int += S[s] - '0';
    }
    for(int s = dot_place + 1; s < S.length(); s++)
    {
        d_double += pow(10, dot_place - s) * (S[s] - '0');
    }
    return (d_int + d_double);
}
int main()
{
    system("chcp 65001");
    pugi::xml_document doc;
    doc.load_file("information.xml");
    pugi::xml_node data = doc.child("dataset");
    Station_info station[7628];
    for(pugi::xml_node one_station = data.child("transport_station"); one_station; one_station = one_station.next_sibling())
    {
        int it = stoi(one_station.child("number").child_value()) - 1;
        station[it].type_of_vehicle = one_station.child("type_of_vehicle").child_value();
        station[it].object_type = one_station.child("object_type").child_value();
        station[it].name_stopping = one_station.child("name_stopping").child_value();
        station[it].the_official_name = one_station.child("the_official_name").child_value();
        station[it].location = one_station.child("location").child_value();
        string R = one_station.child("routes").child_value();
        int j = 0;
        while(j < R.length())
        {
            string route;
            while(j < R.length() && R[j] != ',' && R[j] != '.')
            {
                route += R[j];
                j++;
            }
            station[it].routes.push_back(route);
            while(j < R.length() && (R[j] != ',' || R[j] != '.')) j++;
        }
        string C = one_station.child("coordinates").child_value();
        string C1 = "", C2 = "";
        int t = 1;
        for(int i = 0; i < C.length(); i++)
        {
            if(t == 2) C2 += C[i];
            if(C[i] == ',') t = 2;
            if(t == 1) C1 += C[i];
        }
        station[it].coordinate_x = stod(C1);
        station[it].coordinate_y = stod(C2);
    }
    map <string, int> quantity_stations;

    for(int i = 0; i < 7628; i++) for(int j = 0; j < station[i].routes.size(); j++) quantity_stations[station[i].routes[j]]++;
    string max_route;
    int ma = 0;
    for(auto q: quantity_stations) if(ma < q.second)
    {
        ma = q.second;
        max_route = q.first;
    }
    cout << max_route << " route include " << ma << " stations." << endl;
}
