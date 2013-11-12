// Generated by Trentino TDIL CPP interface generator. do not modify

#ifndef TrentinoExampleBasicCalculatorRemoteClientBasicCalculatorH
#define TrentinoExampleBasicCalculatorRemoteClientBasicCalculatorH

#include "BasicCalculatorGlobal.h"
#ifndef NULL
#define NULL 0
#endif


#include <boost/cstdint.hpp>
#include <string>

typedef  boost::int32_t  tint32_t;
typedef  boost::uint32_t  tuint32_t;
typedef  boost::int64_t  tint64_t;
typedef  boost::uint64_t  tuint64_t;

namespace Trentino{
namespace Example{
namespace BasicCalculatorRemoteClient{

//forward declaration
class Address;
class ComplexNumber;
class Phone;
class Person;
class TupleComplexNumber;
class ValidationException;


 //****************************************************************************************************
 //                                         Address
 //****************************************************************************************************
 //! \brief 
 //****************************************************************************************************
class TRENTINO_EXAMPLE_BASICCALCULATORREMOTECLIENT_IMPORT_EXPORT Address{
private:
	std::string* street_;
	Phone* phone_;

public:
// constructor and destructor---------------------------------------
	Address();
	virtual ~Address();
// default instance
   static const Address& default_instance();
// accessors -------------------------------------------------------
 	const std::string& street() const;
 	void set_street(const std::string& value);
	void set_street(const char* value);
	void set_street(const char* value, size_t size);
	Phone* mutable_phone();
	Phone& phone() const;
	bool has_phone() const;
 
 //default instance data
 private:
   static Address* default_instance_;
}; //class Address

 //****************************************************************************************************
 //                                         ComplexNumber
 //****************************************************************************************************
 //! \brief 
 //****************************************************************************************************
class TRENTINO_EXAMPLE_BASICCALCULATORREMOTECLIENT_IMPORT_EXPORT ComplexNumber{
private:
	tint32_t a_;
	tint32_t b_;

public:
// constructor and destructor---------------------------------------
	ComplexNumber();
	virtual ~ComplexNumber();
// default instance
   static const ComplexNumber& default_instance();
// accessors -------------------------------------------------------
	void set_a(tint32_t value);
	tint32_t a() const; 
	void set_b(tint32_t value);
	tint32_t b() const; 
 
 //default instance data
 private:
   static ComplexNumber* default_instance_;
}; //class ComplexNumber

 //****************************************************************************************************
 //                                         Phone
 //****************************************************************************************************
 //! \brief 
 //****************************************************************************************************
class TRENTINO_EXAMPLE_BASICCALCULATORREMOTECLIENT_IMPORT_EXPORT Phone{
private:
	std::string* home_;
	std::string* mobile_;

public:
// constructor and destructor---------------------------------------
	Phone();
	virtual ~Phone();
// default instance
   static const Phone& default_instance();
// accessors -------------------------------------------------------
 	const std::string& home() const;
 	void set_home(const std::string& value);
	void set_home(const char* value);
	void set_home(const char* value, size_t size);
 	const std::string& mobile() const;
 	void set_mobile(const std::string& value);
	void set_mobile(const char* value);
	void set_mobile(const char* value, size_t size);
 
 //default instance data
 private:
   static Phone* default_instance_;
}; //class Phone

 //****************************************************************************************************
 //                                         Person
 //****************************************************************************************************
 //! \brief 
 //****************************************************************************************************
class TRENTINO_EXAMPLE_BASICCALCULATORREMOTECLIENT_IMPORT_EXPORT Person{
private:
	Address* addres_;
	std::string* name_;
	std::string* surname_;
	Person* mother_;

public:
// constructor and destructor---------------------------------------
	Person();
	virtual ~Person();
// default instance
   static const Person& default_instance();
// accessors -------------------------------------------------------
	Address* mutable_addres();
	Address& addres() const;
	bool has_addres() const;
 	const std::string& name() const;
 	void set_name(const std::string& value);
	void set_name(const char* value);
	void set_name(const char* value, size_t size);
 	const std::string& surname() const;
 	void set_surname(const std::string& value);
	void set_surname(const char* value);
	void set_surname(const char* value, size_t size);
	Person* mutable_mother();
	Person& mother() const;
	bool has_mother() const;
 
 //default instance data
 private:
   static Person* default_instance_;
}; //class Person

 //****************************************************************************************************
 //                                         TupleComplexNumber
 //****************************************************************************************************
 //! \brief 
 //****************************************************************************************************
class TRENTINO_EXAMPLE_BASICCALCULATORREMOTECLIENT_IMPORT_EXPORT TupleComplexNumber{
private:
	ComplexNumber* a_;
	ComplexNumber* b_;

public:
// constructor and destructor---------------------------------------
	TupleComplexNumber();
	virtual ~TupleComplexNumber();
// default instance
   static const TupleComplexNumber& default_instance();
// accessors -------------------------------------------------------
	ComplexNumber* mutable_a();
	ComplexNumber& a() const;
	bool has_a() const;
	ComplexNumber* mutable_b();
	ComplexNumber& b() const;
	bool has_b() const;
 
 //default instance data
 private:
   static TupleComplexNumber* default_instance_;
}; //class TupleComplexNumber

 //****************************************************************************************************
 //                                         ValidationException
 //****************************************************************************************************
 //! \brief 
 //****************************************************************************************************
class TRENTINO_EXAMPLE_BASICCALCULATORREMOTECLIENT_IMPORT_EXPORT ValidationException{
private:
	std::string* details_;

public:
// constructor and destructor---------------------------------------
	ValidationException();
	virtual ~ValidationException();
// default instance
   static const ValidationException& default_instance();
// accessors -------------------------------------------------------
 	const std::string& details() const;
 	void set_details(const std::string& value);
	void set_details(const char* value);
	void set_details(const char* value, size_t size);
 
 //default instance data
 private:
   static ValidationException* default_instance_;
}; //class ValidationException

 //****************************************************************************************************
 //                                         BasicCalculator
 //****************************************************************************************************
 //! \brief 
 //****************************************************************************************************
class BasicCalculator{
  //services
public:
	virtual ComplexNumber add (const ComplexNumber& a,const ComplexNumber& b) =0;
	virtual tint32_t addSimple (const tint32_t a,const tint32_t b) =0;
	virtual ComplexNumber divide (const ComplexNumber& a,const ComplexNumber& b) =0;
	virtual void multiply (const ComplexNumber& a,const ComplexNumber& b, ComplexNumber& c) =0;
	virtual ComplexNumber divide2 (const TupleComplexNumber& tuple) =0;
	virtual tuint32_t calculateAge (const Person& person) throw (ValidationException)=0;
  
}; //class BasicCalculator
} //namespace Trentino
} //namespace Example
} //namespace BasicCalculatorRemoteClient

#endif //TrentinoExampleBasicCalculatorRemoteClientBasicCalculatorH