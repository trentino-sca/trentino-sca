package tidl.samples;

import org.trentino.tidl.TInterface;
import org.trentino.tidl.TInt;
import org.trentino.tidl.Out;;

public interface BasicCalculator extends TInterface{

	ComplexNumber add(ComplexNumber a, ComplexNumber b);
	TInt addSimple(TInt a, TInt b);
	ComplexNumber divide(ComplexNumber a, ComplexNumber b);
	void multiply(ComplexNumber a, ComplexNumber b,@Out ComplexNumber c);
	ComplexNumber divide2 (TupleComplexNumber tuple);
	//TUInt calculateAge (Person person) throws ValidationException;
}
