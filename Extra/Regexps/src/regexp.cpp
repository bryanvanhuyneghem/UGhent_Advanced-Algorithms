#include "regexp.h"

Regexp::Regexp(const string &re)
{
    analyseer(voorzieVanConcatSymbool(re));
}

Regexp::opcode Regexp::geefOpcode() const
{
    return deOpcode;
}

const Regexp *Regexp::geefEersteOperand() const
{
    return op1.get();
}

const Regexp *Regexp::geefTweedeOperand() const
{
    return op2.get();
}

uchar Regexp::geefLetter() const
{
    return deLetter;
}

ostream &operator<<(ostream &os, const Regexp &re)
{
    re.schrijf(os);
    return os;
}

Regexp::Regexp(const string &re, bool alVoorzienVanConcatSymbool)
{
    if (alVoorzienVanConcatSymbool || re.size() <= 1)
    {
        analyseer(re);
    }
    else
    {
        analyseer(voorzieVanConcatSymbool(re));
    }
}

string Regexp::voorzieVanConcatSymbool(const string &re) const
{
    string metplus;
    metplus += re[0];
    for (int i = 1; i < re.size(); i++)
    {
        if (re[i - 1] != '|' && re[i - 1] != '(' && re[i] != '*' && re[i] != '|' && re[i] != ')')
        {
            metplus += '_';
        }
        metplus += re[i];
    }
    return metplus;
}

int Regexp::laatste(const string &re, const uchar c, vector<int> &haakniveau)
{
    int i = re.size() - 1;
    while (i >= 0 && (re[i] != c || haakniveau[i] != 0))
        i--;
    return i;
}

void Regexp::analyseer(const string &re)
{
    int n = re.size();
    if (n == 0)
        throw Taalexceptie("leeg operand");
    vector<int> haakniveau(n);
    int niveau = 0;
    bool nulniveau = false; //is er iets buiten haakjes?
    for (int i = 0; i < n; i++)
    {
        if (re[i] == '(')
            niveau++;
        if (niveau == 0)
        {
            nulniveau = true;
        }
        haakniveau[i] = niveau;
        if (re[i] == ')')
        {
            niveau--;
        }
    }
    if (!nulniveau)
    { //alles tussen haakjes
        analyseer(re.substr(1, n - 2));
    }
    else
    {
        int i;
        if (-1 != (i = laatste(re, '|', haakniveau)))
        {
            if (i == 0 || i == n - 1)
                throw Taalexceptie("| met operand te weinig.");
            deOpcode = of;
            //Noot:
            //            op1=make_unique<Regexp>(re.substr(0,i),true);
            // wordt niet gebruikt omdat de hier gebruikte constructoren verborgen moeten blijven en dus protected zijn
            op1.reset(new Regexp(re.substr(0, i), true));
            op2.reset(new Regexp(re.substr(i + 1, n - i - 1), true));
        }
        else if (-1 != (i = laatste(re, '_', haakniveau)))
        {
            if (i == 0 || i == n - 1)
                throw Taalexceptie("+ met operand te weinig.");
            deOpcode = concatenatie;
            op1.reset(new Regexp(re.substr(0, i), true));
            op2.reset(new Regexp(re.substr(i + 1, n - i - 1), true));
        }
        else if (re[n - 1] == '*')
        {
            if (n == 1)
                throw Taalexceptie("* zonder operand.");
            op1.reset(new Regexp(re.substr(0, n - 1), true));
            deOpcode = ster;
        }
        else
        {
            if (n > 1 || string("()|").find(re[0]) != string::npos)
            {
                string fout = " verloren gelopen ";
                fout += re[0];
                throw Taalexceptie(fout);
            }
            deOpcode = letter;
            deLetter = re[0];
        }
    }
}

void Regexp::schrijf(ostream &os) const
{
    switch (deOpcode)
    {
    case letter:
        os << deLetter;
        break;
    case ster:
        os << "[" << *op1 << "]*";
        break;
    case concatenatie:
        os << "[" << *op1 << " + " << *op2 << ']';
        break;
    default:
        os << "[" << *op1 << " | " << *op2 << ']';
        break;
    }
}
