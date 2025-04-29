#include <iostream>

class my_parse_error : public std::exception
{
private:
    std::string m_error;
public:
    my_parse_error(std::string error) : m_error(error) {}

    const char* what() const noexcept { return m_error.c_str(); }
};