//
// Created by Emil Akopyan on 24.04.2020.
//

#ifndef ALGOPROJ_NUMBER_H
#define ALGOPROJ_NUMBER_H


#include <vector>
#include <iostream>
#include <utility>
#include <random>
#include <tuple>

class Number
{

public:
    Number(){};

    Number(const std::vector<char>& numb)
            : _numb(numb) {}

    Number(std::vector<char>&& numb)
            : _numb(numb) {}


    Number(const Number& numb)
            : _numb(numb._numb) {}

    Number(Number&& numb)
            : _numb(numb._numb) {}

    Number& operator = (Number&& numb)
    {
        _numb = numb._numb;
        return *this;
    }

    Number& operator =(const Number& num)
    {
        _numb = num._numb;
        return *this;
    }


public:

    size_t getlength() const
    {
        return _numb.size();
    }

    //////////////////////////////////////OVERLOADED OPERATIONS/////////////////////////////////////////////////////////

    char operator [](size_t i) const
    {
        return _numb[i];
    }

    char& operator[](size_t i)
    {
        return _numb[i];
    }

    Number& operator +=(const Number& another);
    Number& operator -=(const Number& another);

    Number operator +(const Number& b) const;

    bool operator == (const  Number& a) {return this->_numb == a._numb;}


    ///////////////////////////////////////AUXILLARY METHODS ALGORITHMS////////////////////////////////////////////////////

    void deletezeroes();

    static void equalize(Number& num1, Number& num2);


    void multiplyby10(size_t n);




    static std::tuple<Number,Number,Number,Number> split(const Number& num1,const Number& num2);


private:

    std::vector<char> _numb;
};


std::ostream& operator<<(std::ostream& s, const Number& number);

class Multiplicator
{

public:

    static Number randgenerator(size_t i);


    ///////////////////////////////////////MULTIPLICATION ALGORITHMS////////////////////////////////////////////////////
public:

    static Number gradeschoolmultiplication(const Number& num1,const Number& num2);

    static Number karatsuba(const Number& num1,const Number& num2);

    static Number divconq(const Number& num1,const Number& num2);
};




#endif //ALGOPROJ_NUMBER_H
