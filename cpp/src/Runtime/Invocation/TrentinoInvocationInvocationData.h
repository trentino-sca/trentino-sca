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

#ifndef TrentinoAPIInvocationDataH
#define TrentinoAPIInvocationDataH

//standard
#include <string>
#include <vector>

//specific
#include "TrentinoInvocation.h"
#include "./../RuntimeModel/TrentinoRuntimeModel.h"

namespace Trentino{
namespace Invocation 
{
   //**********************************************************************************************
   //                                        InvocationData
   //**********************************************************************************************
   //! \ingroup Invocation
   //! \brief Contains all the necessary information to perform an invocation of a service and 
   //!        store the return value.
   //! \par Example:
   //! \code
   //! //caller side
   //! InvocationDataPtr invocationData = boost::make_shared<InvocationData>();
   //! invocationData->setTargetService(addingService);
   //! invocationData->setOperation("add");
   //! const int a = 23; 
   //! const int b = 46;
   //! InvocationData::Parameters params;
   //! params.reserve(2);
   //! params.push_back(&a);
   //! params.push_back(&b);
   //! invocationData->setParameters(params);
   //! invoker->invoke(invocationData, ...);
   //! const int result = *static_cast<int*>(invocationData->response());
   //!
   //! //callee side
   //! if(invocationData->operation() == "add")
   //! {
   //!    const int param1 = *static_cast<int*>(invocationData->parameters()[0]);
   //!    const int param2 = *static_cast<int*>(invocationData->parameters()[1]);
   //!    int* result = new int;
   //!    *result = serviceImpl->add(param1, param2);
   //!    invocationData->setResponse(result);
   //! }   
   //! \endcode
   //**********************************************************************************************
	class INVOCATION_IMPORT_EXPORT InvocationData 
   {
      //additional
   public:
      typedef std::vector<void*> Parameters;

      //construction
	public:
      //*******************************************************************************************
      //                                  InvocationData()
      //*******************************************************************************************      
      //! \brief Empty constructor. 
      //*******************************************************************************************
		InvocationData();

      //*******************************************************************************************
      //                                  ~InvocationData()
      //*******************************************************************************************      
      //! \brief Empty destructor.
      //*******************************************************************************************
		~InvocationData();
   private:
      //*******************************************************************************************
      //                         InvocationData(const InvocationData&)
      //*******************************************************************************************      
      //! \brief Disallow inadvertent copy construction. 
      //*******************************************************************************************
      InvocationData(const InvocationData&);

      //operators
   private:
      //*******************************************************************************************
      //                                       operator=()
      //*******************************************************************************************
      //! \brief Disallow assignment.
      //*******************************************************************************************
      void operator=(const InvocationData&);

      //services
   public:
      //*******************************************************************************************
      //                                       operation()
      //*******************************************************************************************      
      //! \brief Returns the operation to be invoked on the target service. 
      //! \return Name of the operation (=service method) to be invoked.      
      //! \sa setOperation(), targetService()
      //*******************************************************************************************
      const std::string& operation() const;

      //*******************************************************************************************
      //                                       setOperation()
      //*******************************************************************************************      
      //! \brief Sets the operation to be invoked on the target service. 
      //! \param[in] operation Name of the operation (=service method) to be invoked.     
      //! \sa operation(), targetService()
      //*******************************************************************************************
      void setOperation(const std::string& operation);

      //*******************************************************************************************
      //                                       parameters()
      //*******************************************************************************************      
      //! \brief Returns a list of the parameters to be passed to the operation to be invoked.
      //! \return A collection of \c void pointers to the parameters. 
      //! \attention The \c void pointers returned by this method must be casted into correct types
      //!            before they can be passed to the method to be invoked. 
      //! \sa setParameters(), operation()
      //*******************************************************************************************
      const Parameters& parameters() const;

      //*******************************************************************************************
      //                                       setParameters()
      //*******************************************************************************************      
      //! \brief Sets the parameters to be passed to the operation to be invoked.
      //! \param[in] params A collection of \c void pointers to the parameters. The collection is
      //!            copied and stored as a member.
      //! \sa parameters(), operation()
      //*******************************************************************************************
      void setParameters(const Parameters& params);


      //*******************************************************************************************
      //                                      targetService()
      //*******************************************************************************************
      //! \brief Returns the target service to be invoked. 
      //! \return the name of the service to be invoked. 
      //! \sa setTargetService()
      //*******************************************************************************************
      const std::string& targetService() const;

      //*******************************************************************************************
      //                                      setTargetService
      //*******************************************************************************************
      //! \brief Sets the target service to be invoked. 
      //! \param[in] targetService A shared pointer to the target service to be invoked.
      //! \sa targetService()
      //*******************************************************************************************
      void setTargetService(const std::string& targetService);


      //*******************************************************************************************
      //                                      targetComponent()
      //*******************************************************************************************
      //! \brief Returns the target component to be invoked. 
      //! \return the name of the component to be invoked. 
      //! \sa setTargetComponent()
      //*******************************************************************************************
      const std::string& targetComponent() const;

      //*******************************************************************************************
      //                                      setTargetComponent
      //*******************************************************************************************
      //! \brief Sets the target component that implements the service to be invoked 
      //! \sa targetService()
      //*******************************************************************************************
      void setTargetComponent(const std::string& componentName);

      //data
	private:
      //! Name of the operation (= service method) to be invoked.
	   std::string mOperation;
      //! Collection of parameters to be passed to the method to be invoked.
		Parameters mParameters;
      //! Target service to be invoked.
      std::string mTargetService;
      std::string mTargetComponent;
	};//class InvocationData

   #include "TrentinoInvocationInvocationData.inl"

}//namespace API
}//namespace Trentino

#endif //TrentinoAPIInvocationDataH
