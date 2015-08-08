#include "training_module.h"

#include <iostream>
#include <string>

static void showHelp()
{
	std::cout << "\nTraining module for Boosting Sex Identification Performance article. \n"
		"Usage:\n"
		"  --train <1 or 0>\n"
		"	1 - to train model\n"
		"	0 - to evaluate accuracy of trained model (default)\n"
		"  --data_filename <filename> \n "
		"	File with images in *.vec format\n"
		"  --model_filename <filename> \n"
		"	Filename to save model\n"
		"  --percent_trainset <percent>\n"
		"	Percent of data as trainset should be in [0.5; 1], if evaluate [0; 1]\n"
		"	Can be used for evaluating accuracy on (100% - percent_train) data\n"
		"	(default - 0.0 (0 %)\n"
		"  --percent_classifiers <percent>\n"
		"	Percent of classifiers to observe in every iterations, Should be [0.01, 1].\n"
		"	(default - 1.0 (100%)\n"
		"  --num_classifiers <amount> \n"
		"	Amount of classifiers to train. Should be from 1 to 1000.\n"
		"  --save_period <period> \n"
		"	Save trained classifiers every 'period' iterations (default - 100)\n"
		"  --balanced <1 or 0>\n"
		"	Set flag to 1 if you want balanced train data (default - 0)\n"
		"\n"
		"Sample to train model:\n"
		"  *.exe --train 1 --data_filename \"16samples00.vec\" --model_filename \"model.txt\" \n"
		"    --percent_train 0.8 --num_classifiers 20 --save_period 10\n"
		"\n"
		"Sample to evaluate accuracy of trained model:\n"
		"  *.exe --data_filename \"16samples00.vec\" --model_filename \"model.txt\" \n"
		"--percent_train 0.8\n";
}

int main(int argc, char *argv[])
{
	if (argc == 1) 
	{
		showHelp();
		return 0;
	}

	TrainingModule tm;
	if (tm.init(argc, argv) == true)
		tm.run();

	return 0;
}