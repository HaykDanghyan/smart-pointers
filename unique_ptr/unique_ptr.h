#ifndef UNIQUE_PTR_H
#define UNIQUE_PTR_H

#include <iostream>
#include <memory>

template <typename T, typename Deleter = std::default_delete<T>>
class unique_ptr {
    using pointer = T*;
public:
    unique_ptr();
    unique_ptr(std::nullptr_t);
    unique_ptr(T*);
    unique_ptr(unique_ptr<T, Deleter>&&);
    ~unique_ptr();

    unique_ptr<T, Deleter>& operator=(unique_ptr<T, Deleter>&&);

public:
    pointer release() noexcept;
    void swap(unique_ptr<T, Deleter>&);
    void reset(pointer ptr = pointer()) noexcept;

public:
    pointer get() const noexcept;
    Deleter& get_deleter() noexcept;
    const Deleter& get_deleter() const noexcept;
    explicit operator bool() const noexcept;

public:
    T& operator*() const noexcept;
    pointer operator->() const noexcept;
private:
    pointer m_data;
};

#include "unique_ptr.hpp"
#endif // UNIQUE_PTR_H