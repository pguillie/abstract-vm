#ifndef AVM_H_
#define AVM_H_

#include <iostream>
#include <fstream>

#include "parser/Parser.hpp"

std::queue<Instruction> parse(std::string source_file);

#endif // AVM_H_