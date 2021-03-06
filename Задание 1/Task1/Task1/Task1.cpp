// Task1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

class B1 {
	int a;
public:
	B1() { cout << "object of " << typeid(*this).name() << " was created\n"; }
	B1(int x) :B1() { a = x; }
	~B1() { cout << "object of " << typeid(*this).name() << " was destroyed\n"; }
};

class B2 {
	int b;
public:
	B2() { cout << "object of " << typeid(*this).name() << " was created\n"; }
	B2(int x) :B2() { b = x; }
	~B2() { cout << "object of " << typeid(*this).name() << " was destroyed\n"; }
};

class D1 : virtual private B1, virtual public B2 {
	int c;
public:
	D1(int x, int y, int z) : B1(y), B2(z)
	{
		c = x;
		cout << "object of " << typeid(*this).name() << " was created\n";
	};
	~D1() { cout << "object of " << typeid(*this).name() << " was destroyed\n"; }
};

class D2 : virtual public B1, virtual private B2 {
	int d;
public:
	D2(int x, int y, int z) : B1(y), B2(z)
	{
		d = x;
		cout << "object of " << typeid(*this).name() << " was created\n";
	};
	~D2() { cout << "object of " << typeid(*this).name() << " was destroyed\n"; }
};

class D3 : private D1, public D2 {
	int e;
public:
	D3(int x, int y, int z, int i, int j) : D1(y, i, j), D2(z, i, j)
	{
		e = x;
		cout << "object of " << typeid(*this).name() << " was created\n";
	}
	~D3() { cout << "object of " << typeid(*this).name() << " was destroyed\n"; }
};


int main()
{
	D3 temp1(1, 2, 3, 4, 5);

    return 0;
}

