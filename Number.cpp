//
// Created by Emil Akopyan on 24.04.2020.
//
#include "Number.h"

///////////////////////////////////////MULTIPLICATION ALGORITHMS////////////////////////////////////////////////////

Number Multiplicator::gradeschoolmultiplication(const Number& num1,const Number& num2)
{
    Number num1c(num1);
    Number num2c(num2);


    std::vector<char> resnum(num1c.getlength()+num2c.getlength());
    for (int j = 0; j < num1c.getlength()+num2c.getlength(); ++j)
        resnum.push_back(0);

    Number newnumb (resnum);

    for (size_t i = 0; i < num1c.getlength(); ++i)
    {
        int carry = 0;
        for (size_t j = 0; j < num2c.getlength(); ++j)
        {
            newnumb[i+j] += num1c[i]*num2c[j] + carry;
            carry = newnumb[i+j] / 10;
            newnumb[i+j] %= 10;
        }
        newnumb[i+num2c.getlength()] += carry;
    }
    newnumb.deletezeroes();

    return newnumb;
}

Number Multiplicator::divconq(const Number& num1,const Number& num2)
{


    if(num1.getlength() == 1 || num2.getlength() == 1)
    {
        return gradeschoolmultiplication(num1,num2);
    }

    size_t n = std::max(num1.getlength(),num2.getlength());


    auto partition = Number::split(num1,num2);


    Number result = divconq(std::get<1>(partition),std::get<3>(partition));
    result.multiplyby10(n/2*2);
    result += divconq(std::get<0>(partition), std::get<2>(partition));
    Number sum1 = divconq(std::get<1>(partition), std::get<2>(partition))+ \
    divconq(std::get<0>(partition),std::get<3>(partition));
    sum1.multiplyby10(n/2);
    result += sum1;
    return result;

}

Number Multiplicator::karatsuba(const Number& num1,const Number& num2)
{
    if(num1.getlength() == 1 && num2.getlength() == 1)
    {
        return gradeschoolmultiplication(num1,num2);
    }



    size_t n = std::max(num1.getlength(),num2.getlength());


    auto partition = Number::split(num1,num2);


    Number firstterm = karatsuba(std::get<1>(partition),std::get<3>(partition));

    Number lastterm = karatsuba(std::get<0>(partition),std::get<2>(partition));


    Number middleterm = karatsuba(std::get<1>(partition)+std::get<0>(partition),std::get<2>(partition)+std::get<3>(partition));

    middleterm -= firstterm;
    middleterm -= lastterm;

    firstterm.multiplyby10(n/2*2);
    middleterm.multiplyby10(n/2);

    firstterm += middleterm;
    firstterm += lastterm;

    return firstterm;
}



///////////////////////////////////////AUXILLARY METHODS ////////////////////////////////////////////////////

void Number::equalize(Number& num1, Number& num2)
{
    if (num1.getlength()>num2.getlength())
    {
        while(num1.getlength() !=num2.getlength())
        {
            num2._numb.push_back(0);
        }
    }

    else
    {
        while(num1.getlength() !=num2.getlength())
        {
            num1._numb.push_back(0);
        }
    }
}

std::tuple<Number,Number,Number,Number> Number::split(const Number& num1,const Number& num2)
{
    size_t n = std::max(num1.getlength(),num2.getlength());
    std::tuple<Number,Number,Number,Number> newnumbers;
    for (size_t i = 0; i < n; ++i)
    {
        if (i < n / 2) {
            if (i < num1.getlength()) {
                std::get<0>(newnumbers)._numb.push_back(num1[i]);
            } else
                std::get<0>(newnumbers)._numb.push_back(0);
            if (i < num2.getlength()) {
                std::get<2>(newnumbers)._numb.push_back(num2[i]);
            } else
            {
                std::get<2>(newnumbers)._numb.push_back(0);
            }
        } else if (i < n)
        {
            if (i < num1.getlength())
            {
                std::get<1>(newnumbers)._numb.push_back(num1[i]);
            } else
                std::get<1>(newnumbers)._numb.push_back(0);
            if (i < num2.getlength())
            {
                std::get<3>(newnumbers)._numb.push_back(num2[i]);
            } else
            {
                std::get<3>(newnumbers)._numb.push_back(0);
            }
        }
    }
    return newnumbers;
}

void Number::multiplyby10 (size_t pow)
{
    _numb.reserve(_numb.size()+pow+10);
    for (size_t i = 0; i < pow; i++)
    {
        int size = _numb.size();
        _numb.insert(_numb.begin(), 0);
    }
}

void Number::deletezeroes()
{
    while ((*(this->_numb.end()-1)== 0)&& (this->getlength()>1))
        *this->_numb.erase(_numb.end()-1);
}

Number Multiplicator::randgenerator(size_t i)
{
    std::vector<char> a;
    int b = 0;
    int j = 0;
    while (j < i)
    {
        b = (rand() % 10);
        if ((j == i - 1) && ( b != 0))
        {
            b = rand() % 10;
        }
        a.push_back(b);
        ++j;
    }
    Number result (a);
    return result;
}



///////////////////////////////////////OVERLOADED OPERATORS////////////////////////////////////////////////////

Number& Number::operator +=(const Number& another)
{
    Number anotherc (another);
    equalize(*this,anotherc);

    for (int i= 0; i < this->getlength(); ++i)
    {
        (*this)[i] = _numb[i]+anotherc[i];
    }

    for (auto i = 0; i != _numb.size(); ++i) {
        if (_numb.size() != i+1)
        {
            _numb[i + 1] += _numb[i] / 10;
            _numb[i] %= 10;
        } else
        {
            _numb.push_back(_numb[i] / 10);
            _numb[i] %= 10;
            break;
        }
    }
    while ((*(_numb.end() - 1) == 0) && (_numb.size() > 1))
    {
        _numb.erase(_numb.end() - 1);
    }
    return *this;
}


Number& Number::operator -=(const Number& another)
{
    Number anotherc (another);
    equalize(*this,anotherc);

    for (size_t i = 0; i < this->getlength(); ++i)
    {
        (*this)[i] -= anotherc[i];
        if ((*this)[i]<0 && (i != (*this).getlength()-1))
        {
            (*this)[i] = 10 + (*this)[i];
            (*this)[i+1] -= 1;
        }
    }

    return *this;

}

Number Number::operator+(const Number& b) const
{
    Number a = *this;
    a += b;
    return a;
}


std::ostream& operator<<(std::ostream& s, const Number& number)
{

    for (size_t i = number.getlength()-1; i != -1; i--)
    {
        s << number[i];
    }
    return s;
}

