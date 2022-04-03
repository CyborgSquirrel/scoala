#ifndef vec_hpp_INCLUDED
#define vec_hpp_INCLUDED

#include <memory>
#include <string>
#include <array>
#include <initializer_list>

#include <iostream>

class VecException {
private:
	std::string msg;
public:
	VecException(const std::string &msg);
};

template <typename T>
class Vec;

template <typename T>
class VecIterator {
public:
	using difference_type = long;
	using value_type = T;
	using pointer = T*;
	using reference = T&;
	using iterator_category = std::random_access_iterator_tag;
private:
	const Vec<value_type> *vec;
	size_t index;
	
	VecIterator(const Vec<value_type> *vec, size_t index)
		: vec(vec), index(index) { }
public:
	friend Vec<T>;
	
	VecIterator() = delete;
	
	VecIterator(const VecIterator<value_type> &it)
		: vec(it.vec), index(it.index) { }
	
	VecIterator<value_type> &operator=(VecIterator<value_type> it) {
		this->vec = it.vec;
		this->index = it.index;
		return *this;
	}
	
	friend const VecIterator<value_type> &operator+=(const VecIterator<value_type> &it, difference_type offset) {
		it.index += offset;
		return it;
	}
	friend const VecIterator<value_type> &operator-=(const VecIterator<value_type> &it, difference_type offset) {
		it.index -= offset;
		return it;
	}
	
	VecIterator<value_type> &operator++() {
		this->index++;
		return *this;
	}
	VecIterator<value_type> operator++(int) {
		VecIterator<value_type> it = *this;
		++(*this);
		return it;
	}
	
	VecIterator<value_type> &operator--() {
		this->index--;
		return *this;
	}
	VecIterator<value_type> operator--(int) {
		VecIterator<value_type> it = *this;
		--(*this);
		return it;
	}
	
	reference operator[](size_t index) {
		if (this->index >= this->vec->len) {
			throw VecException("indice invalid");
		}
		return this->vec->buf[index];
	}
	
	friend VecIterator<value_type> operator+(VecIterator<value_type> it, difference_type offset) {
		it.index += offset;
		return it;
	}
	friend VecIterator<value_type> operator+(difference_type offset, VecIterator<value_type> it) {
		it.index += offset;
		return it;
	}
	
	friend VecIterator<value_type> operator-(VecIterator<value_type> it, difference_type offset) {
		it.index -= offset;
		return it;
	}
	
	friend difference_type operator-(VecIterator<value_type> &lhs, VecIterator<value_type> &rhs) {
		return (difference_type) lhs.index - (difference_type) rhs.index;
	}
	
	friend bool operator!=(const VecIterator<value_type> &lhs, const VecIterator<value_type> &rhs) {
		return lhs.index != rhs.index;
	}
	friend bool operator==(const VecIterator<value_type> &lhs, const VecIterator<value_type> &rhs) {
		return lhs.index == rhs.index;
	}
	friend bool operator<(const VecIterator<value_type> &lhs, const VecIterator<value_type> &rhs) {
		return lhs.index < rhs.index;
	}
	
	friend reference operator*(const VecIterator<value_type> &it) {
		if (it.index >= it.vec->len) {
			throw VecException("indice invalid");
		}
		return it.vec->buf[it.index];
	}
	
	friend reference operator*(VecIterator<value_type> &it) {
		if (it.index >= it.vec->len) {
			throw VecException("indice invalid");
		}
		return it.vec->buf[it.index];
	}
};

template <typename T>
class Vec {
private:
	std::allocator<T> a;
	size_t len, dim;
	T *buf;
public:
	using iterator_type = VecIterator<T>;
	
	friend VecIterator<T>;
	
	// Constructor pentru vector generic.
	Vec() : a(), len(0), dim(10), buf(this->a.allocate(this->dim)) { }
	
	~Vec() {
		delete this->buf;
	}
	
	// Constructor de copiere pentru vector generic.
	// in: vec -- vectorul care va fi copiat
	Vec(const Vec<T> &vec) : a(), len(vec.len), dim(vec.dim), buf(this->a.allocate(this->dim)) {
		for (int i = 0; i < this->len; ++i) {
			new (this->buf + i) T(vec.buf[i]);
		}
	}
	
	Vec(std::initializer_list<T> list) : dim(10) {
		while (this->dim < list.size()) { this->dim *= 2; }
		this->len = list.size();
		this->buf = this->a.allocate(this->dim);
		size_t i = 0;
		for (const auto &element : list) {
			new (this->buf + i) T(element);
			i++;
		}
	}
	
	// Returneaza lungimea vectorului.
	size_t size() const {
		return this->len;
	}
	
	// Adauga elementul furnizat la sfarsitul vectorului.
	// in: element -- elementul care va fi adaugat la sfarsit
	void push_back(const T &element) {
		if (this->len >= this->dim) {
			auto old_dim = this->dim;
			this->dim *= 2;
			auto old_buf = this->buf;
			this->buf = this->a.allocate(this->dim);
			for (int i = 0; i < this->len; ++i) {
				this->buf[i] = old_buf[i];
			}
			this->a.deallocate(old_buf, old_dim);
		}
		new (this->buf + this->len) T(element);
		this->len++;
	}
	
	// Sterge elementul referit de iteratorul furnizat.
	// in: it -- iteratorul la locatia caruia va fi sters elementul
	void erase(const VecIterator<T> &it) {
		size_t index = it.index;
		if (index >= this->len) {
			throw VecException("indice invalid");
		}
		for (int i = index+1; i < this->len; ++i) {
			this->buf[i-1] = this->buf[i];
		}
	}
	
	// Acces fara modificare.
	// in: index -- indicele
	const T &operator[](size_t index) const {
		if (index >= this->len) {
			throw VecException("indice invalid");
		}
		return this->buf[index];
	}
	
	// Acces cu modificare.
	// in: index -- indicele
	T &operator[](size_t index) {
		if (index >= this->len) {
			throw VecException("indice invalid");
		}
		return this->buf[index];
	}
	
	// Returneaza un iterator care trimite la inceputul vectorului.
	VecIterator<T> begin() const {
		return VecIterator<T>(this, 0);
	}
	
	// Returneaza un iterator care trimite la sfarsitul vectorului.
	VecIterator<T> end() const {
		return VecIterator<T>(this, this->len);
	}
	
	friend bool operator==(const Vec<T> &lhs, const Vec<T> &rhs) {
		if (lhs.len != rhs.len) return false;
		for (int i = 0; i < lhs.len; ++i) {
			if (!(lhs.buf[i] == rhs.buf[i])) return false;
		}
		return true;
	}
};

void test_vec();

#endif // vec_hpp_INCLUDED
