#include "SiestaEngine.h"
#include "SiestaEditor.h"

#include "Type.h"
#include "SiestaEditor.gen.cpp"

DEFINE_OBJECT_CONSTRUCTOR(SEditorEngine)
{ }

int main()
{
	SEngine* Engine = CreateEngine("SEditorEngine");
	Engine->BeginMainLoop();
	delete Engine;
}