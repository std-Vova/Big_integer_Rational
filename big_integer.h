// big_integer.h.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include<vector>
#include<string>
#include<iostream>

class big_integer {
private:
	bool sign;
	std::vector<int> v;
public:
	big_integer();
	big_integer(int);
	big_integer(const char*);
	big_integer(const std::string&);
	big_integer(const big_integer&);

	friend std::ostream& operator<<(std::ostream&, const big_integer&);
	friend std::istream& operator>>(std::istream&, big_integer&);

	big_integer& operator=(const big_integer&);

	friend bool operator>(const big_integer&, const big_integer&);
	friend bool operator>=(const big_integer&, const big_integer&);

	friend bool operator<(const big_integer&, const big_integer&);
	friend bool operator<=(const big_integer&, const big_integer&);


	friend bool operator==(const big_integer&, const big_integer&);
	friend bool operator!=(const big_integer&, const big_integer&);


	big_integer& operator++();
	big_integer operator++(int);

	big_integer& operator--();
	big_integer operator--(int);


	big_integer& operator+=(const big_integer&);
	friend big_integer operator+(const big_integer&, const big_integer&);

	big_integer& operator*=(const big_integer&);
	friend big_integer operator*(const big_integer&, const big_integer&);

	big_integer& operator/=(const big_integer& b);
	friend big_integer operator/(const big_integer&, const big_integer&);

	big_integer& operator%=(const big_integer&);
	friend big_integer operator%(const big_integer&, const big_integer&);

	friend big_integer operator-(const big_integer&, const big_integer&);
	big_integer& operator-=(const big_integer&);

	bool operator!() const;
	big_integer& operator-();
	big_integer& operator+();

	explicit operator bool() const;

	explicit operator int() const;

	std::string to_string() const;
	big_integer Abs() const;
private:
	void CheckSignAndWrite(const char*);
	void HelperForCheckSingAndWrite(const char*, int);
	int CheckSignForChar(const char*);
	void HelperToString(std::string&) const;
	template<typename T>
	void CheckSignForOut(T&) const;

	void PredSummer(const big_integer&);
	void Summer(size_t, size_t, const big_integer&, bool Ifsmaller, size_t = 0);
	void HelperForSummer(int&, size_t, int = 0);

	void PredDestr(const big_integer&, size_t&);
	void Destructer(const big_integer&, size_t, size_t, size_t&, bool);
	void HelperDestructer1(const big_integer&, int&, size_t&, bool);
	void HelperDestructer2(const big_integer&, int&, size_t&, bool);

	void Multiply(const big_integer& a, const big_integer& b);
	bool HelperForMemcmp(const big_integer&, const big_integer&) const;

	bool HelperForOperatorLowandBig(const big_integer&, const big_integer&) const;
};
//                                         ОБЪЯВЛЕНИЯ СПЕЦИАЛИЗАЦИЙ
template<>
void big_integer::CheckSignForOut(std::string&) const;
template<>
void big_integer::CheckSignForOut(std::ostream&) const;
