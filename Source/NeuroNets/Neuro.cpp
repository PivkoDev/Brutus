#include "Neuro.h"

#include <cassert>
#include <iostream>

Neuro::Neuro(int layer_in, int input_count) : 
	error(EN_None),
	sum(0.f),
	layer(layer_in),
	inputs_count(input_count)
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
		error = EN_InputNotMatchWeights;
		return;
	}
	
	sum = 0.f;

	for (int index = 0; index < weights.size(); index++)
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
void 
Neuro::update()
{
	error = EN_None;
	sumarize();
	if (error == EN_None)
	{
		activate();
	}
}

void
Neuro::randomizeWeights()
{
	for (int i = 0; i < weights.size(); i++)
	{
		float weight = ((rand() % 21) / 10.0f) - 1.0f;
		weights[i] = weight;
	}
}