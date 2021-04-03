#include <bits/stdc++.h>
#define pb push_back
#define f first
#define s second
using namespace std;
class Polynom
{
friend istream& operator>> (istream &in, Polynom &other);
friend ostream& operator<< (ostream &out, const Polynom &other);
private:
    map <unsigned, double> summands;
public:
    Polynom() = default;
    explicit Polynom(map <unsigned, double> M)
    : summands(M)
    {

    }
    Polynom(const Polynom &copy)
    : summands(copy.summands)
    {

    }
    Polynom& operator= (const Polynom &p)
    {
        summands = p.summands;
    }
    bool operator== (Polynom P) const
    {
        if(summands == P.summands) return true;
        return false;
    }
    bool operator!= (Polynom P) const
    {
        if(summands != P.summands) return true;
        return false;
    }
    map <unsigned, double> GetSummands()
    {
        return summands;
    }
    Polynom operator- () const
    {
        Polynom mP;
        for(auto q: summands)
        {
            mP.summands[q.f] = -q.s;
        }
        return mP;
    }
    Polynom& operator+= (const Polynom &P1)
    {
        Polynom P2 = P1;
        for(auto q: P2.summands)
        {
            summands[q.f] += q.s;
        }
        return *this;
    }
    Polynom operator+ (const Polynom &P1) const
    {
        Polynom P2 = *this;
        P2 += P1;
        return P2;
    }
    Polynom& operator-= (const Polynom &P)
    {
        *this += -P;
        return *this;
    }
    Polynom operator- (const Polynom &P1) const
    {
        Polynom P2 = *this;
        P2 -= P1;
        return P2;
    }
    Polynom& operator*= (const Polynom &P1)
    {
        Polynom P2 = *this;
        Polynom P3 = P1;
        summands.clear();
        for(auto q: P3.summands)
        {
            for(auto r: P2.summands)
            {
                summands[q.f + r.f] += q.s * r.s;
            }
        }
        return *this;
    }
    Polynom operator* (const Polynom &P1) const
    {
        Polynom P2 = *this;
        P2 *= P1;
        return P2;
    }
    Polynom& operator/= (const double &s)
    {
        for(auto q: summands)
        {
            summands[q.f] /= s;
        }
        return *this;
    }
    Polynom operator/ (const double &s) const
    {
        Polynom P2 = *this;
        P2 /= s;
        return P2;
    }
    double operator[] (unsigned pw)
    {
        return summands[pw];
    }
};
istream& operator>> (istream &in, Polynom &other)
{
    int q;
    in >> q;
    int k = 0;
    other.summands.clear();
    while(q--)
    {
        int power;
        double coefficient;
        if(k == 0)
        {
            in >> coefficient;
            char a, b;
            in >> a >> b;
            in >> power;
        }
        else
        {
            char s;
            in >> s;
            in >> coefficient;
            if(s == '-') coefficient = - coefficient;
            char a, b;
            in >> a >> b;
            in >> power;
        }
        other.summands[power] = coefficient;
        k++;
    }
    return in;
}
ostream& operator<< (ostream &out, const Polynom &other)
{
    int t = 0;
    for(auto it = other.summands.rbegin(); it != other.summands.rend(); it++)
    {
        auto q = *it;
        if(t == 0 && q.f > 0) out << q.s << " x ^ " << q.f;
        if(t == 0 && q.f == 0) out << q.s;
        if(t != 0 && q.s > 1e-9 && q.f > 0) out << " + " << q.s << " x ^ " << q.f;
        if(t != 0 && q.s > 1e-9 && q.f == 0) out << " + " << q.s;
        if(t != 0 && q.s < -1e-9 && q.f > 0) out << " - " << abs(q.s) << " x ^ " << q.f;
        if(t != 0 && q.s < -1e-9 && q.f == 0) out << " - " << abs(q.s);
        t++;
    }
    if(t == 0) out << 0;
    return out;
}
int main()
{
    map<unsigned, double> polynomial;
    polynomial[0] = 1;
    polynomial[1] = 2;
    polynomial[2] = 1;
/*    Polynom P1, P2;
    cin >> P1 >> P2;
    cout << endl << P1 << endl << P2 << endl;
    if(P1 != P2) cout << "NOT EQUAL" << endl;
    else cout << "EQUAL" << endl;
    cout << "minus:" << - P1 << endl;
    cout << "sum: " << P1 + P2 << endl;
    cout << "dif: " << P1 - P2 << endl;
    cout << "mul: " << P1 * P2 << endl;
    cout << "del4.3: " << P1 / 4.3 << endl;
    cout << P2[6] << " " << P2[4] << endl;*/

    Polynom myPolynomial {polynomial};
    myPolynomial *= myPolynomial;
    cout << -myPolynomial;
}
/*
4 3 x ^ 4 + 4 x ^ 3 - 5.5 x ^ 2 + 10 x ^ 0
4 -8 x ^ 10 - 2.7 x ^ 5 + 3 x ^ 4 + 4 x ^ 3
*/
