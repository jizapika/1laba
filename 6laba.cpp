#include<bits/stdc++.h>
using namespace std;
class Cube
{
private:
    vector <vector <vector <int> > > scan;
    int cur_front_center = 0;
    int cur_up_center = 3;
public:
    explicit Cube(const vector <vector <vector <int> > > &put_scan)
    {
         scan = put_scan;
    }
    vector <vector <vector <int> > > getter_scan()
    {
        return scan;
    }
    pair<int, int> getter_orientation()
    {
        return {cur_front_center, cur_up_center};
    }
    void side0_depth_clock(int depth)
    {
        // глубина прокрутки слоя, показывает перебег полосок от соседей.
        // если depth = 1, то это вращение одного слоя.
        if(depth > scan[0].size()) return;
        vector <vector <vector <int> > > old_scan = scan;
        for(int j = 0; j < scan[0].size(); j++)
        {
            scan[1][depth-1][j] = old_scan[2][depth-1][j];
            scan[2][depth-1][j] = old_scan[3][depth-1][j];
            scan[3][depth-1][j] = old_scan[4][depth-1][j];
            scan[4][depth-1][j] = old_scan[1][depth-1][j];
        }
    }
    void side0_clock()
    {
        vector <vector <vector <int> > > old_scan = scan;
        for(int i = 0; i < scan[0].size(); i++) for(int j = 0; j < scan[0].size(); j++)
        {
            scan[0][i][j] = old_scan[0][j][scan[0].size() - 1 - i];
        }
        side0_depth_clock(1);
    }
    void side0_depth_counter(int depth)
    {
        if(depth > scan[0].size()) return;
        vector <vector <vector <int> > > old_scan = scan;
        for(int j = 0; j < scan[0].size(); j++)
        {
            scan[1][depth-1][j] = old_scan[4][depth-1][j];
            scan[2][depth-1][j] = old_scan[1][depth-1][j];
            scan[3][depth-1][j] = old_scan[2][depth-1][j];
            scan[4][depth-1][j] = old_scan[3][depth-1][j];
        }
    }
    void side0_counter()
    {
        vector <vector <vector <int> > > old_scan = scan;
        for(int i = 0; i < scan[0].size(); i++) for(int j = 0; j < scan[0].size(); j++)
        {
            scan[0][i][j] = old_scan[0][scan[0].size() - 1 - j][i];
        }
        side0_depth_clock(1);
    }
    void side1_depth_clock(int depth)
    {
        if(depth > scan[0].size()) return;
        vector <vector <vector <int> > > old_scan = scan;
        for(int j = 0; j < scan[0].size(); j++)
        {
            scan[0][scan[0].size()-depth][scan[0].size()-j-1] = old_scan[4][j][scan[0].size()-depth];
            scan[2][depth-1][j] = old_scan[0][depth-1][j];
            scan[4][depth-1][j] = old_scan[5][depth-1][j];
            scan[5][depth-1][j] = old_scan[2][depth-1][j];
        }
    }

};
Cube new_cube()
{
    cout << "Please, enter size of cube: " << endl;
    int size_of_cube;
    cin >> size_of_cube;
    vector <vector <vector <int> > > my_scan(6, vector< vector<int> > (size_of_cube, vector<int> (size_of_cube)));
    cout << "Please, enter scan of cube in this view: " << endl << endl;
    for(int i = 0; i < size_of_cube; i++)
    {
        for(int j = 0; j < size_of_cube; j++)
        {
            cout << "0 ";
        }
        cout << endl;
    }
    cout << endl;
    for(int i = 0; i < size_of_cube; i++)
    {
        for(int c = 1; c <= 4; c++)
        {
            for(int j = 0; j < size_of_cube; j++)
            {
                cout << c << " ";
            }
            cout << " ";
        }
        cout << endl;
    }
    cout << endl;
    for(int i = 0; i < size_of_cube; i++)
    {
        for(int j = 0; j < size_of_cube; j++)
        {
            cout << "5 ";
        }
        cout << endl;
    }
    cout << endl;
    cout << "-----------------------" << endl;
    for(int i = 0; i < size_of_cube; i++) for(int j = 0; j < size_of_cube; j++) cin >> my_scan[0][i][j];
    for(int i = 0; i < size_of_cube; i++) for(int c = 1; c <= 4; c++) for(int j = 0; j < size_of_cube; j++) cin >> my_scan[c][i][j];
    for(int i = 0; i < size_of_cube; i++) for(int j = 0; j < size_of_cube; j++) cin >> my_scan[5][i][j];
    Cube my_cube(my_scan);
    return my_cube;
}
void print_cube(const Cube &cube)
{
    vector <vector <vector <int> > > my_scan = cube.getter_scan();
    int size_of_cube = my_scan[0].size();
    for(int i = 0; i < size_of_cube; i++)
    {
        for(int j = 0; j < size_of_cube; j++)
        {
            cout << my_scan[0][i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    for(int i = 0; i < size_of_cube; i++)
    {
        for(int c = 1; c <= 4; c++)
        {
            for(int j = 0; j < size_of_cube; j++)
            {
                cout << my_scan[c][i][j] << " ";
            }
            cout << " ";
        }
        cout << endl;
    }
    cout << endl;
    for(int i = 0; i < size_of_cube; i++)
    {
        for(int j = 0; j < size_of_cube; j++)
        {
            cout << my_scan[5][i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}
void assembly_3to3(const Cube &cube)
{

}
void assembly(const Cube &cube)
{

}
int main()
{
    Cube my_cube = new_cube();
    print_cube(my_cube);
    my_cube.side0_clock();
    print_cube(my_cube);
  //  assembly(my_cube);
}
/*
3

3 0 0
0 0 1
0 0 1

2 2 4  5 5 2  3 3 5  4 1 1
0 1 1  2 2 2  3 3 4  3 4 4
1 4 4  0 2 2  3 3 4  3 4 5

2 1 1
5 5 5
0 5 5
*/
