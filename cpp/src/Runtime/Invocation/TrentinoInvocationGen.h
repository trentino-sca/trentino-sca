// **********************************************************************************
// Trentino - A C++ based lightweight, non-invasive SCA runtime.
// Copyright (C) Siemens AG, 2012
// All Rights Reserved
// http://trentino.sourceforge.net/
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
// **********************************************************************************
#ifndef TrentinoInvocationGenH
#define TrentinoInvocationGenH

//standard
#include <boost/shared_ptr.hpp>
#include "TrentinoInvocation.h"
#include "../RuntimeModel/TrentinoRuntimeModelWireBase.h"


namespace Trentino{

namespace Gen
   {
       template <typename T>
    struct IsVoid{
    enum {isVoid =0};
    };

    template <>
    struct IsVoid<void>{
    enum {isVoid =1};
    };

    template <typename T>
    bool isVoid(){
       return IsVoid<T>::isVoid == 1;
      }

    template <typename T>
    struct IsPointer{
    enum {isPointer =0};
    };
    
     template <typename T>
    struct IsPointer<T*>{
    enum {isPointer =1};
    };
    
    template <typename T>
    bool isPointer(){
     return IsPointer<T>::isPointer ==1;
    }
    
    template <typename T>
    struct IsRef{
    enum {isRef =0};
    };
    
     template <typename T>
    struct IsRef<T&>{
    enum {isRef =1};
    };
    
	template <typename T>
	struct IsConst
	{
	 enum {isConst = 0};
	};
	
	template <typename T>
	struct IsConst<const T>
	{
	 enum {isConst = 1};
	};
	
	template <typename T>
	bool isConst(){
	return IsConst<T>::isConst ==1;
	}

  INVOCATION_IMPORT_EXPORT extern void TRENTINO_CDECL trentino_gen_invoke(void* retVal,
   const std::string& opName,
   Trentino::Invocation::Parameters& params,
   Trentino::RuntimeModel::WireBase* wire);
    
    template<typename T>
    struct invoke_helper
    {
       T ret[1];
       void invoke(const std::string& opName,
       Trentino::Invocation::Parameters& params,
       Trentino::RuntimeModel::WireBase* wire
       ){
          trentino_gen_invoke((void*)ret,opName,params,wire);
          }
       T get()
          {
           return ret[0];
          }
    };

    
    template<typename T>
    struct invoke_helper<const T>
    {
       T ret[1];
       void invoke(const std::string& opName,
       Trentino::Invocation::Parameters& params,
       Trentino::RuntimeModel::WireBase* wire
       ){
          trentino_gen_invoke((void*)ret,opName,params,wire);
          }
        
      (const T) get()
          {
           return ret[0];
          }
    };
    
    template<typename T>
    struct invoke_helper<T&>{
       T ret[1];
       void invoke(const std::string& opName,
       Trentino::Invocation::Parameters& params,
       Trentino::RuntimeModel::WireBase* wire
       ){
          trentino_gen_invoke((void*)ret,opName,params,wire);
          }
        
       T& get()
          {
           return ret[0];
          }
    };
    
    template<typename T>
    struct invoke_helper<const T&>{
       T ret[1];
       void invoke(const std::string& opName,
       Trentino::Invocation::Parameters& params,
       Trentino::RuntimeModel::WireBase* wire
       ){
          trentino_gen_invoke((void*)ret,opName,params,wire);
          }
        
       T& get()
          {
           return ret[0];
          }
    };

    template<>
    struct invoke_helper<void>
    {
       
       void invoke(const std::string& opName,
       Trentino::Invocation::Parameters& params,
       Trentino::RuntimeModel::WireBase* wire
       ){
          trentino_gen_invoke(nullptr,opName,params,wire);
        }
    
       void get()
         {
           //do nothing
         }
    };
         
   template<typename T>
   struct Trentino_Converter
   {
      void convert(void* retValPointer, T& returnedValue)
      {
        T* ret = static_cast<T*>(retValPointer);
        *ret = returnedValue;
      }      
   };

   template<typename T>
   struct Trentino_Converter<T&>
   {
      void convert(void* retValPointer, T& returnedValue)
      {
        T* ret = static_cast<T*>(retValPointer);
        *ret = returnedValue;
      }      
   };
   
   template<typename T>
   struct Trentino_Converter<const T>
   {
       void convert(void* retValPointer,const T& returnedValue)
       {
         T* ret = static_cast<T*>(retValPointer);
         *ret = *const_cast<T*>(&returnedValue);
       }     
    };

   template<typename T>
   struct Trentino_Converter<const T&>
   {
       void convert(void* retValPointer,const T& returnedValue)
       {
         T* ret = static_cast<T*>(retValPointer);
         *ret = *const_cast<T*>(&returnedValue);
       }     
    };  
  
   template<typename ParamType>
   struct GetParam{
     ParamType* get(const Trentino::Invocation::InvocationData& data, int i)
       {
        return (ParamType*)data.parameters()[i];
       }
     };

   template<typename ParamType>
   struct GetParam<ParamType&>{
     ParamType* get(const Trentino::Invocation::InvocationData& data, int i)
       {
        return (ParamType*)data.parameters()[i];
       }
     };

  template<class T>
  struct Trentino_Param_Push_Back
  {
      void push_back(T& elem, Trentino::Invocation::Parameters& params)
       {
         params.push_back(&elem);
       }
  };
  
  template<class T>
  struct Trentino_Param_Push_Back<const T>
  {
      void push_back(const T& elem, Trentino::Invocation::Parameters& params)
      {
         params.push_back(const_cast<T*>(&elem));
      }
   
  };
  
  
  template<class T>
  struct Trentino_Param_Push_Back<const T&>
  {
       void push_back(const T& elem, Trentino::Invocation::Parameters& params)
       {
         params.push_back(const_cast<T*>(&elem));
       }
  };
  
  
    template<typename P0>
    void trentino_gen_internal_push_back(P0& p0, Trentino::Invocation::Parameters& params)
    {
            static Trentino::Gen::Trentino_Param_Push_Back<P0> pb;
            pb.push_back(p0,params);
    }
    
    
   
   template<typename T  >
   void invoke(T* myInstance,void* retValPointer,const Trentino::Invocation::InvocationData& data, void (*call)(T*)){
      call(myInstance);
      (void)retValPointer;
      }
      
    template<typename T,typename R  >
    void invoke(T* myInstance,void* retValPointer,const Trentino::Invocation::InvocationData& data, R (*call)(T*)){
        R res = call(myInstance);
        static Trentino_Converter<R> converter;
        converter.convert(retValPointer,res);
      }  
   
   template<typename T , typename P0 >
   void invoke(T* myInstance,void* retValPointer,const Trentino::Invocation::InvocationData& data, void (*call)(T*, P0)){
      static GetParam<P0> gP0;
      call(myInstance,*gP0.get(data,0));
      (void)retValPointer;
      }
      
    template<typename T,typename R , typename P0 >
    void invoke(T* myInstance,void* retValPointer,const Trentino::Invocation::InvocationData& data, R (*call)(T*, P0)){
      static GetParam<P0> gP0;
        R res = call(myInstance,*gP0.get(data,0));
        static Trentino_Converter<R> converter;
        converter.convert(retValPointer,res);
      }  
   
   template<typename T , typename P0, typename P1 >
   void invoke(T* myInstance,void* retValPointer,const Trentino::Invocation::InvocationData& data, void (*call)(T*, P0, P1)){
      static GetParam<P0> gP0;
      static GetParam<P1> gP1;
      call(myInstance,*gP0.get(data,0),*gP1.get(data,1));
      (void)retValPointer;
      }
      
    template<typename T,typename R , typename P0, typename P1 >
    void invoke(T* myInstance,void* retValPointer,const Trentino::Invocation::InvocationData& data, R (*call)(T*, P0, P1)){
      static GetParam<P0> gP0;
      static GetParam<P1> gP1;
        R res = call(myInstance,*gP0.get(data,0),*gP1.get(data,1));
        static Trentino_Converter<R> converter;
        converter.convert(retValPointer,res);
      }  
   
   template<typename T , typename P0, typename P1, typename P2 >
   void invoke(T* myInstance,void* retValPointer,const Trentino::Invocation::InvocationData& data, void (*call)(T*, P0, P1, P2)){
      static GetParam<P0> gP0;
      static GetParam<P1> gP1;
      static GetParam<P2> gP2;
      call(myInstance,*gP0.get(data,0),*gP1.get(data,1),*gP2.get(data,2));
      (void)retValPointer;
      }
      
    template<typename T,typename R , typename P0, typename P1, typename P2 >
    void invoke(T* myInstance,void* retValPointer,const Trentino::Invocation::InvocationData& data, R (*call)(T*, P0, P1, P2)){
      static GetParam<P0> gP0;
      static GetParam<P1> gP1;
      static GetParam<P2> gP2;
        R res = call(myInstance,*gP0.get(data,0),*gP1.get(data,1),*gP2.get(data,2));
        static Trentino_Converter<R> converter;
        converter.convert(retValPointer,res);
      }  
   
   template<typename T , typename P0, typename P1, typename P2, typename P3 >
   void invoke(T* myInstance,void* retValPointer,const Trentino::Invocation::InvocationData& data, void (*call)(T*, P0, P1, P2, P3)){
      static GetParam<P0> gP0;
      static GetParam<P1> gP1;
      static GetParam<P2> gP2;
      static GetParam<P3> gP3;
      call(myInstance,*gP0.get(data,0),*gP1.get(data,1),*gP2.get(data,2),*gP3.get(data,3));
      (void)retValPointer;
      }
      
    template<typename T,typename R , typename P0, typename P1, typename P2, typename P3 >
    void invoke(T* myInstance,void* retValPointer,const Trentino::Invocation::InvocationData& data, R (*call)(T*, P0, P1, P2, P3)){
      static GetParam<P0> gP0;
      static GetParam<P1> gP1;
      static GetParam<P2> gP2;
      static GetParam<P3> gP3;
        R res = call(myInstance,*gP0.get(data,0),*gP1.get(data,1),*gP2.get(data,2),*gP3.get(data,3));
        static Trentino_Converter<R> converter;
        converter.convert(retValPointer,res);
      }  
   
   template<typename T , typename P0, typename P1, typename P2, typename P3, typename P4 >
   void invoke(T* myInstance,void* retValPointer,const Trentino::Invocation::InvocationData& data, void (*call)(T*, P0, P1, P2, P3, P4)){
      static GetParam<P0> gP0;
      static GetParam<P1> gP1;
      static GetParam<P2> gP2;
      static GetParam<P3> gP3;
      static GetParam<P4> gP4;
      call(myInstance,*gP0.get(data,0),*gP1.get(data,1),*gP2.get(data,2),*gP3.get(data,3),*gP4.get(data,4));
      (void)retValPointer;
      }
      
    template<typename T,typename R , typename P0, typename P1, typename P2, typename P3, typename P4 >
    void invoke(T* myInstance,void* retValPointer,const Trentino::Invocation::InvocationData& data, R (*call)(T*, P0, P1, P2, P3, P4)){
      static GetParam<P0> gP0;
      static GetParam<P1> gP1;
      static GetParam<P2> gP2;
      static GetParam<P3> gP3;
      static GetParam<P4> gP4;
        R res = call(myInstance,*gP0.get(data,0),*gP1.get(data,1),*gP2.get(data,2),*gP3.get(data,3),*gP4.get(data,4));
        static Trentino_Converter<R> converter;
        converter.convert(retValPointer,res);
      }  
   
   template<typename T , typename P0, typename P1, typename P2, typename P3, typename P4, typename P5 >
   void invoke(T* myInstance,void* retValPointer,const Trentino::Invocation::InvocationData& data, void (*call)(T*, P0, P1, P2, P3, P4, P5)){
      static GetParam<P0> gP0;
      static GetParam<P1> gP1;
      static GetParam<P2> gP2;
      static GetParam<P3> gP3;
      static GetParam<P4> gP4;
      static GetParam<P5> gP5;
      call(myInstance,*gP0.get(data,0),*gP1.get(data,1),*gP2.get(data,2),*gP3.get(data,3),*gP4.get(data,4),*gP5.get(data,5));
      (void)retValPointer;
      }
      
    template<typename T,typename R , typename P0, typename P1, typename P2, typename P3, typename P4, typename P5 >
    void invoke(T* myInstance,void* retValPointer,const Trentino::Invocation::InvocationData& data, R (*call)(T*, P0, P1, P2, P3, P4, P5)){
      static GetParam<P0> gP0;
      static GetParam<P1> gP1;
      static GetParam<P2> gP2;
      static GetParam<P3> gP3;
      static GetParam<P4> gP4;
      static GetParam<P5> gP5;
        R res = call(myInstance,*gP0.get(data,0),*gP1.get(data,1),*gP2.get(data,2),*gP3.get(data,3),*gP4.get(data,4),*gP5.get(data,5));
        static Trentino_Converter<R> converter;
        converter.convert(retValPointer,res);
      }  
   
   template<typename T , typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6 >
   void invoke(T* myInstance,void* retValPointer,const Trentino::Invocation::InvocationData& data, void (*call)(T*, P0, P1, P2, P3, P4, P5, P6)){
      static GetParam<P0> gP0;
      static GetParam<P1> gP1;
      static GetParam<P2> gP2;
      static GetParam<P3> gP3;
      static GetParam<P4> gP4;
      static GetParam<P5> gP5;
      static GetParam<P6> gP6;
      call(myInstance,*gP0.get(data,0),*gP1.get(data,1),*gP2.get(data,2),*gP3.get(data,3),*gP4.get(data,4),*gP5.get(data,5),*gP6.get(data,6));
      (void)retValPointer;
      }
      
    template<typename T,typename R , typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6 >
    void invoke(T* myInstance,void* retValPointer,const Trentino::Invocation::InvocationData& data, R (*call)(T*, P0, P1, P2, P3, P4, P5, P6)){
      static GetParam<P0> gP0;
      static GetParam<P1> gP1;
      static GetParam<P2> gP2;
      static GetParam<P3> gP3;
      static GetParam<P4> gP4;
      static GetParam<P5> gP5;
      static GetParam<P6> gP6;
        R res = call(myInstance,*gP0.get(data,0),*gP1.get(data,1),*gP2.get(data,2),*gP3.get(data,3),*gP4.get(data,4),*gP5.get(data,5),*gP6.get(data,6));
        static Trentino_Converter<R> converter;
        converter.convert(retValPointer,res);
      }  
   
   template<typename T , typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7 >
   void invoke(T* myInstance,void* retValPointer,const Trentino::Invocation::InvocationData& data, void (*call)(T*, P0, P1, P2, P3, P4, P5, P6, P7)){
      static GetParam<P0> gP0;
      static GetParam<P1> gP1;
      static GetParam<P2> gP2;
      static GetParam<P3> gP3;
      static GetParam<P4> gP4;
      static GetParam<P5> gP5;
      static GetParam<P6> gP6;
      static GetParam<P7> gP7;
      call(myInstance,*gP0.get(data,0),*gP1.get(data,1),*gP2.get(data,2),*gP3.get(data,3),*gP4.get(data,4),*gP5.get(data,5),*gP6.get(data,6),*gP7.get(data,7));
      (void)retValPointer;
      }
      
    template<typename T,typename R , typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7 >
    void invoke(T* myInstance,void* retValPointer,const Trentino::Invocation::InvocationData& data, R (*call)(T*, P0, P1, P2, P3, P4, P5, P6, P7)){
      static GetParam<P0> gP0;
      static GetParam<P1> gP1;
      static GetParam<P2> gP2;
      static GetParam<P3> gP3;
      static GetParam<P4> gP4;
      static GetParam<P5> gP5;
      static GetParam<P6> gP6;
      static GetParam<P7> gP7;
        R res = call(myInstance,*gP0.get(data,0),*gP1.get(data,1),*gP2.get(data,2),*gP3.get(data,3),*gP4.get(data,4),*gP5.get(data,5),*gP6.get(data,6),*gP7.get(data,7));
        static Trentino_Converter<R> converter;
        converter.convert(retValPointer,res);
      }  
   
   template<typename T , typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8 >
   void invoke(T* myInstance,void* retValPointer,const Trentino::Invocation::InvocationData& data, void (*call)(T*, P0, P1, P2, P3, P4, P5, P6, P7, P8)){
      static GetParam<P0> gP0;
      static GetParam<P1> gP1;
      static GetParam<P2> gP2;
      static GetParam<P3> gP3;
      static GetParam<P4> gP4;
      static GetParam<P5> gP5;
      static GetParam<P6> gP6;
      static GetParam<P7> gP7;
      static GetParam<P8> gP8;
      call(myInstance,*gP0.get(data,0),*gP1.get(data,1),*gP2.get(data,2),*gP3.get(data,3),*gP4.get(data,4),*gP5.get(data,5),*gP6.get(data,6),*gP7.get(data,7),*gP8.get(data,8));
      (void)retValPointer;
      }
      
    template<typename T,typename R , typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8 >
    void invoke(T* myInstance,void* retValPointer,const Trentino::Invocation::InvocationData& data, R (*call)(T*, P0, P1, P2, P3, P4, P5, P6, P7, P8)){
      static GetParam<P0> gP0;
      static GetParam<P1> gP1;
      static GetParam<P2> gP2;
      static GetParam<P3> gP3;
      static GetParam<P4> gP4;
      static GetParam<P5> gP5;
      static GetParam<P6> gP6;
      static GetParam<P7> gP7;
      static GetParam<P8> gP8;
        R res = call(myInstance,*gP0.get(data,0),*gP1.get(data,1),*gP2.get(data,2),*gP3.get(data,3),*gP4.get(data,4),*gP5.get(data,5),*gP6.get(data,6),*gP7.get(data,7),*gP8.get(data,8));
        static Trentino_Converter<R> converter;
        converter.convert(retValPointer,res);
      }
   } //namespace Gen
} //namespace Trentino

#endif //TrentinoInvocationGenH
