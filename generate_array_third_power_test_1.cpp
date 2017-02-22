#include <gmp.h>
#include <stdint.h>
#include <vector>
#include <iostream>
#include <utility>
#include <map>
#include <algorithm>

#define POWER 3
#define MODULUS 17

using namespace std;

int main()
{
	

	vector<uint32_t> values(MODULUS);

	mpz_t modulus, result, base;

	mpz_init(modulus);
	mpz_init(result);
	mpz_init(base);

	mpz_set_ui(modulus, MODULUS);

	for(unsigned int x=1; x<MODULUS; x++)
	{
		mpz_set_ui(base,x);
		mpz_powm_ui(result, base, POWER, modulus);

//		cout << mpz_get_ui(result) << endl;

		values[mpz_get_ui(result)] = x;
	}

	for (unsigned int y = 1; y < MODULUS; y++)
	{
		cout << y << ": " << values[y] << endl;
	}

	mpz_t a;
	mpz_t b;
	mpz_t subanswer;
	mpz_t poweranswer;
	mpz_t modanswer;

	mpz_t first_term_powered, second_term_powered, second_term_mpz, power_sum;

	typedef pair<uint32_t,uint32_t> terms;

	terms taxicab_terms;
	terms found_taxicab_terms;

	vector<uint32_t> taxicab_numbers;

	map <uint32_t, terms> sum_map;
	map <uint32_t, terms>::iterator it;

	mpz_init(a);
	mpz_init(b);
	mpz_init(subanswer);
	mpz_init(poweranswer);
	mpz_init(modanswer);
	mpz_init(first_term_powered);
	mpz_init(second_term_powered);
	mpz_init(power_sum);
	mpz_init(second_term_mpz);


	for(uint32_t test_modulus = 0; test_modulus < MODULUS; test_modulus++)
	{
		for(uint32_t first_term = 1; first_term <= MODULUS; first_term++)
		{
			mpz_set_ui(a,test_modulus);
			mpz_set_ui(b,first_term);
			mpz_set_ui(subanswer,0);
			mpz_set_ui(poweranswer,0);
			mpz_set_ui(modanswer,0);

			mpz_pow_ui(poweranswer,b,POWER);
			mpz_sub(subanswer,a,poweranswer);
			mpz_mod(modanswer,subanswer,modulus);

			uint32_t second_term = values[mpz_get_ui(modanswer)];

			cout << first_term << " ^ " << POWER << " - " << test_modulus << " % " << MODULUS << " = " << mpz_get_ui(modanswer) << endl;

			mpz_set_ui(second_term_mpz, second_term);

			if (second_term <= first_term) 
			{
				taxicab_terms.first = first_term;
				taxicab_terms.second = second_term;

				mpz_pow_ui(first_term_powered, b, POWER);
				mpz_pow_ui(second_term_powered, second_term_mpz, POWER);
				mpz_add(power_sum,first_term_powered,second_term_powered);

				it = sum_map.find(mpz_get_ui(power_sum));

				if (it == sum_map.end())
				{
					sum_map[mpz_get_ui(power_sum)] = taxicab_terms;
				}
				else
				{
					found_taxicab_terms = it->second;

//					cout <<  "Both " << taxicab_terms.first << "," << taxicab_terms.second << " and " << found_taxicab_terms.first << "," << found_taxicab_terms.second << " is " << it->first << endl;
					
					taxicab_numbers.push_back(it->first);
				}
			}
		}
	sum_map.clear();
	}

	sort(taxicab_numbers.begin(), taxicab_numbers.end());

	for (const auto i: taxicab_numbers)
	{
		cout << i << endl;
	}

return 0;
}
