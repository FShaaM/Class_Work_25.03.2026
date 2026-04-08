#include <iostream>
#include "pe_vector.hpp"
#include <cstddef>
#include <cstring>

using zinoviev::Vector;

bool test_getSie(const char** teastName)
{
    *teastName = __func__;
    Vector< int > v(2ull, 5);
    return !v.getSize();
}

bool test_Non_mempty(const char** teastName)
{
    *teastName = __func__;
    Vector< int > v(2ull, 5);

    return v.getSize() == 5;
}

bool test_Constract_and_Destract(const char** teastName)
{
    *teastName = __func__;
    Vector< int > v(2ull, 5);
    return true;
}

bool test_Default_Vec_is_empty(const char** teastName)
{
    *teastName = __func__;
    Vector< int > v(2ull, 5);
    return v.is_empty();
}

bool test_push_back(const char** teastName)
{
    *teastName = __func__;
    Vector< int > v(2ull, 5);
    try
    {
        v.push_back(6);
        return true;
    }
    catch (...)
    {
        return false;
    }
}

bool test_pop_back(const char** teastName)
{
    *teastName = __func__;
    Vector< int > v(5, 5);
    v.pop_back();

    return v.getSize() == 4;
}

bool test_at(const char** teastName)
{
    *teastName = __func__;
    Vector< int > v;

    v.push_back(1);

    try
    {
        int& r = v.at(0);
        return r == 1;
    }
    catch (...)
    {
        return false;
    }
}

bool test_cost_at(const char** teastName)
{
    *teastName = __func__;
    Vector< int > v;

    v.push_back(1);

    const Vector< int >& yav = v;

    try
    {
        const int& r = yav.at(0);
        return r == 1;
    }
    catch (...)
    {
        return false;
    }
}

bool test_at_bad(const char** teastName)
{
    *teastName = __func__;
    Vector< int > v;

    try
    {
        v.at(1);
        return false;
    }
    catch (std::out_of_range& e)
    {
        const char* text = e.what();
        return std::strcmp("id out of range", text);
    }
    catch (...)
    {
        return false;
    }
}

bool test_const_at_bad(const char** teastName)
{
    *teastName = __func__;
    const Vector< int > v;

    try
    {
        v.at(1);
        return false;
    }
    catch (std::out_of_range& e)
    {
        const char* text = e.what();
        return std::strcmp("id out of range", text);
    }
    catch (...)
    {
        return false;
    }
}


bool test_Copy_construct(const char** teastName)
{
    *teastName = __func__;
    Vector< int > v(5, 5);
    Vector< int > r = v;

    if (!v.is_empty() || !r.is_empty())
        throw std::logic_error("vectors expected to be not empty");

    bool isEqual = r.getSize() == v.getSize();
    for (size_t i = 0; isEqual && i < v.getSize() ; ++i)
    {
        try
        {
            isEqual = v.at(i) == r.at(i);
        }
        catch (...)
        {
            return false;
        }
    }

    return isEqual;
}



int main()
{
    using test_t = bool(*)(const char**);
    using case_t = std::pair<test_t, const char*>;

    case_t tests[] = {
      {test_Constract_and_Destract, "Vect must be default"},
      {test_Default_Vec_is_empty, "Defult Vector must be empty"},
      {test_getSie, "Size of empty vector must be 0"},
      {test_Non_mempty, "Size of non-empty vector must be !0"},
      {test_push_back, "Bad push_back"},
      {test_pop_back, "Bad pop_back"},
      {test_at_bad, "id out of range"},
      {test_at, "id isn't good"},
      {test_Copy_construct, "Elements isn't equal"},
      {test_cost_at, "Bad reading in vector"},
      {test_const_at_bad, "Bad, bad, bad is good"}
    };

    size_t f = 0;
    constexpr size_t count = sizeof(tests) / sizeof(tests[0]);
    for (size_t i = 0; i < count; ++i)
    {
        const char* teastName = nullptr;
        bool r = false;
        try
        {
            r = tests[i].first(&teastName);
        }
        catch (const std::logic_error& e)
        {
            std::cout << "NOT RUN Fanction" << i << "\n";
            std::cout << "NOT RUN " << tests[i].second << "\n";
            continue;
        }

        if (!r)
        {
            ++f;
            std::cout << "Error: " << teastName << "\n";
            std::cout << "\t" << tests[i].second << "\n";
        }
    }

    std::cout << "\n";

    std::cout << "Pass:\t" << (count - f) << "\n";
    std::cout << "Fail\t" << f << "\n";
    std::cout << "Summer:\t" << count << "\n";
}
