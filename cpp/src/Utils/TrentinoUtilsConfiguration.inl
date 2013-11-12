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


//class Configuration 

//magement
inline boost::program_options::options_description& Configuration::configOptions()
{ 
  return mConfigOptions; 
}

inline const boost::program_options::variables_map& Configuration::optionsMap() const
{ 
   return mOptionsMap; 
}


inline const std::string Configuration::getConfigFilepath() const
{
  return mConfigFilePath;
}

//*************************************************************************************************
//                                   for later use
//*************************************************************************************************
//inline boost::program_options::options_description& Configuration::genericOptions()    
//{ 
//   return mGenericOptions; 
//}
//
//inline boost::program_options::options_description& Configuration::hiddenOptions()     
//{ 
//   return mHiddenOptions; 
//}
//
//inline boost::program_options::positional_options_description& Configuration::positionalOptions() 
//{ 
//   return mPositionalOptions; 
//}
//
//inline boost::program_options::options_description& Configuration::debugOptions()
//{ 
//   return mDebugOptions; 
//}
