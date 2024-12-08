#include "ALU.h"
#include "Utilities.h"
#include <sstream>
#include <cstdint>
#include <iomanip>

void ALU::addTwosComplement(CPU *cpuPtr) { //5RST
    int regIndexS = Utilities::Conversions::hexToDec(std::string(1, cpuPtr->ir[2]));
    int regIndexT = Utilities::Conversions::hexToDec(std::string(1, cpuPtr->ir[3]));

    int valueS = Utilities::Conversions::hexToDec(cpuPtr->registers->getCell(regIndexS));
    int valueT = Utilities::Conversions::hexToDec(cpuPtr->registers->getCell(regIndexT));


    int result = valueS + valueT;

    if (result > 127) result -= 256;
    else if (result < -128) result += 256;

    int regIndexR = Utilities::Conversions::hexToDec(std::string(1, cpuPtr->ir[1]));

    std::stringstream stream;
    stream << std::hex << std::setw(2) << std::setfill('0') << (result & 0xFF);
    cpuPtr->registers->setCell(regIndexR, stream.str());
}

void ALU::addFloatingPt(CPU *cpuPtr) {
    std::string S = cpuPtr->registers->getCell(
            Utilities::Conversions::hexToDec(std::string(1, cpuPtr->ir[2])));
    std::string T = cpuPtr->registers->getCell(
            Utilities::Conversions::hexToDec(std::string(1, cpuPtr->ir[3])));

    int valueS = Utilities::Conversions::hexToDec(S);
    int valueT = Utilities::Conversions::hexToDec(T);

    double floating_pointS = Utilities::Conversions::binToFloat(
            Utilities::Conversions::intToBin(valueS));
    double floating_pointT = Utilities::Conversions::binToFloat(
            Utilities::Conversions::intToBin(valueT));

    double result = floating_pointS + floating_pointT;
    if (result > 7.5) result = 7.5;
    else if (result < -7.5) result = -7.5;

    int valueR = std::stoi(Utilities::Conversions::floatToBin(result), nullptr, 2);
    std::stringstream stream;
    stream << std::hex << std::setw(2) << std::setfill('0') << valueR;

    cpuPtr->registers->setCell(
            Utilities::Conversions::hexToDec(std::string(1, cpuPtr->ir[1])), stream.str());
}

void ALU::bitwiseAND(CPU *cpuPtr) {
    int regIndexS = Utilities::Conversions::hexToDec(std::string(1, cpuPtr->ir[2]));
    int regIndexT = Utilities::Conversions::hexToDec(std::string(1, cpuPtr->ir[3]));

    int valueS = Utilities::Conversions::hexToDec(cpuPtr->registers->getCell(regIndexS));
    int valueT = Utilities::Conversions::hexToDec(cpuPtr->registers->getCell(regIndexT));


    int result = valueS & valueT;

    std::stringstream stream;
    stream << std::hex << std::setw(2) << std::setfill('0') << result;
    cpuPtr->registers->setCell(
            Utilities::Conversions::hexToDec(std::string(1, cpuPtr->ir[1])), stream.str());
}

void ALU::bitwiseOR(CPU *cpuPtr) {
    int regIndexS = Utilities::Conversions::hexToDec(std::string(1, cpuPtr->ir[2]));
    int regIndexT = Utilities::Conversions::hexToDec(std::string(1, cpuPtr->ir[3]));

    int valueS = Utilities::Conversions::hexToDec(cpuPtr->registers->getCell(regIndexS));
    int valueT = Utilities::Conversions::hexToDec(cpuPtr->registers->getCell(regIndexT));

    int result = valueS | valueT;

    std::stringstream stream;
    stream << std::hex << std::setw(2) << std::setfill('0') << result;
    cpuPtr->registers->setCell(
            Utilities::Conversions::hexToDec(std::string(1, cpuPtr->ir[1])), stream.str());
}

void ALU::bitwiseXOR(CPU *cpuPtr) {
    int regIndexS = Utilities::Conversions::hexToDec(std::string(1, cpuPtr->ir[2]));
    int regIndexT = Utilities::Conversions::hexToDec(std::string(1, cpuPtr->ir[3]));

    int valueS = Utilities::Conversions::hexToDec(cpuPtr->registers->getCell(regIndexS));
    int valueT = Utilities::Conversions::hexToDec(cpuPtr->registers->getCell(regIndexT));

    int result = valueS ^ valueT;

    std::stringstream stream;
    stream << std::hex << std::setw(2) << std::setfill('0') << result;
    cpuPtr->registers->setCell(
            Utilities::Conversions::hexToDec(std::string(1, cpuPtr->ir[1])), stream.str());
}

void ALU::rotateRight(CPU *cpuPtr) {
    int regIndexR = Utilities::Conversions::hexToDec(std::string(1, cpuPtr->ir[1]));
    int value = Utilities::Conversions::hexToTwosComplementInt(
            cpuPtr->registers->getCell(regIndexR));

    int steps = Utilities::Conversions::hexToDec(std::string(1, cpuPtr->ir[3])) % 8;

    uint8_t rotatedValue = (value >> steps) | (value << (8 - steps));

    std::stringstream stream;
    stream << std::hex << std::setw(2) << std::setfill('0') << (rotatedValue & 0xFF);
    cpuPtr->registers->setCell(regIndexR, stream.str());
}
