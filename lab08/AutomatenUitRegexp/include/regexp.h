#ifndef REGEXP_H
#define REGEXP_H
#include <string>
#include <iostream>
#include <exception>
#include <memory>
#include <vector>
using std::exception;
using std::ostream;
using std::string;
using std::unique_ptr;
using std::vector;
typedef unsigned char uchar;
//Regexp leest een reguliere expressie in, en zet ze om naar een
//boomstructuur.

class Taalexceptie : public exception
{
public:
    Taalexceptie(const string &_fout) : exception(), fout(_fout){};
    ~Taalexceptie() throw(){};
    virtual const char *what()
    {
        return fout.c_str();
    };

private:
    string fout;
};


/**
 * Deze klasse parset reguliere expressies met alleen |, * en concatenatie.
 * 
 * Een regexp is ofwel:
 * - een letter;
 * - twee regexpoperanden verbonden met een opcode 'of' (`|`) of 'concatenatie' (`_`);
 * - een regexp met de opcode 'ster' `*` 
 * 
 * epsilon wordt beschouwd als een gewone letter.
 */
class Regexp
{
public:
    enum opcode
    {
        ster,
        of,
        concatenatie,
        letter
    };
    Regexp(const string &re);
    opcode geefOpcode() const;
    const Regexp *geefEersteOperand() const; //zinloos als opcode letter is.
    const Regexp *geefTweedeOperand() const; //zinloos als opcode letter of ster is.
    uchar geefLetter() const;                //zinloos als opcode niet letter is.
    friend ostream &operator<<(ostream &os, const Regexp &re);

private:
    //parsen is gemakkelijker als de _ expliciet vermeld zijn
    //maar dit mag van buitenuit niet gezien zijn.
    Regexp(const string &re, bool alVoorzienVanConcatSymbool);

    string voorzieVanConcatSymbool(const string &re) const;
    //zoek meest rechtse voorkomen van operator c die niet tussen haakjes staat.
    int laatste(const string &re, const uchar c, vector<int> &haakniveau);
    void analyseer(const string &re);
    void schrijf(ostream &os) const;
    unique_ptr<Regexp> op1, op2;

    // r = RE_a|RE_b  geefEersteop()->opcode == letter 
    // aaab  a_a_a_b
    opcode deOpcode;
    uchar deLetter;
};

#endif