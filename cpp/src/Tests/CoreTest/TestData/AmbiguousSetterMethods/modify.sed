#add an overload 
/^.*Trentino::Reflection::Data::Method::Param setExecuteLinker[[:digit:]]*MethodParams.*$/a\
static const Trentino::Reflection::Data::Method::Param setExecuteLinkerMethodParams2__[] = {"Something" };

/^.*{[[:space:]]*\"setExecuteLinker\".*}/a\
{ "setExecuteLinker", 0, setExecuteLinkerMethodParams2__, COUNT_OF(setExecuteLinkerMethodParams2__), setExecuteLinkerMethod },

