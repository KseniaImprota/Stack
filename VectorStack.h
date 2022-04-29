#pragma once

using namespace std;

#include <cstddef>
#include <stdexcept>
#include <vector>
#include "StackImplementation.h"

class VectorStack : public IStackImplementation {
private:
    vector<ValueType> _vector;
public:
    VectorStack() = default;

    VectorStack(const ValueType* rawArray, const size_t size);

    void push(const ValueType& value);

    void pop();

    const ValueType& top() const;

    bool isEmpty() const;

    size_t size() const;
};
