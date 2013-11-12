package org.trentino.mmtool.TrentinoMMTool.server;

import org.apache.shiro.SecurityUtils;
import org.apache.shiro.authc.IncorrectCredentialsException;
import org.apache.shiro.authc.LockedAccountException;
import org.apache.shiro.authc.UnknownAccountException;
import org.apache.shiro.authc.UsernamePasswordToken;
import org.trentino.mmtool.TrentinoMMTool.client.AuthenticationService;

import com.google.gwt.user.server.rpc.RemoteServiceServlet;

@SuppressWarnings("serial")
public class AuthenticationServiceImpl extends RemoteServiceServlet implements AuthenticationService {

	public String attempToLogin(String name, String password) throws IllegalArgumentException {
		org.apache.shiro.subject.Subject currentUser = SecurityUtils.getSubject();

		UsernamePasswordToken token = new UsernamePasswordToken(name, password);
		token.setRememberMe(true);
		try {
			currentUser.login(token);
		} catch (UnknownAccountException uae) {
			throw new IllegalArgumentException("There is no user with username of " + token.getPrincipal());
		} catch (IncorrectCredentialsException ice) {
			throw new IllegalArgumentException("Password for account " + token.getPrincipal() + " was incorrect!");
		} catch (LockedAccountException lae) {
			throw new IllegalArgumentException("The account for username " + token.getPrincipal() + " is locked.  " +
					"Please contact your administrator to unlock it.");
		}
		return "Authentication is successful!";
	}

}
