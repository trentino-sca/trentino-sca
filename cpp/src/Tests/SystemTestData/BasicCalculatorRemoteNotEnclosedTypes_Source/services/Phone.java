package Trentino.Example.BasicCalculatorRemote;

import org.trentino.tidl.*;

	class Phone extends TStruct{
	TString home;
	@Default(sv="0123457465")
	TString mobile;
	}
	
