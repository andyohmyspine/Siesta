#pragma once

#include "ConfigAPI.h"
#include "SiestaCore.h"

#include <nlohmann/json.hpp>

class SConfig;
extern SConfig* GConfig;

class CONFIG_API SConfig
{
public:
	SConfig();
	~SConfig();

private:
	nlohmann::json m_Document;
};