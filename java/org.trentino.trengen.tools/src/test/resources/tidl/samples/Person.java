package tidl.samples;

import org.trentino.tidl.TStruct;
import org.trentino.tidl.TString;

public class Person extends TStruct{
Address addres;
TString name;
TString surname;
Person mother;
}