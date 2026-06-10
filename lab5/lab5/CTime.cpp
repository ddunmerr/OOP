#include "CTime.h"
#include <iomanip>

const char FILL_EMPTY = '0';
const unsigned SECONDS_PER_MINUTE = 60;
const unsigned HOURS_PER_DAY = 24;

CTime::CTime(unsigned hours, unsigned minutes, unsigned seconds)
	: m_totalSeconds(hours * SECONDS_PER_MINUTE * SECONDS_PER_MINUTE + minutes * SECONDS_PER_MINUTE + seconds)
	, m_isValid(hours <= (HOURS_PER_DAY - 1) && minutes <= (SECONDS_PER_MINUTE - 1) && seconds <= (SECONDS_PER_MINUTE - 1))
{
}

CTime::CTime(unsigned timestamp)
	: m_totalSeconds(timestamp % (SECONDS_PER_MINUTE * SECONDS_PER_MINUTE * HOURS_PER_DAY))
	, m_isValid(true)
{
}

CTime::CTime(unsigned totalSeconds, bool isValid)
	: m_totalSeconds(totalSeconds)
	, m_isValid(isValid)
{
}

unsigned CTime::GetHours() const
{
	return (m_totalSeconds / (SECONDS_PER_MINUTE * SECONDS_PER_MINUTE));
}

unsigned CTime::GetMinutes() const
{
	return (m_totalSeconds % (SECONDS_PER_MINUTE * SECONDS_PER_MINUTE)) / SECONDS_PER_MINUTE;
}

unsigned CTime::GetSeconds() const
{
	return m_totalSeconds % SECONDS_PER_MINUTE;
}

unsigned CTime::GetTotalSeconds() const
{
	return m_totalSeconds;
}

bool CTime::IsValid() const
{
	return m_isValid;
}

unsigned CTime::Normalize(long long totalSeconds) const
{
	long long result = (totalSeconds % (SECONDS_PER_MINUTE * SECONDS_PER_MINUTE * HOURS_PER_DAY));
	if (result < 0)
	{
		result += (SECONDS_PER_MINUTE * SECONDS_PER_MINUTE * HOURS_PER_DAY);
	}
	return static_cast<unsigned>(result);
}

CTime& CTime::operator++()
{
	if (m_isValid)
	{
		m_totalSeconds = ((m_totalSeconds + 1) % (SECONDS_PER_MINUTE * SECONDS_PER_MINUTE * HOURS_PER_DAY));
	}
	return *this;
}

CTime CTime::operator++(int)
{
	CTime temp(*this);
	++(*this);
	return temp;
}

CTime& CTime::operator--()
{
	if (m_isValid)
	{
		m_totalSeconds = m_totalSeconds == 0 ? (SECONDS_PER_MINUTE * SECONDS_PER_MINUTE * HOURS_PER_DAY) - 1 : m_totalSeconds - 1;
	}
	return *this;
}

CTime CTime::operator--(int)
{
	CTime temp(*this);
	--(*this);
	return temp;
}

CTime CTime::operator+(const CTime& other) const
{
	if (!m_isValid || !other.m_isValid)
	{
		return CTime(0, false);
	}
	return CTime(Normalize(static_cast<long long>(m_totalSeconds) + other.m_totalSeconds), true);
}

CTime CTime::operator-(const CTime& other) const
{
	if (!m_isValid || !other.m_isValid)
	{
		return CTime(0, false);
	}
	return CTime(Normalize(static_cast<long long>(m_totalSeconds) - other.m_totalSeconds), true);
}

CTime& CTime::operator+=(const CTime& other)
{
	*this = *this + other;
	return *this;
}

CTime& CTime::operator-=(const CTime& other)
{
	*this = *this - other;
	return *this;
}

CTime CTime::operator*(unsigned multiplier) const
{
	if (!m_isValid)
	{
		return CTime(0, false);
	}
	return CTime(Normalize(static_cast<long long>(m_totalSeconds) * multiplier), true);
}

CTime& CTime::operator*=(unsigned multiplier)
{
	*this = *this * multiplier;
	return *this;
}

CTime CTime::operator/(unsigned divisor) const
{
	if (!m_isValid || divisor == 0)
	{
		return CTime(0, false);
	}
	return CTime(m_totalSeconds / divisor, true);
}

unsigned CTime::operator/(const CTime& other) const
{
	if (!m_isValid || !other.m_isValid || other.m_totalSeconds == 0)
	{
		return 0;
	}
	return m_totalSeconds / other.m_totalSeconds;
}

CTime& CTime::operator/=(unsigned divisor)
{
	*this = *this / divisor;
	return *this;
}

bool CTime::operator==(const CTime& other) const
{
	if (!m_isValid && !other.m_isValid)
	{
		return true;
	}
	if (!m_isValid || !other.m_isValid)
	{
		return false;
	}
	return m_totalSeconds == other.m_totalSeconds;
}

bool CTime::operator!=(const CTime& other) const
{
	return !(*this == other);
}

bool CTime::operator<(const CTime& other) const
{
	if (!m_isValid || !other.m_isValid)
	{
		return false;
	}
	return m_totalSeconds < other.m_totalSeconds;
}

bool CTime::operator>(const CTime& other) const
{
	if (!m_isValid || !other.m_isValid)
	{
		return false;
	}
	return m_totalSeconds > other.m_totalSeconds;
}

bool CTime::operator<=(const CTime& other) const
{
	return *this < other || *this == other;
}

bool CTime::operator>=(const CTime& other) const
{
	return *this > other || *this == other;
}

CTime operator*(unsigned multiplier, const CTime& time)
{
	return time * multiplier;
}

std::ostream& operator<<(std::ostream& os, const CTime& time)
{
	if (!time.IsValid())
	{
		os << ERROR_INVALID;
	}
	else
	{
		os << std::setfill(FILL_EMPTY) << std::setw(2) << time.GetHours() << ":"
		   << std::setfill(FILL_EMPTY) << std::setw(2) << time.GetMinutes() << ":"
		   << std::setfill(FILL_EMPTY) << std::setw(2) << time.GetSeconds();
	}
	return os;
}

std::istream& operator>>(std::istream& is, CTime& time)
{
	unsigned hours = 0;
	unsigned minutes = 0;
	unsigned seconds = 0;
	char colon1 = 0;
	char colon2 = 0;

	if (is >> hours >> colon1 >> minutes >> colon2 >> seconds && colon1 == ':' && colon2 == ':')
	{
		time = CTime(hours, minutes, seconds);
	}
	else
	{
		time = CTime(0, 0, 0);
		is.setstate(std::ios::failbit);
	}

	return is;
}
