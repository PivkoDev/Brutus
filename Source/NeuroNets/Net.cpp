#include "Net.h"
#include "..\Tools\Tools.h"
#include "..\Tools\Serializer.h"

Net::Net() : 
	name{ "DefaultNet" },
	inputs_count{ 0 },
	outputs_count{ 0 },
	learning_vector_validated{ false },
	learn_status_ok{ false },
	layers_count{ 0 }
{
	std::cout << "Net cretion started..." << EL;
	srand(static_cast<unsigned int>(time(NULL)));
}

Net::~Net()
{
	std::cout << "Net removed." << EL;
}

void
Net::setUpTestNetwork()
{
	std::vector<int> net = { 2,2,4,2,2 };

	// cwiartki 1,2,3,4 ( 0,1,2,3 ) binarnie 00,01,10,11
	std::vector<float> inputs_1 = { -1.f,-1.f };	// 3 (2) (10)
	std::vector<float> outputs_1 = { 1.f, 0.f };
	
	std::vector<std::vector<float>> learning_vectors;
	learning_vectors.push_back(inputs_1);
	learning_vectors.push_back(outputs_1);

	setup(net);
	setupLearningVector(learning_vectors);
}

void
Net::setUpTestNetworkSimple()
{
	std::vector<int> net = { 1,2,1};

	// cwiartki 1,2,3,4 ( 0,1,2,3 ) binarnie 00,01,10,11
	std::vector<float> inputs_1 = { 0.f };	// 3 (2) (10)
	std::vector<float> outputs_1 = { 1.f };

	std::vector<std::vector<float>> learning_vectors;
	learning_vectors.push_back(inputs_1);
	learning_vectors.push_back(outputs_1);

	setup(net);
	setupLearningVector(learning_vectors);
}

void
Net::setupLearningVector(std::vector<std::vector<float>>& lv)
{
	learning_vectors.clear();
	learning_vector_validated = true;

	int index = 0;
	for (auto it : lv)
	{
		std::cout << "lv[" << index << "]:size:" << it.size() << "\n";
		learning_vectors.push_back(it);
		index++;

		if( index % 2 == 0 && it.size() != inputs_count)
		{
			std::cout << "Bad learning vector or wrong inputs count.";
			learning_vector_validated = false;
			break;
		}

		if (index % 2 == 1 && it.size() != outputs_count)
		{
			std::cout << "Bad learning vector or wrong outputs count.";
			learning_vector_validated = false;
			break;
		}
	}
}

void
Net::setup(std::vector<int>& net)
{
	neuros.clear();

	layers_count = net.size();

	for (size_t layer=0; layer<net.size(); layer++ )
	{
		int count = net[layer];
		int input_count = 1;
		if (layer > 0)
		{
			input_count = net[layer - 1];
		} 
		else
		{
			this->inputs_count = count;
		}
		if (layer == net.size() - 1)
		{
			this->outputs_count = count;
		}
		for (int i = 0; i < count; i++)
		{
			Neuro neuro(layer, input_count);
			neuro.randomizeWeights();
			neuros.push_back(neuro);
		}
	}
}
 
void
Net::learn(int steps_count, int step_repeat_count)
{	
	if (learning_vector_validated == false)
	{
		std::cout << "learning vector not set or validated.";
		return;
	}

	learn_status_ok = true;

	for (int i = 0; i < steps_count; i++)
	{
		if (learn_status_ok)
		{
			for (int j = 0; j < step_repeat_count; j++)
			{
				learnStep(i);
			}
		}
	}

	if (learn_status_ok == false)
	{
		std::cout << "Errors in learning :\n";
		for (auto error : errors)
		{
			std::cout << error << "\n";
		}
	}
}

void
Net::learnStep(int index)
{
	size_t inputs_index = index * 2;
	size_t outputs_index = (index * 2) + 1;
	
	//std::cout << "learnStep(" << index << ")\n";

	if (inputs_index > learning_vectors.size() - 1 ||
		outputs_index > learning_vectors.size() - 1)
	{
		learn_status_ok = false;
		errors.push_back("bad learning vectors index");
		return;
	}

	auto inputs = learning_vectors[inputs_index];
	auto outputs = learning_vectors[outputs_index];

	if (inputs.size() != inputs_count
		|| outputs.size() != outputs_count)
	{
		learn_status_ok = false;
		errors.push_back("wrong position in learning vector");
		return;
	}

	// forward propagation
	for (size_t n = 0; n < neuros.size(); n++)
	{
		auto& neuro = neuros[n];
	
		// Input layer
		if (neuro.layer == 0)
		{
			if (neuro.inputs_count != 1 || neuro.inputs.size() != 1)
			{
				learn_status_ok = false;
				errors.push_back("neuro in input layer wrong inputs count");
				continue;
			}
			
			// set input
			neuro.inputs[0] = inputs[n];
		}
		else
		{
			//neuro

			// go through previous layer neuros
			int n_prev = n - 1;
			int layer_prev = neuro.layer;
			size_t prev_index = 0;
			size_t prev_index_reversed = 0;

			while (n_prev >= 0 && layer_prev >= (neuro.layer-1) )
			{
				auto& neuro_prev = neuros[n_prev];
				layer_prev = neuro_prev.layer;

				if (neuro_prev.layer == (neuro.layer - 1))
				{
					assert(prev_index >= 0 && prev_index < neuro.weights.size() && prev_index < neuro.inputs.size());

					// last will be first because we iterate backwards
					prev_index_reversed = neuro.inputs.size() - prev_index - 1;

					assert(prev_index_reversed >= 0 && prev_index < neuro.weights.size());

					neuro.inputs[prev_index_reversed] = neuro_prev.output;

					prev_index += 1;
				}

				n_prev -= 1;
			}

			//std::cout << "prev_count: " << prev_index << "\n";
		}

		// Neuro update main.
		neuro.update();

		// Just debug print then.
		//for (int i = 0; i < neuro.inputs_count; i++)
		//{
		//	std::cout << "["<< neuro.layer << "].neuro[" << n << "].input[" << i << "] = " << neuro.inputs[i] \
		//		<< " * " << neuro.weights[i] << "\n";
		//}
		//std::cout << "Neuro sum: " << neuro.sum << " activated: " << neuro.output << "\n";
	}

	// backward propagation
	size_t output_index = 0;
	size_t output_index_rev = outputs.size() - 1;

	//std::cout << "\nbackward propagation\n";
	
	for (int n = neuros.size() - 1; n >= 0; n--)
	{
		auto& neuro = neuros[n];

		// Output layer
		if (neuro.layer == (layers_count - 1))
		{
			output_index_rev = outputs.size() - 1 - output_index;
			assert(output_index_rev >= 0 && output_index_rev < outputs.size());

			neuro.delta = outputs[output_index_rev] - neuro.output;

			output_index++;
		}
		else
		{
			// go through next layer neuros
			size_t n_next = n + 1;
			int layer_next = neuro.layer;
			int next_index = 0;
		
			// reset delta
			neuro.delta = 0;

			while (n_next < neuros.size() && layer_next <= (neuro.layer + 1))
			{
				auto& neuro_next = neuros[n_next];
				layer_next = neuro_next.layer;

				size_t weight_index = 0;

				if (neuro_next.layer == (neuro.layer + 1))
				{
					assert(weight_index < neuro_next.weights.size());
					neuro.delta += neuro_next.delta * neuro_next.weights[weight_index];
					weight_index++;
				}

				n_next++;
			}
		}

		//std::cout << "[" << neuro.layer << "].neuro[" << n << "].delta = " << neuro.delta << "\n";
	}

	/**
	* Weights update weight_updated = weight + update
	* update =
	*	learning_factor
	*   * error  // delta, per neuro , same for all weights
	*   * output from previus neuro  // diffrent for each weight
	*   * derivate(output) // per neuro, same for all weights
	*/
	for (size_t n = 0; n < neuros.size(); n++)
	{
		auto& neuro = neuros[n];

		neuro.updateWeights();
	}

	//std::cout << "\n";
}


void
Net::print(int level)
{
	std::cout << "Neuros total: ";
	std::cout << neuros.size();
	std::cout << " , inputs: ";
	std::cout << inputs_count;
	std::cout << " , outputs: ";
	std::cout << outputs_count;
	std::cout << "\n";

	if (level < 1) return;

	for (size_t i = 0; i < neuros.size(); i++)
	{
		std::cout << i;
		std::cout << ":";
		std::cout << neuros[i].layer;
		std::cout << ":";

		for (size_t w=0; w < neuros[i].weights.size(); w++)
		{
			std::cout << "w[";
			std::cout << w;
			std::cout << "]=";
			std::cout << neuros[i].weights[w];
			std::cout << ",";
		}

		std::cout << "\n";
		std::cout << " output = " << neuros[i].output << "\n";
	}

	std::cout << "\n";
}