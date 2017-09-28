#include "Net.h"
#include "..\Tools.h"
#include "..\Serializer.h"

Net::Net() : name("DefaultNet"), inputs_count(0), outputs_count(0)
{
	std::cout << "Net cretion started..." << EL;
	srand(time(NULL));
}

Net::~Net()
{
	std::cout << "Net removed." << EL;
}

void
Net::init()
{
	if (neuros.size() == 0)
	{
		for (int i = 0; i < 10; i++)
			neuros.push_back(Neuro());
	}
}

void
Net::setUpTestNetwork()
{
	std::vector<int> net = { 2,1,4,1,2 };

	// cwiartki 1,2,3,4 ( 0,1,2,3 ) binarnie 00,01,10,11
	std::vector<float> inputs_1 = { -1.f,-1.f };	// 3(2)
	std::vector<float> outputs_1 = { 1.f, 0.f };
	
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

	for (int layer=0; layer<net.size(); layer++ )
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
Net::learn(int steps_count)
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
			learnStep(i);
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
	int inputs_index = index * 2;
	int outputs_index = (index * 2) + 1;

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
	for (int n = 0; n < neuros.size(); n++)
	{
		auto& neuro = neuros[n];
		std::cout << "ln[" << n << "]:" << "\n";

		// Input layer
		if (n < inputs_count)
		{
			if (neuro.in_count != 1 || neuro.inputs.size() != 1)
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

		}

		for (int i = 0; i < neuro.in_count; i++)
		{
			std::cout << " i: " << i << " : " << neuro.inputs[i];
			std::cout << " : " << neuro.weights[i] << "\n";
		}
	}
}


void
Net::print()
{
	std::cout << "Neuros total: ";
	std::cout << neuros.size();
	std::cout << " , inputs: ";
	std::cout << inputs_count;
	std::cout << " , outputs: ";
	std::cout << outputs_count;
	std::cout << "\n";

	for (int i = 0; i < neuros.size(); i++)
	{
		std::cout << i;
		std::cout << ":";
		std::cout << neuros[i].layer;
		std::cout << ":";

		for (int w=0; w < neuros[i].weights.size(); w++)
		{
			std::cout << "w[";
			std::cout << w;
			std::cout << "]=";
			std::cout << neuros[i].weights[w];
			std::cout << ",";
		}

		std::cout << "\n";
	}

	std::cout << "\n";
}