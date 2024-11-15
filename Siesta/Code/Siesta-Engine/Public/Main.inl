#pragma once

int main()
{
	PUniquePtr<SEngine> Engine = WrapUnique(CreateEngine());
	Engine->Run();
}
