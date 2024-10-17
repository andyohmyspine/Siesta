#include "SiestaEngine.h"
#include "SiestaEditor.h"

#include "Type.h"
#include "SiestaEditor.gen.cpp"

DEFINE_OBJECT_CONSTRUCTOR(SEditorEngine)
{ }

int main()
{
	SEngine* Engine = CreateEngine("SEditorEngine");
	SetFieldValue(Engine, "Lols1", 25.0f);
	SIESTA_BREAK();
}