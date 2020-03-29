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

	void randomizeWeights();
	void update();
	void updateWeights();

	int inputs_count;
	float x, y, z;
	std::vector<float> weights;
	int layer;
	float learning_factor;
	std::vector<float> inputs;
	float output;
	float delta;

private:
	ErrorNeuro error;
	float sum;

	void activate();
	void sumarize();
	
	// activation functions
	float sigmoid(float in);
	float sigmoidDerivate(float in);
};