#ifndef MY_STD_FUNCTION_H
#define MY_STD_FUNCTION_H

#include "forward.hpp"

#include <memory>
#include <stdexcept>

namespace my_std
{

template<class R, typename ... Types>
class function;

template<typename R, typename ... Types>
class CallableObject
{
public:
    virtual ~CallableObject() {}
    virtual R call(Types ... args) = 0;
    virtual std::unique_ptr<CallableObject<R, Types ...>> copy() const = 0;
};

template<typename Callable, typename R, typename ... Types>
class CallableObjectImpl : public CallableObject<R, Types ...>
{
public:
    CallableObjectImpl(Callable callable) : func_(callable) {}
    R call(Types ... args) override { return func_(my_std::forward<Types>(args)...); }
    std::unique_ptr<CallableObject<R, Types ...>> copy() const override { return std::make_unique<CallableObjectImpl<Callable, R, Types ...>>(func_); }
private:
    Callable func_;
};

template<typename R, typename ... Types>
class function<R(Types ...)>
{
public:
    template<typename Callable>
    function(Callable callable);

    function();
    function(const function &other);
    function(function &&other);

    function &operator=(const function &other);
    function &operator=(function &&other);
    function &operator=(std::nullptr_t);

    void swap(function &other);

    explicit operator bool() const;

    R operator()(Types ... args);

private:
    std::unique_ptr<CallableObject<R, Types ...>> func_;
};

template<typename R, typename ... Types>
template<typename Callable>
function<R(Types ...)>::function(Callable callable)
    :   func_(std::make_unique<CallableObjectImpl<Callable, R, Types ...>>(callable)) {}

template<typename R, typename ... Types>
function<R(Types ...)>::function(const function &other)
    :   func_(std::move(other.func_->copy())) {}

template<typename R, typename ... Types>
function<R(Types ...)>::function(function &&other)
    :   func_(std::move(other.func_)) {}

template<typename R, typename ... Types>
function<R(Types ...)>::function()
    :   func_(nullptr) {}

template<typename R, typename ... Types>
function<R(Types ...)> &function<R(Types ...)>::operator=(const function &other)
{
    func_ = std::move(other.func_->copy());
    return *this;
}

template<typename R, typename ... Types>
function<R(Types ...)> &function<R(Types ...)>::operator=(function &&other)
{
    func_ = std::move(other.func_);
    return *this;
}

template<typename R, typename ... Types>
function<R(Types ...)> &function<R(Types ...)>::operator=(std::nullptr_t)
{
    func_ = nullptr;
    return *this;
}

template<typename R, typename ... Types>
void function<R(Types ...)>::swap(function &other)
{
    std::swap(func_, other.func_);
}

template<typename R, typename ... Types>
function<R(Types ...)>::operator bool() const
{
    return func_ != nullptr;
}

template<typename R, typename ... Types>
R function<R(Types ...)>::operator()(Types ... args)
{
    if ( !func_ )
    {
        throw std::runtime_error("function pointer is nullptr");
    }
    return func_->call(std::forward<Types>(args)...);
}

} // namespace my_std

#endif // MY_STD_FUNCTION_H
