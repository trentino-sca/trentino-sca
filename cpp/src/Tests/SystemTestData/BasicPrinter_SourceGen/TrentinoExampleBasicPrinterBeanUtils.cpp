#pragma warning(push)
#pragma warning(disable:4290 4512 4244)
#include "TrentinoExampleBasicPrinterBeanUtils.h"
#pragma warning(pop)


void Trentino::Example::BasicPrinterBeanUtils::copyProperties(const protobuf::Trentino::Example::BasicPrinter::PB_ValidationException& pbObject, Trentino::Example::BasicPrinter::ValidationException* object)
{
	object->set_details(pbObject.details());
}

void Trentino::Example::BasicPrinterBeanUtils::copyProperties(const Trentino::Example::BasicPrinter::ValidationException& object, protobuf::Trentino::Example::BasicPrinter::PB_ValidationException* pbObject)
{
	pbObject->set_details(object.details());
}

void Trentino::Example::BasicPrinterBeanUtils::copyProperties(const protobuf::Trentino::Example::BasicPrinter::PB_Address& pbObject, Trentino::Example::BasicPrinter::Address* object)
{
	object->set_street(pbObject.street());
	if (pbObject.has_phone())
	{
		const protobuf::Trentino::Example::BasicPrinter::PB_Phone& m_pb = pbObject.phone();
		Trentino::Example::BasicPrinter::Phone* m =object->mutable_phone();
		copyProperties(m_pb, m);
	}
}

void Trentino::Example::BasicPrinterBeanUtils::copyProperties(const Trentino::Example::BasicPrinter::Address& object, protobuf::Trentino::Example::BasicPrinter::PB_Address* pbObject)
{
	pbObject->set_street(object.street());
	if (object.has_phone())
	{
		protobuf::Trentino::Example::BasicPrinter::PB_Phone* m_pb = pbObject->mutable_phone();
		Trentino::Example::BasicPrinter::Phone& m =object.phone();
		copyProperties(m, m_pb);
	}
}

void Trentino::Example::BasicPrinterBeanUtils::copyProperties(const protobuf::Trentino::Example::BasicPrinter::PB_TupleComplexNumber& pbObject, Trentino::Example::BasicPrinter::TupleComplexNumber* object)
{
	if (pbObject.has_a())
	{
		const protobuf::Trentino::Example::BasicPrinter::PB_ComplexNumber& m_pb = pbObject.a();
		Trentino::Example::BasicPrinter::ComplexNumber* m =object->mutable_a();
		copyProperties(m_pb, m);
	}
	if (pbObject.has_b())
	{
		const protobuf::Trentino::Example::BasicPrinter::PB_ComplexNumber& m_pb = pbObject.b();
		Trentino::Example::BasicPrinter::ComplexNumber* m =object->mutable_b();
		copyProperties(m_pb, m);
	}
}

void Trentino::Example::BasicPrinterBeanUtils::copyProperties(const Trentino::Example::BasicPrinter::TupleComplexNumber& object, protobuf::Trentino::Example::BasicPrinter::PB_TupleComplexNumber* pbObject)
{
	if (object.has_a())
	{
		protobuf::Trentino::Example::BasicPrinter::PB_ComplexNumber* m_pb = pbObject->mutable_a();
		Trentino::Example::BasicPrinter::ComplexNumber& m =object.a();
		copyProperties(m, m_pb);
	}
	if (object.has_b())
	{
		protobuf::Trentino::Example::BasicPrinter::PB_ComplexNumber* m_pb = pbObject->mutable_b();
		Trentino::Example::BasicPrinter::ComplexNumber& m =object.b();
		copyProperties(m, m_pb);
	}
}

void Trentino::Example::BasicPrinterBeanUtils::copyProperties(const protobuf::Trentino::Example::BasicPrinter::PB_Phone& pbObject, Trentino::Example::BasicPrinter::Phone* object)
{
	object->set_home(pbObject.home());
	object->set_mobile(pbObject.mobile());
}

void Trentino::Example::BasicPrinterBeanUtils::copyProperties(const Trentino::Example::BasicPrinter::Phone& object, protobuf::Trentino::Example::BasicPrinter::PB_Phone* pbObject)
{
	pbObject->set_home(object.home());
	pbObject->set_mobile(object.mobile());
}

void Trentino::Example::BasicPrinterBeanUtils::copyProperties(const protobuf::Trentino::Example::BasicPrinter::PB_Person& pbObject, Trentino::Example::BasicPrinter::Person* object)
{
	if (pbObject.has_addres())
	{
		const protobuf::Trentino::Example::BasicPrinter::PB_Address& m_pb = pbObject.addres();
		Trentino::Example::BasicPrinter::Address* m =object->mutable_addres();
		copyProperties(m_pb, m);
	}
	object->set_name(pbObject.name());
	object->set_surname(pbObject.surname());
	if (pbObject.has_mother())
	{
		const protobuf::Trentino::Example::BasicPrinter::PB_Person& m_pb = pbObject.mother();
		Trentino::Example::BasicPrinter::Person* m =object->mutable_mother();
		copyProperties(m_pb, m);
	}
}

void Trentino::Example::BasicPrinterBeanUtils::copyProperties(const Trentino::Example::BasicPrinter::Person& object, protobuf::Trentino::Example::BasicPrinter::PB_Person* pbObject)
{
	if (object.has_addres())
	{
		protobuf::Trentino::Example::BasicPrinter::PB_Address* m_pb = pbObject->mutable_addres();
		Trentino::Example::BasicPrinter::Address& m =object.addres();
		copyProperties(m, m_pb);
	}
	pbObject->set_name(object.name());
	pbObject->set_surname(object.surname());
	if (object.has_mother())
	{
		protobuf::Trentino::Example::BasicPrinter::PB_Person* m_pb = pbObject->mutable_mother();
		Trentino::Example::BasicPrinter::Person& m =object.mother();
		copyProperties(m, m_pb);
	}
}

void Trentino::Example::BasicPrinterBeanUtils::copyProperties(const protobuf::Trentino::Example::BasicPrinter::PB_ComplexNumber& pbObject, Trentino::Example::BasicPrinter::ComplexNumber* object)
{
	object->set_a(pbObject.a());
	object->set_b(pbObject.b());
}

void Trentino::Example::BasicPrinterBeanUtils::copyProperties(const Trentino::Example::BasicPrinter::ComplexNumber& object, protobuf::Trentino::Example::BasicPrinter::PB_ComplexNumber* pbObject)
{
	pbObject->set_a(object.a());
	pbObject->set_b(object.b());
}


Trentino::Example::BasicPrinterBeanUtils::BasicPrinterBeanUtils() {}
Trentino::Example::BasicPrinterBeanUtils::~BasicPrinterBeanUtils() {}
