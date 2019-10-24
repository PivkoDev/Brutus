#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/version.hpp>

#include "Tools.h"

#include "..\NeuroNets\Net.h"
#include "..\NeuroNets\Neuro.h"


class Serializer
{

public:
	
	void serialize(Net& net)
	{
		const char * DAT_FILENAME("net.dat");
		std::ofstream file_stream(DAT_FILENAME);
		boost::archive::binary_oarchive oa(file_stream);
		oa << net;
	}

	void deserialize(Net& net)
	{
		const char * DAT_FILENAME("net.dat");
		std::ifstream file_stream(DAT_FILENAME);
		boost::archive::binary_iarchive ia(file_stream);
		ia >> net;
	}
	

};

namespace boost {
	namespace serialization {

		template<class Archive>
		void serialize(Archive& ar, Net& net, const unsigned int version)
		{
			ar & net.name;
			ar & net.neuros;
			ar & net.inputs_count;
			ar & net.outputs_count;
		}

		template<class Archive>
		void serialize(Archive& ar, Neuro& neuro, const unsigned int version)
		{
			ar & neuro.x;
			ar & neuro.y;
			ar & neuro.z;
			ar & neuro.weights;
		}
	}
}

BOOST_CLASS_VERSION(Net, 1)
BOOST_CLASS_VERSION(Neuro, 1)
