1- JAXB should be downloaded from http://jaxb.java.net/2.2.5/
2- Downloaded .zip file should be extracted.
3- In bin folder, run this command: xjc.bat -b sca-core-1.1-cd06.xjb sca-1.1-csd09.xsd

NOTE: "sca-implementation-cpp-1.1-cd06.xsd" is changed in order to validate implementation and interface elements in .composite files.
NOTE 2: Since we are using JDK 1.6 in Trentino, we included jaxb_api.jar in build path.