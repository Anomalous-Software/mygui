/*
 * This source file is part of MyGUI. For the latest info, see http://mygui.info/
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "MyGUI_Precompiled.h"
#include "MyGUI_ContainerResponsive.h"

namespace MyGUI
{
	ContainerResponsive::ContainerResponsive()
		: columns(4)
	{
	}

	ContainerResponsive::~ContainerResponsive()
	{

	}

	void ContainerResponsive::setPropertyOverride(const std::string& _key, const std::string& _value)
	{
		
		if (_key == "Columns")
			columns = utility::parseValue<int>(_value);

		else
		{
			Base::setPropertyOverride(_key, _value);
			return;
		}

		eventChangeProperty(this, _key, _value);
	}

	int ContainerResponsive::getColumnCount()
	{
		return columns;
	}

} // namespace MyGUI
