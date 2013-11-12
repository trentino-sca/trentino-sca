package org.trentino.mmtool.TrentinoMMTool.client;

import com.google.gwt.core.client.GWT;
import com.google.gwt.junit.client.GWTTestCase;
import com.google.gwt.user.client.rpc.AsyncCallback;
import com.google.gwt.user.client.rpc.ServiceDefTarget;

/**
 * GWT JUnit <b>integration</b> tests must extend GWTTestCase.
 * Using <code>"GwtTest*"</code> naming pattern exclude them from running with
 * surefire during the test phase.
 * 
 * If you run the tests using the Maven command line, you will have to 
 * navigate with your browser to a specific url given by Maven. 
 * See http://mojo.codehaus.org/gwt-maven-plugin/user-guide/testing.html 
 * for details.
 */
public class GwtTestTrentinoMMTool extends GWTTestCase {

  /**
   * Must refer to a valid module that sources this class.
   */
  public String getModuleName() {
    return "org.trentino.mmtool.TrentinoMMTool.TrentinoMMToolJUnit";
  }

  /**
   * This test will send a request to the server using the authenticationServer method in
   * authenticationingService and verify the response.
   */
  public void testAuthenticationingService() {
    // Create the service that we will test.
    AuthenticationServiceAsync authenticationService = GWT.create(AuthenticationService.class);
    ServiceDefTarget target = (ServiceDefTarget) authenticationService;
    target.setServiceEntryPoint(GWT.getModuleBaseURL() + "TrentinoMMTool/authentication");

    // Since RPC calls are asynchronous, we will need to wait for a response
    // after this test method returns. This line tells the test runner to wait
    // up to 10 seconds before timing out.
    delayTestFinish(10000);

    // Send a request to the server.
    authenticationService.attempToLogin("GWT User","GWT Password", new AsyncCallback<String>() {
      public void onFailure(Throwable caught) {
        // The request resulted in an unexpected error.
        fail("Request failure: " + caught.getMessage());
      }

      public void onSuccess(String result) {
        // Verify that the response is correct.
        assertTrue(result.startsWith("Hello, GWT User!"));

        // Now that we have received a response, we need to tell the test runner
        // that the test is complete. You must call finishTest() after an
        // asynchronous test finishes successfully, or the test will time out.
        finishTest();
      }
    });
  }


}
