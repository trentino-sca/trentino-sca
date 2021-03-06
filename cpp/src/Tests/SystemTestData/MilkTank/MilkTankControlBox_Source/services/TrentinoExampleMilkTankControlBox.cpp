// Generated by Trentino TDIL CPP interface generator. do not modify

#include "TrentinoExampleMilkTankControlBox.h"

using namespace ::Trentino::Example;

//********************************************************************************************
//!                             Class State
//********************************************************************************************
State::State (){
 //default_instance();
	description_ = NULL;
}

State::~State(){
	delete description_;
}

const State& State::default_instance() {
  if (default_instance_ == NULL) {
   default_instance_ = new State();
  }
  return *default_instance_;
}

State* State::default_instance_ = NULL;


 tint32_t State::state() const{
	return state_;
}

 void State::set_state(tint32_t value){
	state_ = value;
}

	
 const std::string& State::description() const{
	return *description_;
}

 void State::set_description(const std::string& value){
	if (description_ == 0 ) {
    	description_ = new std::string;
  	}
  	description_->assign(value);
}

 void State::set_description(const char* value){
	if (description_ == 0) {
		description_ = new std::string;
  	}
  	description_->assign(value);
}

 void State::set_description(const char* value, size_t size){
	if (description_ == 0) {
    	description_ = new std::string;
  	}
  	description_->assign(reinterpret_cast<const char*>(value), size);
}


	

 tuint32_t State::percentageFinished() const{
	return percentageFinished_;
}

 void State::set_percentageFinished(tuint32_t value){
	percentageFinished_ = value;
}

	

