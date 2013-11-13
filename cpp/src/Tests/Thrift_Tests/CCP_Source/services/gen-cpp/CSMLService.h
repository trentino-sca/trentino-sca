/**
 * Autogenerated by Thrift Compiler (0.9.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef CSMLService_H
#define CSMLService_H

#include <thrift/TDispatchProcessor.h>
#include "CSML_types.h"

namespace siemens { namespace bt { namespace csml {

class CSMLServiceIf {
 public:
  virtual ~CSMLServiceIf() {}
  virtual void getInterfaceVersion(std::string& _return) = 0;
  virtual void CSMLRequest(std::string& _return, const std::string& p_Request) = 0;
};

class CSMLServiceIfFactory {
 public:
  typedef CSMLServiceIf Handler;

  virtual ~CSMLServiceIfFactory() {}

  virtual CSMLServiceIf* getHandler(const ::apache::thrift::TConnectionInfo& connInfo) = 0;
  virtual void releaseHandler(CSMLServiceIf* /* handler */) = 0;
};

class CSMLServiceIfSingletonFactory : virtual public CSMLServiceIfFactory {
 public:
  CSMLServiceIfSingletonFactory(const boost::shared_ptr<CSMLServiceIf>& iface) : iface_(iface) {}
  virtual ~CSMLServiceIfSingletonFactory() {}

  virtual CSMLServiceIf* getHandler(const ::apache::thrift::TConnectionInfo&) {
    return iface_.get();
  }
  virtual void releaseHandler(CSMLServiceIf* /* handler */) {}

 protected:
  boost::shared_ptr<CSMLServiceIf> iface_;
};

class CSMLServiceNull : virtual public CSMLServiceIf {
 public:
  virtual ~CSMLServiceNull() {}
  void getInterfaceVersion(std::string& /* _return */) {
    return;
  }
  void CSMLRequest(std::string& /* _return */, const std::string& /* p_Request */) {
    return;
  }
};


class CSMLService_getInterfaceVersion_args {
 public:

  CSMLService_getInterfaceVersion_args() {
  }

  virtual ~CSMLService_getInterfaceVersion_args() throw() {}


  bool operator == (const CSMLService_getInterfaceVersion_args & /* rhs */) const
  {
    return true;
  }
  bool operator != (const CSMLService_getInterfaceVersion_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const CSMLService_getInterfaceVersion_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class CSMLService_getInterfaceVersion_pargs {
 public:


  virtual ~CSMLService_getInterfaceVersion_pargs() throw() {}


  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _CSMLService_getInterfaceVersion_result__isset {
  _CSMLService_getInterfaceVersion_result__isset() : success(false) {}
  bool success;
} _CSMLService_getInterfaceVersion_result__isset;

class CSMLService_getInterfaceVersion_result {
 public:

  CSMLService_getInterfaceVersion_result() : success() {
  }

  virtual ~CSMLService_getInterfaceVersion_result() throw() {}

  std::string success;

  _CSMLService_getInterfaceVersion_result__isset __isset;

  void __set_success(const std::string& val) {
    success = val;
  }

  bool operator == (const CSMLService_getInterfaceVersion_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const CSMLService_getInterfaceVersion_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const CSMLService_getInterfaceVersion_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _CSMLService_getInterfaceVersion_presult__isset {
  _CSMLService_getInterfaceVersion_presult__isset() : success(false) {}
  bool success;
} _CSMLService_getInterfaceVersion_presult__isset;

class CSMLService_getInterfaceVersion_presult {
 public:


  virtual ~CSMLService_getInterfaceVersion_presult() throw() {}

  std::string* success;

  _CSMLService_getInterfaceVersion_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

typedef struct _CSMLService_CSMLRequest_args__isset {
  _CSMLService_CSMLRequest_args__isset() : p_Request(false) {}
  bool p_Request;
} _CSMLService_CSMLRequest_args__isset;

class CSMLService_CSMLRequest_args {
 public:

  CSMLService_CSMLRequest_args() : p_Request() {
  }

  virtual ~CSMLService_CSMLRequest_args() throw() {}

  std::string p_Request;

  _CSMLService_CSMLRequest_args__isset __isset;

  void __set_p_Request(const std::string& val) {
    p_Request = val;
  }

  bool operator == (const CSMLService_CSMLRequest_args & rhs) const
  {
    if (!(p_Request == rhs.p_Request))
      return false;
    return true;
  }
  bool operator != (const CSMLService_CSMLRequest_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const CSMLService_CSMLRequest_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class CSMLService_CSMLRequest_pargs {
 public:


  virtual ~CSMLService_CSMLRequest_pargs() throw() {}

  const std::string* p_Request;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _CSMLService_CSMLRequest_result__isset {
  _CSMLService_CSMLRequest_result__isset() : success(false) {}
  bool success;
} _CSMLService_CSMLRequest_result__isset;

class CSMLService_CSMLRequest_result {
 public:

  CSMLService_CSMLRequest_result() : success() {
  }

  virtual ~CSMLService_CSMLRequest_result() throw() {}

  std::string success;

  _CSMLService_CSMLRequest_result__isset __isset;

  void __set_success(const std::string& val) {
    success = val;
  }

  bool operator == (const CSMLService_CSMLRequest_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const CSMLService_CSMLRequest_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const CSMLService_CSMLRequest_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _CSMLService_CSMLRequest_presult__isset {
  _CSMLService_CSMLRequest_presult__isset() : success(false) {}
  bool success;
} _CSMLService_CSMLRequest_presult__isset;

class CSMLService_CSMLRequest_presult {
 public:


  virtual ~CSMLService_CSMLRequest_presult() throw() {}

  std::string* success;

  _CSMLService_CSMLRequest_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

class CSMLServiceClient : virtual public CSMLServiceIf {
 public:
  CSMLServiceClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) :
    piprot_(prot),
    poprot_(prot) {
    iprot_ = prot.get();
    oprot_ = prot.get();
  }
  CSMLServiceClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, boost::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) :
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
  void getInterfaceVersion(std::string& _return);
  void send_getInterfaceVersion();
  void recv_getInterfaceVersion(std::string& _return);
  void CSMLRequest(std::string& _return, const std::string& p_Request);
  void send_CSMLRequest(const std::string& p_Request);
  void recv_CSMLRequest(std::string& _return);
 protected:
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> piprot_;
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> poprot_;
  ::apache::thrift::protocol::TProtocol* iprot_;
  ::apache::thrift::protocol::TProtocol* oprot_;
};

class CSMLServiceProcessor : public ::apache::thrift::TDispatchProcessor {
 protected:
  boost::shared_ptr<CSMLServiceIf> iface_;
  virtual bool dispatchCall(::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, const std::string& fname, int32_t seqid, void* callContext);
 private:
  typedef  void (CSMLServiceProcessor::*ProcessFunction)(int32_t, ::apache::thrift::protocol::TProtocol*, ::apache::thrift::protocol::TProtocol*, void*);
  typedef std::map<std::string, ProcessFunction> ProcessMap;
  ProcessMap processMap_;
  void process_getInterfaceVersion(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_CSMLRequest(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
 public:
  CSMLServiceProcessor(boost::shared_ptr<CSMLServiceIf> iface) :
    iface_(iface) {
    processMap_["getInterfaceVersion"] = &CSMLServiceProcessor::process_getInterfaceVersion;
    processMap_["CSMLRequest"] = &CSMLServiceProcessor::process_CSMLRequest;
  }

  virtual ~CSMLServiceProcessor() {}
};

class CSMLServiceProcessorFactory : public ::apache::thrift::TProcessorFactory {
 public:
  CSMLServiceProcessorFactory(const ::boost::shared_ptr< CSMLServiceIfFactory >& handlerFactory) :
      handlerFactory_(handlerFactory) {}

  ::boost::shared_ptr< ::apache::thrift::TProcessor > getProcessor(const ::apache::thrift::TConnectionInfo& connInfo);

 protected:
  ::boost::shared_ptr< CSMLServiceIfFactory > handlerFactory_;
};

class CSMLServiceMultiface : virtual public CSMLServiceIf {
 public:
  CSMLServiceMultiface(std::vector<boost::shared_ptr<CSMLServiceIf> >& ifaces) : ifaces_(ifaces) {
  }
  virtual ~CSMLServiceMultiface() {}
 protected:
  std::vector<boost::shared_ptr<CSMLServiceIf> > ifaces_;
  CSMLServiceMultiface() {}
  void add(boost::shared_ptr<CSMLServiceIf> iface) {
    ifaces_.push_back(iface);
  }
 public:
  void getInterfaceVersion(std::string& _return) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->getInterfaceVersion(_return);
    }
    ifaces_[i]->getInterfaceVersion(_return);
    return;
  }

  void CSMLRequest(std::string& _return, const std::string& p_Request) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->CSMLRequest(_return, p_Request);
    }
    ifaces_[i]->CSMLRequest(_return, p_Request);
    return;
  }

};

}}} // namespace

#endif
