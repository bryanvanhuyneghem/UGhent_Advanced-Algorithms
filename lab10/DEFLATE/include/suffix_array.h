#include <vector>
#include "sais.hxx"
#include <string>
/**
 * Suffix Array
 * 
 * Deze klasse construeert een suffix array in lineaire tijd dankzij het 
 * SAIS algoritme (Suffix Array Induced Sorting)
 * 
 * @returns een gesorteerde lijst van start-indexen van suffixen
 * 
 */
class SuffixArray
{

private:
    std::vector<int> lcp;
    std::vector<int> sa;
    std::vector<int> inv_sa;
public:
    friend std::ostream& operator<<(std::ostream & os,const SuffixArray & l);

    SuffixArray(const unsigned char *T, int len);
    SuffixArray(const std::string &s);

    /**
     * Zoek de langste substring in de search buffer + lookahead buffer die start in de search buffer en
     * die een prefix is in de lookahead buffer (waarbij + string concatenatie voorstelt). 
     * Prefixen van 3 of minder karakters worden genegeerd.
     * 
     * @param search_buffer_begin de index waar de *search buffer* (en dus ook het *sliding window* begint)
     * 
     * @param search_buffer_lengte het aantal karakters in de *search buffer*
     * 
     * @param lookahead_buffer_lengte het aantal karakters in de *lookahead buffer* 
     *        (search_buffer_lengte + lookahead_buffer_lengte == sliding_window_lengte)
     * @returns een (lengte, afstand) paar, waarbij `lengte` de lengte van de gematchte substring teruggeeft, 
     *          en `afstand` het aantal karakters dat moet worden teruggekeerd in de search buffer om tot de start
     *          van de gematchte substring te komen. `lengte = 0` indien er geen match is van minstens 4 karakters lang. 
     */
    std::pair<int, int> zoekHerhaling(size_t search_buffer_begin, size_t search_buffer_lengte, size_t lookahead_buffer_lengte);
};
