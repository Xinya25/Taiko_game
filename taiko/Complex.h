#pragma once
#include <stdio.h>

class Complex
{
private:
	double r;
	double i;
public:
	Complex();
	Complex(double _r, double _i);
	Complex operator+(Complex b);
	Complex operator-(Complex b);
	Complex operator*(Complex b);
	Complex operator/(double b);
	double real();
	double imag();
	friend double operator+(double a, Complex b);
};

