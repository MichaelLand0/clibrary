
double power(double base, double n)
{
	double p=1;
	double i;	
	for(i=0; i<n; i++)
		p *= base;
	return p;
}
