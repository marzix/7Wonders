#include "AIWonder.h"
#include <ios>
#include <iostream>
#include <fstream>
#include <iomanip>
using std::cout;
using std::cerr;
using std::endl;
using std::setw;
using std::left;
using std::right;
using std::showpos;
using std::noshowpos;

#define netFileName "AIWonder.net"
#define trainingDataFile "AIWonder.data"
#pragma warning(disable: 4996)


AIWonder AIWonder::AI;
FANN::neural_net AIWonder::net;

AIWonder::AIWonder()
{
}

AIWonder::AIWonder(const AIWonder &)
{
}

AIWonder & AIWonder::getSingleton()
{
	return AI;
}

int AIWonder::takeCard(char * cardsData)
{
	int taken = 0;
	float temp = 0.0f;
	fann_type inputData[6];
	char * codes = strtok(cardsData, " ");
	for (int i = 0; i < 6; i++)
	{
		inputData[i] = atof(codes);
		codes = strtok(NULL, " ");
	}

	fann_type *calc_out = net.run(inputData);
	for (int j = 0; j < 5; j++)
	{
		if (calc_out[j] > temp)
		{
			temp = calc_out[j];
			taken = j + 1;
		}
	}
	return taken;
}

void AIWonder::train()
{
	std::ifstream dataFile(trainingDataFile);

	if (!dataFile.good())
	{
		cout << "No dataFile for training AI\n";
		system("pause");
		exit(0);
	}
	const float learning_rate = 0.7f;
	const unsigned int num_layers = 3;
	const unsigned int num_input = 6;
	const unsigned int num_hidden = 6;
	const unsigned int num_output = 5;
	const float desired_error = 0.0001f;
	const unsigned int max_iterations = 300000;
	const unsigned int iterations_between_reports = 100000;

	cout << endl << "Creating network." << endl;
	if (!net.create_standard(num_layers, num_input, num_hidden, num_output))
	{
		system("pause");
		exit(0);
	}

	net.set_learning_rate(learning_rate);

	net.set_activation_steepness_hidden(0.8);
	net.set_activation_steepness_output(0.8);

	net.set_activation_function_hidden(FANN::SIGMOID_SYMMETRIC_STEPWISE);
	net.set_activation_function_output(FANN::SIGMOID_SYMMETRIC_STEPWISE);

	// Set additional properties such as the training algorithm
	net.set_training_algorithm(FANN::TRAIN_QUICKPROP);

	// Output network type and parameters

	cout << endl << "Training network." << endl;

	FANN::training_data data;
	if (data.read_train_from_file(trainingDataFile))
	{
		// Initialize and train the network with the data
		net.init_weights(data);
		cout << "Max Epochs " << setw(8) << max_iterations << ". "
			<< "Desired Error: " << left << desired_error << right << endl;
		net.train_on_data(data, max_iterations,
			iterations_between_reports, desired_error);
/*
		cout << endl << "Testing network." << endl;

		for (unsigned int i = 0; i < data.length_train_data(); ++i)
		{
			// Run the network on the test data
			fann_type *calc_out = net.run(data.get_input()[i]);

			cout << "XOR test (" << showpos << data.get_input()[i][0] << ", " << data.get_input()[i][1] << ", " << data.get_input()[i][2] << ", " << data.get_input()[i][3] << ", " << data.get_input()[i][4] << ", " << data.get_input()[i][5] << ") -> "
				<< calc_out[0] << ", " << calc_out[1] << ", " << calc_out[2] << ", " << calc_out[3] << ", " << calc_out[4] << ", "
				<< ", should be " << data.get_output()[i][0] << ", " << data.get_output()[i][1] << ", " << data.get_output()[i][2] << ", " << data.get_output()[i][3] << ", " << data.get_output()[i][4] << ", "
				<< "difference = " << noshowpos
				<< fann_abs(*calc_out - data.get_output()[i][0]) << endl;
			int taken = 0;
			float temp = 0.0f;
			for (int j = 0; j < 5; j++)
			{
				if (abs(calc_out[j]) > temp)
				{
					temp = abs(calc_out[j]);
					taken = j + 1;
				}
			}
			cout << "Taken : " << taken << endl;
		}
		system("pause\n");
		*/
		cout << endl << "Saving network." << endl;

		// Save the network in floating point and fixed point
		net.save(netFileName);

		cout << endl << "Training AI completed\n" << endl;

	}
}

void AIWonder::initAI()
{
	std::ifstream netFile(netFileName);
	if (netFile.good())
	{
		cout << "Reading neural network from file\n";
		net.create_from_file(netFileName);
	}
	else
	{
		cout << "Neural network have not been found. Try to train on data from file " << trainingDataFile << endl;
		train();
	}
}