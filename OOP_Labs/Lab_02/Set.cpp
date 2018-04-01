#include "Set.h"

namespace Lab_02
{

	template <typename T>
	Set<T>::Set(T *elements, int count)
	{
		int actualLength = count;
		T temp = new T[count];
		int tempIndex = 0;
		for (int i = 0; i < count; i++)
		{
			bool exists = false;
			for (int j = 0; j < tempIndex; j++)
			if (temp[j] == elements[i])
			{
				exists = true;
				break;
			}
			if (!exists)
			{
				temp[tempIndex] = elements[i];
				tempIndex++;
			}
			else
				actualLength--;
		}

		data_ = new T[actualLength];
		for (int i = 0; i < actualLength; i++)
		{
			data_[i] = temp[i];
		}
		length_ = actualLength;

		delete[] temp;
	}

	template <typename T>
	Set<T>::Set(const Set& obj)
	{
		length_ = obj.length_;
		data_ = new T[length_];
		for (int i = 0; i < length_; i++)
			data_[i] = obj.data_[i];
	}

	template <typename T>
	Set<T>::Set(Set&& obj)
	{
		data_ = obj.data_;
		length_ = obj.length_;
	}

	template <typename T>
	Set<T>::Set()
	{
		length_ = 0;
		data_ = nullptr;
	}

	template <typename T>
	Set<T>::~Set()
	{
		delete[] data_;
	}

	template <typename T>
	bool Set<T>::operator==(const Set& other) const
	{
		if (length_ != other.length_)
		{
			return false;
		}
		for (int i = 0; i < length_; i++)
		if (!contains(other.data_[i]))
		{
			return false;
		}
		return true;
	}

	template <typename T>
	void Set<T>::operator+=(const Set& other)
	{
		for (int i = 0; i < other.length_; i++)
			add(other.data_[i]);
	}

	template <typename T>
	Set<T>& Set<T>::operator+(const Set& b)
	{
		Set<T> *res = new Set<T>();
		for (int i = 0; i < this.length_; i++)
			res.add(this.data_[i]);
		for (int i = 0; i < b.length_; i++)
			res.add(b.data_[i]);
		return res;
	}

	template <typename T>
	Set<T>& Set<T>::operator*(const Set& b)
	{
		Set<T> *res = new Set(this);
		res *= b;
		return res;
	}

	template <typename T>
	Set<T>& Set<T>::operator-(const Set& b)
	{
		Set<T> *res = new Set(this);
		res -= b;
		return res;
	}

	template <typename T>
	void Set<T>::operator-=(const Set& other)
	{
		for (int i = 0; i < length_; i++)
		if (other.contains(data_[i]))
		{
			remove(data_[i]);
			i--;
		}
	}

	template <typename T>
	void Set<T>::operator*=(const Set& other)
	{
		for (int i = 0; i < length_; i++)
		if (!other.contains(data_[i]))
		{
			remove(data_[i]);
			i--;
		}
	}

	template <typename T>
	int Set<T>::get_length() const
	{
		return length_;
	}

	template <typename T>
	void Set<T>::add(T element)
	{
		if (contains(element))
			return;

		T *temp = new T[length_];
		for (int i = 0; i < length_; i++)
			temp[i] = data_[i];

		delete[] data_;
		data_ = new T[length_ + 1];

		for (int i = 0; i < length_; i++)
			data_[i] = temp[i];
		data_[length_] = element;
		length_++;

		delete[] temp;
	}

	template <typename T>
	void Set<T>::remove(T element)
	{
		int ind = -1;
		for (int i = 0; i < length_; i++)
		if (data_[i] == element)
			ind = i;

		if (ind == -1)
			return;

		T *temp = new T[length_];
		for (int i = 0, j = 0; i < length_; i++)
		{
			if (i != ind)
			{
				temp[j] = data_[i];
				j++;
			}
		}

		delete[] data_;
		data_ = new T[--length_];
		for (int i = 0; i < length_; i++)
		{
			data_[i] = temp[i];
		}

		delete[] temp;
	}

	template <typename T>
	bool Set<T>::contains(T element) const
	{
		for (int i = 0; i < length_; i++)
		if (data_[i] == element)
			return true;
		return false;
	}

	template <typename T>
	T* Set<T>::to_array() const
	{
		T arr[] = new T[length_];
		for (int i = 0; i < length_; i++)
		{
			arr[i] = data_[i];
		}
		return arr;
	}
}