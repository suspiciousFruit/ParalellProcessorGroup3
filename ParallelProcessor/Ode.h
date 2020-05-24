#pragma once
#include <map>
#include <string>
#include "Vector.h"
#include<cmath>



// Класс который предоставляет интерфейс для любой ОДУ
class Ode
{
public:
	Vector<double> operator() (double time, const Vector<double>& state) const;
	// Установка настроек
	void setSettings(const std::map<std::string, std::string>&);
	// Геттеры
	inline size_t getDimention() const; // Только ОДУ знает размерность системы (должна совпадать с размерностью нулевого вектора)
	inline Vector<double> getNullState() const; // Только ОДУ знает как формируется начальный вектор
};

class LorenzAttractor : public Ode
{
private:
	double sigma;
	double b;
	double r;
	Vector<double> null_state_;
public:
	LorenzAttractor() : r(28.0), b(8.0 / 3), sigma(10.0), null_state_({ 0, 0, 0 })
	{ }
	// {x0, y0, z0}
	Vector<double> operator() (double time, const Vector<double>& state) const
	{
		Vector<double> res(3);

		res[0] = sigma * (state[1] - state[0]);
		res[1] = state[0] * (r - state[2]) - state[1];
		res[2] = state[0] * state[1] - b * state[2];

		return res;
	}

	void setSettings(const std::map<std::string, std::string>& settings)
	{
		const std::map<std::string, std::string>::const_iterator nope = settings.end();
		std::map<std::string, std::string>::const_iterator pair;

		auto set = [&settings, &pair, &nope](double& var, const char* name) -> void
		{
			if ((pair = settings.find(name)) != nope)
			{
				var = std::atof(pair->second.c_str());
			}
		};

		set(sigma, "sigma");
		set(b, "b");
		set(r, "r");
		set(null_state_[0], "x0");
		set(null_state_[1], "y0");
		set(null_state_[2], "z0");
	}

	inline Vector<double> getNullState() const
	{ return null_state_; }

	inline size_t getDimention() const
	{ return 3; }
};

class DoublePendulum : public Ode
{
private:
	double m;
	double L;
	double g;
	Vector<double> null_state_;
public:
	DoublePendulum() :
		m(1.0), L(1.2), g(9.8), null_state_({ 0, 0, 0, 0 })
	{ }
	// { theta1, theta2, p1, p2 }
	Vector<double> operator() (double time, const Vector<double>& state) const
	{
		Vector<double> res(4);

		double k = 6.0 / (m * L * L);
		double arg = state[0] - state[1];
		double denominator = (16.0 - 9.0 * std::cos(arg) * std::cos(arg));

		res[0] = k * (2.0 * state[2] - 3.0 * std::cos(arg) * state[3]) / denominator;
		res[1] = k * (8.0 * state[3] - 3.0 * std::cos(arg) * state[2]) / denominator;
		res[2] = (-0.5 * m * L * L) * (res[0] * res[1] * std::sin(arg) + 3 * (g / L) * std::sin(state[0]));
		res[3] = (-0.5 * m * L * L) * (-res[0] * res[1] * std::sin(arg) + (g / L) * std::sin(state[1]));

		return res;
	}

	void setSettings(const std::map<std::string, std::string>& settings)
	{
		const std::map<std::string, std::string>::const_iterator nope = settings.end();
		std::map<std::string, std::string>::const_iterator pair;

		auto set = [&settings, &pair, &nope](double& var, const char* name) -> void
		{
			if ((pair = settings.find(name)) != nope)
			{
				var = std::atof(pair->second.c_str());
			}
		};

		set(m, "m");
		set(L, "L");
		set(g, "g");
		set(null_state_[0], "theta1");
		set(null_state_[1], "theta2");
		set(null_state_[2], "p1");
		set(null_state_[3], "p2");
	}

	inline Vector<double> getNullState() const
	{ return null_state_; }

	inline size_t getDimention() const
	{ return 4; }
};
