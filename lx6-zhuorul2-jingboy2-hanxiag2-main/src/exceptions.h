/**
 * @file exceptions.h
 * @author Unidentity (jingboy2@illinois.edu)
 * @brief Definitions of customized exceptions.
 * @date 2021-12-08
 * 
 */

#pragma once

#include <string>

using std::string;

/**
 * @brief Fatal error that inevitably stops the business process. 
 * 
 * @note When caught, the program may halt, crash, or start over.
 * 
 */
class __fatal_error : std::exception
{
protected:
    string err_msg;
public:
    __fatal_error() {}

    __fatal_error(string what) : err_msg(what) {}

    virtual const char* what() const throw() {
        return err_msg.c_str();
    }
};

/**
 * @brief Thrown when statements act abnormaly, but can be dealt with 
 * without halting. 
 * 
 * @note When caught, the program should take care of whatever happened, without
 * stopping the workflow.
 * 
 */
class __unexpected_behavior : std::exception
{
protected:
    string err_msg;
public:
    __unexpected_behavior() {}

    __unexpected_behavior(string what) : err_msg(what) {}

    virtual const char* what() const throw() {
        return err_msg.c_str();
    }
};

class __critical_data_not_found : public __unexpected_behavior
{
public:
    __critical_data_not_found(string which) {
        err_msg = which;
        err_msg.append(" is undefined (not found).");
    }
};

struct __vector_len_does_not_match : public __unexpected_behavior
{
    const char* what() const throw() {
        return "Passed vector has invalid size.";
    }
};

class __fail_to_open_file : public __fatal_error
{
public:
    __fail_to_open_file(string p) {
        err_msg = "Failed to open csv file at ";
        err_msg.append(p);
        err_msg.append(".");
    }
};
