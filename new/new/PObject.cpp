#include "PObject.h"

PObject::PObject()
{
}

PObject::PObject(const void* ctx)
{
}

PObject::PObject(const PObject& obj)
{
}

PObject::~PObject()
{
}

PObject& PObject::operator=(const PObject& obj)
{
	// TODO: �ڴ˴����� return ���
	return *this;
}

void* PObject::operator new(size_t size)
{
	return nullptr;
}
