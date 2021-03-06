# Install script for directory: I:/Trentino/trentino/DEV/cpp/src/Tests/SystemTestData/ContributionInfoTestData/BasicCalculatorGen

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "I:/Trentino/trentino/DEV/cpp/src/Tests/SystemTestData/ContributionInfoTestData")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "Release")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/BasicCalculator/META-INF" TYPE STATIC_LIBRARY OPTIONAL FILES "I:/Trentino/trentino/DEV/cpp/src/Tests/SystemTestData/ContributionInfoTestData/BasicCalculatorGen_Build/build/x86Windows/Debug/sca-contribution.lib")
  ELSEIF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/BasicCalculator/META-INF" TYPE STATIC_LIBRARY OPTIONAL FILES "I:/Trentino/trentino/DEV/cpp/src/Tests/SystemTestData/ContributionInfoTestData/BasicCalculatorGen_Build/build/x86Windows/Release/sca-contribution.lib")
  ELSEIF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/BasicCalculator/META-INF" TYPE STATIC_LIBRARY OPTIONAL FILES "I:/Trentino/trentino/DEV/cpp/src/Tests/SystemTestData/ContributionInfoTestData/BasicCalculatorGen_Build/build/x86Windows/MinSizeRel/sca-contribution.lib")
  ELSEIF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/BasicCalculator/META-INF" TYPE STATIC_LIBRARY OPTIONAL FILES "I:/Trentino/trentino/DEV/cpp/src/Tests/SystemTestData/ContributionInfoTestData/BasicCalculatorGen_Build/build/x86Windows/RelWithDebInfo/sca-contribution.lib")
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/BasicCalculator/META-INF" TYPE SHARED_LIBRARY FILES "I:/Trentino/trentino/DEV/cpp/src/Tests/SystemTestData/ContributionInfoTestData/BasicCalculatorGen_Build/build/x86Windows/Debug/sca-contribution.dll")
  ELSEIF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/BasicCalculator/META-INF" TYPE SHARED_LIBRARY FILES "I:/Trentino/trentino/DEV/cpp/src/Tests/SystemTestData/ContributionInfoTestData/BasicCalculatorGen_Build/build/x86Windows/Release/sca-contribution.dll")
  ELSEIF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/BasicCalculator/META-INF" TYPE SHARED_LIBRARY FILES "I:/Trentino/trentino/DEV/cpp/src/Tests/SystemTestData/ContributionInfoTestData/BasicCalculatorGen_Build/build/x86Windows/MinSizeRel/sca-contribution.dll")
  ELSEIF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/BasicCalculator/META-INF" TYPE SHARED_LIBRARY FILES "I:/Trentino/trentino/DEV/cpp/src/Tests/SystemTestData/ContributionInfoTestData/BasicCalculatorGen_Build/build/x86Windows/RelWithDebInfo/sca-contribution.dll")
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/BasicCalculator/META-INF" TYPE FILE FILES "I:/Trentino/trentino/DEV/cpp/src/Tests/SystemTestData/ContributionInfoTestData/BasicCalculatorGen/sca-contribution.conf")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
ELSE(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
ENDIF(CMAKE_INSTALL_COMPONENT)

FILE(WRITE "I:/Trentino/trentino/DEV/cpp/src/Tests/SystemTestData/ContributionInfoTestData/BasicCalculatorGen_Build/${CMAKE_INSTALL_MANIFEST}" "")
FOREACH(file ${CMAKE_INSTALL_MANIFEST_FILES})
  FILE(APPEND "I:/Trentino/trentino/DEV/cpp/src/Tests/SystemTestData/ContributionInfoTestData/BasicCalculatorGen_Build/${CMAKE_INSTALL_MANIFEST}" "${file}\n")
ENDFOREACH(file)
