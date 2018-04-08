#include <iostream>
#include <conio.h>
#include "Set.h"

using namespace Util;
using namespace std;

int main()
{
	Set<int> set = Set<int>();

	// Test 1: adding an element, which is contained
	set += 0;
	set += 1;
	set += 2;
	set += 3;
	set += 2;
	cout << set.to_string() << endl;

	// Test 2: Removing elements
	set -= 0;
	set -= 3;
	cout << set.to_string() << endl;

	// Test 3a: Union. +=
	int *arr_a = new int[3]{ 8, 7, 6 };
	Set<int> other_a = Set<int>(arr_a, 3);
	set += other_a;
	delete[] arr_a;
	cout << set.to_string() << endl;

	// Test 3b: Union. +
	int *arr_b = new int[4]{ 1, 2, 6, 9 };
	Set<int> other = Set<int>(arr_b, 4);

	Set<int> united = set + other;
	delete[] arr_b;

	cout << set.to_string() << 
		" + " << 
		other.to_string() <<
		" = " <<
		united.to_string() <<
		endl;


	// Test 4a. Intersection. *=
	int *arr4_a = new int[4]{ 1, 2, 3, 7 };
	Set<int> other4_a = Set<int>(arr4_a, 4);
	cout << set.to_string() << " *= " << other4_a.to_string() << " == ";
	set *= other4_a;
	delete[] arr4_a;
	cout << set.to_string() << endl;

	// Test 4b. Intersection. *
	set += 4;
	set += 5;
	set += 10;
	int *arr4_b = new int[4]{ 1, 10, 3, 7 };
	Set<int> other4_b = Set<int>(arr4_b, 4);
	cout << set.to_string() << " * " << other4_b.to_string() << " = ";
	Set<int> intersetion = set * other4_b;
	delete[] arr4_b;
	cout << intersetion.to_string() << endl;

	// Test 5a. Bisection. -=
	int *arr5_a = new int[4]{ 1, 2, 3, 7 };
	Set<int> other5_a = Set<int>(arr5_a, 4);
	cout << set.to_string() << " -= " << other5_a.to_string() << " == ";
	set -= other5_a;
	delete[] arr5_a;
	cout << set.to_string() << endl;

	// Test 5b. Bisection. -
	set += 1;
	set += 2;
	set += 3;
	int *arr5_b = new int[4]{ 1, 10, 3, 7 };
	Set<int> other5_b = Set<int>(arr5_b, 4);
	cout << set.to_string() << " - " << other4_b.to_string() << " = ";
	Set<int> bis = set - other4_b;
	delete[] arr5_b;
	cout << bis.to_string() << endl;

	// Test 6a. Comparing different
	bool equal_a = set == other;
	cout << set.to_string() <<
		" == " <<
		other.to_string() <<
		" = " <<
		equal_a <<
		endl;

	// Test 6b. Comparing equal
	Set<int> same = set.clone();
	bool equal_b = set == same;
	cout << set.to_string() <<
		" == " <<
		same.to_string() <<
		" = " <<
		equal_b <<
		endl;

	// Test 6c. Comparing empty
	Set<int> empty1 = Set<int>();
	Set<int> empty2 = Set<int>();
	bool equal_c = empty1 == empty2;
	cout << empty1.to_string() <<
		" == " <<
		empty2.to_string() <<
		" = " <<
		equal_c <<
		endl;

	// Operations with empty sets
	cout << endl;
	set += empty1;	
	cout << set.to_string();
	cout << endl;
	set -= empty1;
	cout << set.to_string();
	cout << endl;
	set *= empty1;
	cout << set.to_string();
	cout << endl;

	set += other;
	cout << set.to_string();
	cout << endl;


	_getch();
}
