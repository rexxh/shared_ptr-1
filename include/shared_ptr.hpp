#include <iostream>

template <class T>
class shared_ptr {
private:
	T * ptr_;
	size_t *counter_;
public:
	shared_ptr();
	shared_ptr(T* obj); 
	shared_ptr(const shared_ptr &);
	shared_ptr(shared_ptr &&);
	auto operator = (const shared_ptr&)->shared_ptr&;
	auto operator = (shared_ptr&&)->shared_ptr&;
	auto operator * () const->T&;
	auto operator -> () const->T*;
	auto get() const->T*;	
	auto count()-> const size_t;
	auto swap(shared_ptr&) -> void;
	~shared_ptr();
};

template <class T>
shared_ptr<T>::shared_ptr() : ptr_(nullptr), counter_(nullptr) {};

template <class T>
shared_ptr<T>::shared_ptr(T* other) : ptr_(other), counter_(new size_t(1)) {};

template <class T>
shared_ptr<T>::shared_ptr(const shared_ptr & other) : ptr_(other.ptr_), counter_(other.counter_) {
	if (counter_ != nullptr)
	{
		*counter_+=1;
	}
} 
template <class T>
shared_ptr<T>::shared_ptr(shared_ptr && other) : ptr_(other.ptr_), counter_(other.counter_) {
	other.ptr_ = nullptr;
	other.counter_ = nullptr;
}

template <class T>
auto shared_ptr<T>::operator = (const shared_ptr& other) ->shared_ptr& {
	if (this != &other)
	{
		(shared_ptr<T>(other)).swap(*this);
	}
	return *this;
}

template <class T>
auto shared_ptr<T>::operator = (shared_ptr&& other) ->shared_ptr& {
	if (this != &other)
	{
		this->swap(other);
	}
	return *this;
}

template <class T>
auto shared_ptr<T>::operator * () const ->T& {
	if (ptr_ != nullptr) return ptr_;
	else throw ("nullptr");
}

template <class T>
auto shared_ptr<T>::operator -> () const  ->T* {
	if (ptr_ != nullptr) return ptr_;
	else throw ("nullptr");
}

template <typename T>
auto shared_ptr<T>::get() const -> T*
{
	return ptr_;
}

template <class T>
auto shared_ptr<T>::count()->const size_t {
	if (counter_ != nullptr) return *counter_;
	else return 0;
}

template <class T>
auto shared_ptr<T>::swap(shared_ptr & other) -> void{
	std::swap(ptr_, other.ptr_);
	std::swap(counter_, other.counter_);
}

template <class T>
shared_ptr<T>::~shared_ptr() {
	if (counter_ != nullptr && --(*counter_) == 0)
	{
			delete ptr_;
			delete counter_;
	}
}

template <typename T, class ...Args>
auto make_shared( Args && ...args ) -> shared_ptr<T>
{
    return shared_ptr<T>( new T( std::forward<Args>(args)... ) );
}
