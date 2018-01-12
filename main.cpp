#include <iostream>
#include "bond.h"

using namespace std;

int main() {
	double c, d, FV, PV;
	int N;
	cout << " coupon value = ";
	cin >> c;
	cout << " year fraction until next coupon payment = ";
	cin >> d;
	cout << " face value of a bond = ";
	cin >> FV;
	cout << " present value of a bond = ";
	cin >> PV;
	cout << " number of full years until maturity = ";
	cin >> N;
	cout << endl;

	Bond b(c,d,FV,PV,N);
	cout << " year to maturity = " << b.YTM() << endl;

	return 0;
}
