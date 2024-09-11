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

		absComplex = 0;
		argsComplex = 0;
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

	Complex operator+ (Complex& other)
	{
		return Complex(re + other.re, im + other.im);
	}

	Complex operator- (Complex& other)
	{
		return Complex(re - other.re, im - other.im);
	}

	Complex operator* (Complex& other)
	{
		return Complex(re * other.re + im * other.im * (-1), re * other.im + im * other.re);
	}

	Complex operator/ (Complex& other)
	{
		return Complex((this->re * other.re + this->im * other.im) / (pow(other.re, 2) + pow(other.im, 2)), (this->im * other.re - this->re * other.im) / (pow(other.re, 2) + pow(other.im, 2)));
	}

	friend std::ostream& operator<< (std::ostream& sys, Complex& complex)
	{
		sys << complex.printComplex(1);
		return sys;
	}

	friend std::istream& operator>> (std::istream& sys, Complex& complex)
	{
		float a, b;

		sys >> a;
		sys >> b;

		complex.setValue(a, b);

		return sys;
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

	float getRe()
	{
		return re;
	}

	float getIm()
	{
		return im;
	}

	~Complex()
	{
	}

private:
	float re;
	float im;
	float absComplex;
	float argsComplex;

	void absComplexF()
	{
		absComplex = sqrt(pow(re, 2) + pow(im, 2));
	}

	void argComplex()
	{
		argsComplex = atan(im / re);
	}

	void setValue(float a, float b)
	{
		re = a;
		im = b;
	}
};

int main()
{
	Complex com = Complex(1,2);
	Complex com2 = Complex(5, 4);

	Complex com3 = Complex();

	Complex res;

	res = com + com2;

	std::cout << res.printComplex(1) << std::endl;

	std::cout << com.printComplex(1) << std::endl;

	std::cout << com << std::endl;

	std::cin >> com3;

	std::cout << com3 << std::endl;

	return 0;
}
