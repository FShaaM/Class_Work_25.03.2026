#include <iostream>
#include "vector.hpp"
#include <cstddef>
#include <cstring>
#include <stdexcept>

using namespace zinoviev;

bool testConstructAndDestruct(const char** pname) {
    *pname = __func__;
    Vector<int> v;
    return true;
}

bool testDefaultVectorIsEmpty(const char** pname) {
    *pname = __func__;
    Vector<int> v;
    return v.is_empty();
}

bool testSizeOfEmptyVector(const char** pname) {
    *pname = __func__;
    Vector<int> v;
    return !v.getSize();
}

bool testSizeOfNonEmptyVector(const char** pname) {
    *pname = __func__;
    constexpr size_t size = 2;
    Vector<int> v(size, 5);
    return v.getSize() == size;
}

bool testElementCheckedAccess(const char** pname) {
    *pname = __func__;
    Vector<int> v;
    v.push_back(2);
    try {
        int& r = v.at(0);
        return r == 2;
    }
    catch (...) {
        return false;
    }
}

bool testElementCheckedConstAccess(const char** pname) {
    *pname = __func__;
    Vector<int> v;
    v.push_back(2);
    const Vector<int>& rv = v;
    try {
        const int& r = rv.at(0);
        return r == 2;
    }
    catch (...) {
        return false;
    }
}

bool testElementCheckedOutOfBoundAccess(const char** pname) {
    *pname = __func__;
    Vector<int> v;
    try {
        v.at(0);
        return false;
    }
    catch (const std::out_of_range& e) {
        const char* text = e.what();
        return !std::strcmp("id out of bound", text);
    }
    catch (...) {
        return false;
    }
}

bool testElementCheckedOutOfBoundConstAccess(const char** pname) {
    *pname = __func__;
    const Vector<int> v;
    try {
        v.at(0);
        return false;
    }
    catch (const std::out_of_range& e) {
        const char* text = e.what();
        return !std::strcmp("id out of bound", text);
    }
    catch (...) {
        return false;
    }
}

bool testCopyConstructor(const char** pname) {
    *pname = __func__;
    Vector<int> v{ 1, 2 };
    Vector<int> yav = v;
    if (v.is_empty() || yav.is_empty()) {
        throw std::logic_error("Vectors expected to be non-empty");
    }
    bool isEqual = yav.getSize() == v.getSize();
    for (size_t i = 0; isEqual && i < v.getSize(); ++i) {
        try {
            isEqual = v.at(i) == yav.at(i);
        }
        catch (...) {
            return false;
        }
    }
    return isEqual;
}

bool testMoveConstructor(const char** pname) {
    *pname = __func__;
    Vector<int> v;
    v.push_back(1);
    v.push_back(2);
    size_t oldSize = v.getSize();
    Vector<int> moved(std::move(v));
    if (moved.getSize() != oldSize) return false;
    if (v.getSize() != 0) return false;
    if (moved[0] != 1 || moved[1] != 2) return false;
    return true;
}

bool testCopyAssignment(const char** pname) {
    *pname = __func__;
    Vector<int> a;
    a.push_back(1);
    a.push_back(2);
    Vector<int> b;
    b = a;
    if (b.getSize() != a.getSize()) return false;
    for (size_t i = 0; i < a.getSize(); ++i)
        if (b[i] != a[i]) return false;
    b = b;
    if (b.getSize() != 2) return false;
    if (b[0] != 1 || b[1] != 2) return false;
    return true;
}

bool testMoveAssignment(const char** pname) {
    *pname = __func__;
    Vector<int> a;
    a.push_back(1);
    a.push_back(2);
    Vector<int> b;
    b = std::move(a);
    if (b.getSize() != 2) return false;
    if (a.getSize() != 0) return false;
    if (b[0] != 1 || b[1] != 2) return false;
    b = std::move(b);
    if (b.getSize() != 2) return false;
    return true;
}

bool testSwap(const char** pname) {
    *pname = __func__;
    Vector<int> a;
    a.push_back(1);
    a.push_back(2);
    Vector<int> b;
    b.push_back(3);
    b.push_back(4);
    b.push_back(5);
    size_t aSize = a.getSize();
    size_t bSize = b.getSize();
    a.swap(b);
    if (a.getSize() != bSize || b.getSize() != aSize) return false;
    if (a[0] != 3 || a[1] != 4 || a[2] != 5) return false;
    if (b[0] != 1 || b[1] != 2) return false;
    return true;
}

bool testInsertSingle(const char** pname) {
    *pname = __func__;
    Vector<int> v;
    v.push_back(1);
    v.push_back(3);
    v.insert(1, 2);
    if (v.getSize() != 3) return false;
    if (v[0] != 1 || v[1] != 2 || v[2] != 3) return false;
    v.insert(0, 0);
    if (v[0] != 0) return false;
    v.insert(v.getSize(), 4);
    if (v[v.getSize() - 1] != 4) return false;
    return true;
}

bool testInsertRange(const char** pname) {
    *pname = __func__;
    Vector<int> v;
    v.push_back(1);
    v.push_back(5);
    Vector<int> toInsert;
    toInsert.push_back(2);
    toInsert.push_back(3);
    toInsert.push_back(4);
    v.insert(1, toInsert, 0, toInsert.getSize());
    if (v.getSize() != 5) return false;
    if (v[0] != 1 || v[1] != 2 || v[2] != 3 || v[3] != 4 || v[4] != 5) return false;
    v.insert(2, toInsert, 1, 1);
    if (v.getSize() != 5) return false;
    return true;
}

bool testEraseSingle(const char** pname) {
    *pname = __func__;
    Vector<int> v;
    for (int i = 0; i < 5; ++i) v.push_back(i);
    v.erase(2);
    if (v.getSize() != 4) return false;
    if (v[0] != 0 || v[1] != 1 || v[2] != 3 || v[3] != 4) return false;
    v.erase(0);
    if (v[0] != 1) return false;
    v.erase(v.getSize() - 1);
    if (v.getSize() != 2) return false;
    if (v[0] != 1 || v[1] != 3) return false;
    return true;
}

bool testEraseRange(const char** pname) {
    *pname = __func__;
    Vector<int> v;
    for (int i = 0; i < 10; ++i) v.push_back(i);
    v.erase(2, 5);
    if (v.getSize() != 7) return false;
    for (size_t i = 0; i < v.getSize(); ++i) {
        int expected = (i < 2) ? i : i + 3;
        if (v[i] != expected) return false;
    }
    v.erase(3, v.getSize());
    if (v.getSize() != 3) return false;
    if (v[0] != 0 || v[1] != 1 || v[2] != 5) return false;
    v.erase(1, 1);
    if (v.getSize() != 3) return false;
    return true;
}

int main() {
    using test_t = bool(*)(const char**);
    using case_t = std::pair<test_t, const char*>;
    case_t tests[] = {
        { testConstructAndDestruct, "Vector must be default constructable" },
        { testDefaultVectorIsEmpty, "Default constructed vector must be empty" },
        { testSizeOfEmptyVector, "Size of empty vector must be zero" },
        { testSizeOfNonEmptyVector, "Size of non-empty vector must be greater than zero" },
        { testElementCheckedAccess, "Inbound access must return lvalue reference to indexed value" },
        { testElementCheckedOutOfBoundAccess, "Out of bound access must generate exception with specific text" },
        { testElementCheckedConstAccess, "Same as inbound access but const" },
        { testElementCheckedOutOfBoundConstAccess, "Same as out of bound but const" },
        { testCopyConstructor, "Copied vector must be equal to original" },
        { testMoveConstructor, "Move constructor transfers ownership and empties source" },
        { testCopyAssignment, "Copy assignment must produce equal vector" },
        { testMoveAssignment, "Move assignment must transfer ownership" },
        { testSwap, "swap must exchange contents of two vectors" },
        { testInsertSingle, "insert single element at position" },
        { testInsertRange, "insert range from another vector" },
        { testEraseSingle, "erase single element by index" },
        { testEraseRange, "erase range of elements" }
    };
    constexpr size_t count = sizeof(tests) / sizeof(case_t);
    size_t failed = 0;
    for (size_t i = 0; i < count; ++i) {
        const char* testName = nullptr;
        bool r = false;
        try {
            r = tests[i].first(&testName);
        }
        catch (const std::logic_error& e) {
            std::cout << "[NOT RUN] " << testName << "\n";
            std::cout << "\tReason: " << e.what() << "\n";
            ++failed;
            continue;
        }
        if (!r) {
            ++failed;
            std::cout << "[FAIL] " << testName << "\n";
            std::cout << "\t" << tests[i].second << "\n";
        }
    }
    std::cout << "Summary:\n\t" << (count - failed) << " passed\n";
    std::cout << "\t" << count << " total\n";
}
