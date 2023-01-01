#ifndef SHARED_PTR_H
#define SHARED_PTR_H

#include <iostream>
#include <memory>

template <typename T>
class shared_ptr {
    using pointer = T*;
    using reference = T&;
public:
    shared_ptr(pointer ptr = nullptr);
    shared_ptr(const shared_ptr<T>&);
    ~shared_ptr();

public:
    void reset();
    void swap(shared_ptr<T>&);
    size_t use_count() const;

    pointer get() const noexcept;
    reference operator*() const noexcept;
    pointer operator->() const noexcept;

private:
    class CountBlock {
    public:
        CountBlock() = default;
        ~CountBlock() = default;

    public:
        void reset() {
            m_counter = 0;
        }
        size_t get() const {
            return m_counter;
        }
        void set(size_t count) {
            m_counter = count;
        }
        void operator++() { ++m_counter }
        void operator--() { --m_counter }
        void operator++(int) { ++m_counter } 
        void operator--(int) { --m_counter }

    private:
        CountBlock(const CountBlock&) = delete;
        CountBlock(CountBlock&&) = delete;

    private:
        size_t m_counter;
    };

private:
    pointer m_data;
    CountBlock* m_refcount;
};
#include "shared_ptr.hpp"
#endif // SHARED_PTR_H