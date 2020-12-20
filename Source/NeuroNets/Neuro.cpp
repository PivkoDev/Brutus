#include "Neuro.h"

#include <cassert>
#include <iostream>

Neuro::Neuro(int layer_in, int input_count) : 
	error{ ErrorNeuro::EN_None },
	sum{ 0.f },
	layer{ layer_in },
	inputs_count{ input_count },
	x{ 0.f },
	y{ 0.f },
	z{ 0.f },
	learning_factor{ 0.5f },
	delta{ 0.f },
	output{ 0.f }
{
	for (int i = 0; i < inputs_count; i++)
	{
		inputs.push_back(0.f);
		weights.push_back(0.f);
	}
}


Neuro::~Neuro()
{

}

void
Neuro::sumarize()
{
	if (weights.size() != inputs.size())
	{
		error = ErrorNeuro::EN_InputNotMatchWeights;
		return;
	}
	
	sum = 0.f;

	for (size_t index = 0; index < weights.size(); index++)
	{
		sum += inputs[index] * weights[index];
	}
}

void
Neuro::activate()
{
	assert(weights.size() == inputs.size());

	output = sigmoid(sum);
}

float
Neuro::sigmoid(float in)
{
	float ret;
	ret = 1 / (1 + exp(-in));
	return ret;
}

float
Neuro::sigmoidDerivate(float in)
{
	float ret;

	/**
	* ret = sigmoid(in) * (1 - sigmoid(in));
	* it should look like that but sigmoid already calculated so
	* use it
	*/
	ret = in * (1 - in);

	return ret;
}
void 
Neuro::update()
{
	error = ErrorNeuro::EN_None;
	sumarize();
	if (error == ErrorNeuro::EN_None)
	{
		activate();
	}
}

void
Neuro::randomizeWeights()
{
	for (size_t i = 0; i < weights.size(); i++)
	{
		float weight = ((rand() % 21) / 10.0f) - 1.0f;
		//float weight = 1.0f;
		weights[i] = weight;
	}
}

void
Neuro::updateWeights()
{
	for (size_t i = 0; i < weights.size(); i++)
	{
		float update = learning_factor * delta
			* inputs[i] * sigmoidDerivate(output);

		weights[i] = weights[i]  + update;
	}
}