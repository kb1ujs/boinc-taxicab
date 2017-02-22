#include <gmpxx.h>
#include <gmp.h>
#include <vector>
#include <iostream>
#include <utility>
#include <map>
#include <algorithm>

#define POWER 5
#define MODULUS 44275279

using namespace std;

int main()
{
	

	vector<unsigned int> values(MODULUS);

	mpz_class modulus, result, base;

	modulus = MODULUS;

	for(unsigned int x=1; x<MODULUS; x++)
	{	
		base = x;

		mpz_powm_ui(result.get_mpz_t(), base.get_mpz_t(), POWER, modulus.get_mpz_t());

		values[mpz_get_ui(result.get_mpz_t())] = x;

	}

	cout << "Generated modulus array." << endl;
	cout << "Modulus array has " << values.size() << " elements."  << endl;

	mpz_class a, b, subanswer, poweranswer, modanswer, first_term_powered, second_term_powered, second_term_mpz, power_sum;

	vector<mpz_class> taxicab_numbers;

	vector<mpz_class> sum_vector;
	vector<mpz_class>::iterator it;

	for(unsigned int test_modulus = 0; test_modulus < 100; test_modulus++)
	{
		for(unsigned int first_term = 1; first_term < MODULUS; first_term++)
		{

			a = test_modulus;

			b = first_term;

			subanswer = 0;
			poweranswer = 0;
			modanswer = 0;

			mpz_pow_ui(poweranswer.get_mpz_t(),b.get_mpz_t(),POWER);

			subanswer = a - poweranswer;

			// modanswer = subanswer % modulus;

			mpz_mod(modanswer.get_mpz_t(),subanswer.get_mpz_t(),modulus.get_mpz_t());

			unsigned int second_term = values[mpz_get_ui(modanswer.get_mpz_t())];

			second_term_mpz = second_term;

	//		cout << b << " ^ " << POWER << " - " << a << " % " << modulus << " = " << mpz_get_ui(modanswer.get_mpz_t()) << endl;				


			if (second_term <= first_term) 
			{				

				mpz_pow_ui(first_term_powered.get_mpz_t(), b.get_mpz_t(), POWER);
				mpz_pow_ui(second_term_powered.get_mpz_t(), second_term_mpz.get_mpz_t(), POWER);

				power_sum = first_term_powered + second_term_powered;

				sum_vector.push_back(power_sum);

			}
		}

		cout << "Filled result array." << endl;
		cout << "Result array has " << sum_vector.size() << " elements."  << endl;

		sort(sum_vector.begin(),sum_vector.end());

		cout << "Sorted result array." << endl;

		it = sum_vector.begin();

		while(it != sum_vector.end())
		{
			it = adjacent_find(it, sum_vector.end());

			if (it != sum_vector.end())
			{
				cout << "FOUND IT!" << endl;				

				taxicab_numbers.push_back(*it);
				++it;
			}
		}

		cout << "Searched result array." << endl;

		sum_vector.clear();

		cout << "Deleted result array." << endl;
	}
	sort(taxicab_numbers.begin(), taxicab_numbers.end());

	for (const auto i: taxicab_numbers)
	{
		cout << i << endl;
	}

return 0;
}
