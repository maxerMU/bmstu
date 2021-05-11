#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>

class base_exception : public std::exception
{
public:
    base_exception() = default;
    explicit base_exception(std::string &message): error_info(message) {}

    const char *what() const noexcept override
    {
        return "Something wrong with viewer.";
    }

    const std::string &get_info() const noexcept
    {
        return error_info;
    }

protected:
    std::string error_info;
};

#endif // EXCEPTIONS_H
