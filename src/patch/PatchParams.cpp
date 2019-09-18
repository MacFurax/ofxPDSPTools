#include "PatchParams.h"

template <class Container>
void split2(const std::string& str, Container& cont, char delim)
{
	std::stringstream ss(str);
	std::string token;
	while (std::getline(ss, token, delim)) {
		cont.push_back(token);
	}
}

PatchParams::PatchParams()
{
  rootGroup.setName("patch");
  patchVersion.set("version", "none");
  rootGroup.add(patchVersion);
  patchName.set("name", "");
  rootGroup.add(patchName);
  patchDescription.set("description", "");
  rootGroup.add(patchDescription);
}

PatchParams::~PatchParams()
{
  parameters.clear();
  childsGroups.clear();
  parametersByName.clear();
}

void PatchParams::AddParam(string name, float value, float minValue, float maxValue, float smoothingTime, ParamDesc::Layouts layout)
{
  // TODO add check that param doesn't already exists
  shared_ptr<ParamDesc> paramDesc = make_shared<ParamDesc>();
  paramDesc->pdspParameter = make_shared<pdsp::Parameter>();;
  paramDesc->type = ParamDesc::ParamTypes::Float;
  paramDesc->layout = layout;

  tuple<string, string> splitedName = SplitParamName(name);

  string groupName = std::get<0>(splitedName);
  string paramName = std::get<1>(splitedName);

  ofLogNotice() << "PatchParams::AddParam - Add float param [" << paramName << "] in group [" << groupName  << "]";
  
  // init pdsd::Parameter
  // save it in list and map
  paramDesc->pdspParameter->set(paramName, value, minValue, maxValue);
  paramDesc->pdspParameter->enableSmoothing(smoothingTime);

  Store(paramName, groupName, paramDesc);
}

void PatchParams::AddParam(string name, int value, int minValue, int maxValue)
{
  // TODO add check that param doesn't already exists
  shared_ptr<ParamDesc> paramDesc = make_shared<ParamDesc>();
  paramDesc->pdspParameter = make_shared<pdsp::Parameter>();;
  paramDesc->type = ParamDesc::ParamTypes::Int;

  tuple<string, string> splitedName = SplitParamName(name);

  string groupName = std::get<0>(splitedName);
  string paramName = std::get<1>(splitedName);

  ofLogNotice() << "PatchParams::AddParam - Add int param [" << paramName << "] in group [" << groupName << "]";

  // init pdsd::Parameter
  // save it in list and map
  paramDesc->pdspParameter->set(paramName, value, minValue, maxValue);
  
  Store(paramName, groupName, paramDesc);
  
}

void PatchParams::AddParam(string name, int value, vector<string> values)
{
  // TODO add check that param doesn't already exists
  shared_ptr<ParamDesc> paramDesc = make_shared<ParamDesc>();
  paramDesc->pdspParameter = make_shared<pdsp::Parameter>();
  paramDesc->type = ParamDesc::ParamTypes::Combo;
  paramDesc->comboOptions = values;

  tuple<string, string> splitedName = SplitParamName(name);

  string groupName = std::get<0>(splitedName);
  string paramName = std::get<1>(splitedName);

  ofLogNotice() << "PatchParams::AddParam - Add combo param [" << paramName << "] in group [" << groupName << "]";

  // init pdsd::Parameter
  // save it in list and map
  paramDesc->pdspParameter->set(paramName, value, 0, values.size());

  Store(paramName, groupName, paramDesc);
}

pdsp::Patchable PatchParams::Patch(string name)
{
  auto paramDesc = parametersByName.find(name);
  if (paramDesc != parametersByName.end())
  {
    return *(paramDesc->second->pdspParameter);
  }
  ofLogError() << "PatchParams::Patch - Seek for an unknown parameter named [" << name << "]";
  return pdsp::Patchable();
}

void PatchParams::Set(string name, int value)
{
  auto paramDesc = parametersByName.find(name);
  //TODO check that we find a match
  if (paramDesc->second->type == ParamDesc::ParamTypes::Int)
  {
    paramDesc->second->pdspParameter->set(value);
  }
  else 
  {
    ofLogError() << "PatchParams::Set - Set an int to a none int param ?";
  }
}

void PatchParams::Set(string name, float value)
{
  auto paramDesc = parametersByName.find(name);
  //TODO check that we find a match
  if (paramDesc->second->type == ParamDesc::ParamTypes::Float)
  {
    paramDesc->second->pdspParameter->set(value);
  }
  else
  {
    ofLogError() << "PatchParams::Set - Set an float to a none float param ?";
  }
}

shared_ptr<ParamDesc> PatchParams::getParamDesc(string name)
{
  auto pair = parametersByName.find(name);
  if (pair != parametersByName.end())
  {
    return pair->second;
  }
  // not found
  return nullptr;
}

shared_ptr<ParamDesc> PatchParams::getParamDesc(string groupName, string paramName)
{
  return getParamDesc(groupName+"."+ paramName);
}

shared_ptr<pdsp::Parameter> PatchParams::getPDSPParameter(string name)
{
  auto paramDesc = parametersByName.find(name);
  if (paramDesc != parametersByName.end())
  {
    ofLogError() << "PatchParams::getPDSPParameter - Seek for an unknown parameter named [" << name << "]";
    return paramDesc->second->pdspParameter;
  }
  return nullptr;
}

ofParameter<float>& PatchParams::getOfParameterFloat(string name)
{
  auto paramDesc = parametersByName.find(name);
  if (paramDesc != parametersByName.end())
  {
    ofLogError() << "PatchParams::getOfParameterFloat - Seek for an unknown parameter named [" << name << "]";
    return paramDesc->second->pdspParameter->getOFParameterFloat();
  }
  return ofParameter<float>("empty", 0.0f);
}

ofParameter<int>& PatchParams::getOfParameterInt(string name)
{
  auto paramDesc = parametersByName.find(name);
  if (paramDesc != parametersByName.end())
  {
    ofLogError() << "PatchParams::getOfParameterInt - Seek for an unknown parameter named [" << name << "]";
    return paramDesc->second->pdspParameter->getOFParameterInt();
  }
  return ofParameter<int>("empty", 0);
}

ofParameter<string>& PatchParams::version()
{
  return patchVersion;
}

ofParameter<string>& PatchParams::name()
{
  return patchName;
}

ofParameter<string>& PatchParams::description()
{
  return patchDescription;
}

bool PatchParams::Save(string path)
{
  ofLogNotice() << "PatchParams::Save - Save patch to " << path;

  ofxXmlSettings tmpxmlset;
  ofSerialize(tmpxmlset, rootGroup);
  tmpxmlset.saveFile(path);
  return true;
}

bool PatchParams::Load(string path)
{
  ofLogNotice() << "PatchParams::Load - Load patch from " << path;

  ofxXmlSettings tmpxmlset;
  tmpxmlset.loadFile(path);
  ofDeserialize(tmpxmlset, rootGroup);
  return true;
}

ofParameterGroup & PatchParams::getParameterGroup()
{
	return rootGroup;
}

void PatchParams::Store(string name, string groupName, shared_ptr<ParamDesc> paramDesc)
{
  parameters.push_back(paramDesc);
  parametersByName[groupName+"."+name] = paramDesc;

  // check if the group exists
  // if not create it
  // if yes add parameter to the group
  auto groupPair = groupsByName.find(groupName);
  shared_ptr<ofParameterGroup> group;
  if (groupPair != groupsByName.end())
  {
    // group already exists
    group = groupPair->second;
  }
  else
  {
    // group doesn't exists yet
    // create it and store it 
    group = make_shared<ofParameterGroup>();
    group->setName(groupName);
    groupsByName[groupName] = group;
    childsGroups.push_back(group);
    rootGroup.add(*group);
  }

  // Add param to the group
  switch (paramDesc->type)
  {
  case ParamDesc::ParamTypes::Float:
    group->add(paramDesc->pdspParameter->getOFParameterFloat());
    break;
  case ParamDesc::ParamTypes::Int:
    group->add(paramDesc->pdspParameter->getOFParameterInt());
    break;
  case ParamDesc::ParamTypes::Combo:
    group->add(paramDesc->pdspParameter->getOFParameterInt());
    break;
  default:
    ofLogError() << "PatchParams::Store - Unkown param type ["<< paramDesc->type <<"]";
  }
}

tuple<string, string> PatchParams::SplitParamName(string fullParamName)
{
  auto dotPos = fullParamName.find_first_of(".");

  /*string groupName = fullParamName.substr(0, dotPos);
  string paramName = fullParamName.substr(dotPos + 1);

  return tuple<string, string>(groupName, paramName);*/

  return tuple<string, string>(fullParamName.substr(0, dotPos), fullParamName.substr(dotPos + 1));
}
