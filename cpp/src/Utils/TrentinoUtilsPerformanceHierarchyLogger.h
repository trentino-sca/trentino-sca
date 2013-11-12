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

#ifndef TrentinoUtilsPerformanceHierarchyLoggerH
#define TrentinoUtilsPerformanceHierarchyLoggerH

#ifdef WIN32
#ifdef UTILS_EXPORTS
#define PERFORMANCE_IMPORT_EXPORT __declspec(dllexport)
#else
#define PERFORMANCE_IMPORT_EXPORT __declspec(dllimport)       
#endif //UTILS_EXPORTS
#else
#define PERFORMANCE_IMPORT_EXPORT
#endif //WIN32


//standard
#include <string>
#include <malloc.h>
#include <assert.h>

//specific
#include "../Global/TrentinoGlobal.h"

//! \todo refactor and comment

namespace Trentino{
namespace Utils{
//! \defgroup Performance
namespace Performance
{
   //forward declarations
   class HierarchyLogger;
   class HierarchyNode;

   //class declaration
   //**********************************************************************************************
   //                             HierarchyNodeScope
   //**********************************************************************************************
   //! \brief Helper class to construct a hierarchy model of \sa HierarchyNodes..
   //! Creates a new Node with a functionname, given by \sa HLOGGER().
   //! Internally a time measurement will be done.
   //**********************************************************************************************
   class HierarchyNodeScope
   {
      //construction
   public:
      //*******************************************************************************************
      //                                   constructor()                               
      //*******************************************************************************************
      //! Creates a new \sa HierarchyNode and sets the functionsName.
      //! Additionally a time measurement will be started here.
      //! \param[in] A specified functionname of function. 
      //! e.g. you can use __FUNCTION macro for this.
      //*******************************************************************************************
      HierarchyNodeScope(const char* functionName);

      //*******************************************************************************************
      //                                   destructor()                               
      //*******************************************************************************************
      //! Destroys scope object a goes one hierarchylevel up.
      //! Time measurement is stopped here and stored in \sa mNode
      //! instance
      //*******************************************************************************************
      ~HierarchyNodeScope();
      //management
   private:
      //*******************************************************************************************
      //                                   beginMeasurement()                               
      //*******************************************************************************************
      //! Starts a new time measurement here
      //! \todo: Implement for linux/unix
      //*******************************************************************************************
      void PERFORMANCE_IMPORT_EXPORT beginMeasurement();

      //*******************************************************************************************
      //                                   endMeasurement()                               
      //*******************************************************************************************
      //! Ends the time measurement and stores into \sa mStartTime
      //! \todo: Implement for linux/unix
      //*******************************************************************************************
      void PERFORMANCE_IMPORT_EXPORT endMeasurement();
      //data
   private:
      //! Node creates by this instance in constructor
      HierarchyNode* mNode;
      
      //! Measurement during construction and destruction call of this object. 
      //! Result is stored in \sa mNode.
      uint64_t mStartTime;
   };//class HierarchyNodeScope

   //class declaration
   //**********************************************************************************************
   //                             HierarchyNode
   //**********************************************************************************************
   //! \brief Each Node stores the calling levels done by \sa HLOGGER()
   //! It holds information about functionName, ExecutionTime, Type of information and a additional
   //! information about this node.
   //! Internally all neighbours, parents and children are stored.
   //**********************************************************************************************
   class HierarchyNode
   {
      friend class HierarchyLogger;
      friend class HierarchyNodeScope;
      //construction
   public:
      //*******************************************************************************************
      //                                   constructor()                               
      //*******************************************************************************************
      //! Constructor of \sa HierarchyNode
      //! \param[in] Information about the functionName of this node.
      //! \param[in] Parent of this node.
      //*******************************************************************************************
      HierarchyNode(const char* functionName, HierarchyNode* parent);

   private:
      //*******************************************************************************************
      //                                   constructor()                               
      //*******************************************************************************************
      //! Default constructor is private to avoid construction from outside
      //! Only \sa HierarchyLogger is responsible for this.
      //*******************************************************************************************
      HierarchyNode();

      //*******************************************************************************************
      //                                   destructor()                               
      //*******************************************************************************************
      //! Destructor is private to avoid destruction from outside
      //! Only \sa HierarchyLogger is responsible for this.
      //*******************************************************************************************
      ~HierarchyNode();

      //*******************************************************************************************
      //                                   constructor()                               
      //*******************************************************************************************
      //! Copy constructor is private to avoid construction from outside
      //! Only \sa HierarchyLogger is responsible for this.
      //*******************************************************************************************
      HierarchyNode(const HierarchyNode& /*node*/);

      //operators
   private:
      //*******************************************************************************************
      //                                   Assignment operator()                               
      //*******************************************************************************************
      //! Assignment operator is private to avoid assignment from outside
      //*******************************************************************************************
      HierarchyNode& operator=(const HierarchyNode& /*source*/);

      //services
   public:
      //*******************************************************************************************
      //                                   parent()                               
      //*******************************************************************************************
      //! Returns parent of this node.
      //! \return Current parent of this node. \sa nullptr is root.
      //*******************************************************************************************
      HierarchyNode* parent() const;

      //*******************************************************************************************
      //                                   firstChild()                               
      //*******************************************************************************************
      //! Returns first child of this node
      //! \return Current first entry of childnode. \sa nullptr if no children available.
      //*******************************************************************************************
      HierarchyNode* firstChild() const;

      //*******************************************************************************************
      //                                   successor()                               
      //*******************************************************************************************
      //! Returns successor of this node.
      //! \return Current successor of this node. \sa nullptr if no successor available.
      //*******************************************************************************************
      HierarchyNode* successor() const;

      //*******************************************************************************************
      //                                   predeccessor()                               
      //*******************************************************************************************
      //! Returns predeccessor of this node.
      //! \return Current predeccessor of this node. \sa nullptr if no predeccessor available.
      //*******************************************************************************************
      HierarchyNode* predeccessor() const;

      //*******************************************************************************************
      //                                   functionName()                               
      //*******************************************************************************************
      //! Returns functionname of this node.
      //! \return Current functionname of this node, given by constructor.
      //*******************************************************************************************
      const char* functionName() const;

      //*******************************************************************************************
      //                                   elapsedTime()                               
      //*******************************************************************************************
      //! Returns elapsedTime of this node.
      //! This is the complete processing time by this node, inclusive all childnodes!
      //! \return Overall elapsed time of this node.
      //*******************************************************************************************
      float elapsedTime() const;

      //*******************************************************************************************
      //                                   info()                               
      //*******************************************************************************************
      //! Returns an extra info about this node, if available.
      //! \return Data about an extra information stored in this node.
      //*******************************************************************************************
      const char* info() const;

      //*******************************************************************************************
      //                                   setInfo()                               
      //*******************************************************************************************
      //! Sets extra info in this node, used by \sa HLOGGER_INFO.
      //! \param[in] Information to be stored in this node.
      //*******************************************************************************************
      void setInfo(const char* info);

      //*******************************************************************************************
      //                                   type()                               
      //*******************************************************************************************
      //! Returns an extra type about this node, if available.
      //! Can be "Info" or "Except".
      //! \return Data about an extra type information stored in this node.
      //*******************************************************************************************
      const char* type() const;

      //*******************************************************************************************
      //                                   setType()                               
      //*******************************************************************************************
      //! Sets extra type in this node, used by \sa HLOGGER_INFO.
      //! Can be "Info:" or "Except:".
      //! \param[in] Information of type to be stored in this node.
      //*******************************************************************************************
      void setType(const char* type);
      //operators

      //data
   private:
      //! Parent of node
      HierarchyNode* mParent;
      //! Successor of node
      HierarchyNode* mSuccessor;
      //! Predecessor of node
      HierarchyNode* mPredeccessor;
      //! First child of node
      HierarchyNode* mFirstChild;
      //! Functionname of node
      std::string mFunctionName;
      //! TypeInfo of node
      std::string mType;
      //! Extra info of node
      std::string mInfo;
      //! Elapsed overall time of node
      float mTimeMSec;
   };//class HierarchyNode

   //class declaration
   //**********************************************************************************************
   //                             HierarchyLogger
   //**********************************************************************************************
   //! \brief Central instance and factory to create instances of \sa HierarchyNode
   //! Holds current node and root node. 
   //! \todo Only one instance of \sa HierarchyLogger allowed. Is not thread safe and reentrant.
   //**********************************************************************************************
   class PERFORMANCE_IMPORT_EXPORT HierarchyLogger
   {
      //construction
   public:
      //*******************************************************************************************
      //                                   constructor()                               
      //*******************************************************************************************
      //! Default constructor of HierarchyLogger
      //*******************************************************************************************
      HierarchyLogger();

      //*******************************************************************************************
      //                                   destructor()                               
      //*******************************************************************************************
      //! Destructor of HierarchyLogger
      //*******************************************************************************************
      ~HierarchyLogger();
      //services
   public:
      //*******************************************************************************************
      //                                   instance()                               
      //*******************************************************************************************
      //! Returns singleton instance of HierarchyLogger. Currently there are only one instance
      //! of HierarchyLogger allowed.
      //! \return Instance of HierarchyLogger
      //*******************************************************************************************
      static HierarchyLogger& instance();

      //*******************************************************************************************
      //                                   createNode()                               
      //*******************************************************************************************
      //! Creates a new \sa HierarchyNode with a given functionName
      //! Scope of \sa currentNode() is set by this new node and 
      //! a \sa rootNode is set if is not available.
      //! \param[in] Functionname which should be set in new \sa HierarchyNode
      //! \return A new instance of a \sa HierarchyNode
      //*******************************************************************************************
      HierarchyNode* createNode(const char* functionName);

      //*******************************************************************************************
      //                                   createSibling()                               
      //*******************************************************************************************
      //! Creates a new \sa HierarchyNode with a given functionName as a sibling
      //! Scope of \sa currentNode() is set by this new node and 
      //! a \sa rootNode is set if is not available.
      //! New node is available at \sa currentNode().
      //! \param[in] Functionname which should be set in new \sa HierarchyNode
      //*******************************************************************************************
      void createSibling(const char* functionName);
      
      //*******************************************************************************************
      //                                   moveUp()                               
      //*******************************************************************************************
      //! Moves \sa currentNode() one level up. Parent of currentNode() is the new currentNode.
      //*******************************************************************************************
      void moveUp();

      //*******************************************************************************************
      //                                   currentNode()                               
      //*******************************************************************************************
      //! Returns current node set in \sa HierarchyLogger. 
      //! \attention This method is not threadsafe or reentrant.
      //*******************************************************************************************
      HierarchyNode* currentNode() const;

      //*******************************************************************************************
      //                                   rootNode()                               
      //*******************************************************************************************
      //! Returns root node set in \sa HierarchyLogger. 
      //! \attention This method is not threadsafe or reentrant.
      //*******************************************************************************************
      HierarchyNode* rootNode() const;

      //*******************************************************************************************
      //                                   clear()                               
      //*******************************************************************************************
      //! Clears the whole hierarchy. \sa rootNode and \sa currentNode set to nullptr.
      //*******************************************************************************************
      void clear();
 
   //management
   private:
      //*******************************************************************************************
      //                                   createInternalNode()                               
      //*******************************************************************************************
      //! Helper method to create a new \sa HierarchyNode.
      //! \param[in] Functionname which should be set in new \sa HierarchyNode
      //! \param[in] ParentNode to set.
      //! \return A new instance of a \sa HierarchyNode
      //*******************************************************************************************
      HierarchyNode* createInternalNode(
         const char* functionName
        ,HierarchyNode* parentNode = nullptr);
      //data
   private:
      //! Current root node
      HierarchyNode* mRoot;
      //! Current node
      HierarchyNode* mCurrentNode;
   };//class HierarchyLogger

   #ifdef TRENTINO_DEBUG_OUTPUT
      #ifndef TRENTINO_HLOGGER
         #define TRENTINO_HLOGGER
      #endif //TRENTINO_HLOGGER
   #endif//TRENTINO_DEBUG_OUTPUT


   #ifdef TRENTINO_HLOGGER
      //*******************************************************************************************
      //                                   HLOGGER()                               
      //*******************************************************************************************
      //! Helper macro to use it in your own methods
      //! Only available if \sa TRENTINO_HLOGGER macro is set (\sa TRENTINO_DEBUG_OUTPUT set)
      //! Use it as:
      //! void foo()
      //! {
      //!    HLOGGER();
      //!    ...
      //! }
      //*******************************************************************************************
      #define HLOGGER() Trentino::Utils::Performance::HierarchyNodeScope scope##__LINE__##(__FUNCTION__)

      //*******************************************************************************************
      //                                   HLOGGER_INFO()                               
      //*******************************************************************************************
      //! Helper macro to set an extra info in \sa HierarchyLogger::currentNode()
      //! Only available if \sa TRENTINO_HLOGGER macro is set (\sa TRENTINO_DEBUG_OUTPUT set)
      //! Use it as:
      //! void foo()
      //! {
      //!    HLOGGER();
      //!    HLOGGER_INFO("newInfo");
      //!    ...
      //! }
      //*******************************************************************************************
      #define HLOGGER_INFO(info) \
         {  \
            Trentino::Utils::Performance::HierarchyLogger::instance().currentNode()->setType("Info:"); \
            Trentino::Utils::Performance::HierarchyLogger::instance().currentNode()->setInfo(info); \
         }

      //*******************************************************************************************
      //                                   HLOGGER_EXCEPTION()                               
      //*******************************************************************************************
      //! Helper macro to set an extra exception info in \sa HierarchyLogger::currentNode()
      //! Only available if \sa TRENTINO_HLOGGER macro is set (\sa TRENTINO_DEBUG_OUTPUT set)
      //! Use it as:
      //! void foo()
      //! {
      //!    HLOGGER();
      //!    HLOGGER_EXCEPTION("newException information");
      //!    ...
      //! }
      //*******************************************************************************************
      #define HLOGGER_EXCEPTION(excpt) \
         {  \
            Trentino::Utils::Performance::HierarchyLogger::instance().currentNode()->setType("Excpt:"); \
            Trentino::Utils::Performance::HierarchyLogger::instance().currentNode()->setInfo(excpt); \
         }
   #else
      //*******************************************************************************************
      //                                   HLOGGER()                               
      //*******************************************************************************************
      //! Helper macro to use it in your own methods
      //! Only available if \sa TRENTINO_HLOGGER macro is set (\sa TRENTINO_DEBUG_OUTPUT set)
      //! Use it as:
      //! void foo()
      //! {
      //!    HLOGGER();
      //!    ...
      //! }
      //*******************************************************************************************
      #define HLOGGER()

      //*******************************************************************************************
      //                                   HLOGGER_INFO()                               
      //*******************************************************************************************
      //! Helper macro to set an extra info in \sa HierarchyLogger::currentNode()
      //! Only available if \sa TRENTINO_HLOGGER macro is set (\sa TRENTINO_DEBUG_OUTPUT set)
      //! Use it as:
      //! void foo()
      //! {
      //!    HLOGGER();
      //!    HLOGGER_INFO("newInfo");
      //!    ...
      //! }
      //*******************************************************************************************
      #define HLOGGER_INFO(info)

      //*******************************************************************************************
      //                                   HLOGGER_EXCEPTION()                               
      //*******************************************************************************************
      //! Helper macro to set an extra exception info in \sa HierarchyLogger::currentNode()
      //! Only available if \sa TRENTINO_HLOGGER macro is set (\sa TRENTINO_DEBUG_OUTPUT set)
      //! Use it as:
      //! void foo()
      //! {
      //!    HLOGGER();
      //!    HLOGGER_EXCEPTION("newException information");
      //!    ...
      //! }
      //*******************************************************************************************
      #define HLOGGER_EXCEPTION(excpt)
   #endif//TRENTINO_HLOGGER
   
   #include "TrentinoUtilsPerformanceHierarchyLogger.inl"



}//namespace Performance
}//namespace Utils
}//namespace Trentino


#endif//TrentinoUtilsPerformanceHierarchyLoggerH