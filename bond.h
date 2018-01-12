#include <math.h>
#include <algorithm>

class Bond {
	
	private:
		const double c;
		const double d;
		const double FV;
		const double PV;
		const int N;
	
	public:
		Bond(const double c,
			 const double d,
			 const double FV,
			 const double PV,
			 const int N)
			: c(c),d(d),FV(FV),PV(PV),N(N) {}
		double YTM() const;

	private:	
		double approximateYTM() const;
		double SecantMethod(double r0, double r1) const;
		// target function for secant method
		double foo(const double & r) const; 
};

double Bond::approximateYTM() const {
	return (c + (FV-PV)/(N+d)) / ((FV+PV)/2);
}

double Bond::foo(const double & r ) const {
   return PV - c/r * pow(1+r,1-d) - (FV-c/r) / pow(1+r,N+d);
}   

double Bond::SecantMethod(double r0, double r1) const {
	double r;
	const double epsilon = pow(10,-10);
	do {
	   r = r1 - (foo(r1) * (r1-r0)) / (foo(r1)-foo(r0));
	   r0 = r1;
	   r1 = r;
	} while( abs(r1-r0) > epsilon );
	return r;
}	

double Bond::YTM() const {
	// zero-coupon bond case
	if (c == 0) 
		return pow(FV/PV, 1/(N+d)) - 1;
	// bond's price is equal to its par value
	if (FV==PV) 
		return c/FV;
	// general case
	double r0, r1;
	r1 = approximateYTM();
	r0 = r1 * 0.95;
	return SecantMethod(r0, r1);
}
