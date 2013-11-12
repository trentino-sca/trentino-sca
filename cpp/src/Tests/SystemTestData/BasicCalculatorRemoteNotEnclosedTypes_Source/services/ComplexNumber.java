package Trentino.Example.BasicCalculatorRemote;

import org.trentino.tidl.*;

public class ComplexNumber extends TStruct{
    @Default(nv=-1)
	TInt a;
	TInt b;
}
