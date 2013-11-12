package Trentino.Example.HelloWorldRemote;

//We should ALWAYS Import org.trentino.tidl.* in a TIDL file
import org.trentino.tidl.*;

/**
* HelloWord Service, receive hello world messages 
* and send wellcome to the client.
**/
public interface HelloWorld extends TInterface{

enum MessageType {
GOOD_MORNING,
GOOD_AFTERNOON,
GOOD_EVENING
}

/**
* The server receive an Hello message and send a 
* wellcome message back to the client who sent 
* the message
* @param name: the name of the client who sent the message
* @return TString a welcome message
**/
TString hello(TString name, MessageType messageType);
}
