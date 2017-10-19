#pragma once

#include <vector>

class Serializer;

enum ErrorNeuro
{
	EN_None,
	EN_InputNotMatchWeights
};
class Neuro
{
	

public:
	Neuro(int layer_in=0, int input_count=0);
	~Neuro();

	// state persistent
	int inputs_count;
	float x, y, z;
	std::vector<float> weights;
	int layer;
	float learning_factor;
	

	// state flow
	float sum;
	float output;
	float delta;
	std::vector<float> inputs;

	ErrorNeuro error;

	// flow
	void activate();
	void sumarize();
	void update();

	// change state
	void randomizeWeights();
	void updateWeights();

	// activation functions
	float sigmoid(float in);
	float sigmoidDerivate(float in);
};