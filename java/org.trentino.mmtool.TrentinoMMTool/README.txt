1- derby.log, mmtool_log.txt, .classpath and .project should be rewritable. 
2- "mvn eclipse:eclipse" is needed from command line.Then the project should be refreshed in Eclipse.
3- "mvn gwt:run" is needed after each change. This will copy the resources to SNAPSHOT directory.
4- While running, "-Djava.naming.factory.initial=org.mortbay.naming.InitialContextFactory" argument should be set.

SOME FURTHER NOTES:
5- Shiro.ini should be in resources.
6- For GWT, use jetty-web.xml. Don't change the name!
7- liquibase listener creates the database.
8- For using GWT, your regional settings should be ENGLISH!

For further info; refer to:
http://uptick.com.au/content/getting-started-gwt-maven-and-eclipse