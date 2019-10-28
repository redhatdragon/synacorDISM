#include <stdint.h>
#include <stdlib.h>
#include <iostream>

struct Instruction;
Instruction* instruction = nullptr;
uint8_t instructionCount = 0;

struct Instruction {
	uint8_t argCount = 0;
	Instruction() {
		if (instruction == nullptr) {
			instruction = (Instruction*)malloc(sizeof(instruction) * 22);
		}
		//instruction[instructionCount] = *this;
		//instructionCount++;
	}
	virtual void setup() {}
	virtual void execute() = 0;
};

#define INSTRUCTION_SETUP(className) \
struct className : public Instruction{ \
	className() { \
		memcpy(&instruction[instructionCount], this, sizeof(Instruction)); \
		instructionCount++; \
	}

//Got the idea from https://stackoverflow.com/questions/1132751/how-can-i-generate-unique-values-in-the-c-preprocessor
//by user Magnus.
#define MERGE_(a,b)  a##b
#define LABEL_(a) MERGE_(unique_label_, a)
#define UNIQUE_NAME LABEL_(__LINE__)

#define INSTRUCTION_END() }UNIQUE_NAME;

INSTRUCTION_SETUP(Test1)
	void setup(){
		argCount = 0;
	}
	void execute() {
		std::cout << "test1" << std::endl;
	}
INSTRUCTION_END()
//Test1 *t1 = new Test1();
INSTRUCTION_SETUP(Test2)
	void setup(){
		argCount = 1;
	}
	void execute() {
		std::cout << "test2" << std::endl;
	}
INSTRUCTION_END()


int main() {
	for (unsigned int i = 0; i < instructionCount; i++) {
		instruction[i].setup();
	}

	instruction[0].execute();
	instruction[1].execute();
	std::cout << (int)instruction[1].argCount << std::endl;
	return 0;
}