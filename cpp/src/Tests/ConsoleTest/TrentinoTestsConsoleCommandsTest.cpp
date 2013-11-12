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

//header
#include "TrentinoTestsConsoleCommandsTest.h"

//standard
#include <boost/foreach.hpp>
#include <boost/scoped_ptr.hpp>
#include <vector>

//specific
#include "TrentinoTestsDummyManagementInterface.h"
#include "../../Console/TrentinoConsoleParser.h"
#include "../../Console/TrentinoConsoleCommandInfo.h"
#include "../../Console/TrentinoConsoleCommandInstall.h"
#include "../../Console/TrentinoConsoleCommandRemove.h"
#include "../../Console/TrentinoConsoleCommandRewire.h"
#include "../../Console/TrentinoConsoleCommandSetProperty.h"
#include "../../Console/TrentinoConsoleContext.h"
#include "../../Runtime/Core/TrentinoCoreRuntimeAPI.h"

using namespace std;
using namespace Trentino::Console;
using Trentino::Tests::Console::CommandsTest;

using namespace Trentino::Tests::Console;
//class ParserTest
   //services
class ContextTest : public ContextAccessor
{
   //services
public:
   void setManagementInterface(Trentino::ManagementInterface* iface) 
   {
      mManagmentInterface = iface;
   }

   virtual Trentino::ManagementInterface* managementInterface() const
   {
      return mManagmentInterface;
   }
   
   virtual Trentino::Core::RuntimeAPIPtr runtimeAPI() const
   {
      return Trentino::Core::RuntimeAPIPtr();
   }
   //data
private:
   Trentino::ManagementInterface* mManagmentInterface;
}; //class ContextTest


TEST_F(CommandsTest,testCommandInfo)
{
   boost::scoped_ptr<Trentino::ManagementInterface> ifacePtr(
      new DummyManagementInterface);

   ContextTest context;   
   context.setManagementInterface(ifacePtr.get());
   
   CommandInfo::CommandArgs cmdInfoArgs;

   cmdInfoArgs.getAttributes = true;
   cmdInfoArgs.getProperties = true;
   cmdInfoArgs.getReferences = true;
   cmdInfoArgs.getReferenceTargets = true;
   cmdInfoArgs.URI = "myComponent";

   CommandInfo cmd(cmdInfoArgs, context);
   cmd.execute();
   
   ASSERT_TRUE(cmd.getOutput().availableOutput == CommandInfo::Output::Components);
   CommandInfo::SCAComponent component = cmd.getOutput().components[0];

   Trentino::ManagementInterface::Attributes attrs;
   attrs["name"] = "attribute";
   attrs["size"] = "huge";
   ASSERT_TRUE(component.attributes == attrs);

   Trentino::ManagementInterface::PropertiesNames names;
   names.push_back("currency");
   ASSERT_TRUE(component.properties == names);

   Trentino::ManagementInterface::References refs;
   refs.push_back("reference1");
   refs.push_back("reference2");
   refs.push_back("reference3");
   ASSERT_TRUE(component.references == refs);

   Trentino::ManagementInterface::ReferenceTargets targets;
   targets.push_back("yandex");
   targets.push_back("google");
   targets.push_back("yahoo");
   ASSERT_TRUE(component.referencesTargets["reference1"] == targets);
   ASSERT_TRUE(component.referencesTargets["reference2"] == targets);
   ASSERT_TRUE(component.referencesTargets["reference3"] == targets);
}

TEST_F(CommandsTest,testCommandInstall)
{
   boost::scoped_ptr<Trentino::ManagementInterface> ifacePtr(
      new DummyManagementInterface);

   ContextTest context;   
   context.setManagementInterface(ifacePtr.get());
   CommandInstall::CommandArgs cmdInstallArgs;

   cmdInstallArgs.doDeploy = true;
   cmdInstallArgs.pathToContribution = "pathToContribution";
   cmdInstallArgs.contributionBaseURI = "contributionBaseURI";

   CommandInstall cmd(cmdInstallArgs, context);
   cmd.execute();

   ASSERT_TRUE(cmd.errorMessage().empty());   
   ASSERT_TRUE(cmd.deployStatus().empty());
}

TEST_F(CommandsTest,testCommandRemove)
{
   boost::scoped_ptr<Trentino::ManagementInterface> ifacePtr(
      new DummyManagementInterface);

   ContextTest context;   
   context.setManagementInterface(ifacePtr.get());
   CommandRemove::CommandArgs cmdRemoveArgs;

   cmdRemoveArgs.removeComponent = false;
   cmdRemoveArgs.identifier = "contributionIdentifier";

   CommandRemove cmd(cmdRemoveArgs, context);
   cmd.execute();

   ASSERT_TRUE(cmd.errorMessage().empty());
}

TEST_F(CommandsTest,testCommandRewire)
{
   boost::scoped_ptr<Trentino::ManagementInterface> ifacePtr(
      new DummyManagementInterface);

   ContextTest context;   
   context.setManagementInterface(ifacePtr.get());
   CommandRewire::CommandArgs cmdRewireArgs;

   cmdRewireArgs.referenceURI = "myReference";
   cmdRewireArgs.target = "targerService";

   CommandRewire cmd(cmdRewireArgs, context);
   cmd.execute();

   ASSERT_TRUE(cmd.errorMessage().empty());
}

TEST_F(CommandsTest,testCommandSet)
{
   boost::scoped_ptr<Trentino::ManagementInterface> ifacePtr(
      new DummyManagementInterface);

   ContextTest context;   
   context.setManagementInterface(ifacePtr.get());
   CommandSetProperty::CommandArgs cmdSetPropertyArgs;

   cmdSetPropertyArgs.propertyURI = "myProperty";
   cmdSetPropertyArgs.values.push_back("Value1");
   cmdSetPropertyArgs.values.push_back("Value2");

   CommandSetProperty cmd(cmdSetPropertyArgs, context);
   cmd.execute();

   ASSERT_TRUE(cmd.errorMessage().empty());
}