#ifndef MY_STD_FUNCTION_H
#define MY_STD_FUNCTION_H

#include <iostream>

namespace my_std
{

template<class R, typename ... Types>
class function;

template<typename R, typename ... Types>
class function<R(Types ...)>
{
public:
    function();
    function(R (*func_ptr)(Types ...));
    function(const function& other);
    function(function&& other);

    // template<class F>
    // function(F&& f);

    ~function();

    function& operator=(const function& other);
    function& operator=(function&& other);
    function & operator=(std::nullptr_t);

    void swap(function& other);

    explicit operator bool() const;

    R operator()(Types ... args);


private:
    R (*func_ptr_)(Types ...) = nullptr;
};

template<typename R, typename ... Types>
function<R(Types ...)>::function() {}

template<typename R, typename ... Types>
function<R(Types ...)>::function(R (*func_ptr)(Types ...))
    :   func_ptr_(func_ptr) {}

template<typename R, typename ... Types>
function<R(Types ...)>::function(const function& other)
    :   func_ptr_(other.func_ptr_) {}

template<typename R, typename ... Types>
function<R(Types ...)>::function(function&& other)
    :   func_ptr_(other.func_ptr_)
{
    other.func_ptr_ = nullptr;
}

template<typename R, typename ... Types>
function<R(Types ...)>::~function() {}

template<typename R, typename ... Types>
function<R(Types ...)>& function<R(Types ...)>::operator=(const function& other)
{
    func_ptr_ = other.func_ptr_;
    return *this;
}

template<typename R, typename ... Types>
function<R(Types ...)>& function<R(Types ...)>::operator=(function&& other)
{
    func_ptr_ = other.func_ptr_;
    other.func_ptr_ = nullptr;
    return *this;
}

template<typename R, typename ... Types>
function<R(Types ...)>& function<R(Types ...)>::operator=(std::nullptr_t)
{
    func_ptr_ = nullptr;
    return *this;
}

template<typename R, typename ... Types>
void function<R(Types ...)>::swap(function& other)
{
    std::swap(func_ptr_, other.func_ptr_);
}

template<typename R, typename ... Types>
function<R(Types ...)>::operator bool() const
{
    return func_ptr_ != nullptr;
}

template<typename R, typename ... Types>
R function<R(Types ...)>::operator()(Types ... args)
{
    if ( !func_ptr_ )
    {
        throw std::runtime_error("function pointer is nullptr");
    }
    return func_ptr_(args...);
}

} // namespace my_std

#endif // MY_STD_FUNCTION_H
