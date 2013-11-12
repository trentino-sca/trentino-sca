rem # ***********************************************************************************
rem # Trentino - A C++ based lightweight, non-invasive SCA runtime.
rem # Copyright (C) Siemens AG, 2012
rem # All Rights Reserved
rem # http://trentino.sourceforge.net/
rem #
rem # This library is free software; you can redistribute it and/or
rem # modify it under the terms of the GNU Lesser General Public
rem # License as published by the Free Software Foundation; either
rem # version 2.1 of the License, or (at your option) any later version.
rem #
rem # This library is distributed in the hope that it will be useful,
rem # but WITHOUT ANY WARRANTY; without even the implied warranty of
rem # MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
rem # Lesser General Public License for more details.
rem #
rem # You should have received a copy of the GNU Lesser General Public
rem # License along with this library; if not, write to the Free Software
rem # Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
rem # ***********************************************************************************

echo "create Visual studio "
rmdir /s /q cpp_build
mkdir cpp_build
cd cpp_build
mkdir "build/x86Windows/Debug"
mkdir "build/x86Windows/Release"
cmake -G "Visual Studio 10" -D TRENTINO_BUILD_CORETESTS=OFF ../cpp
cd "../../../../../../../cpp_build"
echo "build trentino"
msbuild ALL_BUILD.vcxproj /p:Configuration=Release
msbuild [Copy3rdPartyLibs].vcxproj /p:Configuration=Release
msbuild INSTALL.vcxproj /p:Configuration=Release
msbuild RUN_TESTS.vcxproj /p:Configuration=Release
msbuild [BUILD_COMMON_SERVICES].vcxproj /p:Configuration=Release
msbuild [INSTALL_COMMON_SERVICES].vcxproj /p:Configuration=Release