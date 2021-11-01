#ifndef __SIMULANNEAL
#define __SIMULANNEAL
#include <cstdlib>
#include <memory>
#include <iostream>

/**
 * Abstracte klasse voor simulated annealing.
 * 
 * Hier worden GEEN probleemafhankelijke functies gedefinieerd. Deze zijn allemaal virtual.
 * 
 * @param S: De Search Scope. De oplossing (zowel de voorlopige als de uiteindelijke) is een S.
 */
template <class S>
class SimulatedAnnealing
{
public:
    S oplossing()
    {
        T = beginTemperatuur();
        s = beginOplossing();
        int k = 0;
        while (!stopConditie())
        {
            if(k % 10'000'000 == 0){
                std::cout << k << " temp: " << T << "\n";
            }
            auto [nieuwOplossing, deltaf] = neemRandom(s);

            if (deltaf < 0 || rand() < p(T, deltaf) * RAND_MAX)
            {
                s = std::move(nieuwOplossing);
            }
            updateT(k++);
        }
        return s;  
    }

protected:
    double T;                              //temperatuur;
    S s;                                   //voorlopige en eindoplossing.
    virtual double beginTemperatuur() = 0; //initiele temperatuur
    virtual bool stopConditie() = 0;       //true als stoppen met zoeken
    virtual double f(const S &) = 0;       //objectieffunctie. Moet > 0 blijven
    virtual S beginOplossing() = 0;
    virtual std::pair<S, double> neemRandom(const S &) = 0;
    virtual double p(double T, double deltaf) = 0; //probabiliteit verandering
    virtual void updateT(int k = 0) = 0;
};

#endif
