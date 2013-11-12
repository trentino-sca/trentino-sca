package org.trentino.mmtool.TrentinoMMTool.server;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import javax.naming.InitialContext;
import javax.naming.NamingException;
import javax.sql.DataSource;

import org.apache.shiro.authc.AuthenticationException;
import org.apache.shiro.authc.AuthenticationInfo;
import org.apache.shiro.authc.AuthenticationToken;
import org.apache.shiro.authc.SimpleAuthenticationInfo;
import org.apache.shiro.authc.UsernamePasswordToken;
import org.apache.shiro.authz.AuthorizationException;
import org.apache.shiro.realm.jdbc.JdbcRealm;
import org.apache.shiro.util.JdbcUtils;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

/**
 * This realm has all {@link JdbcRealm} capabilities. It also supports JNDI as datasource source and
 * can add salt to passwords.
 */
public class DatabaseRealm extends JdbcRealm {

	private static final Logger log = LoggerFactory.getLogger(DatabaseRealm.class);

	protected String jndiDataSourceName;

	public DatabaseRealm() {
	}

	public String getJndiDataSourceName() {
		return jndiDataSourceName;
	}

	public void setJndiDataSourceName(String jndiDataSourceName) {
		this.jndiDataSourceName = jndiDataSourceName;
		this.dataSource = getDataSourceFromJNDI(jndiDataSourceName);
	}

	private DataSource getDataSourceFromJNDI(String jndiDataSourceName) {
		try {
			InitialContext ic = new InitialContext();
			return (DataSource) ic.lookup(jndiDataSourceName);
		} catch (NamingException e) {
			log.error("JNDI error while retrieving " + jndiDataSourceName, e);
			throw new AuthorizationException(e);
		}
	}

	@Override
	protected AuthenticationInfo doGetAuthenticationInfo(AuthenticationToken token) throws AuthenticationException {
		//identify account to log to
		UsernamePasswordToken userPassToken = (UsernamePasswordToken) token;
		String username = userPassToken.getUsername();

		if (username == null) {
			log.debug("Username is null.");
			return null;
		}

		String passwd = getPasswordForUser(username);

		if (passwd == null) {
			log.debug("No account found for user [" + username + "]");
			return null;
		}

		SimpleAuthenticationInfo info = new SimpleAuthenticationInfo(username, passwd, getName());
		return info;
	}

	private String getPasswordForUser(String username) {
		PreparedStatement statement = null;
		ResultSet resultSet = null;
		Connection conn = null;
		try {
			conn = dataSource.getConnection();
			statement = conn.prepareStatement(authenticationQuery);
			statement.setString(1, username);

			resultSet = statement.executeQuery();

			boolean hasAccount = resultSet.next();
			if (!hasAccount)
				return null;

			String password = resultSet.getString(1);
			if (resultSet.next()) {
				throw new AuthenticationException("More than one user row found for user [" + username + "]. Usernames must be unique.");
			}

			return password;
		} catch (SQLException e) {
			final String message = "There was a SQL error while authenticating user [" + username + "]";
			if (log.isErrorEnabled()) {
				log.error(message, e);
			}
			throw new AuthenticationException(message, e);

		} finally {
			JdbcUtils.closeResultSet(resultSet);
			JdbcUtils.closeStatement(statement);
			JdbcUtils.closeConnection(conn);
		}
	}
}