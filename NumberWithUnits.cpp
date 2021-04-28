#include "NumberWithUnits.hpp"
#include <map>
#include <iostream>
#include <fstream>

using namespace std;

using namespace ariel;

const double epsilon = 0.001;

namespace ariel
{
    static map<string, map<string, double> > units_converts;

    NumberWithUnits :: NumberWithUnits(double value, const string& type)
    {
        units_converts.at(type);

        this->unit=type; 
        this->val=value;  
    }

    double convers(double value, const string& from, const string& to)
    {
        if(units_converts[from][to] == 0)
        {
            throw "Invalid unit";
        }
        if(from == to) 
        {
            return value;
        }
        
        return value * units_converts[from][to];
    };

    void NumberWithUnits ::read_units(ifstream& units_file)
    {
        double num1, num2=0; 
        string unit1, unit2, eq;

        while(units_file >> num1 >> unit1 >> eq >> num2 >> unit2)
        {
            units_converts[unit1][unit2] = num2;
            units_converts[unit2][unit1]= num1/num2;
            
            for(auto &pair : units_converts[unit1]) 
            {
                double cast = units_converts[unit2][unit1] * pair.second;

                units_converts[pair.first][unit2] = 1/cast;
                units_converts[unit2][pair.first] = cast;
                
            }
            for(auto &pair : units_converts[unit2]) 
            {
                double cast = units_converts[unit1][unit2] * pair.second;

                units_converts[pair.first][unit1] = 1/cast;
                units_converts[unit1][pair.first] = cast;
            }
        }
    }

    void NumberWithUnits :: print()
    {
        for(auto& unit1 : units_converts)
        {
            for (auto& unit2 : unit1.second)
            {
               cout<< unit1.first << " " << unit2.first << " "<<unit2.second<< endl;
            }
        }
    }

    NumberWithUnits& NumberWithUnits::operator++()
    {
        ++(this->val);

        return *this;
    }

    NumberWithUnits NumberWithUnits::operator++(int n)
    {
        return NumberWithUnits((this->val)++, this->unit);
    }

    NumberWithUnits& NumberWithUnits::operator--()
    {
        --(this->val);

        return *this;
    }
    
    NumberWithUnits NumberWithUnits::operator--(int n)
    {
        return NumberWithUnits((this->val)--, this->unit);
    }

    NumberWithUnits NumberWithUnits::operator+(const NumberWithUnits& n2) 
    {
        double convert = convers(n2.val, n2.unit, this->unit);

        NumberWithUnits ans(this->val+convert, this->unit);

        return ans;
    }

    NumberWithUnits NumberWithUnits::operator-(const NumberWithUnits& n2) 
    {
        double convert = convers(n2.val, n2.unit, this->unit);

        NumberWithUnits ans(this->val-convert, this->unit);

        return ans;
    }

    NumberWithUnits NumberWithUnits::operator+()
    {
        NumberWithUnits ans(+this->val , this->unit);

        return ans;
    }

    NumberWithUnits NumberWithUnits::operator-()
    {
        NumberWithUnits ans(-this->val, this->unit);

        return ans;
    }

    NumberWithUnits& NumberWithUnits::operator+=(const NumberWithUnits &n) 
    {
    this->val+= convers(n.val, n.unit, this->unit);

    return *this;
    }

    NumberWithUnits& NumberWithUnits::operator-=(const NumberWithUnits &n) 
    {
    this->val-= convers(n.val, n.unit, this->unit);

    return *this;
    }

    NumberWithUnits operator*(const NumberWithUnits& n, const double num)  
    {
        return NumberWithUnits(n.val*num, n.unit);
    }

    NumberWithUnits operator*(const double num, const NumberWithUnits& n)  
    {
        return NumberWithUnits(n.val*num, n.unit);
    }

    NumberWithUnits& NumberWithUnits::operator*=(double num) 
    {
        this->val*=num;

        return *this;
    }

    bool operator<(const NumberWithUnits& n1, const NumberWithUnits& n2)
    {
        return (n1.val < convers(n2.val, n2.unit, n1.unit));
    }

    bool operator>(const NumberWithUnits& n1, const NumberWithUnits& n2)
    {
        return (n1.val > convers(n2.val, n2.unit, n1.unit));
    }

    bool operator>=(const NumberWithUnits& n1, const NumberWithUnits& n2)
    {
        return ((n1 == n2) || (n1>n2) );
    }

    bool operator<=(const NumberWithUnits& n1, const NumberWithUnits& n2)
    {
        return (  (n1==n2) ||(n1<n2));
    }

    bool operator==(const NumberWithUnits& n1, const NumberWithUnits& n2)
    {
        return (abs(n1.val- convers(n2.val, n2.unit, n1.unit)) <= epsilon);
    }

    bool operator!=(const NumberWithUnits& n1, const NumberWithUnits& n2)
    {
        return !(n1==n2);
    }

    ostream& operator<<(ostream& out, const NumberWithUnits& n)
    {
        out << n.val << "[" << n.unit << "]";

        return out;
    }

    std::istream &operator>>(std::istream &in, NumberWithUnits &n) 
    {
        char c='0';
        double val=0;
        string type;
    
        in >> val >> c;

        while(c!=']')
        {
            if(c!='[')
            {
                type.insert(type.end(),c);
            }
            in>>c;
        }
       if(units_converts[type].empty())
       {
           throw invalid_argument{"unit doesnt exist"};
        };
        n.val=val;
        n.unit=type;

        return in;
    }
}
