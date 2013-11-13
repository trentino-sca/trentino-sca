/**
 * Autogenerated by Thrift Compiler (0.9.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef OAMService_H
#define OAMService_H

#include <thrift/TDispatchProcessor.h>
#include "OAM_types.h"

namespace siemens { namespace bt { namespace oam {

class OAMServiceIf {
 public:
  virtual ~OAMServiceIf() {}
  virtual void serviceCall( ::siemens::bt::type::ServiceResult& _return, const std::string& authenticationToken, const std::string& viewState, const  ::siemens::bt::type::ServiceCommand& command) = 0;
  virtual void prepareBackgroundImage(ImageResult& _return, const std::string& authToken, const std::string& viewId, const int32_t pageId, const std::string& imageDestPath) = 0;
};

class OAMServiceIfFactory {
 public:
  typedef OAMServiceIf Handler;

  virtual ~OAMServiceIfFactory() {}

  virtual OAMServiceIf* getHandler(const ::apache::thrift::TConnectionInfo& connInfo) = 0;
  virtual void releaseHandler(OAMServiceIf* /* handler */) = 0;
};

class OAMServiceIfSingletonFactory : virtual public OAMServiceIfFactory {
 public:
  OAMServiceIfSingletonFactory(const boost::shared_ptr<OAMServiceIf>& iface) : iface_(iface) {}
  virtual ~OAMServiceIfSingletonFactory() {}

  virtual OAMServiceIf* getHandler(const ::apache::thrift::TConnectionInfo&) {
    return iface_.get();
  }
  virtual void releaseHandler(OAMServiceIf* /* handler */) {}

 protected:
  boost::shared_ptr<OAMServiceIf> iface_;
};

class OAMServiceNull : virtual public OAMServiceIf {
 public:
  virtual ~OAMServiceNull() {}
  void serviceCall( ::siemens::bt::type::ServiceResult& /* _return */, const std::string& /* authenticationToken */, const std::string& /* viewState */, const  ::siemens::bt::type::ServiceCommand& /* command */) {
    return;
  }
  void prepareBackgroundImage(ImageResult& /* _return */, const std::string& /* authToken */, const std::string& /* viewId */, const int32_t /* pageId */, const std::string& /* imageDestPath */) {
    return;
  }
};

typedef struct _OAMService_serviceCall_args__isset {
  _OAMService_serviceCall_args__isset() : authenticationToken(false), viewState(false), command(false) {}
  bool authenticationToken;
  bool viewState;
  bool command;
} _OAMService_serviceCall_args__isset;

class OAMService_serviceCall_args {
 public:

  OAMService_serviceCall_args() : authenticationToken(), viewState() {
  }

  virtual ~OAMService_serviceCall_args() throw() {}

  std::string authenticationToken;
  std::string viewState;
   ::siemens::bt::type::ServiceCommand command;

  _OAMService_serviceCall_args__isset __isset;

  void __set_authenticationToken(const std::string& val) {
    authenticationToken = val;
  }

  void __set_viewState(const std::string& val) {
    viewState = val;
  }

  void __set_command(const  ::siemens::bt::type::ServiceCommand& val) {
    command = val;
  }

  bool operator == (const OAMService_serviceCall_args & rhs) const
  {
    if (!(authenticationToken == rhs.authenticationToken))
      return false;
    if (!(viewState == rhs.viewState))
      return false;
    if (!(command == rhs.command))
      return false;
    return true;
  }
  bool operator != (const OAMService_serviceCall_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const OAMService_serviceCall_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class OAMService_serviceCall_pargs {
 public:


  virtual ~OAMService_serviceCall_pargs() throw() {}

  const std::string* authenticationToken;
  const std::string* viewState;
  const  ::siemens::bt::type::ServiceCommand* command;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _OAMService_serviceCall_result__isset {
  _OAMService_serviceCall_result__isset() : success(false) {}
  bool success;
} _OAMService_serviceCall_result__isset;

class OAMService_serviceCall_result {
 public:

  OAMService_serviceCall_result() {
  }

  virtual ~OAMService_serviceCall_result() throw() {}

   ::siemens::bt::type::ServiceResult success;

  _OAMService_serviceCall_result__isset __isset;

  void __set_success(const  ::siemens::bt::type::ServiceResult& val) {
    success = val;
  }

  bool operator == (const OAMService_serviceCall_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const OAMService_serviceCall_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const OAMService_serviceCall_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _OAMService_serviceCall_presult__isset {
  _OAMService_serviceCall_presult__isset() : success(false) {}
  bool success;
} _OAMService_serviceCall_presult__isset;

class OAMService_serviceCall_presult {
 public:


  virtual ~OAMService_serviceCall_presult() throw() {}

   ::siemens::bt::type::ServiceResult* success;

  _OAMService_serviceCall_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

typedef struct _OAMService_prepareBackgroundImage_args__isset {
  _OAMService_prepareBackgroundImage_args__isset() : authToken(false), viewId(false), pageId(false), imageDestPath(false) {}
  bool authToken;
  bool viewId;
  bool pageId;
  bool imageDestPath;
} _OAMService_prepareBackgroundImage_args__isset;

class OAMService_prepareBackgroundImage_args {
 public:

  OAMService_prepareBackgroundImage_args() : authToken(), viewId(), pageId(0), imageDestPath() {
  }

  virtual ~OAMService_prepareBackgroundImage_args() throw() {}

  std::string authToken;
  std::string viewId;
  int32_t pageId;
  std::string imageDestPath;

  _OAMService_prepareBackgroundImage_args__isset __isset;

  void __set_authToken(const std::string& val) {
    authToken = val;
  }

  void __set_viewId(const std::string& val) {
    viewId = val;
  }

  void __set_pageId(const int32_t val) {
    pageId = val;
  }

  void __set_imageDestPath(const std::string& val) {
    imageDestPath = val;
  }

  bool operator == (const OAMService_prepareBackgroundImage_args & rhs) const
  {
    if (!(authToken == rhs.authToken))
      return false;
    if (!(viewId == rhs.viewId))
      return false;
    if (!(pageId == rhs.pageId))
      return false;
    if (!(imageDestPath == rhs.imageDestPath))
      return false;
    return true;
  }
  bool operator != (const OAMService_prepareBackgroundImage_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const OAMService_prepareBackgroundImage_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class OAMService_prepareBackgroundImage_pargs {
 public:


  virtual ~OAMService_prepareBackgroundImage_pargs() throw() {}

  const std::string* authToken;
  const std::string* viewId;
  const int32_t* pageId;
  const std::string* imageDestPath;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _OAMService_prepareBackgroundImage_result__isset {
  _OAMService_prepareBackgroundImage_result__isset() : success(false) {}
  bool success;
} _OAMService_prepareBackgroundImage_result__isset;

class OAMService_prepareBackgroundImage_result {
 public:

  OAMService_prepareBackgroundImage_result() {
  }

  virtual ~OAMService_prepareBackgroundImage_result() throw() {}

  ImageResult success;

  _OAMService_prepareBackgroundImage_result__isset __isset;

  void __set_success(const ImageResult& val) {
    success = val;
  }

  bool operator == (const OAMService_prepareBackgroundImage_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const OAMService_prepareBackgroundImage_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const OAMService_prepareBackgroundImage_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _OAMService_prepareBackgroundImage_presult__isset {
  _OAMService_prepareBackgroundImage_presult__isset() : success(false) {}
  bool success;
} _OAMService_prepareBackgroundImage_presult__isset;

class OAMService_prepareBackgroundImage_presult {
 public:


  virtual ~OAMService_prepareBackgroundImage_presult() throw() {}

  ImageResult* success;

  _OAMService_prepareBackgroundImage_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

class OAMServiceClient : virtual public OAMServiceIf {
 public:
  OAMServiceClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) :
    piprot_(prot),
    poprot_(prot) {
    iprot_ = prot.get();
    oprot_ = prot.get();
  }
  OAMServiceClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, boost::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) :
    piprot_(iprot),
    poprot_(oprot) {
    iprot_ = iprot.get();
    oprot_ = oprot.get();
  }
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> getInputProtocol() {
    return piprot_;
  }
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> getOutputProtocol() {
    return poprot_;
  }
  void serviceCall( ::siemens::bt::type::ServiceResult& _return, const std::string& authenticationToken, const std::string& viewState, const  ::siemens::bt::type::ServiceCommand& command);
  void send_serviceCall(const std::string& authenticationToken, const std::string& viewState, const  ::siemens::bt::type::ServiceCommand& command);
  void recv_serviceCall( ::siemens::bt::type::ServiceResult& _return);
  void prepareBackgroundImage(ImageResult& _return, const std::string& authToken, const std::string& viewId, const int32_t pageId, const std::string& imageDestPath);
  void send_prepareBackgroundImage(const std::string& authToken, const std::string& viewId, const int32_t pageId, const std::string& imageDestPath);
  void recv_prepareBackgroundImage(ImageResult& _return);
 protected:
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> piprot_;
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> poprot_;
  ::apache::thrift::protocol::TProtocol* iprot_;
  ::apache::thrift::protocol::TProtocol* oprot_;
};

class OAMServiceProcessor : public ::apache::thrift::TDispatchProcessor {
 protected:
  boost::shared_ptr<OAMServiceIf> iface_;
  virtual bool dispatchCall(::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, const std::string& fname, int32_t seqid, void* callContext);
 private:
  typedef  void (OAMServiceProcessor::*ProcessFunction)(int32_t, ::apache::thrift::protocol::TProtocol*, ::apache::thrift::protocol::TProtocol*, void*);
  typedef std::map<std::string, ProcessFunction> ProcessMap;
  ProcessMap processMap_;
  void process_serviceCall(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_prepareBackgroundImage(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
 public:
  OAMServiceProcessor(boost::shared_ptr<OAMServiceIf> iface) :
    iface_(iface) {
    processMap_["serviceCall"] = &OAMServiceProcessor::process_serviceCall;
    processMap_["prepareBackgroundImage"] = &OAMServiceProcessor::process_prepareBackgroundImage;
  }

  virtual ~OAMServiceProcessor() {}
};

class OAMServiceProcessorFactory : public ::apache::thrift::TProcessorFactory {
 public:
  OAMServiceProcessorFactory(const ::boost::shared_ptr< OAMServiceIfFactory >& handlerFactory) :
      handlerFactory_(handlerFactory) {}

  ::boost::shared_ptr< ::apache::thrift::TProcessor > getProcessor(const ::apache::thrift::TConnectionInfo& connInfo);

 protected:
  ::boost::shared_ptr< OAMServiceIfFactory > handlerFactory_;
};

class OAMServiceMultiface : virtual public OAMServiceIf {
 public:
  OAMServiceMultiface(std::vector<boost::shared_ptr<OAMServiceIf> >& ifaces) : ifaces_(ifaces) {
  }
  virtual ~OAMServiceMultiface() {}
 protected:
  std::vector<boost::shared_ptr<OAMServiceIf> > ifaces_;
  OAMServiceMultiface() {}
  void add(boost::shared_ptr<OAMServiceIf> iface) {
    ifaces_.push_back(iface);
  }
 public:
  void serviceCall( ::siemens::bt::type::ServiceResult& _return, const std::string& authenticationToken, const std::string& viewState, const  ::siemens::bt::type::ServiceCommand& command) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->serviceCall(_return, authenticationToken, viewState, command);
    }
    ifaces_[i]->serviceCall(_return, authenticationToken, viewState, command);
    return;
  }

  void prepareBackgroundImage(ImageResult& _return, const std::string& authToken, const std::string& viewId, const int32_t pageId, const std::string& imageDestPath) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->prepareBackgroundImage(_return, authToken, viewId, pageId, imageDestPath);
    }
    ifaces_[i]->prepareBackgroundImage(_return, authToken, viewId, pageId, imageDestPath);
    return;
  }

};

}}} // namespace

#endif