#include "Complex.h"

Complex::Complex()
{
	r = 0;
	i = 0;
}

Complex::Complex(double _r, double _i)
{
	r = _r;
	i = _i;
}

Complex Complex::operator+(Complex b)
{
	return Complex(r + b.r, i + b.i);
}

Complex Complex::operator-(Complex b)
{
	return Complex(r - b.r, i - b.i);
}

Complex Complex::operator*(Complex b)
{
	return Complex(r * b.r - i * b.i, r * b.i + i * b.r);
}

Complex Complex::operator/(double b)
{
	return Complex(r / b, i / b);
}

double operator+(double a, Complex b)
{
	return a + b.real();
}

double Complex::real()
{
	return r;
}

double Complex::imag()
{
	return i;
}