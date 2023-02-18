#ifndef STLITE_VECTOR_H
#define STLITE_VECTOR_H

#include <cmath>
#include <iostream>
#include <stdexcept>

namespace sjtu {

template <class T> class vector {
  public:
    typedef T value_type;
    typedef size_t size_type;
    typedef unsigned int difference_type;
    typedef value_type &reference;
    typedef const value_type &const_reference;
    typedef T *iterator;
    typedef const T *const_iterator;

  public:
    vector() noexcept {
        start = new value_type[1];
        finish = start;
        end_of_storage = start + 1;
    }
    vector(const vector &other) noexcept {
        start = new value_type[other.capacity()];
        finish = start + other.size();
        end_of_storage = start + other.capacity();
        std::copy(other.start, other.finish, start);
    }
    vector(vector &&other) noexcept = default;
    explicit vector(size_type count, const T &value = T()) noexcept {
        int new_size = pow(2, ceil(log2(count)));
        start = new T[new_size];
        finish = start + count;
        for (iterator it = start; it != finish; it++)
            *it = value;
        end_of_storage = start + new_size;
    }

    ~vector() {
        delete[] start;
        start = finish = end_of_storage = nullptr;
    }

    vector &operator=(const vector &other) {
        if (this == &other)
            return *this;
        if (start != nullptr)
            delete[] start;
        start = new value_type[other.capacity()];
        finish = start + other.size();
        end_of_storage = start + other.capacity();
        std::copy(other.start, other.finish, start);
        return *this;
    }

    iterator begin() noexcept { return start; }
    const_iterator cbegin() const noexcept { return start; }
    iterator end() { return finish; }
    const_iterator cend() const noexcept { return finish; }

    size_t size() const noexcept { return cend() - cbegin(); }
    size_t capacity() const noexcept { return end_of_storage - cbegin(); }
    bool empty() const noexcept { return cbegin() == cend(); }

    reference at(const size_type &pos) {
        if (pos >= size())
            throw std::out_of_range("");
        return *(begin() + pos);
    }
    const_reference at(const size_type &pos) const { return at(pos); };

    reference operator[](const size_type &pos) { return *(begin() + pos); }
    const_reference operator[](const size_type &pos) const { return *(cbegin() + pos); };

    const_reference front() const { return *cbegin(); };
    const_reference back() const { return *std::prev(cend()); }

    void reserve(const size_type &new_cap) {
        if (new_cap <= capacity())
            return;
        int new_size = pow(2, ceil(log2(new_cap)));
        iterator new_start = new value_type[new_size];
        iterator new_finish = new_start + size();
        iterator new_end_of_storage = new_start + new_size;
        try {
            std::copy(start, finish, new_start);
        } catch (...) {
            delete[] new_start;
            throw;
        }
        delete[] start;
        start = new_start;
        finish = new_finish;
        end_of_storage = new_end_of_storage;
    }

    void push_back(const value_type &value) {
        if (finish == end_of_storage)
            reserve(capacity() << 1);
        *finish = value;
        finish++;
    }
    void pop_back() { finish--; }
    void clear() { finish = start; }

    iterator insert(iterator pos, const value_type &value) {
        if (pos < start || pos > finish)
            throw std::out_of_range("");
        if (finish == end_of_storage)
            reserve(capacity() << 1);
        std::copy_backward(pos, finish, pos + 1);
        *pos = value;
        return pos;
    }
    iterator insert(const size_t &pos, const T &data) { return insert(begin() + pos, data); }

    iterator erase(iterator pos) {
        if (pos < start || pos >= finish)
            throw std::out_of_range("");
        if (pos + 1 != finish)
            std::copy(pos + 1, finish, pos);
        --finish;
        return pos;
    }
    iterator erase(const size_t &pos) { return erase(begin() + pos); }

  private:
    iterator start;
    iterator finish;
    iterator end_of_storage;
};

template class vector<int>;

} // namespace sjtu

#endif