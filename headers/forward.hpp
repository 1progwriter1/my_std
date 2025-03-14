#ifndef MY_STD_FORWARD_H
#define MY_STD_FORWARD_H

namespace my_std
{

template<typename T>
struct remove_reference
{
    typedef T type;
};

template<typename T>
T &&forward(typename remove_reference<T>::type &t)
{
    return static_cast<T &&>(t);
}

template<typename T>
T &&move(T &t)
{
    return static_cast<T &&>(t);
}

} // namespace my_std

#endif // MY_STD_FORWARD_H
