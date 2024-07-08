#include <iostream>
#include <cmath>
#include <string>

class Complex
{
public:
	Complex(double a, double b)
	{
		re = a;
		im = b;
	}

	Complex(Complex& sourse)
	{
		re = sourse.re;
		im = sourse.im;
	}

	Complex()
	{
		re = 0;
		im = 0;
	}

	Complex operator+ (Complex other)
	{
		return Complex(re + other.re, im + other.im);
	}

	Complex operator- (Complex other)
	{
		return Complex(re - other.re, im - other.im);
	}

	Complex operator* (Complex other)
	{
		return Complex(re * other.re + im * other.im * (-1), re * other.im + im * other.re);
	}

	Complex operator/ (Complex other)
	{
		float tempIm = other.im;
		Complex temp = Complex(other.re, tempIm);

		Complex denominator = Complex * other; // не работать

		return
	}
	void absComplexF()
	{
		absComplex = sqrt(pow(re, 2) + pow(im, 2));
	}

	void argComplex()
	{
		argsComplex = atan(im / re);
	}

	std::string printComplex(int i)
	{
		std::string str;
		switch (i)
		{
		case 1:
			if (im >= 0)
				str = std::to_string(re) + "+" + std::to_string(im) + "i";
			else
				str = std::to_string(re) + std::to_string(im) + "i";
			break;

		case 2:
			absComplexF();
			argComplex();

			str = std::to_string(absComplex) + "(cos(" + std::to_string(argsComplex) + ") + sin(" + std::to_string(argsComplex) + "))";
			break;

		case 3:
			absComplexF();
			argComplex();

			if (argsComplex >= 0)
				str = std::to_string(absComplex) + " * e^(i * " + std::to_string(argsComplex) + ")";
			else
				str = std::to_string(re) + std::to_string(im) + "i";
			break;
		}
		return str;
	}


	~Complex()
	{
	}

private:
	float re;
	float im;
	float absComplex;
	float argsComplex;
};

int main()
{
	Complex com = Complex(1,2);
	Complex com2 = Complex(5, 4);

	Complex res;

	res = com + com2;

	std::cout << res.printComplex(1) << std::endl;

	std::cout << com.printComplex(1);

	return 0;
}
