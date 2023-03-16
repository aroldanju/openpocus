/*
 * Copyright (C) 2023, A. Roldán. All rights reserved.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "config.h"
#include <tinyxml2.h>

using namespace pocus;

bool Config::load(const std::string& filename) {
	tinyxml2::XMLDocument document;
	tinyxml2::XMLError error;
	
	if ((error = document.LoadFile(filename.c_str())) != tinyxml2::XML_SUCCESS) {
		return false;
	}
	
	tinyxml2::XMLElement* element = document.FirstChildElement("config");
	if (!element) {
		return false;
	}
	
	tinyxml2::XMLElement* eInstallationPath = element->FirstChildElement("installation_path");
	if (!eInstallationPath) {
		return false;
	}
	this->installationPath = std::string(eInstallationPath->GetText());
	
	return true;
}

const std::string &Config::getInstallationPath() const {
	return installationPath;
}

void Config::setInstallationPath(const std::string &installationPath) {
	Config::installationPath = installationPath;
}
