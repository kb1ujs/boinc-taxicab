#include <gmp.h>
#include <stdint.h>
#include <vector>
#include <iostream>
#include <utility>
#include <map>

#define POWER 3
#define MODULUS 17

using namespace std;

int main()
{
	map <uint32_t, pair<uint32_t,uint32_t>> summap;
	pair<uint32_t,uint32_t> terms;
	

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

	mpz_init(a);
	mpz_init(b);
	mpz_init(subanswer);
	mpz_init(poweranswer);
	mpz_init(modanswer);
	
	for(uint32_t first_term = 1; z < MODULUS; z++)
	{
		mpz_set_ui(a,0);
		mpz_set_ui(b,z);
		mpz_set_ui(subanswer,0);
		mpz_set_ui(poweranswer,0);
		mpz_set_ui(modanswer,0);

		mpz_pow_ui(poweranswer,b,POWER);
		mpz_sub(subanswer,a,poweranswer);
		mpz_mod(modanswer,subanswer,modulus);

		uint32_t second_term = values[mpz_get_ui(modanswer)];

		if (second_term <= first_term) 
		{
			terms.first = first_term;
			terms.second = second_term;
		}
	}

return 0;
}
