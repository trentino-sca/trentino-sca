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
#ifndef TrentinoBindingTrentinoBindingH
#define TrentinoBindingTrentinoBindingH

//standard
#pragma warning(push)
#pragma warning(disable:4512)
#include <boost/program_options.hpp>
#pragma warning(pop)

//specific
#include "TrentinoBinding.h"
#include "../ServiceRegistry/TrentinoServiceRegistryServiceRegistryBase.h"
#include "../SCAModel/TrentinoSCAModelMetadata.h"

namespace Trentino{
   namespace Binding{
        typedef boost::program_options::options_description ConfigOptions;
      //**********************************************************************************************
      //                             TrentinoBindingContext                             
      //**********************************************************************************************
      //! \ingroup TrentinoBinding
      //! \brief Ligthweight object that holds all information specific to a binding
      //! The binding context hold is a wrapper around a map of ContextAttributes
      //**********************************************************************************************
      typedef boost::program_options::variables_map TrentinoBindingContext;
      typedef TrentinoBindingContext TrentinoBindingContextPtr;

      //class declaration
      //**********************************************************************************************
      //                             TrentinoBinding                             
      //**********************************************************************************************
      //! \ingroup TrentinoBinding
      //! \brief A Trentino Binding
      //! all Bindings should implement this interface, so that the Binding Manager can manage them
      //**********************************************************************************************
      class TrentinoBinding
      {

         //services
      public:
         //**********************************************************************************************
         //                             start()                             
         //**********************************************************************************************
         //! \ingroup TrentinoBinding
         //! \brief Start the Binding. This enable the Binding to handle incoming messages
         //**********************************************************************************************
         virtual void start() = 0;

         //**********************************************************************************************
         //                             stop()                             
         //**********************************************************************************************
         //! \ingroup TrentinoBinding
         //! \brief Stop the Binding Server, removed unused resource and clean memory
         //**********************************************************************************************
         virtual void stop () = 0;

         //**********************************************************************************************
         //                             getId()                             
         //**********************************************************************************************
         //! \ingroup TrentinoBinding
         //! \brief return the Id of the current Binding
         //**********************************************************************************************
         virtual const std::string getId()=0;

         //**********************************************************************************************
         //                             setContext()                             
         //**********************************************************************************************
         //! \ingroup TrentinoBinding
         //! \brief Set the context of the current Binding
         //**********************************************************************************************
         virtual void setContext( const TrentinoBindingContextPtr& context ) = 0;

          //****************************************************************************************************
          //                                         configure()
          //****************************************************************************************************
          //! \brief configure this Binding.
          //! \param Trentino::Binding::ConfigOptions & configOptions: user can describe (add) programm options for
          //! this binding here.
          //! \return void
          //****************************************************************************************************
          virtual void configure( Trentino::Binding::ConfigOptions& configOptions,const Trentino::ServiceRegistry::ServiceRegistryPtr& registry, const Trentino::Invocation::InvokerPtr& invoker) =0;

                   public:
            //****************************************************************************************************
            //                                   setInvoker()
            //****************************************************************************************************
            //! \brief
            //! \param const Trentino::Invocation::InvokerPtr & invoker
            //! \return void
            //****************************************************************************************************
            virtual void setInvoker(const Trentino::Invocation::InvokerPtr& invoker) =0;


            //****************************************************************************************************
            //                                         setServiceRegistry()
            //****************************************************************************************************
            //! \brief set the Service Registry used by this Binding
            //! \param const Trentino::ServiceRegistry::ServiceRegistryPtr & val
            //! \return void
            //****************************************************************************************************
            virtual void setServiceRegistry(const Trentino::ServiceRegistry::ServiceRegistryPtr& val) =0;

            //****************************************************************************************************
            //                                         getServiceMetadata()
            //****************************************************************************************************
            //! \brief get the service metadata from a binding
            //! \param Trentino::RuntimeModel::ServiceBasePtr service: pointer to a runtime service
            //! \return boost::shared_ptr<Trentino::SCA::Model::Metadata>: pointer to a metadata collection
            //****************************************************************************************************
            virtual boost::shared_ptr<Trentino::SCA::Model::Metadata> getServiceMetadata(Trentino::RuntimeModel::ServiceBasePtr service) = 0;

            //****************************************************************************************************
            //                                         getServiceUri()
            //****************************************************************************************************
            //! \brief get the service uri from given metadata from a binding
            //! \param metadata: set of metadata
            //! \return string representation of complete URI or empty string in case of error
            //****************************************************************************************************
            virtual std::string getServiceUri(Trentino::SCA::Model::Metadata& metadata) = 0;



      };//class TrentinoBinding

   }//namespace Binding
}//namespace Trentino

#endif  //TrentinoBindingTrentinoBindingH
