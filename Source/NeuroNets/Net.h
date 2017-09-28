#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Neuro.h"

class Serializer;

class Net
{
	
public:
	Net();
	~Net();

	void init();
	void setUpTestNetwork();
	void setupLearningVector(std::vector<std::vector<float>>& lv);
	void setup(std::vector<int>&);
	void learn(int);
	void learnStep(int);
	void print();

	// input data
	std::vector<std::vector<float>> learning_vectors;

	// state
	std::string name;
	std::vector<Neuro> neuros;
	int inputs_count;
	int outputs_count;

	// non persistent
	bool learning_vector_validated;
	bool learn_status_ok;
	std::vector<std::string> errors;
	
};