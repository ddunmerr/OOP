#pragma once
#include "consts.h"
#include <iosfwd>

class CTime
{
public:
	CTime(unsigned hours, unsigned minutes, unsigned seconds = 0);
	CTime(unsigned timeStamp = 0);

	unsigned GetHours() const;
	unsigned GetMinutes() const;
	unsigned GetSeconds() const;
	unsigned GetTotalSeconds() const;
	bool IsValid() const;

	CTime& operator++();
	CTime operator++(int);

	CTime& operator--();
	CTime operator--(int);

	CTime operator+(const CTime& other) const;
	CTime operator-(const CTime& other) const;
	CTime& operator+=(const CTime& other);
	CTime& operator-=(const CTime& other);

	CTime operator*(unsigned multiplier) const;
	CTime& operator*=(unsigned multiplier);

	CTime operator/(unsigned divisor) const;
	unsigned operator/(const CTime& other) const;
	CTime& operator/=(unsigned divisor);

	bool operator==(const CTime& other) const;
	bool operator!=(const CTime& other) const;
	bool operator<(const CTime& other) const;
	bool operator>(const CTime& other) const;
	bool operator<=(const CTime& other) const;
	bool operator>=(const CTime& other) const;

private:
	CTime(unsigned totalSeconds, bool isValid);
	unsigned Normalize(long long totalSeconds) const;

	unsigned m_totalSeconds;
	bool m_isValid;
};

std::ostream& operator<<(std::ostream& os, const CTime& time);
std::istream& operator>>(std::istream& is, CTime& time);

CTime operator*(unsigned multiplier, const CTime& time);
