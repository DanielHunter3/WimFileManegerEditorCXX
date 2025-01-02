// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include <memory>
#include <array>
#include <stdexcept>

#include "header/usercommand.hpp"
#include "header/details.hpp"

QuantityOfParameters countParameters(const std::string& command, const int8_t& quantityOfParameters) {
    auto ZERO_PARAM = std::make_unique<std::array<std::string, 10>>(
        //"2","2","1" /*...*/
    );
    auto ONE_PARAM = std::make_unique<std::array<std::string, 10>>(
        //"2","2","1" /*...*/
    );
    auto TWO_PARAMS = std::make_unique<std::array<std::string, 10>>(
        //"2","2","1" /*...*/
    );
    auto THREE_PARAMS = std::make_unique<std::array<std::string, 10>>(
        //"2","2","1" /*...*/
    );

    if (in(*ZERO_PARAM, command)) {
        return ZERO;
    } else if (in(*ONE_PARAM, command)) {
        if (quantityOfParameters < 1) {
            throw std::invalid_argument("Invalid number of parameters");
        }
        return ONE;
    } else if (in(*TWO_PARAMS, command)) {
        if (quantityOfParameters < 2) {
            throw std::invalid_argument("Invalid number of parameters");
        }
        return TWO;
    } else if (in(*THREE_PARAMS, command)) {
        if (quantityOfParameters < 3) {
            throw std::invalid_argument("Invalid number of parameters");
        }
        return THREE;
    }

    return ERROR;
}

auto f(const std::vector<std::string>& args) {
    if (args.empty()) throw std::runtime_error("Required arguments");
    const std::string command = args.at(0);
    const uint8_t quantityOfParameters = args.size() - 1;

    QuantityOfParameters paramCount = countParameters(command, quantityOfParameters);
    switch (paramCount) {
        case ZERO:
            // Your implementation for zero-parameter commands

            // End
            break;
        case ONE:
            // Your implementation for one-parameter commands

            // End
            break;
        case TWO:
            // Your implementation for two-parameter commands

            // End
            break;
        case THREE:
            // Your implementation for three-parameter commands

            // End
            break;
        case ERROR:
            throw std::runtime_error("Invalid number of parameters");
            break;
    }
}
