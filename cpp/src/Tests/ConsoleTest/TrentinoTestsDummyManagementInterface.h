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

#ifndef TrentinoTestsDummyManagementInterfaceH
#define TrentinoTestsDummyManagementInterfaceH

#include "../../Runtime/TrentinoManagementInterface.h"

namespace Trentino {
namespace Tests {
namespace Console
{

    class DummyManagementInterface : public ManagementInterface
    {
        //construction
    public:
         DummyManagementInterface()
         : trigger(true)
         {}

        //services
    public:
        ErrorMessage install(const std::string& contributionDirectoryPath,
                             const std::string& arg);
        void update(const std::string &,const std::string &,Trentino::Utils::DataObject &);

        Trentino::ManagementInterface::ContributionData getContribution(const std::string &) const;
        ErrorMessage deploy(const std::string& contributionBaseURI);

        ErrorMessage remove(const std::string& contributionIdentifier);

        ErrorMessage removeComponent(const std::string& componentURI);

        ErrorMessage rewire(const std::string& referenceURI,
                            const std::string& target,
                            const std::string& bindingType);

        ErrorMessage setProperty(const std::string& propertyURI, 
                                 const PropertyValues& newValues);

        Trentino::ManagementInterface::ContributionDatas getContributions() const;

        Attributes getAttributes(const std::string& artifactURI) const;

        Services getServices(const std::string& componentURI) const;

        References getReferences(const std::string& componentURI) const;

        PropertiesNames getPropertiesNames(const std::string& componentURI) const;

        ImplementationType getImplementationType(const std::string& componentURI) const;

        PropertyValues getPropertyValues(const std::string& propertyURI)const ;

        ServiceState getServiceState(const std::string& serviceURI) const;

        ServicesStates getServicesStates(const std::string& componentURI) const;

        ReferenceState getReferenceState(const std::string& referenceURI) const;

        ReferencesStates getReferencesStates(const std::string& componentURI) const;

        ReferenceTargets getReferenceTargets(const std::string& referenceURI)const;

        ComponentState getComponentState(const std::string& componentURI) const;

        Components getComponents(const std::string& /*contributionBaseURI*/) const 
        {
           return Components();
        };

        Components getDomainLevelComponents() const {return Components();};

        void setOwnerProcessExceptionHandler(ownerProcessExceptionHandlerPtr){};

        //private services
    private:
        inline void pullTheTrigger();
        //data
    private:
        bool trigger;

    }; //class DummyRuntimeMangementInterface

    inline void DummyManagementInterface::pullTheTrigger()
    {
        //trigger = (trigger ? false : true);
        trigger = false;
    }

} //namespace Console
} // namespace Tests
} //namespace Trentino

#endif //TrentinoTestsDummyManagementInterface