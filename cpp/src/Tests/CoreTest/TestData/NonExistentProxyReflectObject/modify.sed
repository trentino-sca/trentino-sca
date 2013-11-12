#remove the registrations of proxy reflection for LoggerConsoleReflx and LoggerFileReflx
s/[[:space:]]*static[[:space:]]*Initializer.*LoggerConsoleProxyRflx.*;//
s/[[:space:]]*static[[:space:]]*Initializer.*LoggerFileProxyRflx.*;//