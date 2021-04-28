#include <map>
#include <string>
#include <iostream>

using namespace std;
  
namespace ariel
{
    class NumberWithUnits
    {

    private:
        double val;

        string unit;

    public:

        NumberWithUnits(double value, const string& type);

        double getValue() const
        {
            return val;
        };

        std::string getType() const
        {
            return unit;
        };

        ~NumberWithUnits()
        {

        }
        static void read_units(ifstream& f);

        static void print();

        NumberWithUnits& operator++();
        NumberWithUnits operator++(int n);
        NumberWithUnits& operator--();
        NumberWithUnits operator--(int n);

        NumberWithUnits operator+();
        NumberWithUnits operator-(); 
        NumberWithUnits& operator+=(const NumberWithUnits& num);
        NumberWithUnits& operator-=(const NumberWithUnits& num);
        NumberWithUnits operator+(const NumberWithUnits& n2);
        NumberWithUnits operator-(const NumberWithUnits& n2);
         
        friend NumberWithUnits operator*(const double num, const NumberWithUnits& n);
        friend NumberWithUnits operator*(const NumberWithUnits& n,const double num);

        NumberWithUnits& operator*=(double num);
        
        friend bool operator==(const NumberWithUnits& n1, const NumberWithUnits& n2);
        friend bool operator!=(const NumberWithUnits& n1, const NumberWithUnits& n2);
        friend bool operator>(const NumberWithUnits& n1, const NumberWithUnits& n2);
        friend bool operator<(const NumberWithUnits& n1, const NumberWithUnits& n2);
        friend bool operator>=(const NumberWithUnits& n1, const NumberWithUnits& n2);
        friend bool operator<=(const NumberWithUnits& n1, const NumberWithUnits& n2);
        
        friend ostream& operator<<(ostream& out, const NumberWithUnits& n);
        friend istream& operator>>(istream& in, NumberWithUnits& n);
    };
}