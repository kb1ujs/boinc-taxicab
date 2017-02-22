#include <gmp.h>
#include <stdint.h>
#include <vector>
#include <iostream>
#include "tclap/CmdLine.h"

using namespace std;
using namespace TCLAP;		// Required to TCLAP command line argument library

unsigned int _intPower;		// Power of x in a^x + b^x = c^x + d^x, defaults to 5
unsigned int _intModulus;	// Modulus used to determine search size, defaults to 16777447.
							// Needs to be a prime that is 7 mod 8 for testing 5th powers.

void parseOptions(int argc, char** argv);	// Get user defined options if provided

int main(int argc, char** argv)
{
	parseOptions(argc,argv);				// Get user defined options if provided

	cout << "for intPower we got: " << _intPower << endl << "for intModulus we got: " << _intModulus << endl;	

	vector<uint32_t> values(_intModulus+1);	// Search array for moduli.  It's _intModulus+1 so we can use it as a lookup table directly

	mpz_t modulus, result, base;			// mpz_t so that we can use GMP functions to calculate modular powers.

	mpz_init(modulus);						
	mpz_init(result);
	mpz_init(base);

	mpz_set_ui(modulus, _intModulus);		// 

	for(unsigned int x=1; x<_intModulus+1; x++)
	{
		mpz_set_ui(base,x);								// Calculate modular powers from 1 to _intModulus for lookup table
		mpz_powm_ui(result, base, _intPower, modulus);

		values[mpz_get_ui(result)] = x;					// Stored this way so that values is a lookup table
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

	mpz_pow_ui(poweranswer,b,_intPower);
	mpz_sub(subanswer,a,poweranswer);
	mpz_mod(modanswer,subanswer,modulus);

	gmp_printf("%Zd\n",modanswer);


return 0;
}

void parseOptions(int argc, char** argv)
{
	try {

	CmdLine cmd("BOINC Taxicab", ' ', "0.99" );

	//
	// Define arguments
	//

	ValueArg<unsigned int> ipower("p", "power", "integer power", false, 5, "unsigned int");
	cmd.add( ipower );

	ValueArg<unsigned int> imodulus("m", "modulus", "modulus", false, 16777447, "unsigned int");
	cmd.add( imodulus );

	//
	// Parse the command line.
	//
	cmd.parse(argc,argv);

	//
	// Set variables
	//
	_intPower = ipower.getValue();
	_intModulus = imodulus.getValue();

	} catch ( ArgException& e )
	{ cout << "ERROR: " << e.error() << " " << e.argId() << endl; }
}
