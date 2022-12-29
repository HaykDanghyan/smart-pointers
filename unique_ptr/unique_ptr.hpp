#include "unique_ptr.h"

template <typename T, typename Deleter>
unique_ptr<T, Deleter>::unique_ptr() : m_data{nullptr} {}

template <typename T, typename Deleter>
unique_ptr<T, Deleter>::unique_ptr(std::nullptr_t n) : m_data{n} {}

template <typename T, typename Deleter>
unique_ptr<T, Deleter>::unique_ptr(T* data) : m_data{data} {
    data = nullptr;
}

template <typename T, typename Deleter>
unique_ptr<T, Deleter>::unique_ptr(unique_ptr<T, Deleter>&& rhs) : m_data{nullptr} {
    m_data = rhs.m_data;
    rhs.m_data = nullptr;
}

template <typename T, typename Deleter>
unique_ptr<T, Deleter>::~unique_ptr() {
    Deleter(m_data);
}

template <typename T, typename Deleter>
unique_ptr<T, Deleter>& unique_ptr<T, Deleter>::operator=(unique_ptr<T, Deleter>&& rhs) {
    if (this != &rhs) {
        m_data = rhs.m_data;
        rhs.m_data = nullptr;
    }
    return *this;
}

template <typename T, typename Deleter>
typename unique_ptr<T, Deleter>::pointer unique_ptr<T, Deleter>::release() noexcept {
    T* tmp = m_data;
    m_data = nullptr;
    return tmp;
}

template <typename T, typename Deleter>
void unique_ptr<T, Deleter>::reset(pointer ptr) noexcept {
    m_data = ptr;
}

template <typename T, typename Deleter>
void unique_ptr<T, Deleter>::swap(unique_ptr<T, Deleter>& rhs) {
    using std::swap;
    swap(m_data, rhs.m_data);
}

template <typename T, typename Deleter>
typename unique_ptr<T, Deleter>::pointer unique_ptr<T, Deleter>::get() const noexcept {
    return m_data;
}

template <typename T, typename Deleter>
unique_ptr<T, Deleter>::operator bool() const noexcept {
    return get() != nullptr;
}

template <typename T, typename Deleter>
T& unique_ptr<T, Deleter>::operator*() const noexcept {
    return *m_data;
}

template <typename T, typename Deleter>
T* unique_ptr<T, Deleter>::operator->() const noexcept {
    return m_data;
}
