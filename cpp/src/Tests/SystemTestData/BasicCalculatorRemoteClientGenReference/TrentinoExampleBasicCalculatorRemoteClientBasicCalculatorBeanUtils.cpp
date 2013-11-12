#pragma warning(push)
#pragma warning(disable:4290 4512 4244)
#include "TrentinoExampleBasicCalculatorRemoteClientBasicCalculatorBeanUtils.h"
#pragma warning(pop)



void Trentino::Example::BasicCalculatorRemoteClient::BasicCalculatorBeanUtils::copyProperties(const Trentino::Example::BasicCalculatorRemoteClient::protobuf::PB_Address& pb_Address, Trentino::Example::BasicCalculatorRemoteClient::Address& argAddress)
{
	argAddress.set_street(pb_Address.street());
	if (pb_Address.has_phone())
	{
		const Trentino::Example::BasicCalculatorRemoteClient::protobuf::PB_Phone& m_pb_Phone = pb_Address.phone();
		Trentino::Example::BasicCalculatorRemoteClient::Phone* m_Phone =argAddress.mutable_phone();
		copyProperties(&m_pb_Phone, m_Phone);
	}
}

void Trentino::Example::BasicCalculatorRemoteClient::BasicCalculatorBeanUtils::copyProperties(const Trentino::Example::BasicCalculatorRemoteClient::protobuf::PB_Address* pb_Address, Trentino::Example::BasicCalculatorRemoteClient::Address* argAddress)
{
	argAddress->set_street(pb_Address->street());
	if (pb_Address->has_phone())
	{
		const Trentino::Example::BasicCalculatorRemoteClient::protobuf::PB_Phone& m_pb_Phone = pb_Address->phone();
		Trentino::Example::BasicCalculatorRemoteClient::Phone* m_Phone =argAddress->mutable_phone();
		copyProperties(&m_pb_Phone, m_Phone);
	}
}
	
void Trentino::Example::BasicCalculatorRemoteClient::BasicCalculatorBeanUtils::copyProperties(Trentino::Example::BasicCalculatorRemoteClient::Address& argAddress, Trentino::Example::BasicCalculatorRemoteClient::protobuf::PB_Address& pb_Address)
{
	pb_Address.set_street(argAddress.street());
	if (argAddress.has_phone())
	{
		Trentino::Example::BasicCalculatorRemoteClient::protobuf::PB_Phone* m_pb_Phone = pb_Address.mutable_phone();
		Trentino::Example::BasicCalculatorRemoteClient::Phone* m_Phone =argAddress.mutable_phone();
		copyProperties(m_Phone, m_pb_Phone);
	}
}

void Trentino::Example::BasicCalculatorRemoteClient::BasicCalculatorBeanUtils::copyProperties(Trentino::Example::BasicCalculatorRemoteClient::Address* argAddress, Trentino::Example::BasicCalculatorRemoteClient::protobuf::PB_Address* pb_Address)
{
	pb_Address->set_street(argAddress->street());
	if (argAddress->has_phone())
	{
		Trentino::Example::BasicCalculatorRemoteClient::protobuf::PB_Phone* m_pb_Phone = pb_Address->mutable_phone();
		Trentino::Example::BasicCalculatorRemoteClient::Phone* m_Phone =argAddress->mutable_phone();
		copyProperties(m_Phone, m_pb_Phone);
	}
}
void Trentino::Example::BasicCalculatorRemoteClient::BasicCalculatorBeanUtils::copyProperties(const Trentino::Example::BasicCalculatorRemoteClient::protobuf::PB_ComplexNumber& pb_ComplexNumber, Trentino::Example::BasicCalculatorRemoteClient::ComplexNumber& argComplexNumber)
{
	argComplexNumber.set_a(pb_ComplexNumber.a());
	argComplexNumber.set_b(pb_ComplexNumber.b());
}

void Trentino::Example::BasicCalculatorRemoteClient::BasicCalculatorBeanUtils::copyProperties(const Trentino::Example::BasicCalculatorRemoteClient::protobuf::PB_ComplexNumber* pb_ComplexNumber, Trentino::Example::BasicCalculatorRemoteClient::ComplexNumber* argComplexNumber)
{
	argComplexNumber->set_a(pb_ComplexNumber->a());
	argComplexNumber->set_b(pb_ComplexNumber->b());
}
	
void Trentino::Example::BasicCalculatorRemoteClient::BasicCalculatorBeanUtils::copyProperties(Trentino::Example::BasicCalculatorRemoteClient::ComplexNumber& argComplexNumber, Trentino::Example::BasicCalculatorRemoteClient::protobuf::PB_ComplexNumber& pb_ComplexNumber)
{
	pb_ComplexNumber.set_a(argComplexNumber.a());
	pb_ComplexNumber.set_b(argComplexNumber.b());
}

void Trentino::Example::BasicCalculatorRemoteClient::BasicCalculatorBeanUtils::copyProperties(Trentino::Example::BasicCalculatorRemoteClient::ComplexNumber* argComplexNumber, Trentino::Example::BasicCalculatorRemoteClient::protobuf::PB_ComplexNumber* pb_ComplexNumber)
{
	pb_ComplexNumber->set_a(argComplexNumber->a());
	pb_ComplexNumber->set_b(argComplexNumber->b());
}
void Trentino::Example::BasicCalculatorRemoteClient::BasicCalculatorBeanUtils::copyProperties(const Trentino::Example::BasicCalculatorRemoteClient::protobuf::PB_Phone& pb_Phone, Trentino::Example::BasicCalculatorRemoteClient::Phone& argPhone)
{
	argPhone.set_home(pb_Phone.home());
	argPhone.set_mobile(pb_Phone.mobile());
}

void Trentino::Example::BasicCalculatorRemoteClient::BasicCalculatorBeanUtils::copyProperties(const Trentino::Example::BasicCalculatorRemoteClient::protobuf::PB_Phone* pb_Phone, Trentino::Example::BasicCalculatorRemoteClient::Phone* argPhone)
{
	argPhone->set_home(pb_Phone->home());
	argPhone->set_mobile(pb_Phone->mobile());
}
	
void Trentino::Example::BasicCalculatorRemoteClient::BasicCalculatorBeanUtils::copyProperties(Trentino::Example::BasicCalculatorRemoteClient::Phone& argPhone, Trentino::Example::BasicCalculatorRemoteClient::protobuf::PB_Phone& pb_Phone)
{
	pb_Phone.set_home(argPhone.home());
	pb_Phone.set_mobile(argPhone.mobile());
}

void Trentino::Example::BasicCalculatorRemoteClient::BasicCalculatorBeanUtils::copyProperties(Trentino::Example::BasicCalculatorRemoteClient::Phone* argPhone, Trentino::Example::BasicCalculatorRemoteClient::protobuf::PB_Phone* pb_Phone)
{
	pb_Phone->set_home(argPhone->home());
	pb_Phone->set_mobile(argPhone->mobile());
}
void Trentino::Example::BasicCalculatorRemoteClient::BasicCalculatorBeanUtils::copyProperties(const Trentino::Example::BasicCalculatorRemoteClient::protobuf::PB_Person& pb_Person, Trentino::Example::BasicCalculatorRemoteClient::Person& argPerson)
{
	if (pb_Person.has_addres())
	{
		const Trentino::Example::BasicCalculatorRemoteClient::protobuf::PB_Address& m_pb_Address = pb_Person.addres();
		Trentino::Example::BasicCalculatorRemoteClient::Address* m_Address =argPerson.mutable_addres();
		copyProperties(&m_pb_Address, m_Address);
	}
	argPerson.set_name(pb_Person.name());
	argPerson.set_surname(pb_Person.surname());
	if (pb_Person.has_mother())
	{
		const Trentino::Example::BasicCalculatorRemoteClient::protobuf::PB_Person& m_pb_Person = pb_Person.mother();
		Trentino::Example::BasicCalculatorRemoteClient::Person* m_Person =argPerson.mutable_mother();
		copyProperties(&m_pb_Person, m_Person);
	}
}

void Trentino::Example::BasicCalculatorRemoteClient::BasicCalculatorBeanUtils::copyProperties(const Trentino::Example::BasicCalculatorRemoteClient::protobuf::PB_Person* pb_Person, Trentino::Example::BasicCalculatorRemoteClient::Person* argPerson)
{
	if (pb_Person->has_addres())
	{
		const Trentino::Example::BasicCalculatorRemoteClient::protobuf::PB_Address& m_pb_Address = pb_Person->addres();
		Trentino::Example::BasicCalculatorRemoteClient::Address* m_Address =argPerson->mutable_addres();
		copyProperties(&m_pb_Address, m_Address);
	}
	argPerson->set_name(pb_Person->name());
	argPerson->set_surname(pb_Person->surname());
	if (pb_Person->has_mother())
	{
		const Trentino::Example::BasicCalculatorRemoteClient::protobuf::PB_Person& m_pb_Person = pb_Person->mother();
		Trentino::Example::BasicCalculatorRemoteClient::Person* m_Person =argPerson->mutable_mother();
		copyProperties(&m_pb_Person, m_Person);
	}
}
	
void Trentino::Example::BasicCalculatorRemoteClient::BasicCalculatorBeanUtils::copyProperties(Trentino::Example::BasicCalculatorRemoteClient::Person& argPerson, Trentino::Example::BasicCalculatorRemoteClient::protobuf::PB_Person& pb_Person)
{
	if (argPerson.has_addres())
	{
		Trentino::Example::BasicCalculatorRemoteClient::protobuf::PB_Address* m_pb_Address = pb_Person.mutable_addres();
		Trentino::Example::BasicCalculatorRemoteClient::Address* m_Address =argPerson.mutable_addres();
		copyProperties(m_Address, m_pb_Address);
	}
	pb_Person.set_name(argPerson.name());
	pb_Person.set_surname(argPerson.surname());
	if (argPerson.has_mother())
	{
		Trentino::Example::BasicCalculatorRemoteClient::protobuf::PB_Person* m_pb_Person = pb_Person.mutable_mother();
		Trentino::Example::BasicCalculatorRemoteClient::Person* m_Person =argPerson.mutable_mother();
		copyProperties(m_Person, m_pb_Person);
	}
}

void Trentino::Example::BasicCalculatorRemoteClient::BasicCalculatorBeanUtils::copyProperties(Trentino::Example::BasicCalculatorRemoteClient::Person* argPerson, Trentino::Example::BasicCalculatorRemoteClient::protobuf::PB_Person* pb_Person)
{
	if (argPerson->has_addres())
	{
		Trentino::Example::BasicCalculatorRemoteClient::protobuf::PB_Address* m_pb_Address = pb_Person->mutable_addres();
		Trentino::Example::BasicCalculatorRemoteClient::Address* m_Address =argPerson->mutable_addres();
		copyProperties(m_Address, m_pb_Address);
	}
	pb_Person->set_name(argPerson->name());
	pb_Person->set_surname(argPerson->surname());
	if (argPerson->has_mother())
	{
		Trentino::Example::BasicCalculatorRemoteClient::protobuf::PB_Person* m_pb_Person = pb_Person->mutable_mother();
		Trentino::Example::BasicCalculatorRemoteClient::Person* m_Person =argPerson->mutable_mother();
		copyProperties(m_Person, m_pb_Person);
	}
}
void Trentino::Example::BasicCalculatorRemoteClient::BasicCalculatorBeanUtils::copyProperties(const Trentino::Example::BasicCalculatorRemoteClient::protobuf::PB_TupleComplexNumber& pb_TupleComplexNumber, Trentino::Example::BasicCalculatorRemoteClient::TupleComplexNumber& argTupleComplexNumber)
{
	if (pb_TupleComplexNumber.has_a())
	{
		const Trentino::Example::BasicCalculatorRemoteClient::protobuf::PB_ComplexNumber& m_pb_ComplexNumber = pb_TupleComplexNumber.a();
		Trentino::Example::BasicCalculatorRemoteClient::ComplexNumber* m_ComplexNumber =argTupleComplexNumber.mutable_a();
		copyProperties(&m_pb_ComplexNumber, m_ComplexNumber);
	}
	if (pb_TupleComplexNumber.has_b())
	{
		const Trentino::Example::BasicCalculatorRemoteClient::protobuf::PB_ComplexNumber& m_pb_ComplexNumber = pb_TupleComplexNumber.b();
		Trentino::Example::BasicCalculatorRemoteClient::ComplexNumber* m_ComplexNumber =argTupleComplexNumber.mutable_b();
		copyProperties(&m_pb_ComplexNumber, m_ComplexNumber);
	}
}

void Trentino::Example::BasicCalculatorRemoteClient::BasicCalculatorBeanUtils::copyProperties(const Trentino::Example::BasicCalculatorRemoteClient::protobuf::PB_TupleComplexNumber* pb_TupleComplexNumber, Trentino::Example::BasicCalculatorRemoteClient::TupleComplexNumber* argTupleComplexNumber)
{
	if (pb_TupleComplexNumber->has_a())
	{
		const Trentino::Example::BasicCalculatorRemoteClient::protobuf::PB_ComplexNumber& m_pb_ComplexNumber = pb_TupleComplexNumber->a();
		Trentino::Example::BasicCalculatorRemoteClient::ComplexNumber* m_ComplexNumber =argTupleComplexNumber->mutable_a();
		copyProperties(&m_pb_ComplexNumber, m_ComplexNumber);
	}
	if (pb_TupleComplexNumber->has_b())
	{
		const Trentino::Example::BasicCalculatorRemoteClient::protobuf::PB_ComplexNumber& m_pb_ComplexNumber = pb_TupleComplexNumber->b();
		Trentino::Example::BasicCalculatorRemoteClient::ComplexNumber* m_ComplexNumber =argTupleComplexNumber->mutable_b();
		copyProperties(&m_pb_ComplexNumber, m_ComplexNumber);
	}
}
	
void Trentino::Example::BasicCalculatorRemoteClient::BasicCalculatorBeanUtils::copyProperties(Trentino::Example::BasicCalculatorRemoteClient::TupleComplexNumber& argTupleComplexNumber, Trentino::Example::BasicCalculatorRemoteClient::protobuf::PB_TupleComplexNumber& pb_TupleComplexNumber)
{
	if (argTupleComplexNumber.has_a())
	{
		Trentino::Example::BasicCalculatorRemoteClient::protobuf::PB_ComplexNumber* m_pb_ComplexNumber = pb_TupleComplexNumber.mutable_a();
		Trentino::Example::BasicCalculatorRemoteClient::ComplexNumber* m_ComplexNumber =argTupleComplexNumber.mutable_a();
		copyProperties(m_ComplexNumber, m_pb_ComplexNumber);
	}
	if (argTupleComplexNumber.has_b())
	{
		Trentino::Example::BasicCalculatorRemoteClient::protobuf::PB_ComplexNumber* m_pb_ComplexNumber = pb_TupleComplexNumber.mutable_b();
		Trentino::Example::BasicCalculatorRemoteClient::ComplexNumber* m_ComplexNumber =argTupleComplexNumber.mutable_b();
		copyProperties(m_ComplexNumber, m_pb_ComplexNumber);
	}
}

void Trentino::Example::BasicCalculatorRemoteClient::BasicCalculatorBeanUtils::copyProperties(Trentino::Example::BasicCalculatorRemoteClient::TupleComplexNumber* argTupleComplexNumber, Trentino::Example::BasicCalculatorRemoteClient::protobuf::PB_TupleComplexNumber* pb_TupleComplexNumber)
{
	if (argTupleComplexNumber->has_a())
	{
		Trentino::Example::BasicCalculatorRemoteClient::protobuf::PB_ComplexNumber* m_pb_ComplexNumber = pb_TupleComplexNumber->mutable_a();
		Trentino::Example::BasicCalculatorRemoteClient::ComplexNumber* m_ComplexNumber =argTupleComplexNumber->mutable_a();
		copyProperties(m_ComplexNumber, m_pb_ComplexNumber);
	}
	if (argTupleComplexNumber->has_b())
	{
		Trentino::Example::BasicCalculatorRemoteClient::protobuf::PB_ComplexNumber* m_pb_ComplexNumber = pb_TupleComplexNumber->mutable_b();
		Trentino::Example::BasicCalculatorRemoteClient::ComplexNumber* m_ComplexNumber =argTupleComplexNumber->mutable_b();
		copyProperties(m_ComplexNumber, m_pb_ComplexNumber);
	}
}
void Trentino::Example::BasicCalculatorRemoteClient::BasicCalculatorBeanUtils::copyProperties(const Trentino::Example::BasicCalculatorRemoteClient::protobuf::PB_ValidationException& pb_ValidationException, Trentino::Example::BasicCalculatorRemoteClient::ValidationException& argValidationException)
{
	argValidationException.set_details(pb_ValidationException.details());
}

void Trentino::Example::BasicCalculatorRemoteClient::BasicCalculatorBeanUtils::copyProperties(const Trentino::Example::BasicCalculatorRemoteClient::protobuf::PB_ValidationException* pb_ValidationException, Trentino::Example::BasicCalculatorRemoteClient::ValidationException* argValidationException)
{
	argValidationException->set_details(pb_ValidationException->details());
}
	
void Trentino::Example::BasicCalculatorRemoteClient::BasicCalculatorBeanUtils::copyProperties(Trentino::Example::BasicCalculatorRemoteClient::ValidationException& argValidationException, Trentino::Example::BasicCalculatorRemoteClient::protobuf::PB_ValidationException& pb_ValidationException)
{
	pb_ValidationException.set_details(argValidationException.details());
}

void Trentino::Example::BasicCalculatorRemoteClient::BasicCalculatorBeanUtils::copyProperties(Trentino::Example::BasicCalculatorRemoteClient::ValidationException* argValidationException, Trentino::Example::BasicCalculatorRemoteClient::protobuf::PB_ValidationException* pb_ValidationException)
{
	pb_ValidationException->set_details(argValidationException->details());
}

Trentino::Example::BasicCalculatorRemoteClient::BasicCalculatorBeanUtils::BasicCalculatorBeanUtils() {}
Trentino::Example::BasicCalculatorRemoteClient::BasicCalculatorBeanUtils::~BasicCalculatorBeanUtils() {}
