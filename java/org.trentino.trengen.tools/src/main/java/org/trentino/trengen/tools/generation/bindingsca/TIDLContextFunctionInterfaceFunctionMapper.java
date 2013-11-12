package org.trentino.trengen.tools.generation.bindingsca;

import java.util.ArrayList;
import java.util.List;
import java.util.Set;

import org.trentino.trengen.cpp.model.ClassMethodArgument;
import org.trentino.trengen.tools.bindingsca.TIDLFunctionModel;
import org.trentino.trengen.tools.bindingsca.TIDLParameterModel;

public class TIDLContextFunctionInterfaceFunctionMapper {

	private Set<ContextCppInterface>	protobufContexts;
	private List<String>	          inOutParams	         = new ArrayList<String>();
	private List<TIDLParameterModel>	inOutParamsTIDLParam	= new ArrayList<TIDLParameterModel>();

	public TIDLContextFunctionInterfaceFunctionMapper (Set<ContextCppInterface> protoBufContexts) {

		protobufContexts = protoBufContexts;
	}

	public TIDLFunctionModel findMatchinProtoFunction(String returnType, String funcName, List<ClassMethodArgument> arguments) {
		for (ContextCppInterface contextProto : protobufContexts)
		{
			for (TIDLFunctionModel func : contextProto.getTidlInterfaceModel().getFunctions())
			{
				if(!func.getName().equals(funcName))
				{
					continue;
				}
				returnType = returnType.replace("&", "");
				returnType = returnType.replace("*", "");
				returnType = returnType.replace("const", "");
				String protoFuncReturnType = func.getReturnType().getQualifiedName();
				if(!protoFuncReturnType.equals(returnType))
				{
					continue;
				}

				List<TIDLParameterModel> paramsOfProtoFunc = func.getArguments();

				for (int i = 0; i < arguments.size(); i++)
				{
					ClassMethodArgument argumentType = arguments.get(i);
					String argType = argumentType.getType();
					argType = argType.replace("&", "");
					argType = argType.replace("*", "");
					argType = argType.replace("const", "");
					String protoFuncArgType = paramsOfProtoFunc.get(i).getType().getQualifiedName().replace(".", "::");
					if(!protoFuncArgType.equals(argType))
					{
						continue;
					}

				}
				return func;
			}
			return null;
		}
		TIDLFunctionModel emptyFuncModel = new TIDLFunctionModel();
		return emptyFuncModel;
	}

	public List<TIDLParameterModel> getOutParams(String returnType, String funcName, List<ClassMethodArgument> paramList) {
		inOutParams.clear();
		inOutParamsTIDLParam.clear();
		TIDLFunctionModel funcModel = findMatchinProtoFunction(returnType, funcName, paramList);
		if(funcModel == null)
		{
			// return inOutParams;
			return inOutParamsTIDLParam;
		}
		for (TIDLParameterModel param : funcModel.getArguments())
		{
			if(param.isHasOut() || param.isHasInOut())
			{
				inOutParams.add(param.getName());
				inOutParamsTIDLParam.add(param);
			}
		}
		// return inOutParams;
		return inOutParamsTIDLParam;
	}

}
