#ifndef MY_STD_VECTOR_H
#define MY_STD_VECTOR_H

#include <cstddef>
#include <initializer_list>
#include <iterator>

namespace my_std
{

template<typename T>
class vector
{
private:
    class iterator;
public:
// constructors
    vector();
    explicit vector(size_t count);
    explicit vector(size_t count, const T &value);

    vector(const vector<T> &other);
    vector(vector<T> &&other);

    vector(std::initializer_list<T> init);

    template<typename InputIterator>
    vector(InputIterator first, InputIterator last);
// destructor
    ~vector();
// assignment
    vector &operator=(const vector &other);
    vector &operator=(vector &&other);
    vector &operator=(std::initializer_list<T> init);
// assignment
    template<typename InputIterator>
    void assign(InputIterator first, InputIterator last);

    void assign(size_t count, const T &value);
    void assign(std::initializer_list<T> init);
// element access
    T &at(size_t pos);
    const T &at(size_t pos) const;
    T &operator[](size_t pos);
    const T &operator[](size_t pos) const;
    T &front();
    const T &front() const;
    T &back();
    const T &back() const;
    T *data();
    const T *data() const;
// capacity
    size_t size() const;
    size_t capacity() const;
    size_t max_size() const;
    bool empty() const;
    void reserve(size_t new_cap);
    void shrink_to_fit();
// modifiers
    void clear();
    iterator insert(const iterator pos, const T &value);
    iterator insert(const iterator pos, T &&value);
    iterator insert(const iterator pos, size_t count, const T &value);
    iterator insert(const iterator pos, std::initializer_list<T> init);
    template<typename InputIterator>
    iterator insert(const iterator pos, InputIterator first, InputIterator last);
    template<typename... Args>
    iterator emplace(const iterator &pos, Args&&... args);
    iterator erase(iterator pos);
    iterator erase(iterator first, iterator last);
    void push_back(const T &value);
    void push_back(T &&value);
    template<typename... Args>
    void emplace_back(Args&&... args);
    template<typename... Args>
    iterator emplace_back(Args&&... args);
    void pop_back();
    void resize(size_t count);
    void resize(size_t count, const T &value);
    void swap(vector &other);
// iterators
private:
    class iterator
    {
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = T;
        using difference_type = ptrdiff_t;
        using pointer = T *;
        using reference = T &;

        iterator() = default;
        iterator(const iterator &other);
        iterator &operator=(const iterator &other);
        iterator &operator++();
        iterator operator++(int);
        iterator &operator--();
        iterator operator--(int);
        iterator operator+=(difference_type n) const;
        iterator operator-=(difference_type n) const;
        difference_type operator-(const iterator &other) const;
        reference operator[](difference_type n) const;
        reference operator*() const;
        std::strong_ordering operator<=>(const iterator &other) const;
        bool operator==(const iterator &other) const;
    private:
        T *ptr_;
    };
public:
    iterator begin() const;
    iterator end() const;
    iterator cbegin() const;
    iterator cend() const;
    iterator rbegin() const;
    iterator rend() const;
    iterator crbegin() const;
    iterator crend() const;
};

} // namespace my_std

#endif // MY_STD_VECTOR_H
