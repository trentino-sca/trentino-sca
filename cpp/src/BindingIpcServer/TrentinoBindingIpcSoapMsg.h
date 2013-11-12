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

#ifndef TrentinoBindingIpcSoapMsgH
#define TrentinoBindingIpcSoapMsgH

#include "TrentinoBindingIpcMemoryMapObj.h"
#include <boost/interprocess/managed_shared_memory.hpp> 
#include <boost/interprocess/offset_ptr.hpp>
#include <boost/interprocess/containers/string.hpp> 
#include <boost/interprocess/allocators/allocator.hpp>





using namespace std;
namespace Trentino{
namespace Binding{
namespace IPC
{
   class IpcSoapMsg;
   typedef boost::shared_ptr<IpcSoapMsg> SoapMsgPtr;
   typedef boost::interprocess::allocator<char, boost::interprocess::managed_shared_memory::segment_manager> CharAllocator; 
   typedef boost::interprocess::allocator<void, boost::interprocess::managed_shared_memory::segment_manager>  void_allocator;

   typedef boost::interprocess::basic_string<char, std::char_traits<char>, CharAllocator> my_string;
   typedef boost::interprocess::string shared_string;

   //**************************************************************************************************
   //                                IpcSoapAddressing
   //**************************************************************************************************
   //! \brief  
   //**************************************************************************************************
   class IpcSoapAddressing
   {

      //constructor
      public:
      IpcSoapAddressing(boost::interprocess::managed_shared_memory& shm,
         std::string actionExtended, 
         std::string from,
         std::string fullDestination)
         :mCharAllocator(shm.get_segment_manager()),
         mShm(shm),
         mVoidAllocator(shm.get_segment_manager()),
         mAction(actionExtended.c_str(),mCharAllocator),
         mFrom(from.c_str(),mCharAllocator),
         mTo(fullDestination.c_str(), mCharAllocator)
      {
         //mActionPtr = mShm.find_or_construct<my_string>("mActionPtr")(actionExtended.c_str(), mShm.get_segment_manager());
         //mFromPtr = mShm.find_or_construct<my_string>("mFromPtr")(from.c_str(), mShm.get_segment_manager());
         //mToPtr = mShm.find_or_construct<my_string>("mToPtr")(fullDestination.c_str(), mShm.get_segment_manager());
      }
      virtual ~IpcSoapAddressing()
      {
         //mShm.destroy<my_string>("mActionPtr");
         //mShm.destroy<my_string>("mFromPtr");
         //mShm.destroy<my_string>("mToPtr");
      }

      private:
      IpcSoapAddressing operator=(const IpcSoapAddressing& );

    public:
      //std::string to() const
      //{
      //   return mTo.c_str();
      //}
      //std::string from() const
      //{
      //   return mFrom.c_str();
      //}
      //std::string action() const 
      //{
      //   return mAction.c_str();
      //}

      //void setAction(const char* action)
      //{
      //   //mAction = action;
      //   mAction.assign(action,::strlen(action));
      //}

      //void set_to(const char* to) 
      //{
      //   mTo = to;
      //}

      //void set_to(string to) 
      //{
      //   mTo = to.c_str();
      //}

      //void set_from(string from) 
      //{
      //   mFrom = from.c_str();
      //}
      
      bool hasAction() const
      {
         return (mAction.length() == 0);
      }
      
      bool hasFrom() const
      {
         return (mFrom.length() == 0);
      }
      
      bool hasTo() const
      {
         return (mTo.length() == 0);
      }

   private:
      boost::interprocess::managed_shared_memory& mShm;
      CharAllocator mCharAllocator;
      void_allocator mVoidAllocator;
   //services
   public:
      my_string mFrom;
      my_string mTo;
      my_string mAction;
   };

   //**************************************************************************************************
   //                                IpcSoapHeader
   //**************************************************************************************************
   //! \brief  
   //**************************************************************************************************
   class IpcSoapHeader
   {
      public:
         IpcSoapHeader(boost::interprocess::managed_shared_memory& shm, std::string actionExtended, 
            std::string from,
            std::string fullDestination)
            :mAddressing(shm,actionExtended, from, fullDestination)
      {

      }
      
      const IpcSoapAddressing& addressing() const
      {
         return mAddressing;
      }

      IpcSoapAddressing& addressing_mutable()
      {
         return mAddressing;
      }
   private:
      IpcSoapAddressing mAddressing;
   };

   //**************************************************************************************************
   //                                IpcSoapBody
   //**************************************************************************************************
   //! \brief  
   //**************************************************************************************************
   class IpcSoapBody
   {
   public:
      void setMemMappedObj(IpcMemoryMapObj* memMappedObj)
      {
         mMemoryMappedObj =  memMappedObj;
      }
      void setMemMappedObj2(IpcMemoryMapObj* memMappedObj)
      {
         mMemoryMappedObj2 =  memMappedObj;
      }
      //IpcMemoryMapObj* getMemMappedObj()
      //{
      //   return mMemoryMappedObj;
      //}
   public:
      //IpcMemoryMapObj* mMemoryMappedObj;
      boost::interprocess::offset_ptr<IpcMemoryMapObj> mMemoryMappedObj;
      boost::interprocess::offset_ptr<IpcMemoryMapObj> mMemoryMappedObj2;
   };

   //**************************************************************************************************
   //                                IpcSoapEnvelope
   //**************************************************************************************************
   //! \brief  
   //**************************************************************************************************
   class IpcSoapEnvelope
   {
   public:
      IpcSoapEnvelope(boost::interprocess::managed_shared_memory& shm, 
         std::string actionExtended, 
         std::string from,
         std::string fullDestination)
         :mHeader(shm,actionExtended, from, fullDestination)
      {

      }

      const IpcSoapHeader& header() const
      {
         return mHeader;
      }

      const IpcSoapBody& body() const
      {
         return mBody;
      }

       IpcSoapHeader& header_mutable() 
      {
         return mHeader;
      }

       IpcSoapBody& body_mutable() 
      {
         return mBody;
      }

   private:
      IpcSoapHeader mHeader;
      IpcSoapBody mBody;
   };

   //**************************************************************************************************
   //                                IpcSoapMsg
   //**************************************************************************************************
   //! \brief  
   //**************************************************************************************************
   class IpcSoapMsg 
   {
      //constructor
      public:
         IpcSoapMsg(boost::interprocess::managed_shared_memory& shm, std::string actionExtended, 
            std::string from,
            std::string fullDestination)
            :mEnvelope(shm,actionExtended, from, fullDestination)
      {

      }
      virtual ~IpcSoapMsg()
      {

      }

      //services
   public:
      const IpcSoapEnvelope& envelope() const
      {
         return mEnvelope;
      }
      IpcSoapEnvelope& envelope_mutable() 
      {
         return mEnvelope;
      }

   private:
      IpcSoapEnvelope mEnvelope;

   };

}//namespace IPC
}//namespace TBinding
}//namepsace Trentino

#endif //TrentinoBindingIPCMemoryMapObjH

