/*
 * This source file is part of MyGUI. For the latest info, see http://mygui.info/
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#ifndef MYGUI_SCROLLVIEWRESPONSIVE_H_
#define MYGUI_RESPONSIVECONTAINER_H_

#include "MyGUI_Prerequest.h"
#include "MyGUI_ScrollView.h"

namespace MyGUI
{
	class MYGUI_EXPORT PanelResponsive :
		public Widget
	{
		MYGUI_RTTI_DERIVED(PanelResponsive)

	public:
		PanelResponsive();

		virtual ~PanelResponsive();

		virtual void setPropertyOverride(const std::string& _key, const std::string& _value);

		/** Set widget size */
		virtual void setSize(const IntSize& _value);
		/** Set widget position and size */
		virtual void setCoord(const IntCoord& _value);

	private:
		void repositionChildren();

		int rowColumns;
		int horizontalMaxSize;
		IntSize padding;
		bool reverseChildrenVertically;
	};

} // namespace MyGUI

#endif // MYGUI_SCROLLVIEWRESPONSIVE_H_
