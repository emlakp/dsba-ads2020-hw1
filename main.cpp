#include "Number.h"
#include <chrono>

#include <fstream>

//final


void experiment(std::ofstream& results, size_t upperlimit)
{
    srand(time(nullptr));

    auto end = std::chrono::steady_clock::now();
    auto start = std::chrono::steady_clock::now();
    double time;
    double result = 0;

    results << "Digits," << "Karatsuba," << "GradeSchool," << "DivConquer" << std::endl;
    size_t j = 1;
    while (j < upperlimit)
    {

        results << j << ',';
        Number a = Multiplicator::randgenerator(j);
        Number b = Multiplicator::randgenerator(j);


        for (int i = 1; i < 4; i++) {

            start = std::chrono::steady_clock::now();
            Number o = Multiplicator::karatsuba(a, b);
            end = std::chrono::steady_clock::now();
            time = std::chrono::duration<double>(end - start).count();
            time = round(time * 1000);
            result += time;
        }

        result /= 3;
        results << result << ',';
        result = 0;


        for (int i = 1; i < 4; i++)
        {
            start = std::chrono::steady_clock::now();
            Number o = Multiplicator::gradeschoolmultiplication(a, b);
            end = std::chrono::steady_clock::now();
            time = std::chrono::duration<double>(end - start).count();
            time = round(time * 1000);
            result += time;
        }

        result /= 3;
        results << result << ',';

        result = 0;

        for (int i = 1; i < 4; i++)
        {
            start = std::chrono::steady_clock::now();
            Number o = Multiplicator::divconq(a, b);
            end = std::chrono::steady_clock::now();
            time = std::chrono::duration<double>(end - start).count();
            time = round(time * 1000);
            result += time;
        }

        result /= 3;
        results << result << std::endl;
        result = 0;

        if (j < 100)
            j += 1;
        else if (j < 1000)
            j += 10;
        else if (j < 4000)
            j += 50;
        else if (j < 10000)
            j += 75;

    }
}

int main() {


    std::ofstream results;
    results.open("//Users//emilakopyan//Downloads//data.csv");
    experiment(results, 9000);



    results.close();

//    int i = 11;
//    srand(time(nullptr));
//    Number a = Multiplicator::randgenerator(i);
//    int y = 9;
}

