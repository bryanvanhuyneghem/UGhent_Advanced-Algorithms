#include "pakjes.h"


int min_aantal_voertuigen(int aantalPakjes, const std::vector<int>& voertuigen_grootte){
	//if niet op volgorde -> throw

	if(voertuigen_grootte.size() == 0){
		return -1;
	}
	if(aantalPakjes == 0){
		return 0;
	}
	// [aantalpakjes][voertuigidx]
	std::vector<std::vector<int>> min_v(aantalPakjes + 1, std::vector<int>(voertuigen_grootte.size(), 0));

	// 0 pakketjes = 0 voertuigen
	for (size_t j = 0; j < voertuigen_grootte.size(); j++){
		min_v[0][j] = 0;
	}
	// altijd 1 invullen?
	for (size_t i = 1; i <= aantalPakjes; i++){
		min_v[i][0] = i;
	}

	for (size_t j = 1; j < voertuigen_grootte.size(); j++){
		for (size_t i = 1; i <= aantalPakjes; i++){
			int vorige = min_v[i][j - 1];

			int minimum = std::numeric_limits<int>::max();
			const int aantal = i - voertuigen_grootte[j];
			//???????????????
			// segfault als we  i - voertuigen_grootte[j]; in de if zelf schrijven
			if((aantal) >= 0){
				minimum = std::min(minimum, 1 + min_v[aantal][j]);
			}
			
			min_v[i][j] = std::min(vorige, minimum);
		}
	}

	return min_v[aantalPakjes][voertuigen_grootte.size() - 1];
}

int min(const std::vector<int> &voertuigen_grootte, int m, int V)
{

    // table[i] will be storing the minimum number of vehicles
    // required for i value.  So table[V] will have result
    int table[V + 1];

    // Base case (If given value V is 0)
    table[0] = 0;

    // Initialize all table values as Infinite
    for (int i = 1; i <= V; i++)
        table[i] = std::numeric_limits<int>::max();

    // Compute minimum vehicles required for all
    // values from 1 to V
    for (int i = 1; i <= V; i++)
    {
        // Go through all vehicles smaller than i
        for (int j = 0; j < m; j++)
        {
            if (voertuigen_grootte[j] <= i)
            {
                int sub_res = table[i - voertuigen_grootte[j]];
                if (sub_res != std::numeric_limits<int>::max() && sub_res + 1 < table[i])
                    table[i] = sub_res + 1;
            }
        }
    }
    return table[V];
}

int min_aantal_voertuigen_GESTOLEN(int aantalPakjes, const std::vector<int> &voertuigen_grootte)
{
    if (voertuigen_grootte.size() == 0) return -1;
    if (aantalPakjes == 0) return 0;
    return min(voertuigen_grootte, voertuigen_grootte.size(), aantalPakjes);
}
int top_down_impl(std::vector<int>& min_v, const std::vector<int>& voertuigen_grootte, int aantal){
	if(aantal == 1){
		return 1;
	}
	if(aantal == 0){
		return 0;
	}
	if(min_v[aantal] == -1){
		int min = std::numeric_limits<int>::max();
		for(int v: voertuigen_grootte){
			const int rem = aantal - v;
			if((rem) >= 0){
				min = std::min(min, 1 + top_down_impl(min_v, voertuigen_grootte, rem));
			}
		}
		min_v[aantal] = min;
	}
	return min_v[aantal];
}
int min_aantal_voertuigen_top_down(int aantalPakjes, const std::vector<int>& voertuigen_grootte){
	if(voertuigen_grootte.size() == 0){
		return -1;
	}
	if(aantalPakjes == 0){
		return 0;
	}
	std::vector<int> min_v(aantalPakjes + 1, -1);

	top_down_impl(min_v, voertuigen_grootte, aantalPakjes);
	return min_v[aantalPakjes] ;
}