// Nike Z.
// многопоточное программирование mutex
// защита разделяемых ресурсов и синхронизация потока
// thread6.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>

using namespace std;

class MyClass
{
public:
		MyClass() 
		{
	
		}

	void DoWork();

	void DoWork(int a)
	{
		std::cout << "start thread id=" << this_thread::get_id() << endl;
		this_thread::sleep_for(chrono::milliseconds(8000)); //имитация долгих вычислений
		std::cout << " a=" << a << endl;
		std::cout << "finish thread id=" << this_thread::get_id() << endl;
	}

	int sum(int a, int b)
	{
		std::cout << "start thread id=" << this_thread::get_id() << endl;
		this_thread::sleep_for(chrono::milliseconds(8000)); //имитация долгих вычислений
		std::cout << " a+b=" << a + b << endl;
		std::cout << "finish thread id=" << this_thread::get_id() << endl;
		return a + b;
	}

};

void MyClass::DoWork()
{
	std::cout << "start thread id=" << this_thread::get_id() << endl;
	this_thread::sleep_for(chrono::milliseconds(8000)); //имитация долгих вычислений
	std::cout << "finish thread id=" << this_thread::get_id() << endl;
}

class SimpleTimer 
{
public:
	SimpleTimer();
	~SimpleTimer();
private:
	std::chrono::time_point<std::chrono::high_resolution_clock> start;
	std::chrono::time_point<std::chrono::high_resolution_clock> end;
};

SimpleTimer::SimpleTimer()
{
	start = std::chrono::high_resolution_clock::now();
}
SimpleTimer::~SimpleTimer()
{
	end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
	//double result = duration.count();
	std::cout << "прошло времени: " << duration.count() << " секунд" << std::endl;
}


void Print(char ch) 
{
	for (int i = 0; i < 6; ++i) 
	{
		for (int j = 0; j < 9; j++)
		{
			std::cout << ch;
		}
		std::cout << endl;
	}
}

int main()
{
	setlocale(LC_ALL, "ru");

	std::cout << "Hello World!\n";

	int result;
	MyClass m;
	//result = m.sum(2, 5); // т.к. будем ниже вызывать в потоке

	thread t([&]()
		{
			result = m.sum(2, 5);
		}
	);

	MyClass m2;
	thread t2([&]() { m2.DoWork();});

	//thread t3(&MyClass::DoWork, std::ref(m2), 5);
	//thread t3(static_cast<void (MyClass::*)(int&)>(&MyClass::DoWork), std::ref(m2), 5);
	//	thread t3(&MyClass::DoWork, m2);

	for (int i = 0; i < 20; i++)
	{
		std::cout << "id потока = " << this_thread::get_id() << " i=" << i << endl;
		this_thread::sleep_for(chrono::milliseconds(1000));
	}

	t.join();
	t2.join();
	//t3.join();
	std::cout << "result=" << result << endl;
	std::cout << "finish main" << endl;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
