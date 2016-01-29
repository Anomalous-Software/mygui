/*
 * This source file is part of MyGUI. For the latest info, see http://mygui.info/
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "MyGUI_Precompiled.h"
#include "MyGUI_ContainerResponsive.h"
#include "MyGUI_ScrollViewResponsive.h"
#include "MyGUI_Gui.h"

namespace MyGUI
{
	ScrollViewResponsive::ScrollViewResponsive()
		:rowSlots(12)
	{
	}

	ScrollViewResponsive::~ScrollViewResponsive()
	{

	}

	void ScrollViewResponsive::setPropertyOverride(const std::string& _key, const std::string& _value)
	{

		if (_key == "RowSlots")
			rowSlots = utility::parseValue<int>(_value);

		else
		{
			Base::setPropertyOverride(_key, _value);
			return;
		}

		eventChangeProperty(this, _key, _value);
	}

	/** Set widget size */
	void ScrollViewResponsive::setSize(const IntSize& _value)
	{
		ScrollView::setSize(_value);
		repositionChildren();
	}
	/** Set widget position and size */
	void ScrollViewResponsive::setCoord(const IntCoord& _value)
	{
		ScrollView::setCoord(_value);
		repositionChildren();
	}

	void ScrollViewResponsive::repositionChildren()
	{
		int childCount = getChildCount();
		int rowStart = 0;
		IntCoord viewCoord = getViewCoord();
		int width = viewCoord.width - viewCoord.left;
		int currentY = 0;
		int lowestY = 0;

		for (int i = 0; i < childCount; ++i)
		{
			ContainerResponsive* child = getChildAt(i)->castType<ContainerResponsive>(false);
			if (child != nullptr)
			{
				if (child->isBlock(width))
				{
					currentY = buildRow(rowStart, i, width, currentY);
					//Add current inline row, the current child is that element
					child->setCoord(0, currentY, width, child->getHeight());
					currentY = child->getBottom();
					rowStart = i + 1;
				}
			}
		}
		//Build any remaining row elements
		currentY = buildRow(rowStart, childCount, width, currentY);

		//Set final scroll view size
		setCanvasSize(width, currentY);
	}

	int ScrollViewResponsive::buildRow(int rowStart, int rowEnd, int width, int currentY)
	{
		int lowestY = currentY;
		//Build previous row
		int previousWidgetRight = 0;
		for (int j = rowStart; j < rowEnd; j++)
		{
			ContainerResponsive* rowChild = getChildAt(j)->castType<ContainerResponsive>(false);
			if (rowChild != nullptr)
			{
				int itemWidth = (int)((float)rowChild->getInlineSlotCount() / rowSlots * width);
				rowChild->setCoord(previousWidgetRight, currentY, itemWidth, rowChild->getHeight());
				previousWidgetRight = rowChild->getRight();
				if (rowChild->getBottom() > lowestY)
				{
					lowestY = rowChild->getBottom();
				}
			}
		}
		return lowestY;
	}

} // namespace MyGUI
