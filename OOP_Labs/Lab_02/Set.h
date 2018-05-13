#pragma once

#include <string>

namespace Util
{

#define BLOCK_SIZE 16

	class MemoryException : public std::exception
	{
	public:
		static std::string what()
		{
			return "Bad alloc";
		}
	};

	template<typename T>
	class Set
	{
	private:
		T *data_;
		int length_;
		int allocated = 0;
	public:
		Set(const T *elements, int count)
		{
			data_ = nullptr;
			length_ = 0;
			for (int i = 0; i < count; i++)
			{
				add( elements[i]);
			}
		}

		Set(const Set<T>& obj)
		{
			this->length_ = obj.length_;
			this->data_ = new T[obj.length_];
			if (this->data_ == nullptr)
				throw MemoryException();
			for (int i = 0; i < this->length_; i++)
				this->data_[i] = obj.data_[i];
		}

		Set(Set&& obj)
		{
			data_ = obj.data_;
			length_ = obj.length_;
		}
		
		Set()
		{
			length_ = 0;
			data_ = nullptr;
		}

		~Set()
		{
			delete[] data_;
			data_ = nullptr;
		}

		// Сравнение множеств
		bool operator==(const Set& other) const
		{
			bool equal = length_ == other.length_;
			bool flag = false;
			for (int i = 0; i < length_ && !flag; i++)
			{
				equal &= contains(other.data_[i]);
				flag = true;
			}
			return equal;
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

		Set operator +(const Set& b) const
		{
			Set<T> united = Set<T>(*this);
			united += b;
			return Set(united);
		}

		Set operator *(const Set& b) const
		{
			Set<T> res = Set(*this);
			res *= b;
			return Set(res);
		}

		Set operator -(const Set& b) const
		{
			Set<T> res = Set(*this);
			res -= b;
			return Set(res);
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

			if (length_ + 1 <= allocated)
			{
				data_[length_] = element;				
			}
			else
			{
				T *tmp = new T[allocated + BLOCK_SIZE];
				if (tmp == nullptr)
					throw MemoryException();
				for (int i = 0; i < length_; i++)
				{
					tmp[i] = data_[i];
				}
				tmp[length_] = element;
				delete[] data_;
				data_ = tmp;
				allocated += BLOCK_SIZE;				
			}
			length_++;
		}

		void remove(const T element)
		{
			if (!contains(element))
				return;

			if (length_ - 1 >= allocated - BLOCK_SIZE)
			{
				for (int i = 0; i < length_; i++)
				{
					if (data_[i] == element)
					{
						for (int k = i; k < allocated; k++)
							data_[k] = data_[k] + 1;
					}
				}				
			}
			else
			{
				T* tmp = new T[allocated - BLOCK_SIZE];
				if (tmp == nullptr)
					throw MemoryException();
				int j = 0;
				for (int i = 0; i < length_; i++)
				{
					if (data_[i] != element)
					{
						tmp[j] = data_[i];
						j++;
					}
				}				
			}
			length_--;
		}

		bool contains(T element) const
		{
			bool found = false;
			for (int i = 0; i < length_ && !found; i++)
			if (data_[i] == element)
				found = true;
			return found;
		}

		T *to_array() const
		{
			T *arr = new T[length_];
			if (arr == nullptr)
				throw MemoryException();
			for (int i = 0; i < length_; i++)
			{
				arr[i] = data_[i];
			}
			return arr;
		}

		Set<T> clone() const
		{
			return Set<T>(*this);
		}

		
		std::string to_string() const
		{			
			std::string res = "";
			if (length_ == 0)
			{
				res += "(empty set)";				
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
