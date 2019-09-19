#include "PatchParams.h"

// -------------------------------------------------------
PatchParams::PatchParams()
{
	_rootParamGroup = make_shared<ParamGroup>();
	_ofParameterRootGroup = make_shared<ofParameterGroup>();

	_ofParameterRootGroup->setName("patch");
	_patchVersion.set("version", "none");
	_ofParameterRootGroup->add(_patchVersion);
	_patchName.set("name", "");
	_ofParameterRootGroup->add(_patchName);
	_patchDescription.set("description", "");
	_ofParameterRootGroup->add(_patchDescription);
}

// -------------------------------------------------------
PatchParams::~PatchParams()
{
	_paramDescs.clear();
}

// -------------------------------------------------------
void PatchParams::AddParam(string fullname, float value, float minValue, float maxValue, float smoothingTime, ParamLayouts layout)
{
	vector<string> names;
	names = ofSplitString(fullname, ".");

	shared_ptr<ParamGroup> lastGroup = _rootParamGroup;
	shared_ptr<ofParameterGroup> lastOfParameterGroup = _ofParameterRootGroup;

	int tokenIndex = 0;
	for (string token : names)
	{
		if (tokenIndex == (names.size() - 1))
		{
			// this is the parameter name
			// add it to group
			//ofLogNotice() << "Parameter name:" << token;
			shared_ptr<pdsp::Parameter> param = make_shared<pdsp::Parameter>();
			shared_ptr<ParamDesc> paramDesc = make_shared<ParamDesc>();

			param->set(token, value, minValue, maxValue);
			param->enableSmoothing( smoothingTime);

			paramDesc->pdspParameter = param;
			paramDesc->layout = layout;
			paramDesc->type = ParamTypes::Float;

			_paramDescs[fullname] = paramDesc;
			lastGroup->getParams().push_back(paramDesc);

			lastOfParameterGroup->add(paramDesc->pdspParameter->getOFParameterFloat());

		}
		else {
			//ofLogNotice() << "Group name:" << token;

			// replace by getOrCreateGroups()

			// check if group already exists in ParamGroup
			auto pair = lastGroup->getSubGroups().find(token);
			if (pair != lastGroup->getSubGroups().end())
			{
				// found, set as last group
				lastGroup = pair->second;
			}
			else
			{
				// not found create it
				shared_ptr<ParamGroup> newGroup = make_shared<ParamGroup>();
				lastGroup->getSubGroups()[token] = newGroup;
				lastGroup = newGroup;
			}

			// check if group already exist in ofParameterGroup
			bool found = false;
			shared_ptr<ofParameterGroup> subGroup = nullptr;
			for (auto param : *(lastOfParameterGroup))
			{
				subGroup = dynamic_pointer_cast<ofParameterGroup>(param);
				if (subGroup)
				{
					if (subGroup->getName() == token)
					{
						found = true;
						break;
					}
				}
			}

			if (found)
			{
				// found, set this group as lastOne
				lastOfParameterGroup = subGroup;
			}
			else
			{
				// not found, create one, add it to current group
				// set lastGroup to the new  one
				shared_ptr<ofParameterGroup> newGroup = make_shared<ofParameterGroup>();
				newGroup->setName(token);
				lastOfParameterGroup->add(*(newGroup));
				lastOfParameterGroup = newGroup;
			}

		}
		
		tokenIndex++;
	}
}

void PatchParams::getOrCreateGroups( string name, shared_ptr<ParamGroup> paramGroup, shared_ptr<ofParameterGroup> ofParamGroup)
{

}

// -------------------------------------------------------
shared_ptr<ofParameterGroup> PatchParams::getOfParameterGroup()
{
	return _ofParameterRootGroup;
}

// -------------------------------------------------------
map<string, shared_ptr<ParamGroup>>& ParamGroup::getSubGroups()
{
	return _subGroups;
}

// -------------------------------------------------------
vector<shared_ptr<ParamDesc>>& ParamGroup::getParams()
{
	return _params;
}
