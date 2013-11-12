# Comment blocks should not exceed pre-defined length, see Trentino Coding Style rule C-10
set maxLength [getParameter "max-comment-length" 100]

foreach f [getSourceFileNames] {
    foreach t [getTokens $f 1 0 -1 -1 {cppcomment}] {
        set lineNumber [lindex $t 1]
        set wholeLine [getLine $f $lineNumber]

        if {[string length $wholeLine] > $maxLength} {
            report $f $lineNumber "Comment line is longer than ${maxLength} characters"
        }
    }
}
