#pragma once
#include <cstddef>
#include <utility>
#include <stdexcept>
using std::size_t;

template<class T>
class shared_ptr {
public:
	explicit shared_ptr(T * ptr = nullptr); //strong

	shared_ptr(shared_ptr const &);//strong
	auto operator =(shared_ptr const &) -> shared_ptr &; //strong
	shared_ptr(shared_ptr &&);//noexcept
	auto operator =(shared_ptr &&) -> shared_ptr&; //noexcept
	~shared_ptr(); //noexcept
	auto swap(shared_ptr &) -> void; //noexcept
	auto reset() -> void;//noexcept
	auto get() const -> T *; //noexcept
	auto use_count() const -> size_t; //noexcept
	auto unique() const -> bool; // noexcept
	auto operator*() const -> T &; //strong
	auto operator->() const -> T *; //strong
	operator bool() const; //noexcept

private:
	T * ptr_;
	size_t * count_;
};

template<class T>
shared_ptr<T>::shared_ptr(T * ptr) : ptr_(ptr) {//strong
	count_ = (ptr_ == nullptr) ? nullptr : new size_t(1);
}

template<class T>
shared_ptr<T>::shared_ptr(const shared_ptr & other) : ptr_(other.ptr_) {//strong
	count_ = other.count_;
	if (use_count() != 0)++*count_;
}

template<class T>
auto shared_ptr<T>::operator=(shared_ptr const &other) -> shared_ptr & //strong
{
	if (this != &other) {
		(shared_ptr<T>(other)).swap(*this);
	}
	return *this;
}

template<class T>
shared_ptr<T>::shared_ptr(shared_ptr && other) : ptr_(nullptr), count_(nullptr) {//noexcept
	swap(other);
}

template<class T>
auto shared_ptr<T>::operator=(shared_ptr && other) -> shared_ptr & {//noexcept
	if (this != &other) {
		swap(other);
	}
	return *this;
}

template<class T>
shared_ptr<T>::~shared_ptr() { //noexcept
	if (count_ == nullptr || --*count_ == 0) {
		delete ptr_;
		delete count_;
	}
}

template<class T>
auto shared_ptr<T>::swap(shared_ptr & other) -> void //noexcept
{
	std::swap(ptr_, other.ptr_);
	std::swap(count_, other.count_);
}

template<class T>
auto shared_ptr<T>::reset() -> void { //noexcept
	if (count_ != nullptr) {
		if (--*count_ == 0) {
			delete ptr_;
			delete count_;
		}
		ptr_ = nullptr;
		count_ = nullptr;
	}
}

template<class T>
auto shared_ptr<T>::get() const -> T * { //noexcept
	return ptr_;
}

template<class T>
auto shared_ptr<T>::use_count() const -> size_t { //noexcept
	return count_ == nullptr ? 0 : *count_;
}

template<class T>
auto shared_ptr<T>::unique() const -> bool //noexcept
{
	return (use_count() == 1);
}

template<class T>
auto shared_ptr<T>::operator*() const -> T & //strong
{
	if (ptr_ == nullptr) throw std::logic_error("pointer is nullptr");
	return *ptr_;
}

template<class T>
auto shared_ptr<T>::operator->() const -> T * //strong
{
	if (ptr_ == nullptr) throw std::logic_error("pointer is nullptr");
	return ptr_;
}

template<class T>
shared_ptr<T>::operator bool() const { //noexcept
	return ptr_ != nullptr;
}
