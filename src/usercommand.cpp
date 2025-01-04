// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include <memory>
#include <array>

#include "header/usercommand.hpp"
#include "header/details.hpp"
#include "header/customexception.hpp"
#include "header/funcptr.hpp"

QuantityOfParameters countParameters(const Function& command, const int8_t& quantityOfParameters) noexcept {
    auto ZERO_PARAM = std::make_unique<std::array<Function, 5>>();
    auto ONE_PARAM = std::make_unique<std::array<Function, 10>>();
    auto TWO_PARAMS = std::make_unique<std::array<Function, 10>>();

    // Initialize the arrays with valid command strings
    *ZERO_PARAM = {Cls, Ls, Exit};
    *ONE_PARAM = {Cd, Mkdir, Rmdir, Cat, Pwd, Perm, Touch, Rm};
    *TWO_PARAMS = {Rename, Copy, Echo, Reperm, Cut};

    if (in(*ZERO_PARAM, command)) {
        return ZERO;
    } else if (in(*ONE_PARAM, command)) {
        if (quantityOfParameters < 1) return ARGUMENT_ERROR;
        return ONE;
    } else if (in(*TWO_PARAMS, command)) {
        if (quantityOfParameters < 2) return ARGUMENT_ERROR;
        return TWO;
    }

    return UNDEFINED_ERROR;
}

FMObject getFMObject(const std::vector<std::string>& args) {
    if (args.empty()) throw EmptyCommandException("Required arguments");
    const Function command = stringToFunction(args[0]);
    const uint8_t quantityOfParameters = args.size() - 1;
    auto fmobject = std::make_unique<FMObject>();

    QuantityOfParameters paramCount = countParameters(command, quantityOfParameters);
    switch (paramCount) {
        case UNDEFINED_ERROR:  // Unknown command
            throw UndefinedCommandException("Undefined command");
            break;
        case ARGUMENT_ERROR:  // Invalid quantity of arguments
            throw InvalidArgumentException("Invalid number of arguments");
            break;
        default:
            // Begin of implementation
            if (command == Ls || command == Cd) {
                fmobject->getObject(getFunctionOfDirectoryVector(args)());
            }
            else {
                fmobject->getObject(getStringUniversalFunction(args)());
            }
            // End of implementation
            break;
    }
    return *fmobject;
}
