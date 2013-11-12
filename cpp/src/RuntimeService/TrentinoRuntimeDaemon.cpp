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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <pwd.h>
#include <signal.h>

#include <string>

// The following code represents an empty-body Linux daemon.
//
// Test procedure description:
// 1. Add new user 'trentino' who will own daemon process:
//    $ sudo adduser trentino
// 2. Start executable
// 3. Check that daemon started and user 'trentino' owns it:
//    $ ps aux
//    and find Runtime daemon in the list
// 4. Check that daemon can be stopped
//    $ kill PID
//    $ ps aux
//    ensure that there is no Runtime daemon in the list

using namespace std;

// The daemon name
const string DaemonName = "TrentinoRuntimeDaemon";
// The user name which will own this process
const string DaemonUser = "trentino";

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

// Trap expected signals
static void child_handler(int signum)
{
   switch(signum)
   {

   case SIGALRM:
      exit(EXIT_FAILURE);
      break;

   case SIGUSR1:
      exit(EXIT_SUCCESS);
      break;

   case SIGCHLD:
      exit(EXIT_FAILURE);
      break;

   default:
      break;

   }
}

// Daemonize this process
static void daemonize( const string& lockfile )
{
   int lfp = -1;

   // Already a daemon
   if ( getppid() == 1 )
      return;

   // Create the lock file as the current user
   if ( !lockfile.empty() )
   {
      lfp = open(lockfile.c_str(), O_RDWR|O_CREAT, 0640);

      if ( lfp < 0 )
      {
         exit(EXIT_FAILURE);
      }
   }

   // Drop user if there is one, and we were run as root
   if ( (getuid() == 0) || (geteuid() == 0) )
   {
      struct passwd *pw = getpwnam(DaemonUser.c_str());

      if ( pw )
      {
         setuid( pw->pw_uid );
      }
   }

   // Trap signals that we expect to recieve
   signal(SIGCHLD,child_handler);
   signal(SIGUSR1,child_handler);
   signal(SIGALRM,child_handler);

   // Fork off the parent process
   pid_t pid = fork();

   if ( pid < 0 )
   {
      exit(EXIT_FAILURE);
   }

   // If we got a good PID, then we can exit the parent process.
   if ( pid > 0 )
   {
      // Wait for confirmation from the child via SIGTERM or SIGCHLD, or
      // for two seconds to elapse (SIGALRM).  pause() should not return.
      alarm(2);
      pause();

      exit(EXIT_FAILURE);
   }

   // At this point we are executing as the child process
   pid_t parent = getppid();

   // Cancel certain signals
   signal(SIGCHLD,SIG_DFL); // A child process dies
   signal(SIGTSTP,SIG_IGN); // Various TTY signals
   signal(SIGTTOU,SIG_IGN);
   signal(SIGTTIN,SIG_IGN);
   signal(SIGHUP, SIG_IGN); // Ignore hangup signal
   signal(SIGTERM,SIG_DFL); // Die on SIGTERM

   // Change the file mode mask
   umask(0);

   // Create a new SID for the child process
   pid_t sid = setsid();

   if ( sid < 0 )
   {
      exit(EXIT_FAILURE);
   }

   // Change the current working directory.  This prevents the current
   // directory from being locked; hence not being able to remove it.
   if ( (chdir("/")) < 0 )
   {
      exit(EXIT_FAILURE);
   }

   // Redirect standard files to /dev/null
   freopen( "/dev/null", "r", stdin );
   freopen( "/dev/null", "w", stdout );
   freopen( "/dev/null", "w", stderr );

   // Tell the parent process that we are A-okay
   kill( parent, SIGUSR1 );
}

static void daemonMain()
{
   // Do the work for which we were paid
   while(1)
   {}
}

int main( int argc, char *argv[] )
{

   // Daemonize
   daemonize( "/var/lock/subsys/" + DaemonName );

   // Now we are a daemon
   daemonMain();

   // Finish up
   return 0;
}