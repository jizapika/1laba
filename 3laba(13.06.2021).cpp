#include<bits/stdc++.h>
#include<string>
#include<iostream>
#include<algorithm>
#include "pugixml.cpp"

#define pii pair<int,int>
#define vi vector<int>
#define f first
#define s second
#define pb push_back
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
struct Route
{
    string name;
    string type_of_vehicle;
    vector <Station_info> cur_station;
    int id;
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
    for(int s = 0; s < dot_place; s++)
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
double Earth_radius = 6371300;
double length(Station_info &A, Station_info &B)
{
    double L = sqrt((A.coordinate_x - B.coordinate_x)*(A.coordinate_x - B.coordinate_x) + (A.coordinate_y - B.coordinate_y)*(A.coordinate_y - B.coordinate_y));
    return Earth_radius * L * atan(1) / 45;
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

    map <string, Route> route;
    for(int i = 0; i < 7628; i++)
    {
        for(int j = 0; j < station[i].routes.size(); j++)
        {
            route[station[i].routes[j]].name = station[i].routes[j];
            route[station[i].routes[j]].cur_station.pb(station[i]);
            route[station[i].routes[j]].id = i;
            route[station[i].routes[j]].type_of_vehicle = station[i].type_of_vehicle;
        }
    }
    map <string, pair<string, int> > type_route;
    for(auto q: route)
    {
        if(type_route[q.s.type_of_vehicle].s < q.s.cur_station.size())
        {
            type_route[q.s.type_of_vehicle] = {q.s.name, q.s.cur_station.size()};
        }
    }
    for(auto q: type_route)
    {
        cout << "The best route in " << q.f << " is a " << q.s.f << " route, that included " << q.s.s << " stations" << endl;
    }

    map <string, pair<string, double> > type_length;
    double max_minimal_length = 0;
    for(auto q: route)
    {
        double L[q.s.cur_station.size()][q.s.cur_station.size()];
        for(int i = 0; i < q.s.cur_station.size(); i++) for(int j = 0; j < q.s.cur_station.size(); j++)
        {
            L[i][j] = length(q.s.cur_station[i], q.s.cur_station[j]);
        }
        double MI[q.s.cur_station.size()];
        for(int i = 0; i < q.s.cur_station.size(); i++) MI[i] = 1e9;
        MI[0] = 0;
        bool used[q.s.cur_station.size()];
        for(int i = 0; i < q.s.cur_station.size(); i++) used[i] = false;
        used[0] = true;
        int cur = 0;
        double weight = 0;
        for(int i = 0; i < q.s.cur_station.size() - 1; i++)
        {
            for(int j = 0; j < q.s.cur_station.size(); j++) if(!used[j]) MI[j] = min(MI[j], L[cur][j]);
            double minimal_length = 1e8;
            int id = -1;
            for(int j = 0; j < q.s.cur_station.size(); j++) if(!used[j])
            {
                if(minimal_length > MI[j])
                {
                    minimal_length = MI[j];
                    id = j;
                }
            }
            weight += minimal_length;
            used[id] = true;
            cur = id;
        }
        if(type_length[q.s.type_of_vehicle].s < weight)
        {
            type_length[q.s.type_of_vehicle] = {q.s.name, weight};
        }
    }
    for(auto q: type_length)
    {
        cout << "The longest route in " << q.f << " is a " << q.s.f << " route that " << q.s.s << " m" << endl;
    }

    map <string, int> street;
    for(int i = 0; i < 7628; i++)
    {
        string loc = station[i].location;
        int j = 0;
        while(j < loc.length())
        {
            while(loc[j] == ' ') j++;
            string T = "";
            while(j < loc.length() && loc[j] != ',')
            {
                T += loc[j];
                j++;
            }
            street[T]++;
            j++;
        }
    }
    int max_street = 0;
    string big_street;
    for(auto q: street)
    {
        if(max_street < q.s)
        {
            max_street = q.s;
            big_street = q.f;
        }
    }
    cout << big_street << " includes " << max_street << " stations." << endl;
}
