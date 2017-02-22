#include <gmpxx.h>
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
	vector<mpz_class> testvector;

	mpz_class testmpzone("12309871982379182739812739");
	mpz_class testmpztwo("45928374509823745098723409587203948572093485720938465");
	mpz_class testmpzthree("22384750928347509283745092837459207834650982734650982734095872340958723049587");

	testvector.push_back(testmpztwo);
	testvector.push_back(testmpzone);
	testvector.push_back(testmpzthree);
	
	sort(testvector.begin(), testvector.end());

for (mpz_class n : testvector)
	{
		cout << n << endl;
	}

return 0;
}
