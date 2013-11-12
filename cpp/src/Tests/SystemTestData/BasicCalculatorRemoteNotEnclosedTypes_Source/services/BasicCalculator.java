package Trentino.Example.BasicCalculatorRemote;

import org.trentino.tidl.*;

public interface BasicCalculator extends TInterface{

	ComplexNumber add(ComplexNumber a, ComplexNumber b);
	TInt addSimple(TInt a, TInt b);
	ComplexNumber divide(ComplexNumber a, ComplexNumber b);
	void multiply(ComplexNumber a, ComplexNumber b,@InOut ComplexNumber c);
	ComplexNumber divide2 (TupleComplexNumber tuple);
	TUInt calculateAge (Person person) throws ValidationException;
	
	class ValidationException extends TException{
     TString details;
    }
	 
	 class Address extends TStruct{
	 @Default(sv="uoa")
	  TString street;
	  
	  Phone phone;
	}
	class TupleComplexNumber extends TStruct{
		ComplexNumber a;
		ComplexNumber b;
	}
	
	

	 class Person extends TStruct{
		Address addres;
		TString name;
		TString surname;
     }
}
