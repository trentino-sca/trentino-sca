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

//standard
#include <cstdlib>
#include <exception>
#include <iostream>
#include <string>
#include <boost/smart_ptr/make_shared.hpp>
#ifdef WIN32
#include <windows.h>
#elif defined(__linux)
#include <signal.h>
#endif

//specific
#include "../Global/TrentinoGlobal.h"
#ifdef TRENTINO_LOGGING
#include "./../Utils/TrentinoUtilsLoggingLog4CPlus.h"
#endif//TRENTINO_LOGGING
#include "./../Utils/TrentinoUtilsLogging.h"
#include "./../Utils/TrentinoUtilsPerformanceHierarchyLogger.h"
#include "./../Utils/TrentinoUtilsPerformanceHierarchyLoggerWriter.h"
#include "./../Utils/TrentinoUtilsDebugHeapSnapshot.h"

#include "TrentinoConsole.h"
#include "TrentinoConsoleTextOutputVisitor.h"
#include "TrentinoConsoleCommand.h"
#include "TrentinoConsoleParser.h"
#include "TrentinoConsoleConfiguration.h"
#include "TrentinoConsoleCommandQuit.h"
#include <boost/thread.hpp>


//remove me
//#include "TrentinoConsoleCommandBoot.h"
//#include "TrentinoConsoleCommandShutdown.h"
//#include "TrentinoConsoleCommandInstall.h"
//#include "TrentinoConsoleCommandRemove.h"
//remove me end

using namespace std;
using namespace Trentino;
using namespace Trentino::Console;
using namespace Trentino::Utils::Logging;

Context context;
boost::mutex gMutexExit;
boost::condition_variable gConditionExit;
Parser consoleParser(context);
Trentino::Console::TextOutputVisitor screenManager;


#ifdef WIN32
BOOL WINAPI onExit(DWORD)
   {
   CommandQuit(context).execute();
   //no idea why "false" works and "true" not!
   return false;
   }
#elif defined(__linux)
void onExit(int /*sig*/)
   {
   CommandQuit(contextManager).execute();
   exit(EXIT_SUCCESS);
   }
#endif

void doMainLoop(TextOutputVisitor& screenManager, Parser& consoleParser, string& line)
   {

   Command::CommandSharedPtr cmd;
   try
      {
      //parse command
      cmd = consoleParser.parse(line);
      }
   catch (exception& e)
      {
      //error occurred, print a message
      screenManager.printError(e.what());
      return;
      }

   //help hint was requested
   if (consoleParser.showHelp())
      {
      screenManager.printUsage();
      return;
      }

   //execute command if necessary
   if(cmd)
      {
      if (cmd->showUsage() == false)
         {
            cmd->execute();
         }


      //get command output
      cmd->acceptOutputVisitor(screenManager);
      }
   }

// main console reading loop is converted to be threaded to be able to process
// shut down requests and to be able to avoid blocking
void threadedLoop()
{
   //main command prompt loop
   while (consoleParser.doExit() == false)
   {
      screenManager.printPrompt();
      //get command
      string nline;
      getline(cin, nline);
      
      if(consoleParser.doExit() != false)
         break;
      doMainLoop(screenManager, consoleParser, nline);
      boost::this_thread::interruption_point();
   }
}

std::string splitFilename (const std::string& str)
{
  unsigned found = str.find_last_of("/\\");
  if(found == str.npos || found == str.size())
     {
      return str;
     }
  std::string res = str.substr(found+1);
  return res;
}


int main(int argc, char *argv[])
   {
   //always on

   //Trentino::Utils::Debug::HeapSnapshot heapSnapshotMain;
   //Trentino::Utils::Debug::HeapSnapshot heapSnapshotBoot;
   //Trentino::Utils::Debug::HeapSnapshot heapSnapshotInstall;

#ifdef WIN32
   ::SetConsoleCtrlHandler(onExit, true);
#elif defined(__linux) 
   signal(SIGINT, &onExit);
   signal(SIGTERM, &onExit);
#endif

   TextOutputVisitor screenManager;

   Logger::ConfigDesc config = { "Console", nullptr, "Trentino::Console"};
   Logger::setup(Logger::SetupLogger, &config);
   try
      { 
      Trentino::Console::globalConfiguration = 
         boost::make_shared<Configuration>(Configuration::DefaultConfigFile);

      Configuration configuraiton(Configuration::DefaultConfigFile);      

      Parser consoleParser(context);

      screenManager.printIntro();
      //Boot the runtime by default

      screenManager.printPrompt();
      logInfo("Booting the system");
      string line ="boot";
      bool hasConfig = false;
      if(argc >1)
         {
         std::string confFile (argv[1]);
         std::size_t found = confFile.find("-install");
         if(found==confFile.npos){
         line+=" ";
         line+=confFile;
            hasConfig = true;
            logInfo("Using custom config file");
         }

         }
      doMainLoop(screenManager, consoleParser,line);
      int minimalNumberOfArgsForInstall = 2;
      if(hasConfig)
         {
         minimalNumberOfArgsForInstall = 3;
         }
      //run install command if necessary
      if(argc >minimalNumberOfArgsForInstall)
         {
         std::string install(argv[minimalNumberOfArgsForInstall-1]);
         if(install=="-install")
            {
            std::string contrib (argv[minimalNumberOfArgsForInstall]);
            logInfo("Installing file");
            logInfo(contrib.c_str());
            line ="install ";
            line+=contrib;
            line+=" ";
            line+=splitFilename(contrib);
            doMainLoop(screenManager, consoleParser,line);
            }
         }

      //main command prompt loop
      boost::thread t(&::threadedLoop);

      boost::unique_lock<boost::mutex> lock(gMutexExit);
      gConditionExit.wait(lock);
      if (consoleParser.doExit() != false)
         {
         t.interrupt();
         CommandQuit(context).execute();
         /*line ="exit";
         doMainLoop(screenManager, consoleParser,line);*/


      }
      else
      {
         // if condition is hit doExit should be true
         // since the condition is notified once exit
         // is required
         assert(false);
         }

      }
   catch(exception& e)
      {
      screenManager.printError(e.what());
      return EXIT_FAILURE;
      }

   //heapSnapshotMain.dumpLeaks();
   return EXIT_SUCCESS;
   }
