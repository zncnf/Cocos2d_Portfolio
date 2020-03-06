#include "Cuey.h"

Cuey* Cuey::Instance = nullptr;

Cuey::Cuey()
{
}

Cuey * Cuey::getInstance()
{
	if (Instance == nullptr) {
		Instance = new Cuey();
	}
	return Instance;
}

int Cuey::rand(int min, int max)
{
	auto cur_time = chrono::system_clock::now();
	auto duration = cur_time.time_since_epoch();
	auto millis = chrono::duration_cast<chrono::milliseconds>(duration).count();

	mt19937 engine(millis);
	uniform_int_distribution<int> distribution(min, max);
	auto generator = bind(distribution, engine);
	for (int i = 0; i < 1000; i++) {
		generator();
	}
	return generator();
}

float Cuey::rand(double min, double max)
{
	auto cur_time = chrono::system_clock::now();
	auto duration = cur_time.time_since_epoch();
	auto millis = chrono::duration_cast<chrono::milliseconds>(duration).count();

	mt19937 engine(millis);
	uniform_real_distribution<double> distribution(min, max);
	auto generator = bind(distribution, engine);
	for (int i = 0; i < 1000; i++) {
		generator();
	}
	return generator();
}
