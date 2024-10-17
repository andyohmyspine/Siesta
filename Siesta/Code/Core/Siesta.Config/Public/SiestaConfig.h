#pragma once

#include "Siesta.ConfigAPI.h"
#include "SiestaCore.h"

#include <nlohmann/json.hpp>

class SConfig;
extern SConfig* GConfig;

class SIESTA_CONFIG_API SConfig
{
public:
	SConfig();
	~SConfig();

private:
	nlohmann::json m_Document;
};