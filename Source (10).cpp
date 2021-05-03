#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <climits>
#include <cmath>
#include <cfloat>
#include <cassert>
//#include <unistd.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#if defined ( __cplusplus ) && __cplusplus > 199711L /* C++ 11 */
#include <memory>
#endif /* C++ 11 */
using namespace std;
#endif /* __PROGTEST__ */
struct koef
{
    double value;
    int exp;
};
class CPolynomial
{
public:
    vector<koef> polynom;
    CPolynomial()
    {
        koef tmp;
        tmp.exp = 0;
        tmp.value = 0;
        this->polynom.push_back(tmp);
    }
    CPolynomial operator * (const double number) const // p*5    1*5 4*5 8*5
    {
        // << "zacina nasobeni" << endl;
        CPolynomial ret;
        for (int i = 0; i < (int)(this->polynom.size()); i++)
        {
            koef tmp;
            tmp.exp = i;
            tmp.value = this->polynom[i].value * number;
            //cout << this->polynom[i].value << " * " << number << " = " << tmp.value << endl;
            if (i == 0)
            {
                ret.polynom[0].value = this->polynom[0].value * number;
            }
            else
            {
                ret.polynom.push_back(tmp);
            }

           // cout << "vysledek je: " << ret.polynom[i].value << endl;
        }

        return ret;
    }
    int findExpIndex(int e)
    {
        for (int i = 0; i < (int)(this->polynom.size()); i++)
        {
            if (this->polynom[i].exp == e)
            {
                return i;
            }
        }

        return -1;
    }
    CPolynomial operator * (CPolynomial pol) const
    {
        CPolynomial ret;
        for (int i = 0; i < (int)(pol.polynom.size()); i++) // 1 2 3 *  4 5 6 7 8 
        {
            for (int ii = 0; ii < (int)(this->polynom.size()); ii++)
            {
                int tmpExp = pol.polynom[i].exp + this->polynom[ii].exp;
                int tmpIndex = ret.findExpIndex(tmpExp);
                if (tmpIndex != -1)
                {
                    ret.polynom[tmpIndex].value = ret.polynom[tmpIndex].value + pol.polynom[i].value * this->polynom[ii].value;
                }
                else
                {
                    koef tmpKoef;
                    tmpKoef.value = pol.polynom[i].value * this->polynom[ii].value;
                    tmpKoef.exp = tmpExp;
                    ret.polynom.push_back(tmpKoef);
                }
            }
        }
        return ret;
    }
    friend void operator << (ostringstream& out, CPolynomial pol);
    friend CPolynomial operator * (const double number, CPolynomial pol);
    CPolynomial operator + (CPolynomial pol) const
    {
        //cout << " zacinam scitat";

        CPolynomial ret;
        if (this->polynom.size() <= pol.polynom.size())
        {
            for (int i = 0; i < (int)(this->polynom.size()); i++)
            {

                if (i == 0)
                {
                    ret.polynom[0].value = this->polynom[i].value + pol.polynom[i].value;
                }
                else
                {
                    koef tmp;
                    tmp.value = this->polynom[i].value + pol.polynom[i].value;
                    tmp.exp = this->polynom[i].exp;
                    ret.polynom.push_back(tmp);
                }
            }
            for (size_t i = this->polynom.size(); i < pol.polynom.size(); i++)
            {

                if (i == 0)
                {
                    ret.polynom[0].value = this->polynom[i].value + pol.polynom[i].value;
                }
                else
                {
                    koef tmp;
                    tmp.value = pol.polynom[i].value;
                    tmp.exp = pol.polynom[i].exp;
                    ret.polynom.push_back(tmp);
                }
            }
        }
        else
        {
            //cout << " a vetsi jak b";

            for (size_t i = 0; i < pol.polynom.size(); i++)
            {

                if (i == 0)
                {
                    ret.polynom[0].value = this->polynom[i].value + pol.polynom[i].value;
                }
                else
                {
                    koef tmp;
                    tmp.value = this->polynom[i].value + pol.polynom[i].value;
                    tmp.exp = this->polynom[i].exp;
                    ret.polynom.push_back(tmp);
                }
            }
            for (size_t i = pol.polynom.size(); i < this->polynom.size(); i++)
            {

                if (i == 0)
                {
                    ret.polynom[0].value = this->polynom[i].value + pol.polynom[i].value;
                }
                else
                {
                    koef tmp;
                    tmp.value = this->polynom[i].value;
                    tmp.exp = this->polynom[i].exp;
                    ret.polynom.push_back(tmp);
                }
            }
        }
        return ret;
    }
    CPolynomial operator - (CPolynomial pol) const
    {
        //cout << " ODCITANI" << endl;
        CPolynomial ret;
        if (this->polynom.size() <= pol.polynom.size())
        {
            //cout << " b je etsi jak a" << endl;
            for (size_t i = 0; i < this->polynom.size(); i++)
            {
                //cout << "b : " << pol.polynom[i].value << " exp: "<< pol.polynom[i].exp <<endl;

                if (i == 0)
                {
                    ret.polynom[0].value = this->polynom[i].value - pol.polynom[i].value;
                }
                else
                {
                    koef tmp;
                    tmp.value = this->polynom[i].value - pol.polynom[i].value;
                    tmp.exp = this->polynom[i].exp;
                    ret.polynom.push_back(tmp);
                }
            }
            for (size_t i = this->polynom.size(); i < pol.polynom.size(); i++)
            {
                //cout << " ted jdu sem" << endl;
                //cout << "b : " << pol.polynom[i].value << " exp: " << pol.polynom[i].exp << endl;

                if (i == 0)
                {
                    ret.polynom[0].value = 0 - pol.polynom[i].value;
                }
                else
                {
                    koef tmp;
                    tmp.value = 0 - pol.polynom[i].value;
                    tmp.exp = pol.polynom[i].exp;
                    ret.polynom.push_back(tmp);
                }
            }
        }
        else
        {
            //cout << " a je etsi jak b" << endl;
            for (int i = 0; i < (int)(pol.polynom.size()); i++)
            {

                if (i == 0)
                {
                    ret.polynom[0].value = this->polynom[i].value - pol.polynom[i].value;
                }
                else
                {
                    koef tmp;
                    tmp.value = this->polynom[i].value - pol.polynom[i].value;
                    tmp.exp = this->polynom[i].exp;
                    ret.polynom.push_back(tmp);
                }
            }
            for (size_t i = pol.polynom.size(); i < this->polynom.size(); i++)
            {

                if (i == 0)
                {
                    ret.polynom[0].value = this->polynom[i].value;
                }
                else
                {
                    koef tmp;
                    tmp.value = this->polynom[i].value;
                    tmp.exp = this->polynom[i].exp;
                    ret.polynom.push_back(tmp);
                }
            }
        }
        return ret;
    }
    double operator [] (const int i) const
    {
        if (i < (int)(this->polynom.size())) // 1 2 3 4 5 - - -
        {
            return this->polynom[i].value;
        }
        else
        {
            return 0;
        }
        return this->polynom[i].value;

    }
    double& operator [] (const int i)
    {
        if (i < (int)(this->polynom.size())) // 1 2 3 4 5 - - -
        {
            return this->polynom[i].value;
        }
        else
        {
            int begin = this->polynom.size(); //1 2 3 4 5 6
            //cout << "velikost pole je :" << begin << endl;
            while (i >= begin)
            {
                koef tmp;
                tmp.exp = begin;

                //cout << "pridavam exp" << begin << endl;
                tmp.value = 0;
                this->polynom.push_back(tmp);
                begin++;
            }
            return this->polynom[i].value;
        }
    }
    bool operator == (CPolynomial pol) const

    {
        if (pol.polynom.size() <= this->polynom.size())
        {
            for (int i = 0; i < (int)(pol.polynom.size()); i++)
            {
                if (pol.polynom[i].value != this->polynom[i].value)
                {
                    return false;
                }
            }
            for (size_t i = pol.polynom.size(); i < this->polynom.size(); i++)
            {
                if (this->polynom[i].value != 0)
                {
                    return false;
                }
            }
            return true;
        }
        else
        {
            for (int i = 0; i < (int)(this->polynom.size()); i++)
            {
                if (pol.polynom[i].value != this->polynom[i].value)
                {
                    return false;
                }
            }
            for (size_t i = this->polynom.size(); i < pol.polynom.size(); i++)
            {
                if (pol.polynom[i].value != 0)
                {
                    return false;
                }
            }
            return true;
        }
    }
    bool operator != (CPolynomial pol) const
    {
        if (*this == pol)
        {
            return false;
        }
        return true;
    }
    double operator () (const double x) const
    {
        double ret = 0;
        for (size_t i = 0; i < this->polynom.size(); i++)
        {
            ret = ret + this->polynom[i].value * pow(x, this->polynom[i].exp);
        }
        return ret;
    }
    unsigned int Degree() const
    {
        unsigned int deg = 0;
        //cout << "velikost pole je : " << this->polynom.size() << endl;


        for (size_t i = 0; i < this->polynom.size(); i++)
        {
            //cout << "cleny poole : " << this->polynom[i].value << " exp " << this->polynom[i].exp << endl;

            if (this->polynom[i].value != 0)
            {
                deg = this->polynom[i].exp;
            }
        }
        return deg;
    }

};
void operator << (ostringstream& out, CPolynomial pol)
{
    //polynomFormat(pol.polynom);
    bool isFirst = true;
    for (int i = (int)(pol.polynom.size()) - 1; i >= 0; i--)
    {
        if (pol.polynom[i].value == 1) // round, round in string, printf + prikaz
        {
            if (pol.polynom[i].exp != 0)
            {
                if (isFirst == true)
                {
                    //cout << "x^" << pol.polynom[i].exp;
                    out << "x^" << pol.polynom[i].exp;
                    isFirst = false;
                }
                else
                {
                    //cout << " + x^" << pol.polynom[i].exp;
                    out << " + x^" << pol.polynom[i].exp;
                }
            }
            else
            {
                if (isFirst == true)
                {
                    //cout << "1";
                    out << "1";
                    isFirst = false;
                }
                else
                {
                    //cout << " + 1" << pol.polynom[i].exp;
                    out << " + 1" << pol.polynom[i].exp;
                }
            }

        }
        else if (pol.polynom[i].value > 0) // round, round in string, printf + prikaz
        {
            if (pol.polynom[i].exp != 0)
            {
                if (isFirst == true)
                {
                    //cout << pol.polynom[i].value << "*x^" << pol.polynom[i].exp;
                    out << pol.polynom[i].value << "*x^" << pol.polynom[i].exp;
                    isFirst = false;
                }
                else
                {
                    //cout << " + " << pol.polynom[i].value << "*x^" << pol.polynom[i].exp;
                    out << " + " << pol.polynom[i].value << "*x^" << pol.polynom[i].exp;
                }
            }
            else
            {
                if (isFirst == true)
                {
                    //cout << pol.polynom[i].value;
                    out << pol.polynom[i].value;
                    isFirst = false;
                }
                else
                {
                    //cout << " + " << pol.polynom[i].value;
                    out << " + " << pol.polynom[i].value;
                }
            }

        }
        else if (pol.polynom[i].value == -1)
        {
            if (pol.polynom[i].exp != 0)
            {
                if (isFirst == true)
                {
                    out << "- x^" << pol.polynom[i].exp;
                    isFirst = false;
                }
                else
                {
                    out << " - x^" << pol.polynom[i].exp;
                }
            }
            else
            {
                if (isFirst == true)
                {
                    out << "- 1";
                    isFirst = false;
                }
                else
                {
                    out << " - 1";
                }
            }

        }
        else if (pol.polynom[i].value < 0)
        {
            if (pol.polynom[i].exp != 0)
            {
                if (isFirst == true)
                {
                    out << "- " << fabs(pol.polynom[i].value) << "*x^" << pol.polynom[i].exp;
                    isFirst = false;
                }
                else
                {
                    out << " - " << fabs(pol.polynom[i].value) << "*x^" << pol.polynom[i].exp;
                }
            }
            else
            {
                if (isFirst == true)
                {
                    out << "- " << fabs(pol.polynom[i].value);
                    isFirst = false;
                }
                else
                {
                    //cout << " - " << fabs(pol.polynom[i].value);
                    out << " - " << fabs(pol.polynom[i].value);
                }
            }

        }
        else if ((pol.polynom.size() == 1 && pol.polynom[0].value == 0))
        {
            out << "0";
        }
    }
}
CPolynomial operator * (const double number, CPolynomial pol)
{
    //cout << "zacina nasobeni" << endl;
    CPolynomial ret;
    koef tmp;
    for (int i = 0; i < (int)(pol.polynom.size()); i++)
    {
        tmp.exp = i;
        tmp.value = pol.polynom[i].value * number;
	ret.polynom.push_back(tmp);
        //cout << "nasobek je:  " << tmp.value << "index je " << i;
    }
    return ret;
}

#ifndef __PROGTEST__
bool               smallDiff(double            a,
    double            b)
{
    return (a == b);
}

bool dumpMatch(const CPolynomial& x, const vector<double>& ref)
{
    return true;
}
int                main(void)
{
    CPolynomial a, b, c;
    ostringstream out;

    a[0] = -10;
    a[1] = 3.5;
    a[3] = 1;
    assert(smallDiff(a(2), 5));
    out.str("");
    out << a;
    assert(out.str() == "x^3 + 3.5*x^1 - 10");
    a = a * -2;
    assert(a.Degree() == 3
        && dumpMatch(a, vector<double>{ 20.0, -7.0, -0.0, -2.0 }));

    out.str("");
    out << a;
    assert(out.str() == "- 2*x^3 - 7*x^1 + 20");
    out.str("");
    out << b;
    assert(out.str() == "0");
    b[5] = -1;
    out.str("");
    out << b;
    assert(out.str() == "- x^5");
    c = a + b;
    assert(c.Degree() == 5
        && dumpMatch(c, vector<double>{ 20.0, -7.0, 0.0, -2.0, 0.0, -1.0 }));

    out.str("");
    out << c;
    assert(out.str() == "- x^5 - 2*x^3 - 7*x^1 + 20");
    c = a - b;
    assert(c.Degree() == 5
        && dumpMatch(c, vector<double>{ 20.0, -7.0, -0.0, -2.0, -0.0, 1.0 }));

    out.str("");
    out << c;
    assert(out.str() == "x^5 - 2*x^3 - 7*x^1 + 20");
    c = a * b;
    assert(c.Degree() == 8
        && dumpMatch(c, vector<double>{ -0.0, -0.0, 0.0, -0.0, 0.0, -20.0, 7.0, -0.0, 2.0 }));
    out.str("");
    out << c;
    assert(out.str() == "2*x^8 + 7*x^6 - 20*x^5");
    assert(a != b);
    b[5] = 0;
    assert(!(a == b));
    a = a * 0;
    assert(a.Degree() == 0
        && dumpMatch(a, vector<double>{ 0.0 }));

    assert(a == b);
    return 0;
}
#endif /* __PROGTEST__ */
