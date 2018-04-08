#pragma once

#include <iostream>
#include <string>

namespace Util
{
	template<typename T>
	class Set
	{
	private:
		T *data_;
		int length_;
	public:
		Set(const T *elements, int count)
		{
			int actualLength = count;
			T *temp = new T[count];
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

		Set(const Set<T>& obj)
		{
			this->length_ = obj.length_;
			this->data_ = new T[obj.length_];
			for (int i = 0; i < this->length_; i++)
				this->data_[i] = obj.data_[i];
		}

		/*Set(Set&& obj)
		{
			data_ = obj.data_;
			length_ = obj.length_;
		}*/
		
		Set()
		{
			length_ = 0;
			data_ = nullptr;
		}

		~Set()
		{
			delete[] data_;
		}

		// Сравнение множеств
		bool operator==(const Set& other) const
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

		// Объединение множеств
		void operator+=(const Set& other)
		{
			for (int i = 0; i < other.length_; i++)
				this->add(other.data_[i]);
		}

		void operator+=(const T element)
		{
			add(element);
		}	

		Set operator +(const Set& b)
		{
			Set<T> united = Set<T>(*this);
			united += b;
			return united;
		}

		Set operator *(const Set& b)
		{
			Set<T> res = Set(*this);
			res *= b;
			return res;
		}

		Set operator -(const Set& b)
		{
			Set<T> res = Set(*this);
			res -= b;
			return res;
		}

		// Разность множеств
		void operator-=(const Set& other)
		{
			for (int i = 0; i < length_; i++)
			if (other.contains(data_[i]))
			{
				remove(data_[i]);
				i--;
			}
		}

		void operator-=(const T element)
		{
			remove(element);
		}

		// Пересечение множеств
		void operator*=(const Set& other)
		{
			for (int i = 0; i < length_; i++)
			if (!other.contains(data_[i]))
			{
				remove(data_[i]);
				i--;
			}			
		}

		// Получение текущего размера
		int get_length() const
		{
			return length_;
		}

		void add(const T element)
		{
			if (contains(element))
				return;

			T *tmp = new T[length_ + 1];
			
			for (int i = 0; i < length_; i++)
				tmp[i] = data_[i];
			tmp[length_] = element;

			delete[] data_;
			data_ = tmp;
			length_++;
		}

		void remove(const T element)
		{
			if (!contains(element))
				return;

			T* tmp = new T[length_ - 1];
			for (int i = 0, t = 0; i < length_; i++)
			{
				if (data_[i] != element)
				{
					tmp[t] = data_[i];
					t++;
				}
			}

			delete[] data_;
			data_ = tmp;
			length_--;
		}

		bool contains(T element) const
		{
			for (int i = 0; i < length_; i++)
			if (data_[i] == element)
				return true;
			return false;
		}

		T *to_array() const
		{
			T *arr = new T[length_];
			for (int i = 0; i < length_; i++)
			{
				arr[i] = data_[i];
			}
			return arr;
		}

		Set<int> clone()
		{
			return Set<int>(*this);
		}

		
		std::string to_string() const
		{			
			std::string res = "";
			if (length_ == 0)
			{
				res += "(empty set)";
				return res;
			}
			for (int i = 0; i < length_; i++)
			{
				res += std::to_string(data_[i]);
				if (i < length_ - 1)
					res += " ";
			}
			return res;
		}
	};
}
