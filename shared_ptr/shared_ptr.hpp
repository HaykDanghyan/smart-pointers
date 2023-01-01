#include "shared_ptr.h"

template <typename T>
shared_ptr<T>::shared_ptr(pointer ptr) : m_data{ptr}, m_refcount{new CountBlock()} {
    if (ptr != nullptr) {
        ++(*m_refcount);
    }
}

template <typename T>
shared_ptr<T>::shared_ptr(const shared_ptr<T>& rhs) : m_data{rhs.m_data}, m_refcount{rhs.m_refcount} {
    ++(*m_refcount);
}

template <typename T>
shared_ptr<T>::~shared_ptr() {
    --(*m_refcount);
    if (m_refcount->get() == 0) {
        delete m_refcount;
        delete m_data;
        m_data = nullptr;
        m_refcount = 0;
    }
}

template <typename T>
void shared_ptr<T>::reset() {
    if (m_refcount->get() == 1) {
        delete m_data;
    }
    m_data = nullptr;
    m_refcount->set(0);
}

template <typename T>
void shared_ptr<T>::swap(shared_ptr<T>& rhs) {
    using std::swap;
    swap(m_data, rhs.m_data);
    swap(m_refcount, rhs.m_refcount);
}

template <typename T>
size_t shared_ptr<T>::use_count() const {
    return m_refcount->get();
}

template <typename T>
typename shared_ptr<T>::pointer shared_ptr<T>::get() const noexcept {
    return m_data;
}

template <typename T>
typename shared_ptr<T>::pointer shared_ptr<T>::operator->() const noexcept {
    return m_data;
}

template <typename T>
typename shared_ptr<T>::reference shared_ptr<T>::operator*() const noexcept {
    return *m_data;
}
