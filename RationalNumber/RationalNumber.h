#pragma once

// Your goal is to create a rational number class that would
// support each of the operations given in main.cpp.
//
// In this file you must declare only the interface of your class
// and implement the given functions separately from the class (at the bottom of
// this file inside the namespace).
// Notice that the RationalNumber is a class template, where the
// template parameter is an integer type for numerator and denominator.
//
// Note - Rename the namespace "yourname" to whatever you want, feel creative
// ( but not too much :) ).
//
// After you wrote RationalNumber class and the tests in the main function work
// - write at the bottom of the file the downsides of such rational numbers,
// what would you change/remove/add? Would you use such rational numbers instead
// of double/float numbers? There is no right/wrong answer, this question is
// more of a philosofical kind than technical.

#include <iostream>
#include <numeric>

namespace yourname
{
	template <typename T>
	class RationalNumber
	{
	private:
		T _num;
		T _denom;

		void reduce();

	public:
		RationalNumber(T num = 0, T denom = 1);

		RationalNumber& operator+=(const RationalNumber& other);
		RationalNumber& operator-=(const RationalNumber& other);
		RationalNumber& operator*=(const RationalNumber& other);
		RationalNumber& operator/=(const RationalNumber& other);

		RationalNumber& operator++();
		RationalNumber operator++(int);
		RationalNumber& operator--();
		RationalNumber operator--(int);

		RationalNumber operator+() const;
		RationalNumber operator-() const;

		operator int() const;
		operator float() const;
		operator double() const;
		operator bool() const;


		template <typename U>
		friend std::ostream& operator<<(std::ostream& os, const RationalNumber<U>& source);

		template <typename U>
		friend bool operator<(const RationalNumber<U>& lhs, const RationalNumber<U>& rhs);

		template <typename U>
		friend bool operator==(const RationalNumber<U>& lhs, const RationalNumber<U>& rhs);

	};


	template <typename T>
	RationalNumber<T>::RationalNumber(T num, T denom) : _num(num), _denom(denom)
	{
		if (_denom < 0)
		{
			_num *= -1;
			_denom *= -1;
		}

		reduce();
	}


#pragma region += -= *= /=

	template <typename T>
	RationalNumber<T>& RationalNumber<T>::operator+=(const RationalNumber& other)
	{
		this->_num = this->_num * other._denom + other._num * this->_denom;
		this->_denom *= other._denom;

		reduce();

		return *this;
	}

	template <typename T>
	RationalNumber<T>& RationalNumber<T>::operator-=(const RationalNumber& other)
	{
		this->_num = this->_num * other._denom - other._num * this->_denom;
		this->_denom *= other._denom;

		reduce();

		return *this;
	}

	template <typename T>
	RationalNumber<T>& RationalNumber<T>::operator*=(const RationalNumber& other)
	{
		this->_num *= other._num;
		this->_denom *= other._denom;

		reduce();

		return *this;
	}

	template <typename T>
	RationalNumber<T>& RationalNumber<T>::operator/=(const RationalNumber& other)
	{
		this->_num *= other._denom;
		this->_denom *= other._num;

		reduce();

		return *this;
	}

#pragma endregion

#pragma region Increment Decrement

	template <typename T>
	RationalNumber<T>& RationalNumber<T>::operator++()
	{
		_num += _denom;
		return *this;
	}

	template <typename T>
	RationalNumber<T> RationalNumber<T>::operator++(int)
	{
		RationalNumber result{ *this };
		++(*this);
		return result;
	}

	template <typename T>
	RationalNumber<T>& RationalNumber<T>::operator--()
	{
		_num -= _denom;
		return *this;
	}

	template <typename T>
	RationalNumber<T> RationalNumber<T>::operator--(int)
	{
		RationalNumber result{ *this };
		--(*this);
		return result;
	}

#pragma endregion

#pragma region + - * /

	template <typename T>
	RationalNumber<T> operator+(const RationalNumber<T>& lhs, const RationalNumber<T>& rhs)
	{
		RationalNumber res(lhs);
		res += rhs;
		return res;
	}

	template <typename T>
	RationalNumber<T> operator+(const T& lhs, const RationalNumber<T>& rhs)
	{
		RationalNumber res(lhs);
		res += rhs;
		return res;
	}

	template <typename T>
	RationalNumber<T> operator-(const RationalNumber<T>& lhs, const RationalNumber<T>& rhs)
	{
		RationalNumber res(lhs);
		res -= rhs;
		return res;
	}

	template <typename T>
	RationalNumber<T> operator-(const T& lhs, const RationalNumber<T>& rhs)
	{
		RationalNumber res(lhs);
		res -= rhs;
		return res;
	}

	template <typename T>
	RationalNumber<T> operator*(const RationalNumber<T>& lhs, const RationalNumber<T>& rhs)
	{
		RationalNumber res(lhs);
		res *= rhs;
		return res;
	}

	template <typename T>
	RationalNumber<T> operator*(const T& lhs, const RationalNumber<T>& rhs)
	{
		RationalNumber res(lhs);
		res *= rhs;
		return res;
	}

	template <typename T>
	RationalNumber<T> operator/(const RationalNumber<T>& lhs, const RationalNumber<T>& rhs)
	{
		RationalNumber res(lhs);
		res /= rhs;
		return res;
	}

	template <typename T>
	RationalNumber<T> operator/(const T& lhs, const RationalNumber<T>& rhs)
	{
		RationalNumber res(lhs);
		res /= rhs;
		return res;
	}


	template<typename T>
	inline RationalNumber<T> RationalNumber<T>::operator+() const
	{
		return (*this);
	}

	template<typename T>
	inline RationalNumber<T> RationalNumber<T>::operator-() const
	{
		RationalNumber res(*this);
		res._num *= -1;
		return res;
	}


#pragma endregion

#pragma region Cast Operators

	template<typename T>
	RationalNumber<T>::operator int() const
	{
		return _num / _denom;
	}

	template<typename T>
	RationalNumber<T>::operator float() const
	{
		return float(_num) / _denom;
	}

	template<typename T>
	RationalNumber<T>::operator double() const
	{
		return double(_num) / _denom;
	}

	template<typename T>
	RationalNumber<T>::operator bool() const
	{
		return _num != 0;
	}

#pragma endregion

#pragma region Bool Operators

	template<typename U>
	bool operator==(const RationalNumber<U>& lhs, const RationalNumber<U>& rhs)
	{
		return lhs._num == rhs._num && lhs._denom == rhs._denom;
	}

	template<typename U>
	bool operator!=(const RationalNumber<U>& lhs, const RationalNumber<U>& rhs)
	{
		return !(lhs == rhs);
	}

	template<typename U>
	bool operator<(const RationalNumber<U>& lhs, const RationalNumber<U>& rhs)
	{
		return (lhs._num * rhs._denom) < (rhs._num * lhs._denom);
	}

	template<typename U>
	bool operator<=(const RationalNumber<U>& lhs, const RationalNumber<U>& rhs)
	{
		return !(rhs < lhs);
	}

	template<typename U>
	bool operator>(const RationalNumber<U>& lhs, const RationalNumber<U>& rhs)
	{
		return rhs < lhs;
	}

	template<typename U>
	bool operator>=(const RationalNumber<U>& lhs, const RationalNumber<U>& rhs)
	{
		return !(lhs < rhs);
	}

#pragma endregion



	template<typename T>
	std::ostream& operator<<(std::ostream& os, const RationalNumber<T>& source)
	{
		os << source._num << '/' << source._denom;

		return os;
	}

	template<typename T>
	void RationalNumber<T>::reduce()
	{
		T temp = std::gcd(_num, _denom);
		_num /= temp;
		_denom /= temp;
	}


} // namespace yourname
