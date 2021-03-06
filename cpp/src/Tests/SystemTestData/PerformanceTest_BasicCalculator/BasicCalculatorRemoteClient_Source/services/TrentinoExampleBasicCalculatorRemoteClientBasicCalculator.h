// Generated by Trentino TDIL CPP interface generator. do not modify

#ifndef TrentinoExampleBasicCalculatorRemoteClientBasicCalculatorH
#define TrentinoExampleBasicCalculatorRemoteClientBasicCalculatorH

#include "BasicCalculatorGlobal.h"

#include <boost/cstdint.hpp>
#include <string>

typedef  boost::int32_t  tint32_t;
typedef  boost::uint32_t  tuint32_t;
typedef  boost::int64_t  tint64_t;
typedef  boost::uint64_t  tuint64_t;

namespace Trentino{
namespace Example{
namespace BasicCalculatorRemoteClient{


	//****************************************************************************************************
	//                                         BasicCalculator
	//****************************************************************************************************
	//! \brief 
	//****************************************************************************************************
	class  BasicCalculator{

	public:
	//forward declaration Phone
	class Phone;
	//forward declaration Address
	class Address;
	//forward declaration ComplexNumber
	class ComplexNumber;
	//forward declaration Person
	class Person;
	//forward declaration TupleComplexNumber
	class TupleComplexNumber;
	//forward declaration ValidationException
	class ValidationException;

	public:
	
		//****************************************************************************************************
		//                                         Phone
		//****************************************************************************************************
		//! \brief 
		//****************************************************************************************************
		class  Phone{



		public:
		// constructor and destructor---------------------------------------
			Phone();
			~Phone();

		public:
		// accessors -------------------------------------------------------
			const std::string& home() const;
			void set_home(const std::string& value);
			void set_home(const char* value);
			const std::string& mobile() const;
			void set_mobile(const std::string& value);
			void set_mobile(const char* value);
 
		private:
		//private fields
			std::string home_;
			std::string mobile_;

		}; //class Phone
 
		//****************************************************************************************************
		//                                         Address
		//****************************************************************************************************
		//! \brief 
		//****************************************************************************************************
		class  Address{



		public:
		// constructor and destructor---------------------------------------
			Address();
			~Address();

		public:
		// accessors -------------------------------------------------------
			const std::string& street() const;
			void set_street(const std::string& value);
			void set_street(const char* value);
			void set_phone(Trentino::Example::BasicCalculatorRemoteClient::BasicCalculator::Phone& value);
			const Trentino::Example::BasicCalculatorRemoteClient::BasicCalculator::Phone& phone() const;
		   Trentino::Example::BasicCalculatorRemoteClient::BasicCalculator::Phone& mutable_phone();
			bool has_phone() const;
 
		private:
		//private fields
			std::string street_;
			Trentino::Example::BasicCalculatorRemoteClient::BasicCalculator::Phone phone_;

		}; //class Address
 
		//****************************************************************************************************
		//                                         ComplexNumber
		//****************************************************************************************************
		//! \brief 
		//****************************************************************************************************
		class  ComplexNumber{



		public:
		// constructor and destructor---------------------------------------
			ComplexNumber();
			~ComplexNumber();

		public:
		// accessors -------------------------------------------------------
			void set_a(tint32_t value);
			tint32_t a() const; 
			void set_b(tint32_t value);
			tint32_t b() const; 
 
		private:
		//private fields
			tint32_t a_;
			tint32_t b_;

		}; //class ComplexNumber
 
		//****************************************************************************************************
		//                                         Person
		//****************************************************************************************************
		//! \brief 
		//****************************************************************************************************
		class  Person{



		public:
		// constructor and destructor---------------------------------------
			Person();
			~Person();

		public:
		// accessors -------------------------------------------------------
			void set_addres(Trentino::Example::BasicCalculatorRemoteClient::BasicCalculator::Address& value);
			const Trentino::Example::BasicCalculatorRemoteClient::BasicCalculator::Address& addres() const;
		   Trentino::Example::BasicCalculatorRemoteClient::BasicCalculator::Address& mutable_addres();
			bool has_addres() const;
			const std::string& name() const;
			void set_name(const std::string& value);
			void set_name(const char* value);
			const std::string& surname() const;
			void set_surname(const std::string& value);
			void set_surname(const char* value);
 
		private:
		//private fields
			Trentino::Example::BasicCalculatorRemoteClient::BasicCalculator::Address addres_;
			std::string name_;
			std::string surname_;

		}; //class Person
 
		//****************************************************************************************************
		//                                         TupleComplexNumber
		//****************************************************************************************************
		//! \brief 
		//****************************************************************************************************
		class  TupleComplexNumber{



		public:
		// constructor and destructor---------------------------------------
			TupleComplexNumber();
			~TupleComplexNumber();

		public:
		// accessors -------------------------------------------------------
			void set_a(Trentino::Example::BasicCalculatorRemoteClient::BasicCalculator::ComplexNumber& value);
			const Trentino::Example::BasicCalculatorRemoteClient::BasicCalculator::ComplexNumber& a() const;
		   Trentino::Example::BasicCalculatorRemoteClient::BasicCalculator::ComplexNumber& mutable_a();
			bool has_a() const;
			void set_b(Trentino::Example::BasicCalculatorRemoteClient::BasicCalculator::ComplexNumber& value);
			const Trentino::Example::BasicCalculatorRemoteClient::BasicCalculator::ComplexNumber& b() const;
		   Trentino::Example::BasicCalculatorRemoteClient::BasicCalculator::ComplexNumber& mutable_b();
			bool has_b() const;
 
		private:
		//private fields
			Trentino::Example::BasicCalculatorRemoteClient::BasicCalculator::ComplexNumber a_;
			Trentino::Example::BasicCalculatorRemoteClient::BasicCalculator::ComplexNumber b_;

		}; //class TupleComplexNumber
 
		//****************************************************************************************************
		//                                         ValidationException
		//****************************************************************************************************
		//! \brief 
		//****************************************************************************************************
		class  ValidationException{



		public:
		// constructor and destructor---------------------------------------
			ValidationException();
			~ValidationException();

		public:
		// accessors -------------------------------------------------------
			const std::string& details() const;
			void set_details(const std::string& value);
			void set_details(const char* value);
 
		private:
		//private fields
			std::string details_;

		}; //class ValidationException
 
  //services
	public:
	virtual Trentino::Example::BasicCalculatorRemoteClient::BasicCalculator::ComplexNumber  add (const Trentino::Example::BasicCalculatorRemoteClient::BasicCalculator::ComplexNumber& a,const Trentino::Example::BasicCalculatorRemoteClient::BasicCalculator::ComplexNumber& b) =0;
	virtual tint32_t  addSimple (const tint32_t a,const tint32_t b) =0;
	virtual Trentino::Example::BasicCalculatorRemoteClient::BasicCalculator::ComplexNumber  divide (const Trentino::Example::BasicCalculatorRemoteClient::BasicCalculator::ComplexNumber& a,const Trentino::Example::BasicCalculatorRemoteClient::BasicCalculator::ComplexNumber& b) =0;
	virtual void  multiply (const Trentino::Example::BasicCalculatorRemoteClient::BasicCalculator::ComplexNumber& a,const Trentino::Example::BasicCalculatorRemoteClient::BasicCalculator::ComplexNumber& b, Trentino::Example::BasicCalculatorRemoteClient::BasicCalculator::ComplexNumber& c) =0;
	virtual Trentino::Example::BasicCalculatorRemoteClient::BasicCalculator::ComplexNumber  divide2 (const Trentino::Example::BasicCalculatorRemoteClient::BasicCalculator::TupleComplexNumber& tuple) =0;
	virtual tuint32_t  calculateAge (const Trentino::Example::BasicCalculatorRemoteClient::BasicCalculator::Person& person) throw (Trentino::Example::BasicCalculatorRemoteClient::BasicCalculator::ValidationException)=0;
  
	}; //class BasicCalculator



//********************************************************************************************
//!                             Class Phone
//********************************************************************************************
inline  Trentino::Example::BasicCalculatorRemoteClient::BasicCalculator::Phone::Phone (){ 
}

inline  Trentino::Example::BasicCalculatorRemoteClient::BasicCalculator::Phone::~Phone(){
}
inline  const std::string& Trentino::Example::BasicCalculatorRemoteClient::BasicCalculator::Phone::home() const{
	return home_;
}

inline  void Trentino::Example::BasicCalculatorRemoteClient::BasicCalculator::Phone::set_home(const std::string& value){
  	home_=value;
}

inline  void Trentino::Example::BasicCalculatorRemoteClient::BasicCalculator::Phone::set_home(const char* value){
  	home_= std::string(value);
}

	
inline  const std::string& Trentino::Example::BasicCalculatorRemoteClient::BasicCalculator::Phone::mobile() const{
	return mobile_;
}

inline  void Trentino::Example::BasicCalculatorRemoteClient::BasicCalculator::Phone::set_mobile(const std::string& value){
  	mobile_=value;
}

inline  void Trentino::Example::BasicCalculatorRemoteClient::BasicCalculator::Phone::set_mobile(const char* value){
  	mobile_= std::string(value);
}

	


//********************************************************************************************
//!                             Class Address
//********************************************************************************************
inline  Trentino::Example::BasicCalculatorRemoteClient::BasicCalculator::Address::Address (){ 
}

inline  Trentino::Example::BasicCalculatorRemoteClient::BasicCalculator::Address::~Address(){
}
inline  const std::string& Trentino::Example::BasicCalculatorRemoteClient::BasicCalculator::Address::street() const{
	return street_;
}

inline  void Trentino::Example::BasicCalculatorRemoteClient::BasicCalculator::Address::set_street(const std::string& value){
  	street_=value;
}

inline  void Trentino::Example::BasicCalculatorRemoteClient::BasicCalculator::Address::set_street(const char* value){
  	street_= std::string(value);
}

	

inline  bool Trentino::Example::BasicCalculatorRemoteClient::BasicCalculator::Address::has_phone() const{
        return true;
}


inline  void Trentino::Example::BasicCalculatorRemoteClient::BasicCalculator::Address::set_phone(Trentino::Example::BasicCalculatorRemoteClient::BasicCalculator::Phone& value){
phone_ = value;
}

inline   const Trentino::Example::BasicCalculatorRemoteClient::BasicCalculator::Phone& Trentino::Example::BasicCalculatorRemoteClient::BasicCalculator::Address::phone() const {
		return phone_;
}

inline   Trentino::Example::BasicCalculatorRemoteClient::BasicCalculator::Phone& Trentino::Example::BasicCalculatorRemoteClient::BasicCalculator::Address::mutable_phone(){
  return phone_;
}
	


//********************************************************************************************
//!                             Class ComplexNumber
//********************************************************************************************
inline  Trentino::Example::BasicCalculatorRemoteClient::BasicCalculator::ComplexNumber::ComplexNumber (){ 
}

inline  Trentino::Example::BasicCalculatorRemoteClient::BasicCalculator::ComplexNumber::~ComplexNumber(){
}

inline  tint32_t Trentino::Example::BasicCalculatorRemoteClient::BasicCalculator::ComplexNumber::a() const{
	return a_;
}

inline  void Trentino::Example::BasicCalculatorRemoteClient::BasicCalculator::ComplexNumber::set_a(tint32_t value){
	a_ = value;
}
	

inline  tint32_t Trentino::Example::BasicCalculatorRemoteClient::BasicCalculator::ComplexNumber::b() const{
	return b_;
}

inline  void Trentino::Example::BasicCalculatorRemoteClient::BasicCalculator::ComplexNumber::set_b(tint32_t value){
	b_ = value;
}
	


//********************************************************************************************
//!                             Class Person
//********************************************************************************************
inline  Trentino::Example::BasicCalculatorRemoteClient::BasicCalculator::Person::Person (){ 
}

inline  Trentino::Example::BasicCalculatorRemoteClient::BasicCalculator::Person::~Person(){
}

inline  bool Trentino::Example::BasicCalculatorRemoteClient::BasicCalculator::Person::has_addres() const{
        return true;
}


inline  void Trentino::Example::BasicCalculatorRemoteClient::BasicCalculator::Person::set_addres(Trentino::Example::BasicCalculatorRemoteClient::BasicCalculator::Address& value){
addres_ = value;
}

inline   const Trentino::Example::BasicCalculatorRemoteClient::BasicCalculator::Address& Trentino::Example::BasicCalculatorRemoteClient::BasicCalculator::Person::addres() const {
		return addres_;
}

inline   Trentino::Example::BasicCalculatorRemoteClient::BasicCalculator::Address& Trentino::Example::BasicCalculatorRemoteClient::BasicCalculator::Person::mutable_addres(){
  return addres_;
}
	
inline  const std::string& Trentino::Example::BasicCalculatorRemoteClient::BasicCalculator::Person::name() const{
	return name_;
}

inline  void Trentino::Example::BasicCalculatorRemoteClient::BasicCalculator::Person::set_name(const std::string& value){
  	name_=value;
}

inline  void Trentino::Example::BasicCalculatorRemoteClient::BasicCalculator::Person::set_name(const char* value){
  	name_= std::string(value);
}

	
inline  const std::string& Trentino::Example::BasicCalculatorRemoteClient::BasicCalculator::Person::surname() const{
	return surname_;
}

inline  void Trentino::Example::BasicCalculatorRemoteClient::BasicCalculator::Person::set_surname(const std::string& value){
  	surname_=value;
}

inline  void Trentino::Example::BasicCalculatorRemoteClient::BasicCalculator::Person::set_surname(const char* value){
  	surname_= std::string(value);
}

	


//********************************************************************************************
//!                             Class TupleComplexNumber
//********************************************************************************************
inline  Trentino::Example::BasicCalculatorRemoteClient::BasicCalculator::TupleComplexNumber::TupleComplexNumber (){ 
}

inline  Trentino::Example::BasicCalculatorRemoteClient::BasicCalculator::TupleComplexNumber::~TupleComplexNumber(){
}

inline  bool Trentino::Example::BasicCalculatorRemoteClient::BasicCalculator::TupleComplexNumber::has_a() const{
        return true;
}


inline  void Trentino::Example::BasicCalculatorRemoteClient::BasicCalculator::TupleComplexNumber::set_a(Trentino::Example::BasicCalculatorRemoteClient::BasicCalculator::ComplexNumber& value){
a_ = value;
}

inline   const Trentino::Example::BasicCalculatorRemoteClient::BasicCalculator::ComplexNumber& Trentino::Example::BasicCalculatorRemoteClient::BasicCalculator::TupleComplexNumber::a() const {
		return a_;
}

inline   Trentino::Example::BasicCalculatorRemoteClient::BasicCalculator::ComplexNumber& Trentino::Example::BasicCalculatorRemoteClient::BasicCalculator::TupleComplexNumber::mutable_a(){
  return a_;
}
	

inline  bool Trentino::Example::BasicCalculatorRemoteClient::BasicCalculator::TupleComplexNumber::has_b() const{
        return true;
}


inline  void Trentino::Example::BasicCalculatorRemoteClient::BasicCalculator::TupleComplexNumber::set_b(Trentino::Example::BasicCalculatorRemoteClient::BasicCalculator::ComplexNumber& value){
b_ = value;
}

inline   const Trentino::Example::BasicCalculatorRemoteClient::BasicCalculator::ComplexNumber& Trentino::Example::BasicCalculatorRemoteClient::BasicCalculator::TupleComplexNumber::b() const {
		return b_;
}

inline   Trentino::Example::BasicCalculatorRemoteClient::BasicCalculator::ComplexNumber& Trentino::Example::BasicCalculatorRemoteClient::BasicCalculator::TupleComplexNumber::mutable_b(){
  return b_;
}
	


//********************************************************************************************
//!                             Class ValidationException
//********************************************************************************************
inline  Trentino::Example::BasicCalculatorRemoteClient::BasicCalculator::ValidationException::ValidationException (){ 
}

inline  Trentino::Example::BasicCalculatorRemoteClient::BasicCalculator::ValidationException::~ValidationException(){
}
inline  const std::string& Trentino::Example::BasicCalculatorRemoteClient::BasicCalculator::ValidationException::details() const{
	return details_;
}

inline  void Trentino::Example::BasicCalculatorRemoteClient::BasicCalculator::ValidationException::set_details(const std::string& value){
  	details_=value;
}

inline  void Trentino::Example::BasicCalculatorRemoteClient::BasicCalculator::ValidationException::set_details(const char* value){
  	details_= std::string(value);
}

	


} //namespace Trentino
} //namespace Example
} //namespace BasicCalculatorRemoteClient



#endif //TrentinoExampleBasicCalculatorRemoteClientBasicCalculatorH