#pragma once

#include "SiestaEngine.h"
#include "SiestaEditor.gen.h"

expose_object()
class SEditorEngine : public SEngine
{
	generated_code();

public:
	DECLARE_OBJECT_CONSTRUCTOR(SEditorEngine);
};