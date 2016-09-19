#ifndef _AI_WONDER_H_
#define _AI_WONDER_H_

#include "fann/include/floatfann.h"
#include "fann/include/fann_cpp.h"
class AIWonder
{
public:
	static AIWonder & getSingleton();
	void train();
	int takeCard(char * cardsData);
	void initAI();
private:
	AIWonder();
	AIWonder(const AIWonder &);
	static AIWonder AI;
	static FANN::neural_net net;
};

#endif // !_AI_WONDER_H_