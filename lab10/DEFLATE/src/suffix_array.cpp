#include "suffix_array.h"
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <limits>

SuffixArray::SuffixArray(const unsigned char *T, int len) : lcp(len), sa(len), inv_sa(len)
{
    saisxx(T, std::begin(sa), len);
    

    int k = 0;

    for(int i = 0; i < len; i++){
        inv_sa[sa[i]] = i;
    }

    for(int i = 0; i < len; i++){
        if(inv_sa[i] == len-1) {
            k = 0; 
            continue;
        }
        int j = sa[inv_sa[i]+1];
        while(i + k < len && j + k < len && T[i+k] == T[j+k]){
            k++;
        }
        lcp[inv_sa[i]] = k;
        if (k>0){
            k--; 
        }
    }

    
};

SuffixArray::SuffixArray(const std::string &s) : SuffixArray((unsigned char *)s.c_str(), s.size()) {}


std::pair<int, int> SuffixArray::zoekHerhaling(size_t search_buffer_begin, size_t search_buffer_lengte, size_t lookahead_buffer_lengte)
{
    size_t index = inv_sa[search_buffer_begin+search_buffer_lengte];

    //int suffix = sa[index];

    bool match = false;

    int l_best_lcp_idx = -1;
    int l_min_lcp      = std::numeric_limits<int>::max();

    for(int i = index - 1; i >= 0; i--){
        int matching_length = lcp[i];
        l_min_lcp = std::min(l_min_lcp, matching_length);
        if(sa[i] >= search_buffer_begin && sa[i] < search_buffer_begin + search_buffer_lengte){
            l_best_lcp_idx = i;
            match = true;
            break;
        }  
    }


    int h_best_lcp_idx = -1;
    int h_min_lcp      = std::numeric_limits<int>::max();

    for(int i = index; i < lcp.size(); i++){
        int matching_length = lcp[i];
        if(sa[i] >= search_buffer_begin && sa[i] < search_buffer_begin + search_buffer_lengte){
            h_best_lcp_idx = i;
            match = true;

            break;
        }
        
        h_min_lcp = std::min(h_min_lcp, matching_length);
    }

    if((h_min_lcp < 4 && l_min_lcp < 4) || match == false ){
        return {0,0};
    }
    
    if(h_best_lcp_idx != -1 && (h_min_lcp > l_min_lcp )){
        assert(h_min_lcp > 3);
        int length = std::min((int)lookahead_buffer_lengte, h_min_lcp);
        int dist = search_buffer_begin + search_buffer_lengte - sa[h_best_lcp_idx];
        return {length, dist};
    }
    else if(l_best_lcp_idx != -1) {
        assert(l_min_lcp > 3);
        int length = std::min((int)lookahead_buffer_lengte, l_min_lcp);
        int dist = search_buffer_begin + search_buffer_lengte - sa[l_best_lcp_idx];
        return {length, dist};
    }
    return {0,0};
}




std::ostream& operator<<(std::ostream & os,const SuffixArray& l){
    size_t len = l.lcp.size();
    for(int i: l.lcp){
        std::cout << i << ", ";
    }
    std::cout << "\n";
    for(int i = 0; i < len; i++){
        os << std::setw(5) << std::left << i;
        std::string woord;
        for(int j = l.sa[i]; j < len; j++){
            woord += l.lcp[j];
        }
        os << std::setw(40) << std::left << woord;
        os << std::setw(3) << l.sa[i] << std::endl;
    }
    return os;
}