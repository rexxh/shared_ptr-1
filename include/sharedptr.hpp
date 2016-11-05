#pragma once
#include <cstddef>
#include <utility>
using std::size_t;

template<class T>
class shared_ptr {
public:
	explicit shared_ptr(T * ptr = nullptr);
	
	shared_ptr(shared_ptr const &);
	auto operator =(shared_ptr const &)->shared_ptr &;
	shared_ptr(shared_ptr &&);
	auto operator =(shared_ptr &&)->shared_ptr&;
	~shared_ptr();
	auto swap(shared_ptr &)->void;
	auto reset() -> void;
	auto get()->T *;
	auto use_count()->size_t;
	auto unique() -> bool;
	auto operator*()->T &;
	auto operator->()->T *;
	operator bool();

private:
	T * ptr_;
	size_t * count_;
};

template<class T>
shared_ptr<T>::shared_ptr(T * ptr) : ptr_(ptr){
	count_ = (ptr_ == nullptr) ? nullptr : new size_t(1);
}

template<class T>
shared_ptr<T>::shared_ptr(const shared_ptr & other) : ptr_(other.ptr_){
	count_ = other.count_;
	++*count_;
}

template<class T>
auto shared_ptr<T>::operator=(shared_ptr const &other) -> shared_ptr &
{
	if (this != &other) {
		(shared_ptr<T>(other)).swap(this);
	}
	return *this;
}

template<class T>
shared_ptr<T>::shared_ptr(shared_ptr && other) : ptr_(nullptr), count_(nullptr) {
	swap(other);
}

template<class T>
auto shared_ptr<T>::operator=(shared_ptr && other) -> shared_ptr &{
	if (this != &other) {
		swap(other);
	}
	return *this;
}

template<class T>
shared_ptr<T>::~shared_ptr() {
	if (count_ == nullptr || --*count_ == 0) {
		delete ptr_;
		delete count_;
	}
}

template<class T>
auto shared_ptr<T>::swap(shared_ptr & other) -> void
{
	std::swap(ptr_, other.ptr_);
	std::swap(count_, other.count_);
}

template<class T>
auto shared_ptr<T>::reset() -> void{
	if (count_ != nullptr) {
		ptr_ = nullptr;
		count_ = nullptr;
	}
}

template<class T>
auto shared_ptr<T>::get() -> T *{
	return ptr_;
}

template<class T>
auto shared_ptr<T>::use_count() -> size_t{
	return count_ == nullptr? 0 : *count_;
}

template<class T>
auto shared_ptr<T>::unique() -> bool
{
	return (*count_ == 1);
}

template<class T>
auto shared_ptr<T>::operator*() -> T &
{
	return *ptr_;
}

template<class T>
auto shared_ptr<T>::operator->() -> T *
{
	return ptr_;
}

template<class T>
shared_ptr<T>::operator bool(){
	return ptr_ == nullptr;
}
