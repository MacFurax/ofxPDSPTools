#include "PatchParamsLayout.h"

PatchParamsLayout::PatchParamsLayout()
{
  scopeStack.push(Scopes::Root);
}

PatchParamsLayout::~PatchParamsLayout()
{
}

void PatchParamsLayout::StartWindow(string name)
{
  if (scopeStack.top() == Scopes::Root)
  {
	scopeStack.push(Scopes::Window);

	currentWindow = make_shared<LayoutWindow>(name);
	windows.push_back(currentWindow);

  }
  else
  {
	ofLogError() << "PatchParamsLayout::StartWindow - Not in Root scope.";
  }
}

void PatchParamsLayout::EndWindow()
{
  if (scopeStack.top() == Scopes::Window)
  {
	scopeStack.pop();
  }
  else
  {
	ofLogError() << "PatchParamsLayout::EndWindow - Not in Window scope.";
  }
}

void PatchParamsLayout::StartGroup(string name)
{
  if (scopeStack.top() == Scopes::Window)
  {
	shared_ptr<LayoutGroup> newGroup = make_shared<LayoutGroup>(name);
	currentWindow->subGroup.push_back(newGroup);
	groupStack.push(newGroup);
	scopeStack.push(Scopes::Group);
  }
  else if (scopeStack.top() == Scopes::Group)
  {
	shared_ptr<LayoutGroup> newGroup = make_shared<LayoutGroup>(name);
	groupStack.top()->subGroup.push_back(newGroup);
	groupStack.push(newGroup);
	scopeStack.push(Scopes::Group);
  }
  else
  {
	ofLogError() << "PatchParamsLayout::StartGroup - Not in Window or Group scope.";
  }
}

void PatchParamsLayout::EndGroup()
{
  if (scopeStack.top() == Scopes::Group)
  {
	scopeStack.pop();
  }
  else
  {
	ofLogError() << "PatchParamsLayout::EndGroup - Not in Group scope.";
  }
}

shared_ptr<LayoutParam> PatchParamsLayout::AddParam(string label, shared_ptr<ParamDesc> paramDesc)
{
  shared_ptr<LayoutParam> newParam = make_shared<LayoutParam>(label, paramDesc);
  
  if (paramDesc->type == ParamTypes::Combo) {
	  newParam->widgetType = LayoutParam::WidgetTypes::Combo;
  }
  else if (paramDesc->type == ParamTypes::Float)
  {
	  newParam->widgetType = LayoutParam::WidgetTypes::HFader;
  }

  if (scopeStack.top() == Scopes::Window)
  {
	currentWindow->params.push_back(newParam);
  }
  else if (scopeStack.top() == Scopes::Group)
  {
	groupStack.top()->params.push_back(newParam);
  }
  return newParam;
}

LayoutWindow::LayoutWindow()
{
}
