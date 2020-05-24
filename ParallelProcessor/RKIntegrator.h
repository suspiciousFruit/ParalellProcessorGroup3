#pragma once
#include <map>
#include <string>
#include "Vector.h"



template <typename Ode, typename RKMethod>
class RKIntegrator : public RKMethod
{
private:
	// Параметры которые относятся к ОДУ
	Ode ode_;
	// Параметры которые относятся методу Рунге-Кутте
	using RKMethod::A;
	using RKMethod::b_main;
	using RKMethod::b_subs;
	using RKMethod::c;
	const size_t rk_steps_number_;
	// Парметры которые относятся к интегратору
	size_t iteration_number_;
	double timespan_;
	double null_time_;
	bool is_main_;
public:
	RKIntegrator() : RKMethod(), rk_steps_number_(c.size()), iteration_number_(1),
		is_main_(true), null_time_(0), timespan_(0.05)
	{ }

	void setSettings(const std::map<std::string, std::string>& settings)
	{
		ode_.setSettings(settings);

		const auto nope = settings.end();
		std::map<std::string, std::string>::const_iterator pair;

		if ((pair = settings.find("iteration_number")) != nope)
			iteration_number_ = std::atoi(pair->second.c_str());

		if ((pair = settings.find("null_time")) != nope)
			null_time_ = std::atof(pair->second.c_str());

		if ((pair = settings.find("timespan")) != nope)
			timespan_ = std::atof(pair->second.c_str());

		if ((pair = settings.find("is_main")) != nope)
		{
			if (pair->second.c_str() == "true")
				is_main_ = true;
			else if (pair->second.c_str() == "false")
				is_main_ = false;
		}
	}
	// Функция которая интегрирует ОДУ в переданный файл
	void integrateInFile(std::ofstream& file_out)
	{
		// Получаем от ОДУ начальное положение системы
		Vector<double> null_state = ode_.getNullState();
		// Инициализируем вектора
		Vector<double> a(ode_.getDimention());
		Vector<Vector<double>> k(rk_steps_number_);
		Vector<double> res(ode_.getDimention());
		// Выбираем вектор по которому будет проходить суммирование
		const Vector<double>& b = (is_main_ ? b_main : b_subs);
		// В цикле интегрируем
		for (size_t n = 0; n < iteration_number_; ++n)
		{
			res.apply([](double) -> double { return 0.0; });

			for (size_t i = 0; i < rk_steps_number_; ++i)
			{
				a.apply([](double a) -> double { return 0.0; });

				for (size_t j = 0; j < i; ++j)
					a += A[i][j] * k[j];
				(a *= timespan_) += null_state;

				k[i] = ode_(null_time_ + timespan_ * c[i], a);

				res += k[i] * b[i];
			}
			res *= timespan_;
			res += null_state;
			// Выводим в файл
			file_out << res << std::endl;
			// Переходим к следующему начальному положению
			null_state = res;
			null_time_ += timespan_;
		}
	}
};
