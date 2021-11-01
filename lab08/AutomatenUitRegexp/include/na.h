#ifndef NA_H
#define NA_H
#include "regexp.h"
#include <vector>

struct Transition {
    int from;
    int to;
    char symbol;
    Transition verschuif(int offset) const {
        return {from + offset, to + offset, symbol};
    }
};

class NA {
    public:
        NA(const Regexp& re){
            switch (re.geefOpcode())
            {
            case Regexp::opcode::letter :
            {
                // 0-> 1
                aantalStatenbits = 2;
                verbind(0, 1, re.geefLetter());
                break;
            }
            case Regexp::opcode::of:
            {
                NA op1(*re.geefEersteOperand());
                NA op2(*re.geefTweedeOperand());
                // Nieuwe begin en eindbit
                aantalStatenbits = op1.aantalStatenbits + op2.aantalStatenbits + 2;
                
                // nieuwe beginbit van de volledige NA = 0, dus verschuiven met 1tje
                haalNABinnen(op1, 1);
                // overgangen op2 komen na nieuwe beginbit + alle overgangen op1
                haalNABinnen(op2, 1 + op1.aantalStatenbits);

                // 1 is nu de beginbit van wat op1 was
                verbind(0, 1);
                // 1 + op1.aantalStatenbits is de plaats waar de nieuwe beginbit van op2 nu staat
                verbind(0, 1 + op1.aantalStatenbits);
                // einde op1 verbinden met nieuw einde van de volledige NA
                verbind(1 + op1.aantalStatenbits - 1, aantalStatenbits - 1); // p.138 5->7
                // einde op2 verbinden met nieuw einde van de volledige NA
                // eindeop2 = nieuwe beginbit + alle bits op1 + alle bits op2 -1
                verbind(1 + op1.aantalStatenbits + op2.aantalStatenbits - 1, aantalStatenbits - 1); // p.138 6->7

                break;
            }
            case Regexp::opcode::concatenatie:
            {
                NA op1(*re.geefEersteOperand());
                NA op2(*re.geefTweedeOperand());
                // eindbit op1 wordt beginbit op2 dus -1
                aantalStatenbits = op1.aantalStatenbits + op2.aantalStatenbits -1;
                // beginbit wordt beginbit op1
                haalNABinnen(op1, 0);
                // toevoegen net na op1
                haalNABinnen(op2, op1.aantalStatenbits - 1);

                // niets meer verbinden want eindbit op1 is nu beginbit op2
                break;
            }
            case Regexp::opcode::ster: 
            {
                NA op(*re.geefEersteOperand());
                // Nieuwe begin en eindbit
                aantalStatenbits = op.aantalStatenbits + 2;
                // nieuw beginbit van de volledige NA, dus opschuiven met 1tje
                haalNABinnen(op, 1);
                
                // nieuw begin naar begin van op
                verbind(0, 1);
                // nieuw begin naar einde op
                verbind(0, aantalStatenbits - 1);
                // nieuwe eindbit op met nieuwe beginbit op
                verbind(aantalStatenbits - 2, 1);
                // nieuwe eindbit op met nieuwe eindbit
                verbind(aantalStatenbits - 2, aantalStatenbits - 1);

                break;
            }
            }
        }

        std::vector<Transition> overgangen;
        int aantalStatenbits;
        static constexpr char EPSILON = 0;

        void haalNABinnen(const NA& van, int offset){
            for(auto&& overgang : van.overgangen){
                this->overgangen.push_back(overgang.verschuif(offset));
            }
        }

        void verbind(int from, int to, char symbol = EPSILON){
            overgangen.push_back({from, to, symbol});
        }

        void teken() const{
            std::string pijl;
            pijl="->";
            std::cout<<"digraph {\n";
            std::cout<<"  rankdir=\"LR\";";
            std::cout<<"  -1 [shape=point];\n";
            std::cout<<"  -1 -> 0;\n";
            std::cout<<"  "<<this->aantalStatenbits-1<<" [shape=square];\n";
            for (auto&& transition :overgangen){
                std::cout<<"  "<< transition.from<<" "<<pijl<<" "<<transition.to;
                std::cout<<"[label=\"";
                if (transition.symbol == EPSILON)
                    std::cout<<"epsilon";
                else
                    std::cout<< transition.symbol;
                std::cout<<"\"];\n";
            };
            std::cout<<"}\n";
        };
};


#endif