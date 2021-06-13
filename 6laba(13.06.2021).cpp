#include<bits/stdc++.h>
using namespace std;
class Cube
{
private:
    vector <vector <vector <int> > > scan;
    int cur_front_center = 0;
    int cur_up_center = 4;
    int cur_right_center = 3;
public:
    explicit Cube(const vector <vector <vector <int> > > &put_scan)
    {
         scan = put_scan;
    }
    explicit Cube(int size_of_cube)
    {
        scan.resize(6);
        for(int side = 0; side < 6; side++) scan[side] = vector< vector<int> > (size_of_cube, vector<int> (size_of_cube, side));
    }
    Cube(const Cube &cube_copy)
    {
        scan = cube_copy.getter_scan();
    }
    Cube& operator= (const Cube &cube)
    {
        scan = cube.getter_scan();
    }
    vector <vector <vector <int> > > getter_scan() const
    {
        return scan;
    }
    int opposite_side(int side)
    {
        if(side == 0 || side == 5) return 5 - side;
        if(side < 3) return side + 2;
        return side - 2;
    }
    void side_depth_clock(int side, int depth)
    {
        // глубина прокрутки слоя, показывает перебег полосок от соседей.
        // если depth = 1, то это вращение одного слоя.
        if(depth > scan[0].size()) return;
        vector <vector <vector <int> > > old_scan = scan;
        for(int j = 0; j < scan[0].size(); j++)
        {
            if(side == 0)
            {
                scan[1][depth-1][j] = old_scan[2][depth-1][j];
                scan[2][depth-1][j] = old_scan[3][depth-1][j];
                scan[3][depth-1][j] = old_scan[4][depth-1][j];
                scan[4][depth-1][j] = old_scan[1][depth-1][j];
            }
            if(side == 1)
            {
                scan[0][scan[0].size()-depth][scan[0].size()-j-1] = old_scan[4][j][scan[0].size()-depth];
                scan[2][scan[0].size()-j-1][depth-1] = old_scan[0][scan[0].size()-depth][scan[0].size()-j-1];
                scan[4][j][scan[0].size()-depth] = old_scan[5][depth-1][j];
                scan[5][depth-1][j] = old_scan[2][scan[0].size()-j-1][depth-1];
            }
            if(side == 2)
            {
                scan[0][j][scan[0].size()-depth] = old_scan[1][j][scan[0].size()-depth];
                scan[1][j][scan[0].size()-depth] = old_scan[5][j][scan[0].size()-depth];
                scan[3][scan[0].size()-j-1][depth-1] = old_scan[0][j][scan[0].size()-depth];
                scan[5][j][scan[0].size()-depth] = old_scan[3][scan[0].size()-j-1][depth-1];
            }
        }
        if(side > 2) side_depth_counter(opposite_side(side), scan[0].size()-depth+1);
        if(depth == 1)
        {
            for(int i = 0; i < scan[0].size(); i++) for(int j = 0; j < scan[0].size(); j++)
            {
                scan[side][i][j] = old_scan[side][scan[0].size() - 1 - j][i];
            }
        }
    }
    void side_depth_counter(int side, int depth)
    {
        if(depth > scan[0].size()) return;
        vector <vector <vector <int> > > old_scan = scan;
        for(int j = 0; j < scan[0].size(); j++)
        {
            if(side == 0)
            {
                scan[1][depth-1][j] = old_scan[4][depth-1][j];
                scan[2][depth-1][j] = old_scan[1][depth-1][j];
                scan[3][depth-1][j] = old_scan[2][depth-1][j];
                scan[4][depth-1][j] = old_scan[3][depth-1][j];
            }
            if(side == 1)
            {
                scan[4][j][scan[0].size()-depth] = old_scan[0][scan[0].size()-depth][scan[0].size()-j-1];
                scan[0][scan[0].size()-depth][scan[0].size()-j-1] = old_scan[2][scan[0].size()-j-1][depth-1];
                scan[5][depth-1][j] = old_scan[4][j][scan[0].size()-depth];
                scan[2][scan[0].size()-j-1][depth-1] = old_scan[5][depth-1][j];
            }
            if(side == 2)
            {
                scan[0][j][scan[0].size()-depth] = old_scan[3][scan[0].size()-j-1][depth-1];
                scan[1][j][scan[0].size()-depth] = old_scan[0][j][scan[0].size()-depth];
                scan[3][scan[0].size()-j-1][depth-1] = old_scan[5][j][scan[0].size()-depth];
                scan[5][j][scan[0].size()-depth] = old_scan[1][j][scan[0].size()-depth];
            }
        }
        if(side > 2) side_depth_clock(opposite_side(side), scan[0].size()-depth+1);
        if(depth == 1)
        {
            for(int i = 0; i < scan[0].size(); i++) for(int j = 0; j < scan[0].size(); j++)
            {
                scan[side][i][j] = old_scan[side][j][scan[0].size() - 1 - i];
            }
        }
    }
    void to_up()
    {
        cur_front_center = opposite_side(cur_front_center);
        swap(cur_front_center, cur_up_center);
    }
    void to_down()
    {
        cur_up_center = opposite_side(cur_up_center);
        swap(cur_front_center, cur_up_center);
    }
    void to_right()
    {
        cur_front_center = opposite_side(cur_front_center);
        swap(cur_front_center, cur_right_center);
    }
    void to_left()
    {
        cur_right_center = opposite_side(cur_right_center);
        swap(cur_front_center, cur_right_center);
    }
    void rotate_clock()
    {
        cur_up_center = opposite_side(cur_up_center);
        swap(cur_up_center, cur_right_center);
    }
    void rotate_counter()
    {
        cur_right_center = opposite_side(cur_right_center);
        swap(cur_up_center, cur_right_center);
    }
    void front_depth_clock(int depth)
    {
        side_depth_clock(cur_front_center, depth);
    }
    void front_depth_counter(int depth)
    {
        side_depth_counter(cur_front_center, depth);
    }
    void back_depth_clock(int depth)
    {
        side_depth_clock(opposite_side(cur_front_center), depth);
    }
    void back_depth_counter(int depth)
    {
        side_depth_counter(opposite_side(cur_front_center), depth);
    }
    void up_depth_clock(int depth)
    {
        side_depth_clock(cur_up_center, depth);
    }
    void up_depth_counter(int depth)
    {
        side_depth_counter(cur_up_center, depth);
    }
    void down_depth_clock(int depth)
    {
        side_depth_clock(opposite_side(cur_up_center), depth);
    }
    void down_depth_counter(int depth)
    {
        side_depth_counter(opposite_side(cur_up_center), depth);
    }
    void right_depth_clock(int depth)
    {
        side_depth_clock(cur_right_center, depth);
    }
    void right_depth_counter(int depth)
    {
        side_depth_counter(cur_right_center, depth);
    }
    void left_depth_clock(int depth)
    {
        side_depth_clock(opposite_side(cur_right_center), depth);
    }
    void left_depth_counter(int depth)
    {
        side_depth_counter(opposite_side(cur_right_center), depth);
    }
    void make_scramble(string S)
    {
        vector <vector <vector <int> > > save_scan = scan;
        vector <string> operations;
        int i = 0;
        while(i < S.length())
        {
            while(i < S.length() && S[i] == ' ') i++;
            string operation = "";
            while(i < S.length() && S[i] != ' ')
            {
                operation += S[i];
                i++;
            }
            operations.push_back(operation);
        }
        for(i = 0; i < operations.size(); i++)
        {
            int j = 0;
            int depth = 0;
            while(j < operations[i].length() && operations[i][j] >= '0' && operations[i][j] <= '9')
            {
                depth *= 10;
                depth += (operations[i][j] - '0');
                j++;
            }
            if(depth == 0) depth = 1;
            if(j == operations[i].length() || operations[i][0] == '0' || depth > scan[0].size() / 2 || j + 2 < operations[i].length())
            {
                cout << "You put a command \"" << operations[i] << "\" and it's not correct. Please, try again." << endl;
                scan = save_scan;
                return;
            }
            if(j + 2 == operations[i].length() && operations[i][j+1] != '2' && operations[i][j+1] != '\'')
            {
                cout << "You put a command \"" << operations[i] << "\" and it's not correct. Please, try again." << endl;
                scan = save_scan;
                return;
            }
            if(operations[i][j] == 'F')
            {
                if(j + 2 == operations[i].length() && operations[i][j+1] == '\'') front_depth_counter(depth);
                if(j + 1 == operations[i].length()) front_depth_clock(depth);
                if(j + 2 == operations[i].length() && operations[i][j+1] == '2')
                {
                    front_depth_clock(depth);
                    front_depth_clock(depth);
                }
            }
            else if(operations[i][j] == 'B')
            {
                if(j + 2 == operations[i].length() && operations[i][j+1] == '\'') back_depth_counter(depth);
                if(j + 1 == operations[i].length()) back_depth_clock(depth);
                if(j + 2 == operations[i].length() && operations[i][j+1] == '2')
                {
                    back_depth_clock(depth);
                    back_depth_clock(depth);
                }
            }
            else if(operations[i][j] == 'R')
            {
                if(j + 2 == operations[i].length() && operations[i][j+1] == '\'') right_depth_counter(depth);
                if(j + 1 == operations[i].length()) right_depth_clock(depth);
                if(j + 2 == operations[i].length() && operations[i][j+1] == '2')
                {
                    right_depth_clock(depth);
                    right_depth_clock(depth);
                }
            }
            else if(operations[i][j] == 'L')
            {
                if(j + 2 == operations[i].length() && operations[i][j+1] == '\'') left_depth_counter(depth);
                if(j + 1 == operations[i].length()) left_depth_clock(depth);
                if(j + 2 == operations[i].length() && operations[i][j+1] == '2')
                {
                    left_depth_clock(depth);
                    left_depth_clock(depth);
                }
            }
            else if(operations[i][j] == 'U')
            {
                if(j + 2 == operations[i].length() && operations[i][j+1] == '\'') up_depth_counter(depth);
                if(j + 1 == operations[i].length()) up_depth_clock(depth);
                if(j + 2 == operations[i].length() && operations[i][j+1] == '2')
                {
                    up_depth_clock(depth);
                    up_depth_clock(depth);
                }
            }
            else if(operations[i][j] == 'D')
            {
                if(j + 2 == operations[i].length() && operations[i][j+1] == '\'') down_depth_counter(depth);
                if(j + 1 == operations[i].length()) down_depth_clock(depth);
                if(j + 2 == operations[i].length() && operations[i][j+1] == '2')
                {
                    down_depth_clock(depth);
                    down_depth_clock(depth);
                }
            }
            else if(operations[i][j] == 'x')
            {
                if(j + 2 == operations[i].length() && operations[i][j+1] == '\'') to_down();
                if(j + 1 == operations[i].length()) to_up();
                if(j + 2 == operations[i].length() && operations[i][j+1] == '2')
                {
                    to_up();
                    to_up();
                }
            }
            else if(operations[i][j] == 'y')
            {
                if(j + 2 == operations[i].length() && operations[i][j+1] == '\'') to_left();
                if(j + 1 == operations[i].length()) to_right();
                if(j + 2 == operations[i].length() && operations[i][j+1] == '2')
                {
                    to_right();
                    to_right();
                }
            }
            else if(operations[i][j] == 'z')
            {
                if(j + 2 == operations[i].length() && operations[i][j+1] == '\'') rotate_counter();
                if(j + 1 == operations[i].length()) rotate_clock();
                if(j + 2 == operations[i].length() && operations[i][j+1] == '2')
                {
                    rotate_clock();
                    rotate_clock();
                }
            }
            else
            {
                cout << "You put a command \"" << operations[i] << "\" and it's not correct. Please, try again." << endl;
                scan = save_scan;
                return;
            }
        }
    }
};
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
Cube scan_cube()
{
    cout << "Please, enter size of cube: " << endl;
    int size_of_cube;
    cin >> size_of_cube;
    Cube my_cube(size_of_cube);
    cout << "Please, enter scan of cube in this view: " << endl << endl;
    print_cube(my_cube);
    cout << endl;
    cout << "-----------------------" << endl;
    vector <vector <vector <int> > > my_scan = my_cube.getter_scan();
    for(int i = 0; i < size_of_cube; i++) for(int j = 0; j < size_of_cube; j++) cin >> my_scan[0][i][j];
    for(int i = 0; i < size_of_cube; i++) for(int c = 1; c <= 4; c++) for(int j = 0; j < size_of_cube; j++) cin >> my_scan[c][i][j];
    for(int i = 0; i < size_of_cube; i++) for(int j = 0; j < size_of_cube; j++) cin >> my_scan[5][i][j];
    Cube return_cube(my_scan);
    return return_cube;
}
Cube random_cube(int size_of_cube)
{
    Cube my_cube(size_of_cube);
    long cur_time = time (NULL);
    srand(cur_time);
    cout << "Our scramble: ";
    vector <int> sides;
    for(int i = 0; i < 6; i++) sides.push_back(i);
    for(int number_of_operation = 0; number_of_operation < (size_of_cube - 1) * 10; number_of_operation++)
    {
        int side = sides[rand() % sides.size()];
        int course = rand() % 2;
        int depth =  1 + rand() % (size_of_cube/2);
        int times = 1 + rand() % 2;
        if(depth != 1) cout << depth;
        if(!course || times == 2)
        {
            if(side == 0)
            {
                cout << "F";
                my_cube.front_depth_clock(depth);
                if(times == 2) my_cube.front_depth_clock(depth);
            }
            if(side == 5)
            {
                cout << "B";
                my_cube.back_depth_clock(depth);
                if(times == 2) my_cube.back_depth_clock(depth);
            }
            if(side == 1)
            {
                cout << "R";
                my_cube.right_depth_clock(depth);
                if(times == 2) my_cube.right_depth_clock(depth);
            }
            if(side == 3)
            {
                cout << "L";
                my_cube.left_depth_clock(depth);
                if(times == 2) my_cube.left_depth_clock(depth);
            }
            if(side == 2)
            {
                cout << "U";
                my_cube.up_depth_clock(depth);
                if(times == 2) my_cube.up_depth_clock(depth);
            }
            if(side == 4)
            {
                cout << "D";
                my_cube.down_depth_clock(depth);
                if(times == 2) my_cube.down_depth_clock(depth);
            }
        }
        else
        {
            if(side == 0)
            {
                cout << "F";
                my_cube.front_depth_counter(depth);
                if(times == 2) my_cube.front_depth_counter(depth);
            }
            if(side == 5)
            {
                cout << "B";
                my_cube.back_depth_counter(depth);
                if(times == 2) my_cube.back_depth_counter(depth);
            }
            if(side == 1)
            {
                cout << "R";
                my_cube.right_depth_counter(depth);
                if(times == 2) my_cube.right_depth_counter(depth);
            }
            if(side == 3)
            {
                cout << "L";
                my_cube.left_depth_counter(depth);
                if(times == 2) my_cube.left_depth_counter(depth);
            }
            if(side == 2)
            {
                cout << "U";
                my_cube.up_depth_counter(depth);
                if(times == 2) my_cube.up_depth_counter(depth);
            }
            if(side == 4)
            {
                cout << "D";
                my_cube.down_depth_counter(depth);
                if(times == 2) my_cube.down_depth_counter(depth);
            }
            cout << "'";
        }
        if(times == 2) cout << 2;
        cout << " ";
        sides.clear();
        for(int i = 0; i < 6; i++) if(side != i) sides.push_back(i);
    }
    cout << endl << endl;
    cout << "Our scan:";
    cout << endl << endl;
    print_cube(my_cube);
    return my_cube;
}
string assembly(const Cube assembly_cube)
{
    string assembly_algorithm;
    class bang_bang
    {
        void operator()(Cube &cube, string &assembly_algorithm)
        {
            cube.make_scramble("R U R' U'");
            assembly_algorithm += "R U R' U'";
        }
    };
    class assembly_stage2to2
    {
        void operator()(Cube &cube, string &assembly_algorithm)
        {

            vector< vector<int> > corners = {{0, 1, 2}, {0, 2, 3}, {0, 3, 4}, {0, 4, 1}, {5, 1, 2}, {5, 2, 3}, {5, 3, 4}, {5, 4, 1}};
            map<int, int> opposite_color;
            map<int, map<int, int> > G;
            for(int i = 0; i < 6; i++) for(int j = 0; j < 6; j++) G[i][j] = 1;
            for(int i = 0; i < 8; i++) for(int a = 0; a < 3; a++) for(int b = 0; b < 3; b++)
            {
                G[corners[i][a]][corners[i][b]] = 0;
            }
            for(int color = 0; color < 6; color++) for(auto q: G[color]) if(q.second == 1) opposite_color[color] = q.first;
            int color_side0 = cube.getter_scan()[0][0][0];
            int color_side4 = cube.getter_scan()[4][0][0];
            int color_side3 = cube.getter_scan()[3][0][1];
            int color_side1 = opposite_color[color_side3];
            int color_side2 = opposite_color[color_side4];
            int color_side5 = opposite_color[color_side0];
            cube.make_scramble("x");
        }
    };
    class assembly_stage3to3
    {
        void operator()(Cube &cube, string &assembly_algorithm)
        {

        }
    };
    class assembly_centres
    {
        void operator()(Cube &cube, string &assembly_algorithm)
        {

        }
    };
    class assembly_edges
    {
        void operator()(Cube &cube, string &assembly_algorithm)
        {

        }
    };
    if(assembly_cube.getter_scan()[0].size() == 2) assembly_stage2to2(assembly_cube, assembly_algorithm);
    else
    {
        vector <vector <vector <int> > > scan_3to3(3, vector< vector<int> > (3, vector<int> (3)));
        if(assembly_cube.getter_scan()[0].size() > 3)
        {
            assembly_centres(assembly_cube, assembly_algorithm);
            assembly_edges(assembly_cube, assembly_algorithm);
            for(int side = 0; side < 6; side++)
            {
                for(int i = 0; i < 3; i++) for(int j = 0; j < 3; j++)
                {
                    int I = i, J = j;
                    if(I == 2) I = assembly_cube.getter_scan()[side].size() - 1;
                    if(J == 2) J = assembly_cube.getter_scan()[side].size() - 1;
                    scan_3to3[side][i][j] = assembly_cube.getter_scan()[side][I][J];
                }
            }
        }
        else scan_3to3 = assembly_cube.getter_scan();
        assembly_stage3to3(assembly_cube, assembly_algorithm);
    }
    return assembly_algorithm;
}
int main()
{
    random_cube(2);

    Cube my_cube(3);

  //  assembly(my_cube);
}
/*
    Cube my_cube(3);
    my_cube.make_scramble("y' z");
    for(int i = 0; i < 7; i++)
    {
        my_cube.make_scramble("U' R U R' y");
    }
    print_cube(my_cube);
*/
