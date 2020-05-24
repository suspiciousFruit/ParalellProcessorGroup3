#pragma once
#include "IntegrateTask.h"
#include "RKIntegrator.h"
#include "RKMethods.h"
#include "Ode.h"
#include "KeyValueParser.h"



class task_allocator
{
public:
	virtual Task* allocate(std::ifstream&&, const std::filesystem::path&) = 0;
};

class IntegrateLorenzAttractorAllocator : public task_allocator
{
public:
	virtual Task* allocate(std::ifstream&& file_in, const std::filesystem::path& file_out_name) override
	{
		return new IntegrateTask<RKIntegrator<LorenzAttractor, RKMethodA>, KeyValueParser>
			(std::move(file_in), std::ofstream(file_out_name));
	}
};

class IntegrateDoublePendulumAllocator : public task_allocator
{
public:
	virtual Task* allocate(std::ifstream&& file_in, const std::filesystem::path& file_out_name) override
	{
		return new IntegrateTask<RKIntegrator<DoublePendulum, RKMethodA>, KeyValueParser>
			(std::move(file_in), std::ofstream(file_out_name));
	}
};
