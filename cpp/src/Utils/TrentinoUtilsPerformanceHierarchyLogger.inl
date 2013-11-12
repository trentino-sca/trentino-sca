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

inline HierarchyNode* HierarchyNode::parent() const
{
   return mParent;
}

inline HierarchyNode* HierarchyNode::firstChild() const
{
   return mFirstChild;
}

inline HierarchyNode* HierarchyNode::successor() const
{
   return mSuccessor;
}

inline HierarchyNode* HierarchyNode::predeccessor() const
{
   return mPredeccessor;
}

inline const char* HierarchyNode::functionName() const
{
   return mFunctionName.c_str();
}

inline const char* HierarchyNode::info() const
{
   return mInfo.c_str();
}

inline void HierarchyNode::setInfo(const char* info)
{
   mInfo = info;
}

inline const char* HierarchyNode::type() const
{
   return mType.c_str();
}

inline void HierarchyNode::setType(const char* type)
{
   mType = type;
}

inline HierarchyNode::HierarchyNode()
{
   //does nothing here
   assert(false);
}

inline HierarchyNode::HierarchyNode(const HierarchyNode& /*node*/)
{
   assert(false);
   //does nothing here
}

inline HierarchyNode::HierarchyNode(const char* functionName, HierarchyNode* parent) :
      mParent(parent),
      mSuccessor(nullptr),
      mPredeccessor(nullptr),
      mFirstChild(nullptr),
      mFunctionName(functionName), 
      mTimeMSec(0.0f)
{
   if(parent != nullptr)
   {
      if(parent->mFirstChild == nullptr)
      {
         parent->mFirstChild = this;
      }
      else
      {
         HierarchyNode* currentNode = parent->mFirstChild;
         while(currentNode != nullptr)
         {
            if(currentNode->mSuccessor == nullptr)
            {
               currentNode->mSuccessor = this;
               mPredeccessor = currentNode;
               mParent = parent;
               break;
            }
            currentNode = currentNode->mSuccessor;
         }
      }
   }
}

inline HierarchyNode::~HierarchyNode()
{
   delete mFirstChild;

   delete mSuccessor;

   if(mFirstChild == nullptr && mSuccessor == nullptr)
   {
      if(mPredeccessor != nullptr)
      {
         assert(mPredeccessor->mSuccessor == this);
         mPredeccessor->mSuccessor = nullptr;
      }
      else
      {
         if(mParent != nullptr)
         {
            //assert(mParent == this);
            mParent->mFirstChild = nullptr;
         }
      }
   }
}

inline float HierarchyNode::elapsedTime() const
{
   return mTimeMSec;
}

inline HierarchyNode* HierarchyLogger::currentNode() const
{
   return mCurrentNode;
}

inline HierarchyNode* HierarchyLogger::rootNode() const
{
   return mRoot;
}

inline void HierarchyLogger::moveUp()
{
   if(mCurrentNode != nullptr && mCurrentNode->parent() != nullptr)
      mCurrentNode = mCurrentNode->parent();
}

inline HierarchyNodeScope::HierarchyNodeScope(const char* functionName)
{
   mNode = HierarchyLogger::instance().createNode(functionName);
   beginMeasurement();
}

inline HierarchyNodeScope::~HierarchyNodeScope()
{
   assert(HierarchyLogger::instance().currentNode() != nullptr);
   endMeasurement();
   HierarchyLogger::instance().moveUp();
}
