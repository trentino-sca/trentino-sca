# Certain keywords shall not be used, see rules N-4 and N-5

set keywords {
    NULL
    BOOL
    TRUE
    FALSE
}

proc isKeyword {s} {
    global keywords
    return [expr [lsearch $keywords $s] != -1]
}

foreach file [getSourceFileNames] {
    foreach t [getTokens $file 1 0 -1 -1 {identifier}] {
        set value [lindex $t 0]
        if [isKeyword $value] {
            report $file [lindex $t 1] "${value} should not be used"
        }
    }
}
