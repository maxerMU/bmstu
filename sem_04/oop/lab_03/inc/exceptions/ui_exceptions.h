#ifndef UI_EXCEPTIONS_H
#define UI_EXCEPTIONS_H

#include "base_exception.h"

class ui_field_format_exception: public base_exception
{
public:
    ui_field_format_exception() = default;
    explicit ui_field_format_exception(std::string &message): base_exception(message) {}

    const char *what() const noexcept override
    {
        return "Wrong field format.";
    }
};

#endif // UI_EXCEPTIONS_H
