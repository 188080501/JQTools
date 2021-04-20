/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

#include "screenColorPicker.h"


using namespace ScreenColorPicker;


Manage::Manage(): colorPicker(new ColorPicker)
{
  connect(colorPicker, &ColorPicker::colorSelect, this,  &Manage::colorSelect);
}


void Manage::openPicker()
{
  colorPicker->show();
}
