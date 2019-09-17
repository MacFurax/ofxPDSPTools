#pragma once


#include "PatchParams.h"

class LayoutGroup;

class LayoutParam
{
public:
  enum class WidgetTypes { HFader, VFader, Knob, Text, Combo };
  enum class ParamLayouts { NextLine, SameLine };

  LayoutParam(string label, shared_ptr<ParamDesc> paramDesc)
  {
    mLabel = label;
    mParamDesc = paramDesc;
  }

  WidgetTypes widgetType = WidgetTypes::HFader;
  ParamLayouts paramLayout = ParamLayouts::NextLine;

  string mLabel;
  shared_ptr<ParamDesc> mParamDesc;
};

class LayoutWindow
{
public:
  LayoutWindow();
  LayoutWindow(string name)
  {
    mName = name;
  }

  string mName;
  vector<shared_ptr<LayoutParam>> params;
  vector<shared_ptr<LayoutGroup>> subGroup;
};

class LayoutGroup
{
public:
  LayoutGroup(string name)
  {
    mName = name;
  }
  string mName;
  vector<shared_ptr<LayoutParam>> params;
  vector<shared_ptr<LayoutGroup>> subGroup;
};

class PatchParamsLayout
{
public:
  PatchParamsLayout();
  ~PatchParamsLayout();

  void StartWindow(string name);
  void EndWindow();

  void StartGroup(string name);
  void EndGroup();

  shared_ptr<LayoutParam> AddParam( string label, shared_ptr<ParamDesc> paramDesc);

  vector<shared_ptr<LayoutWindow>> Windows()
  {
    return windows;
  }

private:
  enum Scopes {Root, Window, Group};
  
  shared_ptr<LayoutWindow> currentWindow;
  
  stack<Scopes> scopeStack;
  stack< shared_ptr<LayoutGroup>> groupStack;

  vector<shared_ptr<LayoutWindow>> windows;

};
