#ifndef MODEL_EXCEPTIONS_H
#define MODEL_EXCEPTIONS_H

#include "base_exception.h"

class model_exception: public base_exception
{
public:
    model_exception() = default;
    model_exception(std::string &message): base_exception(message) {}

    const char *what() const noexcept override
    {
        return "Problem with model.";
    }
};

class edge_exception: public model_exception
{
public:
    edge_exception() = default;
    edge_exception(std::string &message): model_exception(message) {}

    const char *what() const noexcept override
    {
        return "Incorrect edges.";
    }
};

#endif // MODEL_EXCEPTIONS_H
