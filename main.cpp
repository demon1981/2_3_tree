#include <iostream>
#include <time.h>
#include <conio.h>
#include "tree.h"

void testDelete()
{
	tree testTree;
	for (size_t i = 1; i <= 15; i++)
	{
		int a = 1 + rand() % 50;
		std::cout << "Insert " << a << std::endl;
		testTree.insert(a);		
		testTree.printTree2();
	}
	int value = 0;
	testTree.printTree2();
	std::cout << "delete: ";
	
	while (true)
	{
		std::cin >> value;
		testTree.erase(value);
		
		if (testTree.checkTree())
			std::cout << "Check OK!!!" << std::endl;
		else
			std::cout << "Check FALSE!!!" << std::endl;;

		
		testTree.printTree2();
		std::cout << "delete: ";
	}
}

void testDelete2()
{
	tree testTree;
	for (size_t i = 1; i <= 12; i++)
	{		
		testTree.insert(i);	
	}

	if (testTree.checkTree())
		std::cout << "Check OK!!!" << std::endl;
	else
		std::cout << "Check FALSE!!!" << std::endl;

	int value = 0;
	testTree.printTree2();
	std::cout << "delete: ";

	while (true)
	{
		std::cin >> value;
		testTree.erase(value);

		if (testTree.checkTree())
			std::cout << "Check OK!!!" << std::endl;
		else
			std::cout << "Check FALSE!!!" << std::endl;

		testTree.printTree2();
		std::cout << "delete: ";
	}
}

void testInsert() 
{	
	int a = 0;

	tree testTree; 
	for (size_t i = 1; i <= 10; i++)
	{
		a = 1 + rand() % 50;
		std::cout << "Insert " << a << std::endl;
		testTree.insert(a);
		testTree.printTree2();
	}	

	while (true)
	{
		std::cin >> a;
		testTree.insert(a);

		if (testTree.checkTree())
			std::cout << "Check OK!!!" << std::endl;
		else
			std::cout << "Check FALSE!!!" << std::endl;

		testTree.printTree2();
		std::cout << "Insert: ";
	}
}



void fullTest()
{
	int a = 0, value = 0;
	tree testTree;
	
	for (size_t i = 1; i <= 15; i++)
	{
		value = 1 + rand() % 50;
		std::cout << "Insert " << value << std::endl;
		testTree.insert(value);
		testTree.printTree2();
	}

	do
	{
		value = 1 + rand() % 50;		
	
		a = rand() % 2;
		if (a)
		{
			std::cout << "Insert " << value << std::endl;
			testTree.insert(value);
			testTree.printTree2();
		}
		else
		{	
			if (testTree.find(value))
			{
				std::cout << "Erase: " << value << std::endl;
				testTree.erase(value);
				testTree.printTree2();
			}
		}		

	}while (testTree.checkTree());
	_getch();
}

void dialogWithUser() {
	char c;
	bool quit = false;
	//while (quit != true) {		
		std::cout << "Select action (i-insert, e-erase, d-erase(rnd), f-full test) > ";
		std::cin >> c;		

		switch (c) {
		case 'i':
			testInsert();
			break;
		case 'd':
			testDelete();
			break;
		case 'e':
			testDelete2();
			break;
		case 'f':
			fullTest();
			break;		
		default:
			std::cout << "Invalid command!" << std::endl;
		}
	//}
}


int main() {
	srand(time(0));
	dialogWithUser();
	system("PAUSE");
	return 0;
}