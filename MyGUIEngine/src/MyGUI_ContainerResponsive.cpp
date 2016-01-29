/*
 * This source file is part of MyGUI. For the latest info, see http://mygui.info/
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "MyGUI_Precompiled.h"
#include "MyGUI_ContainerResponsive.h"
#include "MyGUI_Gui.h"

namespace MyGUI
{
	ContainerResponsive::ContainerResponsive()
		:blockMaxSize(Gui::getInstance().scalePreserve(200)),
		inlineSlots(4)
	{
	}

	ContainerResponsive::~ContainerResponsive()
	{

	}

	void ContainerResponsive::setPropertyOverride(const std::string& _key, const std::string& _value)
	{
		
		if (_key == "InlineSlots")
			inlineSlots = utility::parseValue<int>(_value);

		else if (_key == "BlockMaxSize")
			blockMaxSize = Gui::getInstance().scalePreserve(utility::parseValue<int>(_value));

		else
		{
			Base::setPropertyOverride(_key, _value);
			return;
		}

		eventChangeProperty(this, _key, _value);
	}

	bool ContainerResponsive::isBlock(int rowSize)
	{
		return rowSize < blockMaxSize;
	}

	int ContainerResponsive::getInlineSlotCount()
	{
		return inlineSlots;
	}

} // namespace MyGUI
