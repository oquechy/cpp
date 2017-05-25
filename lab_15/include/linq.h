#ifndef LINQ_H_
#define LINQ_H_

#include <utility>
#include <vector>
#include <iostream>

template<typename T, typename Iter>
class range_enumerator;
template<typename T>
class drop_enumerator;
template<typename T>
class take_enumerator;
template<typename T, typename U, typename F>
class select_enumerator;
template<typename T, typename F>
class where_enumerator;
template<typename T, typename F>
class until_enumerator;

template<typename T>
class enumerator {
public:
    virtual const T& operator*() const = 0; // Получает текущий элемент.
    virtual const enumerator<T>& operator++() = 0;  // Переход к следующему элементу
    virtual operator bool() const = 0;  // Возвращает true, если есть текущий элемент

    auto drop(int count) {
        return drop_enumerator<T>(*this, count);
    }

    auto take(int count) {
        return take_enumerator<T>(*this, count);
    }

    template<typename U = T, typename F>
    auto select(F func) {
        return select_enumerator<U, T, F>(*this, func);
    }

    template<typename F>
    auto until(F func) {
        return until_enumerator<T, F>(*this, func);
    }

    auto until_eq(T x) {
        auto eq = [x](T t) -> bool { return t == x;};
        return until_enumerator<T, decltype(eq)>(*this, eq);
    }

    template<typename F>
    auto where(F func) {
        return where_enumerator<T, F>(*this, func);
    }

    auto where_neq(T x) {
        auto neq = [x](T t) { return t != x;};
        return where_enumerator<T, decltype(neq)>(*this, neq);
    }

    std::vector<T> to_vector() {
        std::vector<T> st;
        for (; *this; ++*this)
            st.push_back(**this);
        return st;
    }

    template<typename Iter>
    void copy_to(Iter it) {
        for (; *this; ++*this, ++it)
            *it = **this;
    }
};

template<typename T, typename Iter>
class range_enumerator : public enumerator<T> {
public:
    range_enumerator(Iter begin, Iter end) : begin_(begin), end_(end) {}

    const T& operator*() const override { // Получает текущий элемент.
        return *begin_;
    }

    const enumerator<T>& operator++() override {  // Переход к следующему элементу
        ++begin_;
        return *this;
    }

    operator bool() const override {  // Возвращает true, если есть текущий элемент
        return begin_ != end_;
    }

private:
    Iter begin_, end_;
};

template<typename T>
auto from(T begin, T end) {
    return range_enumerator<typename std::iterator_traits<T>::value_type, T>(begin, end);
}

template<typename T>
class drop_enumerator : public enumerator<T> {
public:
    drop_enumerator(enumerator<T> &parent, int count) : parent_(parent) {
        for (; parent_ && count; --count)
            ++parent_;
    }

    const T& operator*() const override { // Получает текущий элемент.
        return *parent_;
    }

    const enumerator<T>& operator++() override {  // Переход к следующему элементу
        ++parent_;
        return *this;
    }

    operator bool() const override {  // Возвращает true, если есть текущий элемент
        return parent_;
    }

private:
    enumerator<T> &parent_;
};

template<typename T>
class take_enumerator : public enumerator<T> {
public:
    take_enumerator(enumerator<T> &parent, int count)
            : parent_(parent), count_(count)
    {}

    const T& operator*() const override { // Получает текущий элемент.
        return *parent_;
    }

    const enumerator<T>& operator++() override {// Переход к следующему элементу
        --count_;
        ++parent_;
        return *this;
    }

    operator bool() const override {  // Возвращает true, если есть текущий элемент
        return parent_ && (count_ > 0);
    }

private:
    enumerator<T> &parent_;
    int count_;
};

template<typename T, typename U, typename F>
class select_enumerator : public enumerator<T> {
public:
    select_enumerator(enumerator<U> &parent, F func)
            : parent_(parent), func_(func)
    {
        if (parent_)
            cur_ = func_(*parent_);
    }

    const T& operator*() const override { // Получает текущий элемент.
        return cur_;
    }

    const enumerator<T>& operator++() override {  // Переход к следующему элементу
        if (++parent_)
            cur_ = func_(*parent_);
        return *this;
    }

    operator bool() const override {  // Возвращает true, если есть текущий элемент
        return parent_;
    }

private:
    enumerator<U> &parent_;
    T cur_;
    F func_;
};


template<typename T, typename F>
class where_enumerator : public enumerator<T> {
public:
    where_enumerator(enumerator<T> &parent, F predicate)
            : parent_(parent), predicate_(predicate)
    {
        for (; parent_ && !predicate_(*parent_); ++parent_);
    }

    const T& operator*() const override { // Получает текущий элемент.
        return *parent_;
    }

    const enumerator<T>& operator++() override {  // Переход к следующему элементу
        for (++parent_; parent_ && !predicate_(*parent_); ++parent_);
        return *this;
    }

    operator bool() const override {  // Возвращает true, если есть текущий элемент
        return parent_;
    }

private:
    enumerator<T> &parent_;
    F predicate_;
};


template<typename T, typename F>
class until_enumerator : public enumerator<T> {
public:
    until_enumerator(enumerator<T> &parent, F predicate)
            : parent_(parent), predicate_(predicate)
    {
        if (parent_)
            stop_ = predicate_(*parent_);
    }

    const T& operator*() const override { // Получает текущий элемент.
        return *parent_;
    }

    const enumerator<T>& operator++() override {  // Переход к следующему элементу
        const T &cur = *++parent_;
        stop_ = predicate_(cur);
        return *this;
    }

    operator bool() const override {  // Возвращает true, если есть текущий элемент
        return parent_ && !stop_;
    }

private:
    enumerator<T> &parent_;
    F predicate_;
    bool stop_;
};

#endif