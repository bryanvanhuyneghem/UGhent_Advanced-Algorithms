#include "naiefZoeken.h"

bool naiefZoeken(std::string tekst, std::string patroon, int& vergelijkingen){
    if( tekst.size() < patroon.size()){
        return false;
    }
    for(int i = 0; i< tekst.size()-patroon.size()+1;i++){
        int j = 0;
        vergelijkingen++;
        while(j<patroon.size() && tekst[i+j] == patroon[j]){
                vergelijkingen++;
                j++;
            }
        if(j==patroon.size()){
            vergelijkingen--;
            return true;
        }
    }
    return false;

}