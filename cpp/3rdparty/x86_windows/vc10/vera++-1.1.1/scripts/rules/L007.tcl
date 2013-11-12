# Tab size
set tabSize [getParameter "tab-size" 3]

foreach f [getSourceFileNames] {
set lineNumber 1 
    foreach line [getAllLines $f] {
             
        if [regexp {^([ ]+).*$} $line -> leadingspaces] {
            if { [expr [string length $leadingspaces] % $tabSize] != 0} {
                report $f $lineNumber "Indent sise shall be $tabSize \'$leadingspaces\'"
           }
        }
        incr lineNumber
    }

}
