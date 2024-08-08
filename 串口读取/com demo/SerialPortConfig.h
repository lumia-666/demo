#pragma once
#include <cstdint>
#include <string>

// ���ں�����
struct SerialPortConfig
{
	std::string portName ;		// �˿ں�����
	uint32_t baudRate;		// ������
	uint8_t byteSize ;		// ����λ
	uint8_t parity ;			// ��żУ��λ
	uint8_t stopBits ;		// ֹͣλ
	uint32_t readTimeOut;		// ����ʱʱ�� ���� 0����δ����
	uint32_t writeTimeOut;		// д��ʱʱ�� ���� 0����δ����

	SerialPortConfig()
	{
		baudRate = 115200;
		byteSize = 8;
		parity = 0;
		stopBits = 0;
		readTimeOut = 2000;
		writeTimeOut = 2000;
	}
};