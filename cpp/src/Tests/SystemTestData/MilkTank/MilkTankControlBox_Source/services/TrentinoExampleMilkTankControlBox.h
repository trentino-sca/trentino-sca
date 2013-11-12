// Generated by Trentino TDIL CPP interface generator. do not modify

#ifndef TrentinoExampleMilkTankControlBoxH
#define TrentinoExampleMilkTankControlBoxH

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

//forward declaration
class State;


 //****************************************************************************************************
 //                                         State
 //****************************************************************************************************
 //! \brief 
 //****************************************************************************************************
class TRENTINO_EXAMPLE_IMPORT_EXPORT State{
private:
	tint32_t state_;
	std::string* description_;
	tuint32_t percentageFinished_;

public:
// constructor and destructor---------------------------------------
	State();
	virtual ~State();
// default instance
   static const State& default_instance();
// accessors -------------------------------------------------------
	void set_state(tint32_t value);
	tint32_t state() const; 
 	const std::string& description() const;
 	void set_description(const std::string& value);
	void set_description(const char* value);
	void set_description(const char* value, size_t size);
	void set_percentageFinished(tuint32_t value);
	tuint32_t percentageFinished() const; 
 
 //default instance data
 private:
   static State* default_instance_;
}; //class State

 //****************************************************************************************************
 //                                         MilkTankControlBox
 //****************************************************************************************************
 //! \brief 
 //****************************************************************************************************
class MilkTankControlBox{
  //services
public:
	virtual void setMaxTemperatureThreshold (const tint32_t threshold) =0;
	virtual void setMinTemperatureThreshold (const tint32_t threshold) =0;
	virtual void openAirVentilation (const tuint32_t percentage) =0;
	virtual void startCleaning () =0;
	virtual State getCleaningState () =0;
  
}; //class MilkTankControlBox
} //namespace Trentino
} //namespace Example

#endif //TrentinoExampleMilkTankControlBoxH