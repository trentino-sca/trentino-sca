package client;

import java.io.ByteArrayOutputStream;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.Random;

import com.google.protobuf.ByteString;
import compact_soap.CompactSoap;
import compact_soap.CompactSoap.Soap;
import compact_soap.WsAddressing;

import example.basicCalculator.CalculatorMessage;

public class Main {

	private DataOutputStream outToServer;
	private Socket clientSocket;

	public Main() throws UnknownHostException, IOException {
		clientSocket = new Socket("localhost", 1234);
		outToServer = new DataOutputStream(clientSocket.getOutputStream());
	}

	/**
	 * @param args
	 * @throws IOException
	 * @throws UnknownHostException
	 */
	public static void main(String[] args) throws UnknownHostException,
			IOException {
		// -1321900402, 1781397451
		Main main = new Main();
		StringBuffer bigString = new StringBuffer("bb");
		for(int i=0; i<20;i++){
			bigString.append(bigString.toString());
		}
		bigString.insert(0, 'a');
		bigString.append("c");
		String val = bigString.toString();
		String resp = main.reverse(val);
		if(resp.length()!=val.length()) {
			System.out.println("request and result has differents lengths");
		}
		if(!resp.startsWith("c")){
			System.out.println("Result should start with c");
		}
		if(!resp.endsWith("a")){
			System.out.println("Result should end with a");
		}
		testAdd(main);
	}

	private static void testAdd(Main main) {
		int a, b;

		for (int i = 0; i < 1000; i++) {
			Random r = new Random();
			a = r.nextInt();
			b = r.nextInt();
			int c = main.add(a, b);
			if (c != (a + b)) {
				System.out.println(String.format("a=%d, b=%d, result=%d", a, b,
						c));
			}
		}
	}

	private String reverse(String val) {
		CompactSoap.Soap.Header.Builder headerBuilde = createHeader(
				"tcp://localhost:1234/Calculator", null, "Calculator/reverse");
		ByteString request = getReverseRequest(val);
		CompactSoap.Soap soap = createSoapMessage(request, headerBuilde);

		try {
			Soap result = sendMessage(soap);
			ByteString content = result.getEnvelope().getBody().getContent();
			System.out.println("Length: " + content.size());
			return CalculatorMessage.Calculator.reverseResponse.parseFrom(content)
					.getResult();

		} catch (Exception e) {
			return null;
		}
	}

	private int add(int a, int b) {
		CompactSoap.Soap.Header.Builder headerBuilde = createHeader(
				"tcp://localhost:1234/Calculator", null, "Calculator/add");
		ByteString request = getAddRequest(a, b);
		CompactSoap.Soap soap = createSoapMessage(request, headerBuilde);

		try {
			Soap result = sendMessage(soap);
			ByteString content = result.getEnvelope().getBody().getContent();
			System.out.println("Length: " + content.size());
			return CalculatorMessage.Calculator.addResponse.parseFrom(content)
					.getResult();

		} catch (Exception e) {
			return -1;
		}
	}

	private static CompactSoap.Soap createSoapMessage(ByteString request,
			CompactSoap.Soap.Header.Builder headerBuilder) {
		CompactSoap.Soap.Builder soapBuilder = CompactSoap.Soap.newBuilder();
		compact_soap.CompactSoap.Soap.Envelope.Builder envelope = soapBuilder
				.getEnvelopeBuilder();
		compact_soap.CompactSoap.Soap.Body.Builder body = envelope
				.getBodyBuilder();
		body.setContent(request);
		envelope.setBody(body);
		envelope.setHeader(headerBuilder);
		soapBuilder.setEnvelope(envelope);

		CompactSoap.Soap soap = soapBuilder.build();
		return soap;
	}

	private static CompactSoap.Soap.Header.Builder createHeader(String to,
			String replyTo, String action) {
		WsAddressing.Addressing.Builder addressingBuilder = WsAddressing.Addressing
				.newBuilder();
		addressingBuilder.setTo(to);
		addressingBuilder.setAction(action);
		addressingBuilder.setFrom("default");
		CompactSoap.Soap.Header.Builder headerBuilde = CompactSoap.Soap.Header
				.newBuilder();
		headerBuilde.setAddressing(addressingBuilder);
		return headerBuilde;
	}

	private static ByteString getReverseRequest(String val) {
		CalculatorMessage.Calculator.Builder calculator = CalculatorMessage.Calculator
				.newBuilder();
		CalculatorMessage.Calculator.reverseRequest.Builder reverseReq = calculator
				.getReverseRqBuilder();
		reverseReq.setVal(val);
		CalculatorMessage.Calculator.reverseRequest fAddRq = reverseReq.build();
		return buildToByteString(fAddRq);
	}



	private static ByteString getAddRequest(int a, int b) {
		CalculatorMessage.Calculator.Builder calculator = CalculatorMessage.Calculator
				.newBuilder();
		CalculatorMessage.Calculator.addRequest.Builder addRq = calculator
				.getAddRqBuilder();
		addRq.setA(a);
		addRq.setB(b);
		CalculatorMessage.Calculator.addRequest fAddRq = addRq.build();
		return buildToByteString(fAddRq);
	}
	
	
	private static ByteString buildToByteString(
			com.google.protobuf.AbstractMessageLite fAddRq) {
		ByteArrayOutputStream bos = new ByteArrayOutputStream();
		try {
			fAddRq.writeTo(bos);
		} catch (IOException e) {
			e.printStackTrace();
		}
		return ByteString.copyFrom(bos.toByteArray());
	}
	
	
	private Soap sendMessage(Soap soap) throws Exception {
		Soap result;
        int size = soap.getSerializedSize();
        outToServer.writeInt(size);
		soap.writeTo(outToServer);
		result = readFromServer(clientSocket.getInputStream());
		return result;
	}

	private static Soap readFromServer(InputStream isN) {


		
		ByteArrayOutputStream buffer = new ByteArrayOutputStream();
		try {
	        DataInputStream dis = new DataInputStream(isN);
	       int size = dis.readInt();
			int readed = 0;
			byte[] res = new byte[100];
			// Soap s = Soap.parseFrom(isN);
			while ((readed = isN.read(res)) != -1) {
				buffer.write(res, 0, readed);
				if (isN.available() == 0) {
					break;
				}
				res = new byte[100];
			}
			return Soap.parseFrom(buffer.toByteArray());
		} catch (Exception e) {
			e.printStackTrace();

		}
		return null;
	}

}
