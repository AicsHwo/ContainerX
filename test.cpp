#include <iostream>

// #define _DEBUG
#define _USE_EXPANSION

#include "X.h"

int main(int argc, char** argv)
{
	X<int, 2> a({3,2});
	a(0)(0) = 24;
	std:: cout << a << std::endl;
	a.clearAll();
	a(2)(1) = 15;
	a(1)(1) = -4;
	std::cout << a(2)(1) << std::endl;
	// a.clearAll();
	std:: cout << a << std::endl;
	/*for(auto const& it : a)
	{
		std::cout << it << std::endl;
	}*/
	
	{
		std::cout << "Test Convert to binary stored in std::unique_ptr<T[]>" << std::endl;
		std::unique_ptr<int[]> ab = std::move( Con2Bin( a ) );
		for(int i = 0; i < a.length(); i++)
		{
			std::cout << ab[i] << std::endl;
		}
		
		X<int, 2> b({1, 6});
		std::cout << b << std::endl;
		b.readBin( ab );
		std::cout << b << std::endl;
	}
	
	{
		X<int, 2> b({1, 6});
		b.readBin( Con2Bin( a ) );
		std::cout << "Test File read / write" << std::endl;
		b.write("1x6.bin");
		X<int, 2> c({2, 3});
		std::cout << c << std::endl;
		c.read("1x6.bin");
		std::cout << c << std::endl;
	}

	{
		X<int, 3> d({1,2,3});
		
		d(0, 0, 1) = -114;
		d(0, 1, 2) = 15;
		std::cout << d << std::endl;
	}
	
	if(0)
	{
		X<int, 2> c({2, 3});
		int i = 0;
		for(auto& it : c)
		{
			it = i++;
		}
		{
			std::cout << "Run-Time fetch element inside compile-time dimension determined container :" << std::endl;
			std::cout << "Type number, press ENTER, repeat twice and type -1, ENTER." << std::endl;
			std::cout << "Full Data : " << c << std::endl;
			size_t input;
			std::vector<size_t> inputs;
			while((std::cin >> input) && input != -1)
			{
				inputs.push_back(input);
			}
			std::cout << c( inputs ) << std::endl;
		}
		
		{
			std::cout << "Run-Time allocate compile-time dimension determined container :" << std::endl;
			std::cout << "Type number, press ENTER, repeat twice and type -1, ENTER." << std::endl;
			size_t input;
			std::vector<size_t> inputs;
			while((std::cin >> input) && input != -1)
			{
				inputs.push_back(input);
			}
			X<int, 2> test(inputs);
			test.clearAll();
			int i{};
			for(auto& it : test)
			{
				it = i++;
			}
			std::cout << test << std::endl;
		}
	}
	
	{
		std::cout << "Test Copy constructor" << std::endl;
		X<int, 2> ac(a);
		std::cout << ac << std::endl;
		std::cout << "Test Range" << std::endl;
		Range r1({{1,2}, {3,5}});
		std::cout << r1 << std::endl;
		X<int, 2> d({5, 6});
		int i{};
		for(auto& it : d)
		{
			it = i++;
		}
		std::cout << "Test Container subset by Range" << std::endl;
		std::cout << d << std::endl;
		
		std::cout << d(r1) << std::endl;
	}
	
	{
		std::cout << "Test Range Partition" << std::endl;
		X<int, 2> d({5, 6});
		int i{};
		for(auto& it : d)
		{
			it = i++;
		}
		
		using namespace N_ContainerXRelated;
		Range r2({{0,1919}, {0,1079}});
		std::cout << r2 << std::endl;
		std::cout << split(r2, {3, 4}) << std::endl;
		
		Range dr({{0, 4}, {0, 5}});
		std::cout << split(dr, {2, 2}) << std::endl;
		
		X1<Range> partitions = split(dr, {2, 2});
		for(auto const& it : partitions)
		{
			std::cout << d( it ) << std::endl;
		}
	}
	
	{
		std::cout << "Test Return Range" << std::endl;
		X<int, 2> b({1, 6});
		X<int, 2> d({5, 6});
		std::cout << b.range() << std::endl;
		std::cout << d.range() << std::endl;
	}
	
	{
		std::cout << "Test self-defined initializer class" << std::endl;
		X<int, 2> a({2,3}, {1,2,3,-1,-2,-5});
		std::cout << a << std::endl;
		X1<int> b({7}, {9,10,59,151,875,25,4});
		std::cout << b << std::endl;
	}
	
	{
		std::cout << "Test Operator Overloads" << std::endl;
		X<int, 2> a({2,3}, {1,2,3, 0,-2,-5});
		X<int, 2> b({2,3}, {9,2,-59,151,875,-25});
		std::cout << "a = " << a << std::endl;
		std::cout << "b = " << b << std::endl;
		std::cout << "-a = " << -a << std::endl;
		std::cout << "a + b = " << a + b << std::endl;
		std::cout << "a - b = " << a - b << std::endl;
		std::cout << "a * b = " << a * b << std::endl;
		std::cout << "a / b = " << a / b << std::endl;
		std::cout << "(X2<float>)a = " << (X2<float>)a << std::endl;
		std::cout << "(X2<float>)a / (X2<float>)b = " << (X2<float>)a / (X2<float>)b << std::endl;
		a += b;
		std::cout << "a += b : " << a << std::endl;
		a -= b;
		std::cout << "a -= b : " << a << std::endl;
		a *= b;
		std::cout << "a *= b : " << a << std::endl;
		a /= b;
		std::cout << "a /= b : " << a << std::endl;
		std::cout << "a & b = " << (a & b) << std::endl;
		std::cout << "a | b = " << (a | b) << std::endl;
		std::cout << " !a : " << !a << std::endl;
		std::cout << "a && b : " << (a && b) << std::endl;
		std::cout << "a || b : " << (a || b) << std::endl;
		
		std::cout << "a == b : " << (a == b) << std::endl;
		std::cout << "a != b : " << (a != b) << std::endl;
		std::cout << "a > b : " << (a > b) << std::endl;
		std::cout << "a >= b : " << (a >= b) << std::endl;
		std::cout << "a < b : " << (a < b) << std::endl;
		std::cout << "a <= b : " << (a <= b) << std::endl;
		
		std::cout << "a = " << a << ", b = " << b << std::endl;
		a = b;
		std::cout << "a = " << a << " after a = b;" << std::endl;
		
		
		X<int, 1> c({7}, {1,2,3,4,5,7,6});
		X<int, 1> d({7}, {-1,-2,-3,4,5,-7,6});
		std::cout << "c = " << c << ", d = " << d << std::endl;
		c = d;
		std::cout << "c = " << c << " after c = d;" << std::endl;
	}
	
	{
		std::cout << "Test Common Ops" << std::endl;
		X<int, 2> a({2,3}, {1,2,3, 0,-2,-5});
		using namespace N_ContainerX_CommonOps;
		std::cout << "a = " << a << std::endl;
		std::cout << "Abs(a) = " << Abs(a) << std::endl;
		std::cout << "Max(a) = " << Max(a) << std::endl;
		std::cout << "Min(a) = " << Min(a) << std::endl;
		std::cout << "Sum(a) = " << Sum(a) << std::endl;
		std::cout << "Avg(a) = " << Avg(a) << std::endl;
		std::cout << "Normalize((X<float,2>)a) = " << Normalize((X<float,2>)a) << std::endl;
	}
	
	return 0;
}
