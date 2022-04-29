#include "Stack.h"
#include "ListStack.h"
#include "VectorStack.h"
#include "StackImplementation.h"

#include <stdexcept>
#include <cstddef>

using namespace std;

Stack::Stack(StackContainer container) : _containerType(container)
{
    switch (container)
    {
    case StackContainer::List: {
        _pimpl = static_cast<IStackImplementation*>(new ListStack());    // конкретизируйте под ваши конструкторы, если надо
        break;
    }
    case StackContainer::Vector: {
        _pimpl = static_cast<IStackImplementation*>(new VectorStack());    // конкретизируйте под ваши конструкторы, если надо
        break;
    }
    default:
        throw runtime_error("Неизвестный тип контейнера");
    }
}

Stack::Stack(const ValueType* valueArray, const size_t arraySize, StackContainer container) : _containerType(container)
{
  switch (container)
    {
    case StackContainer::List: {
        _pimpl = static_cast<IStackImplementation*>(new ListStack(valueArray, arraySize)); 
        break;
    }
    case StackContainer::Vector: {
        _pimpl = static_cast<IStackImplementation*>(new VectorStack(valueArray, arraySize));
        break;
    }
    default:
        throw runtime_error("Неизвестный тип контейнера");
    }
    // принцип тот же, что и в прошлом конструкторе
}

Stack::Stack(const Stack& copyStack): Stack(copyStack._containerType)
{
    switch (copyStack._containerType)
    {
    case StackContainer::List: {
        _pimpl = static_cast<IStackImplementation*>(new ListStack(*dynamic_cast<ListStack*>(copyStack._pimpl)));
        break;
    }
    case StackContainer::Vector: {
        _pimpl = static_cast<IStackImplementation*>(new VectorStack(*dynamic_cast<VectorStack*>(copyStack._pimpl)));
        break;
    }
    default:
        throw runtime_error("Неизвестный тип контейнера");
    }
}

Stack& Stack::operator=(const Stack& copyStack)
{
  if (this != &copyStack) {
      delete _pimpl;
      Stack result(copyStack);
      _pimpl = result._pimpl;
      result._pimpl = nullptr;
      _containerType = result._containerType;
      return *this;
	}
  return *this;
    // TODO: вставьте здесь оператор return
}

Stack::Stack(Stack&& moveStack) noexcept {
  _pimpl = moveStack._pimpl;
  moveStack._pimpl = nullptr;
  _containerType = moveStack._containerType;
}
  
Stack& Stack::operator=(Stack&& moveStack) noexcept {
   if (this != &moveStack) {
      delete _pimpl;
      _pimpl = moveStack._pimpl;
      moveStack._pimpl = nullptr;
      _containerType = moveStack._containerType;
      return *this;
    }
    return *this;
}

Stack::~Stack()
{
    delete _pimpl;        // композиция!
}

void Stack::push(const ValueType& value)
{
    // можно, т.к. push определен в интерфейсе
    _pimpl->push(value);
}

void Stack::pop()
{
    _pimpl->pop();
}

const ValueType& Stack::top() const
{
    return _pimpl->top();
}

bool Stack::isEmpty() const
{
    return _pimpl->isEmpty();
}

size_t Stack::size() const
{
    return _pimpl->size();
}
