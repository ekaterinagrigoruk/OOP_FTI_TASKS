#pragma once
#include <utility>

template<class Type, class TDeleter = std::default_delete<Type>>
class SharedPTR final {
    using value_type = std::conditional_t <std::is_array_v<Type>, std::remove_extent_t<Type>, Type>;
    using t_SharedPTR = SharedPTR<Type, TDeleter>;

private:
    struct Inner {
        value_type* ptr;
        size_t* counter;
        TDeleter deleter = TDeleter();
        Inner() = default;
        Inner(value_type* t_ptr, size_t* coun) : ptr(t_ptr), counter(coun) {};
    };
    Inner inner{};

public:
    SharedPTR() = default;
    SharedPTR(value_type* pObj) {
        if (pObj) {
            inner = { pObj, new size_t(1) };
        }
    };
    SharedPTR(t_SharedPTR&& uniquePTR) noexcept : inner(uniquePTR.inner) {
        uniquePTR.inner.ptr = nullptr;
        uniquePTR.inner.counter = nullptr;
    };
    SharedPTR(const t_SharedPTR& other) : inner(other.inner) {
        if (other.inner.ptr) {
            ++*inner.counter;
        }
    };
    ~SharedPTR() {
        release();
    };


    t_SharedPTR& operator=(t_SharedPTR&& sharedPTR) noexcept {
        swap(sharedPTR);
        return *this;
    };
    t_SharedPTR& operator=(value_type* pObject) {
        reset(pObject);
        return *this;
    };
    t_SharedPTR& operator=(const t_SharedPTR& other) {
        release();
        inner = other.inner;
        if (inner.ptr) {
            ++*inner.counter;
        }
        return *this;
    };


    value_type& operator*() const {
        return *(inner.ptr);
    };
    value_type* operator->() const {
        return inner.ptr;
    };
    value_type* get() const {
        return inner.ptr;
    };
    TDeleter& get_deleter() {
        return inner.deleter;
    };
    operator bool() const {
        return inner.ptr != nullptr;
    };

    bool unique() const {
        return *(inner.counter) == 0;
    };

    void release() {
        if (inner.ptr && --*inner.counter == 0) {
            inner.deleter(inner.ptr);
            delete inner.counter;
        }
        inner.ptr = nullptr;
        inner.counter = nullptr;
    };
    void reset(value_type* pObject = nullptr, TDeleter deleter = {}) {
        release();
        inner = { pObject, new size_t(1) };
    };
    void swap(t_SharedPTR& sharedPTR) {
        std::swap(inner, sharedPTR.inner);
    };
};

template<class Type, class... Args>
SharedPTR<Type> make_shared_ptr(Args&&... args) {
    return SharedPTR<Type>(new Type(std::forward<Args>(args)...));
}
