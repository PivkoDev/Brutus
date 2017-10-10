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
	
	/* Interface */
	
	/** 
	 *	Seting up test network and learning vector. For testing purposes only.
	 */
	void setUpTestNetwork();


	/** 
	 *	Setting up learning vector. 
	 *
	 *	@param lv : test vector, [0]<float>inputs_1 [1]<float>outputs_1 [2]<float>inputs_2 [3]<float>outputs_2 ...
	 */
	void setupLearningVector(std::vector<std::vector<float>>& lv);

	/**
	 *	Setting up net architecture, neuros in each layer count.
	 *
	 *	@param net : vector with neuros count in each layer 
	 *				 e.g. std::vector<int>= { 2,1,4,1,2 };
	 *				 1st layer(input) with 2 neuros
	 *				 2nd layer 1 neuro, 3rd layer 4 neuros ...
	 */
	void setup(std::vector<int>& net);

	/**
	 *	Learn process with defined steps count.
	 *
	 *	@param int : learn steps count
	 */
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
	int layers_count;
	std::vector<std::string> errors;
	
};