package org.trentino.mmtool.TrentinoMMTool.server;

import javax.servlet.ServletRequest;
//import org.apache.log4j.Logger;

import org.apache.shiro.authc.AuthenticationException;
import org.apache.shiro.web.filter.authc.FormAuthenticationFilter;

public class VerboseFormAuthenticationFilter extends FormAuthenticationFilter {
	//public static Logger logger = Logger.getLogger(VerboseFormAuthenticationFilter.class);
	@Override
	protected void setFailureAttribute(ServletRequest request, AuthenticationException ae) {
		String message = ae.getMessage();
		request.setAttribute(getFailureKeyAttribute(), message);
	}

}
