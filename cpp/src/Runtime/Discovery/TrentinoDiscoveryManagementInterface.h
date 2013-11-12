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

#ifndef TrentinoDiscoveryManagementInterfaceH
#define TrentinoDiscoveryManagementInterfaceH


namespace Trentino{
namespace Discovery
{
   class DiscoveryInterface;
   typedef DiscoveryInterface* DiscoveryInterfacePtr;
   typedef void (*onDiscoveryStartCBPtr)(bool status, std::string returnValOrStatusInfo);

   //class declaration
   //**********************************************************************************************
   //                             DiscoveryManagementInterface
   //**********************************************************************************************
   //! \ingroup Discovery
   //! \brief Interface to manage discovery framework
   //
   //!  
   //**********************************************************************************************
   class DiscoveryManagementInterface
   {

      //construction
   public:
      virtual ~DiscoveryManagementInterface() {}; 

   public:
      //! Enum to communicate the method used for service discovery
      enum DiscoveryMethod
      {
         //! OpenSLP implementation of SLP protocol RFC  
         SLP
      };
      
      //Discovery Framework Management Functions
      //****************************************************************************************
      //                                start()
      //****************************************************************************************
      //! \brief Function to start discovery framework. Works synchronously
      //! \param[in] retryCount: configured in runtime.conf to specify how many times to retry
      //! a failed task
      //! \param[in] retryInterval: configured in runtime.conf to specify the interval between
      //! retries (in seconds)
      //! \param[in] Callback function to be triggered the start task is finished.
      //****************************************************************************************
      virtual void start(bool isDA, 
         int retryCount,
         int retryInterval, 
         onDiscoveryStartCBPtr discoveryTaskCB ) = 0; 
      
      //****************************************************************************************
      //                                stop()
      //****************************************************************************************
      //! \brief Function to stop discovery framework
      //****************************************************************************************
      virtual void stop(bool isDA) = 0; 

      //****************************************************************************************
      //                                getDiscoveryInterface()
      //****************************************************************************************
      //! \brief Function to retrive the dicovery interface to use for dicovery requests
      //! (i.e.service rgistering, finding .etc)
      //****************************************************************************************
      virtual Trentino::Discovery::DiscoveryInterfacePtr getDiscoveryInterface() = 0;

   }; // class DiscoveryManagementInterface


} // namespace Discovery
} // namespace Trentino

#endif//TrentinoDiscoveryManagementInterfaceH

