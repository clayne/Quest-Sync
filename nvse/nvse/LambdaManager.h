#pragma once
#include "GameScript.h"

class ExpressionEvaluator;

namespace LambdaManager
{
	extern ICriticalSection g_lambdaCs;
	struct ScriptData
	{
		UInt8* scriptData;
		UInt32 size;
		ScriptData() = default;
		ScriptData(UInt8* scriptData, UInt32 size) : scriptData(scriptData), size(size){}
	};

	class LambdaVariableContext
	{
		Script* scriptLambda;
	public:
		LambdaVariableContext(Script* scriptLambda);
		~LambdaVariableContext();
	};
	
	Script* CreateLambdaScript(UInt8* position, const ScriptData& scriptData, const ExpressionEvaluator&);
	ScriptEventList* GetParentEventList(Script* scriptLambda);
	void MarkParentAsDeleted(ScriptEventList* parentEventList);
	bool IsScriptLambda(Script* scriptLambda);
	void DeleteAllForParentScript(Script* parentScript);
	void ClearSavedDeletedEventLists();

	// makes sure that a variable list is not deleted by the game while a lambda is still pending execution
	void SaveLambdaVariables(Script* scriptLambda);
	void UnsaveLambdaVariables(Script* scriptLambda);

	void MarkAsStoredInVariable(Script* scriptLambda);
	void MarkAsRemovedFromVariable(Script* scriptLambda);
}
