#pragma once

#include "StackImplementation.h"
#include <list>
#include <stdexcept>
#include <cstddef>

using namespace std;

class ListStack : public IStackImplementation {
private:
    list<ValueType> _list;
  
public:
    ListStack() = default;
    
    ListStack(const ValueType* rawArray, const size_t size);

    void push(const ValueType& value);

    void pop();

    const ValueType& top() const;

    bool isEmpty() const;

    size_t size() const;
};
