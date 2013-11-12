GUIDemo: Trentino demonstrator with GUI components. 

GUI components are designed using QT. To prevent GUI from blocking Trentino console and runtime, necessary part is isolated in a thread using boost::thread.
Currently there are 2 GUI componets implemented:
Server - component exposing a service and displaying te invocation parameter value using LCD-style label
Client - component referring to the server, carries a slider control. Server is invoked every tim e the slider value is changed.

BThread_QT: Common library used for separation of GUI and components. 

GUIDemo_Source
GUIDemo.win32.cont: basic contribution which shows local contribution deployment. Contains 3 server components and 3 client components. Wires between references and services are 
        established in 1 to 1, 1 to many and many to 1 manner. Component code library from this contribution can be used in all further contributions.

GUIDemoRemote_Source
GuiDemoRemote.win32.cont: Server-party contribution demonstrating remote service invocation. Contains 3 server components. All services are exposed using 
                           default binding and supplemented with "colored" metadata.
                           
GUIDemoRemoteCLient_Source: client-party contribution demonstrating remote service invocation. COntains 1 client component with statically-declared reference 
                            binding address. So it needs to be re-trengen-ed and rebuilt to match server party address.
                            
GuiDemoClientDiscovery_Source
GuiDemoClientDiscovery.win32.cont: Client party contribution with discovery. Contains 3 client components with references supplemented with "colored" meta-data.
                                   Discovers corresponding server party components from GUIDemoRemote_Source.
                                   
 TODO:
 Move component code out of contribution directories (now it is duplicated in every directory except GuiDemoClientDiscovery_Source). 
 Create a separate project/cmakefile to built a single library.