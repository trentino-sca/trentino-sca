#remove the reflections for new methods for LoggerFileProxy and LoggerConsoleProxy
s/\(.*{[[:space:]]*\)\"new\"\(,[[:space:]]*\".*LoggerFileProxy.*},\)/\1\"NoNew"\2/
s/\(.*{[[:space:]]*\)\"new\"\(,[[:space:]]*\".*LoggerConsoleProxy.*},\)/\1\"NoNew"\2/
