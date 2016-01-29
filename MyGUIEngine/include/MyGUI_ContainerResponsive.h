/*
 * This source file is part of MyGUI. For the latest info, see http://mygui.info/
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#ifndef MYGUI_CONTAINERRESPONSIVE_H_
#define MYGUI_CONTAINERRESPONSIVE_H_

#include "MyGUI_Prerequest.h"
#include "MyGUI_Widget.h"

namespace MyGUI
{
	class MYGUI_EXPORT ContainerResponsive :
		public Widget
	{
		MYGUI_RTTI_DERIVED(ContainerResponsive)

	public:
		ContainerResponsive();

		virtual ~ContainerResponsive();

		virtual void setPropertyOverride(const std::string& _key, const std::string& _value);

		int getColumnCount();

	private:
		int columns;
	};

} // namespace MyGUI

#endif // MYGUI_CONTAINERRESPONSIVE_H_
