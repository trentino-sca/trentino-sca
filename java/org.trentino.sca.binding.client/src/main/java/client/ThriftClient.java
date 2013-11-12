// ****************************************************************************
// Trentino - A C++ based lightweight, non-invasive SCA runtime.
// Copyright (C) Siemens AG, 2012
// All Rights Reserved
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// ****************************************************************************
package client;

import org.apache.thrift.protocol.TBinaryProtocol;
import org.apache.thrift.protocol.TProtocol;
import org.apache.thrift.transport.TSocket;
import org.apache.thrift.transport.TTransport;
import org.trentino.example.DataService;
import org.trentino.example.UniqueID;

/**
 * @author z002ttbb
 *
 */
public class ThriftClient {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		ThriftClient c = new ThriftClient();
		c.start();

	}
	
	  private void start(){
	      TTransport transport;
	      try {
	         transport = new TSocket("localhost", 9090);
	         TProtocol protocol = new TBinaryProtocol(transport);
	         DataService.Client client = new DataService.Client(protocol);
	         transport.open();
	         UniqueID time = client.createUniqueID();
	         System.out.println("Time from server:" + time);
	         transport.close();
	      }  catch (Exception e) {
	         e.printStackTrace();
	      }
	   }

}
