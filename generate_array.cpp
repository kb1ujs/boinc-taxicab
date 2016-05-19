#include <gmp.h>
#include <stdint.h>
#include <vector>
#include <iostream>

using namespace std;

int main()
{
	vector<uint32_t> values(16777448);

	mpz_t modulus, result, base;

	mpz_init(modulus);
	mpz_init(result);
	mpz_init(base);

	mpz_set_ui(modulus, 16777447);

	for(unsigned int x=1; x<16777449; x++)
	{
		mpz_set_ui(base,x);
		mpz_powm_ui(result, base, 5, modulus);

		values[mpz_get_ui(result)] = x;
	}

	for (unsigned int y = 1; y < 101; y++)
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
	
	mpz_set_ui(a,0);
	mpz_set_ui(b,100);
	mpz_set_ui(subanswer,0);
	mpz_set_ui(poweranswer,0);
	mpz_set_ui(modanswer,0);

	mpz_pow_ui(poweranswer,b,5);
	mpz_sub(subanswer,a,poweranswer);
	mpz_mod(modanswer,subanswer,modulus);

	gmp_printf("%Zd\n",modanswer);


return 0;
}
