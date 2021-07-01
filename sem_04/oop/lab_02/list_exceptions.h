#ifndef LIST_EXCEPTION_H
#define LIST_EXCEPTION_H

#include <exception>
#include <string.h>
#include <string>

class list_exception : public std::exception
{
protected:
    std::string er_msg;

public:
    list_exception(const std::string &time, const std::string &file_name,
                   const std::string &class_name, const std::string &method_name)
        : er_msg("\nTIME: " + time + \
                 "\nFILE: " + file_name + \
                 "\nCLASS: " + class_name + \
                 "\nMETHOD: " + method_name)
    {
    }

    virtual const char *what() const noexcept override
    {
        char *cer_msg = new char[er_msg.length() + 12];
        strcpy(cer_msg, std::string("LIST ERROR\n" + er_msg).c_str());

        return cer_msg;
    }
};

class list_size_exception : public list_exception
{
public:
    list_size_exception(const std::string &time, const std::string &file_name,
                   const std::string &class_name, const std::string &method_name)
        :list_exception(time, file_name, class_name, method_name)
    {
    }

    virtual const char *what() const noexcept override
    {
        char *cer_msg = new char[er_msg.length() + 12];
        strcpy(cer_msg, std::string("SIZE ERROR\n" + er_msg).c_str());

        return cer_msg;
    }
};

class list_empty_exception : public list_exception
{
public:
    list_empty_exception(const std::string &time, const std::string &file_name,
                   const std::string &class_name, const std::string &method_name)
        :list_exception(time, file_name, class_name, method_name)
    {
    }

    virtual const char *what() const noexcept override
    {
        char *cer_msg = new char[er_msg.length() + 12];
        strcpy(cer_msg, std::string("EMPTY LIST\n" + er_msg).c_str());

        return cer_msg;
    }
};

class list_iterator_exception : public list_exception
{
public:
    list_iterator_exception(const std::string &time, const std::string &file_name,
                   const std::string &class_name, const std::string &method_name)
        :list_exception(time, file_name, class_name, method_name)
    {
    }

    virtual const char *what() const noexcept override
    {
        char *cer_msg = new char[er_msg.length() + 18];
        strcpy(cer_msg, std::string("INVALID ITERATOR\n" + er_msg).c_str());

        return cer_msg;
    }
};

class list_pointer_exception : public list_exception
{
public:
    list_pointer_exception(const std::string &time, const std::string &file_name,
                   const std::string &class_name, const std::string &method_name)
        :list_exception(time, file_name, class_name, method_name)
    {
    }

    virtual const char *what() const noexcept override
    {
        char *cer_msg = new char[er_msg.length() + 15];
        strcpy(cer_msg, std::string("POINTER ERROR\n" + er_msg).c_str());

        return cer_msg;
    }
};

class list_memory_exception : public list_exception
{
public:
    list_memory_exception(const std::string &time, const std::string &file_name,
                   const std::string &class_name, const std::string &method_name)
        :list_exception(time, file_name, class_name, method_name)
    {
    }

    virtual const char *what() const noexcept override
    {
        char *cer_msg = new char[er_msg.length() + 14];
        strcpy(cer_msg, std::string("MEMORY ERROR\n" + er_msg).c_str());

        return cer_msg;
    }
};

#endif // LIST_EXCEPTION_H
