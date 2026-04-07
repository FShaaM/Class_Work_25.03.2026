#include<iostream>
#include "pe_vector.hpp"
#include<cstddef>

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
      {test_pop_back, "Bad pop_back"}
    };

    size_t f = 0;
    constexpr size_t count = sizeof(tests) / sizeof(tests[0]);
    for (size_t i = 0; i < count; ++i)
    {
        const char* teastName = nullptr;
        bool r = tests[i].first(&teastName);

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
