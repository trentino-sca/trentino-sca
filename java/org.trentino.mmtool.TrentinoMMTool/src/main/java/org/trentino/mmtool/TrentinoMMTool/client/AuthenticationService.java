package org.trentino.mmtool.TrentinoMMTool.client;

import com.google.gwt.user.client.rpc.RemoteService;
import com.google.gwt.user.client.rpc.RemoteServiceRelativePath;

/**
 * The client side stub for the RPC service.
 */
@RemoteServiceRelativePath("authentication")
public interface AuthenticationService extends RemoteService {
	String attempToLogin(String name, String password) throws IllegalArgumentException;
}
