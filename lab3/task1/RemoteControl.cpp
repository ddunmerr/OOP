#include "stdafx.h"
#include "RemoteControl.h"
#include "TVSet.h"

CRemoteControl::CRemoteControl(CTVSet& tv, std::istream& input, std::ostream& output)
	: m_tv(tv)
	, m_input(input)
	, m_output(output)
	, m_actionMap({ { TURN_ON_COMMAND, std::bind(&CRemoteControl::TurnOn, this, std::placeholders::_1) },
		  { TURN_OFF_COMMAND, std::bind(&CRemoteControl::TurnOff, this, std::placeholders::_1) },
		  { INFO_COMMAND, std::bind(&CRemoteControl::Info, this, std::placeholders::_1) },
		  { SELECT_CHANNEL_COMMAND, std::bind(&CRemoteControl::SelectChannel, this, std::placeholders::_1) } })
{
}

bool CRemoteControl::HandleCommand()
{
	std::string commandLine;
	getline(m_input, commandLine);
	std::istringstream strm(commandLine);

	std::string action;
	strm >> action;

	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		return it->second(strm);
	}

	return false;
}

bool CRemoteControl::TurnOn(std::istream& /*args*/)
{
	m_tv.TurnOn();
	m_output << TV_IS_TURNED_ON << std::endl;
	return true;
}

bool CRemoteControl::TurnOff(std::istream& /*args*/)
{
	m_tv.TurnOff();
	m_output << TV_IS_TURNED_OFF << std::endl;
	return true;
}

bool CRemoteControl::Info(std::istream& /*args*/)
{
	std::string info = (m_tv.IsTurnedOn())
		? (TV_IS_TURNED_ON + '\n' + CHANNEL_IS + std::to_string(m_tv.GetChannel()) + '\n')
		: TV_IS_TURNED_OFF + '\n';

	m_output << info;

	return true;
}

bool CRemoteControl::SelectChannel(std::istream& args)
{
	int channel;
	if (!(args >> channel))
	{
		return false; // Неверный формат ввода
	}

	if (!m_tv.IsTurnedOn())
	{
		m_output << CANT_SELECT_CHANNEL_TV_OFF << std::endl;
		return true; // Команда распознана и обработана
	}

	if (!m_tv.SelectChannel(channel))
	{
		m_output << INVALID_CHANNEL << std::endl;
		return true; // Команда распознана, канал невалиден
	}

	m_output << CHANNEL_SWITCHED_TO << std::endl;
	return true;
}
