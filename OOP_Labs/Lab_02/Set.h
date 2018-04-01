#pragma once

namespace Lab_02
{
	template<typename T>
	class Set
	{
	private:
		T *data_;
		int length_;
	public:
		Set(T elements[], int count);
		Set(const Set& obj);
		Set(Set&& obj);
		Set();
		~Set();

		// ��������� ��������
		bool operator==(const Set& other) const;

		// ����������� ��������
		void operator+=(const Set& other);

		Set& operator +(const Set& b);
		Set& operator *(const Set& b);
		Set& operator -(const Set& b);

		// �������� ��������
		void operator-=(const Set& other);

		// ����������� ��������
		void operator*=(const Set& other);

		// ��������� �������� �������
		int get_length() const;

		void add(T element);

		void remove(T element);

		bool contains(T element) const;

		T *to_array() const;
	};
}
