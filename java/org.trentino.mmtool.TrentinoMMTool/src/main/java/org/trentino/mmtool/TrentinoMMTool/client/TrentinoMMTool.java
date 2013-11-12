package org.trentino.mmtool.TrentinoMMTool.client;

import com.google.gwt.core.client.EntryPoint;
import com.google.gwt.core.client.GWT;
import com.google.gwt.event.dom.client.ClickEvent;
import com.google.gwt.event.dom.client.ClickHandler;
import com.google.gwt.user.client.rpc.AsyncCallback;
import com.google.gwt.user.client.ui.Button;
import com.google.gwt.user.client.ui.DialogBox;
import com.google.gwt.user.client.ui.HTML;
import com.google.gwt.user.client.ui.Label;
import com.google.gwt.user.client.ui.PasswordTextBox;
import com.google.gwt.user.client.ui.RootPanel;
import com.google.gwt.user.client.ui.TextBox;
import com.google.gwt.user.client.ui.VerticalPanel;
import com.google.gwt.user.client.ui.DecoratedTabBar;
import com.google.gwt.user.client.ui.Hyperlink;
import com.google.gwt.event.dom.client.BlurHandler;
import com.google.gwt.event.dom.client.BlurEvent;

/**
 * Entry point classes define <code>onModuleLoad()</code>.
 */
public class TrentinoMMTool implements EntryPoint {

	/**
	 * Create a remote service proxy to talk to the server-side Greeting service.
	 */
	private final AuthenticationServiceAsync shiroService = GWT.create(AuthenticationService.class);
	private final Messages messages = GWT.create(Messages.class);

	/**
	 * This is the entry point method.
	 */
	public void onModuleLoad() {

		final Button sendButton = new Button( messages.sendButton() );
		sendButton.setStyleName("sendButton");
		sendButton.setText(messages.sendButton());
		// We can add style names to widgets
		sendButton.addStyleName("sendButton");

		final TextBox nameField = new TextBox();
		nameField.addBlurHandler(new BlurHandler() {
			public void onBlur(BlurEvent arg0) {
				if(nameField.getValue().trim().equals(""))
					nameField.setValue(messages.nameField());
			}
		});
		nameField.addClickHandler(new ClickHandler() {
			public void onClick(ClickEvent arg0) {
				if(nameField.getValue().equals(messages.nameField()))
					nameField.setValue("");
			}
		});
		nameField.setText( messages.nameField() );

		final Label errorLabel = new Label();

		// Use RootPanel.get() to get the entire body element
		RootPanel rootPanel = RootPanel.get("nameFieldContainer");
		rootPanel.add(nameField, 10, 74);
		nameField.setSize("180px", "16px");
		nameField.setSize("180px", "16px");

		RootPanel.get("sendButtonContainer").add(sendButton, 140, 156);
		sendButton.setSize("58px", "24px");

		RootPanel.get("errorLabelContainer").add(errorLabel);

		// Focus the cursor on the name field when the app loads
		nameField.setFocus(true);

		final PasswordTextBox passwordField = new PasswordTextBox();
		passwordField.addBlurHandler(new BlurHandler() {
			public void onBlur(BlurEvent arg0) {
				if(passwordField.getValue().trim().equals(""))
					passwordField.setValue(messages.passwordField());
			}
		});
		passwordField.addClickHandler(new ClickHandler() {
			public void onClick(ClickEvent arg0) {
				if(passwordField.getValue().equals(messages.passwordField()))
					passwordField.setValue("");
			}
		});
		passwordField.setText(messages.passwordField());
		passwordField.setFocus(true);
		rootPanel.add(passwordField, 10, 126);
		passwordField.setSize("180px", "16px");

		DecoratedTabBar decoratedTabBar = new DecoratedTabBar();
		decoratedTabBar.addTab("Trentino Management and Monitoring Login");
		rootPanel.add(decoratedTabBar, 10, 20);
		decoratedTabBar.setSize("430px", "26px");

		Hyperlink hprlnkForgotMyPassword = new Hyperlink(messages.hprlnkForgotMyPassword_text(), false, "newHistoryToken");
		rootPanel.add(hprlnkForgotMyPassword, 10, 164);

		Label lblUser = new Label(messages.lblUser_text());
		rootPanel.add(lblUser, 10, 52);

		Label lblUserPassword = new Label(messages.lblUserPassword_text());
		rootPanel.add(lblUserPassword, 10, 104);
		lblUserPassword.setSize("105px", "16px");
		nameField.selectAll();

		// Create the popup dialog box
		final DialogBox dialogBox = new DialogBox();
		dialogBox.setText("Authentication");
		dialogBox.setAnimationEnabled(true);
		final Button closeButton = new Button("Close");

		// We can set the id of a widget by accessing its Element
		closeButton.getElement().setId("closeButton");
		final Label textToServerLabel = new Label();
		final HTML serverResponseLabel = new HTML();
		VerticalPanel dialogVPanel = new VerticalPanel();
		dialogVPanel.addStyleName("dialogVPanel");
		dialogVPanel.add(new HTML("<b>Authenticating the user...</b><br>"));
		dialogVPanel.add(textToServerLabel);
		dialogVPanel.add(new HTML("<br>"));
		dialogVPanel.add(serverResponseLabel);
		dialogVPanel.add(new HTML("<br>"));
		dialogVPanel.setHorizontalAlignment(VerticalPanel.ALIGN_RIGHT);
		dialogVPanel.add(closeButton);
		dialogBox.setWidget(dialogVPanel);

		// Add a handler to close the DialogBox
		closeButton.addClickHandler(new ClickHandler() {
			public void onClick(ClickEvent event) {
				dialogBox.hide();
				sendButton.setEnabled(true);
				sendButton.setFocus(true);
			}
		});

		// Create a handler for the sendButton and nameField
		class MyHandler implements ClickHandler {
			/**
			 * Fired when the user clicks on the sendButton.
			 */
			public void onClick(ClickEvent event) {
				attempToLogin();
			}

			private void attempToLogin() {
				String textToServer = nameField.getText();
				textToServerLabel.setText(textToServer);
				serverResponseLabel.setText("");
				shiroService.attempToLogin(nameField.getText(), passwordField.getText(), new AsyncCallback<String>() {
					public void onFailure(Throwable caught) {
						dialogBox.setText("Login Failure");
						serverResponseLabel.addStyleName("serverResponseLabelError");
						serverResponseLabel.setHTML(caught.getMessage());
						dialogBox.center();
						closeButton.setFocus(true);
					}

					public void onSuccess(String result) {
						dialogBox.setText("Successfull Login");
						serverResponseLabel.removeStyleName("serverResponseLabelError");
						serverResponseLabel.setHTML(result);
						dialogBox.center();
						closeButton.setFocus(true);
					}
				});
			}
		}

		// Add a handler to send the name to the server
		MyHandler handler = new MyHandler();
		sendButton.addClickHandler(handler);
	}
}
