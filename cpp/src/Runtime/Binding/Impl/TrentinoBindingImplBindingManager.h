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

#ifndef TrentinoBindingImplBindingManagerH
#define TrentinoBindingImplBindingManagerH

//baseclass
#include "../TrentinoBindingBindingManagerBase.h"

//standard
#include <string>
#include <map>
#include <vector>

//specific
#include "../../RuntimeModel/TrentinoRuntimeModelContribution.h"
#include "../../../Utils/TrentinoUtilsConfiguration.h"
#include "../../Invocation/TrentinoInvocation.h"
#include "../../ServiceRegistry/ServiceRegistry.h"


namespace Trentino{
   namespace Binding{
      namespace Impl{

         //class Declaration
         //************************************************
         //                     BindingManager
         //************************************************
         //! \brief BindingManager implementation
         //************************************************
         class BindingManager : public BindingManagerBase 
         {
            //constructor
         public:
            BindingManager();
            virtual ~BindingManager();
            // virtual TrentinoBindingrPtr& getBindingById(const std::string& bindingId);
            // virtual void removeBinding(const std::string& bindingId);

            //services
            virtual void createBinding( const std::string& bindingId);
            virtual void startBinding( const std::string& bindingId);
            virtual const TrentinoBindingContextPtr& loadDefaultBindingContext( const std::string& bindingId );
            virtual bool onDeploy(const Trentino::RuntimeModel::ContributionPtr& contribution );
            virtual boost::shared_ptr<Metadata> getServiceMetadata(string bindingId, Trentino::RuntimeModel::ServiceBasePtr service);
            static bool isFakeUri(const char* uri);
            virtual std::string getServiceUri(string bindingId, Metadata & metadata);
            virtual void stop();
            
         private:
            //****************************************************************************************************
            //                                         configFilePath()
            //****************************************************************************************************
            //! \brief return the PATH of the Binding.conf file
            //! \return testing::internal::string
            //****************************************************************************************************
            std::string configFilePath() const;
            //data
         private:
            //! not using sharep pointer because of strange behaviour with vector of shared pointer.
            //! as soon as pointer container is intoduced as library, we will replace this with boost container pointer
            typedef std::vector<Trentino::Binding::BindingFactoryPtr> BindingFactories;
            std::map<std::string, Trentino::Binding::TrentinoBindingPtr> mBindings;
            BindingFactories mBindingFactories;
            //! Relative path to the default configuration file
            static const std::string DefaultConfigFilePath;
            //! Object providing the logic for parsing options from config files (and the cmd line)
            Trentino::Utils::Configuration mConfiguration;
         };//class BindingManager

      } //namespace Impl
   }//namespace Binding
}// namespace Trentino

#endif //TrentinoBindingImplBindingManagerH
