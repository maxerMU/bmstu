#ifndef LOAD_EXCEPTIONS_H
#define LOAD_EXCEPTIONS_H

#include "base_exception.h"

class file_exception: public base_exception
{
public:
    file_exception() = default;
    explicit file_exception(std::string &message): base_exception(message) {}

    const char *what() const noexcept override
    {
        return "File corrupt or does not exist.";
    }
};

class build_exception: public base_exception
{
public:
    build_exception() = default;
    explicit build_exception(std::string &message): base_exception(message) {}

    const char *what() const noexcept override
    {
        return "Model hasn't built yet.";
    }
};

class no_camera_exception: public base_exception
{
public:
    no_camera_exception() = default;
    explicit no_camera_exception(std::string &message): base_exception(message) {}

    const char *what() const noexcept override
    {
        return "Firstly set any camera.";
    }
};

class file_open_exception: public file_exception
{
public:
    file_open_exception() = default;
    explicit file_open_exception(std::string &message): file_exception(message) {}

    const char *what() const noexcept override
    {
        return "Open error.";
    }
};

class file_format_exception: public file_exception
{
public:
    file_format_exception() = default;
    explicit file_format_exception(std::string &message): file_exception(message) {}

    const char *what() const noexcept override
    {
        return "Wrong format.";
    }
};

#endif // LOAD_EXCEPTIONS_H
