// Generated by Trentino TDIL CPP interface generator. do not modify

#include "TrentinoExampleBasicCalculatorRemoteClientBasicCalculator.h"

using namespace ::Trentino::Example::BasicCalculatorRemoteClient;

//********************************************************************************************
//!                             Class Address
//********************************************************************************************
Address::Address (){
 //default_instance();
	street_ = NULL;
	phone_ = NULL;
}

Address::~Address(){
	delete street_;
	delete phone_;
}

const Address& Address::default_instance() {
  if (default_instance_ == NULL) {
   default_instance_ = new Address();
  }
  return *default_instance_;
}

Address* Address::default_instance_ = NULL;

 const std::string& Address::street() const{
	return *street_;
}

 void Address::set_street(const std::string& value){
	if (street_ == 0 ) {
    	street_ = new std::string;
  	}
  	street_->assign(value);
}

 void Address::set_street(const char* value){
	if (street_ == 0) {
		street_ = new std::string;
  	}
  	street_->assign(value);
}

 void Address::set_street(const char* value, size_t size){
	if (street_ == 0) {
    	street_ = new std::string;
  	}
  	street_->assign(reinterpret_cast<const char*>(value), size);
}


	


 bool Address::has_phone() const{
	if (phone_ == NULL ) {
    	return false;
  	}
  	return true;
}

 Phone* Address::mutable_phone(){
	if (phone_==NULL)
		phone_ = new Phone;
	return phone_;
}

 Phone& Address::phone() const{
 	if (phone_ != NULL)
		return *phone_;

	if ( default_instance_ == NULL)
		default_instance();
	return *default_instance_->phone_;
  //return phone_ != NULL ? *phone_: *default_instance_->phone_;
}
	

//********************************************************************************************
//!                             Class ComplexNumber
//********************************************************************************************
ComplexNumber::ComplexNumber (){
 //default_instance();
}

ComplexNumber::~ComplexNumber(){
}

const ComplexNumber& ComplexNumber::default_instance() {
  if (default_instance_ == NULL) {
   default_instance_ = new ComplexNumber();
  }
  return *default_instance_;
}

ComplexNumber* ComplexNumber::default_instance_ = NULL;


 tint32_t ComplexNumber::a() const{
	return a_;
}

 void ComplexNumber::set_a(tint32_t value){
	a_ = value;
}

	

 tint32_t ComplexNumber::b() const{
	return b_;
}

 void ComplexNumber::set_b(tint32_t value){
	b_ = value;
}

	

//********************************************************************************************
//!                             Class Phone
//********************************************************************************************
Phone::Phone (){
 //default_instance();
	home_ = NULL;
	mobile_ = NULL;
}

Phone::~Phone(){
	delete home_;
	delete mobile_;
}

const Phone& Phone::default_instance() {
  if (default_instance_ == NULL) {
   default_instance_ = new Phone();
  }
  return *default_instance_;
}

Phone* Phone::default_instance_ = NULL;

 const std::string& Phone::home() const{
	return *home_;
}

 void Phone::set_home(const std::string& value){
	if (home_ == 0 ) {
    	home_ = new std::string;
  	}
  	home_->assign(value);
}

 void Phone::set_home(const char* value){
	if (home_ == 0) {
		home_ = new std::string;
  	}
  	home_->assign(value);
}

 void Phone::set_home(const char* value, size_t size){
	if (home_ == 0) {
    	home_ = new std::string;
  	}
  	home_->assign(reinterpret_cast<const char*>(value), size);
}


	
 const std::string& Phone::mobile() const{
	return *mobile_;
}

 void Phone::set_mobile(const std::string& value){
	if (mobile_ == 0 ) {
    	mobile_ = new std::string;
  	}
  	mobile_->assign(value);
}

 void Phone::set_mobile(const char* value){
	if (mobile_ == 0) {
		mobile_ = new std::string;
  	}
  	mobile_->assign(value);
}

 void Phone::set_mobile(const char* value, size_t size){
	if (mobile_ == 0) {
    	mobile_ = new std::string;
  	}
  	mobile_->assign(reinterpret_cast<const char*>(value), size);
}


	

//********************************************************************************************
//!                             Class Person
//********************************************************************************************
Person::Person (){
 //default_instance();
	addres_ = NULL;
	name_ = NULL;
	surname_ = NULL;
	mother_ = NULL;
}

Person::~Person(){
	delete addres_;
	delete name_;
	delete surname_;
	delete mother_;
}

const Person& Person::default_instance() {
  if (default_instance_ == NULL) {
   default_instance_ = new Person();
  }
  return *default_instance_;
}

Person* Person::default_instance_ = NULL;



 bool Person::has_addres() const{
	if (addres_ == NULL ) {
    	return false;
  	}
  	return true;
}

 Address* Person::mutable_addres(){
	if (addres_==NULL)
		addres_ = new Address;
	return addres_;
}

 Address& Person::addres() const{
 	if (addres_ != NULL)
		return *addres_;

	if ( default_instance_ == NULL)
		default_instance();
	return *default_instance_->addres_;
  //return addres_ != NULL ? *addres_: *default_instance_->addres_;
}
	
 const std::string& Person::name() const{
	return *name_;
}

 void Person::set_name(const std::string& value){
	if (name_ == 0 ) {
    	name_ = new std::string;
  	}
  	name_->assign(value);
}

 void Person::set_name(const char* value){
	if (name_ == 0) {
		name_ = new std::string;
  	}
  	name_->assign(value);
}

 void Person::set_name(const char* value, size_t size){
	if (name_ == 0) {
    	name_ = new std::string;
  	}
  	name_->assign(reinterpret_cast<const char*>(value), size);
}


	
 const std::string& Person::surname() const{
	return *surname_;
}

 void Person::set_surname(const std::string& value){
	if (surname_ == 0 ) {
    	surname_ = new std::string;
  	}
  	surname_->assign(value);
}

 void Person::set_surname(const char* value){
	if (surname_ == 0) {
		surname_ = new std::string;
  	}
  	surname_->assign(value);
}

 void Person::set_surname(const char* value, size_t size){
	if (surname_ == 0) {
    	surname_ = new std::string;
  	}
  	surname_->assign(reinterpret_cast<const char*>(value), size);
}


	


 bool Person::has_mother() const{
	if (mother_ == NULL ) {
    	return false;
  	}
  	return true;
}

 Person* Person::mutable_mother(){
	if (mother_==NULL)
		mother_ = new Person;
	return mother_;
}

 Person& Person::mother() const{
 	if (mother_ != NULL)
		return *mother_;

	if ( default_instance_ == NULL)
		default_instance();
	return *default_instance_->mother_;
  //return mother_ != NULL ? *mother_: *default_instance_->mother_;
}
	

//********************************************************************************************
//!                             Class TupleComplexNumber
//********************************************************************************************
TupleComplexNumber::TupleComplexNumber (){
 //default_instance();
	a_ = NULL;
	b_ = NULL;
}

TupleComplexNumber::~TupleComplexNumber(){
	delete a_;
	delete b_;
}

const TupleComplexNumber& TupleComplexNumber::default_instance() {
  if (default_instance_ == NULL) {
   default_instance_ = new TupleComplexNumber();
  }
  return *default_instance_;
}

TupleComplexNumber* TupleComplexNumber::default_instance_ = NULL;



 bool TupleComplexNumber::has_a() const{
	if (a_ == NULL ) {
    	return false;
  	}
  	return true;
}

 ComplexNumber* TupleComplexNumber::mutable_a(){
	if (a_==NULL)
		a_ = new ComplexNumber;
	return a_;
}

 ComplexNumber& TupleComplexNumber::a() const{
 	if (a_ != NULL)
		return *a_;

	if ( default_instance_ == NULL)
		default_instance();
	return *default_instance_->a_;
  //return a_ != NULL ? *a_: *default_instance_->a_;
}
	


 bool TupleComplexNumber::has_b() const{
	if (b_ == NULL ) {
    	return false;
  	}
  	return true;
}

 ComplexNumber* TupleComplexNumber::mutable_b(){
	if (b_==NULL)
		b_ = new ComplexNumber;
	return b_;
}

 ComplexNumber& TupleComplexNumber::b() const{
 	if (b_ != NULL)
		return *b_;

	if ( default_instance_ == NULL)
		default_instance();
	return *default_instance_->b_;
  //return b_ != NULL ? *b_: *default_instance_->b_;
}
	

//********************************************************************************************
//!                             Class ValidationException
//********************************************************************************************
ValidationException::ValidationException (){
 //default_instance();
	details_ = NULL;
}

ValidationException::~ValidationException(){
	delete details_;
}

const ValidationException& ValidationException::default_instance() {
  if (default_instance_ == NULL) {
   default_instance_ = new ValidationException();
  }
  return *default_instance_;
}

ValidationException* ValidationException::default_instance_ = NULL;

 const std::string& ValidationException::details() const{
	return *details_;
}

 void ValidationException::set_details(const std::string& value){
	if (details_ == 0 ) {
    	details_ = new std::string;
  	}
  	details_->assign(value);
}

 void ValidationException::set_details(const char* value){
	if (details_ == 0) {
		details_ = new std::string;
  	}
  	details_->assign(value);
}

 void ValidationException::set_details(const char* value, size_t size){
	if (details_ == 0) {
    	details_ = new std::string;
  	}
  	details_->assign(reinterpret_cast<const char*>(value), size);
}


	

