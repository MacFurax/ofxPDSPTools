#include "PatchFilesStore.h"

// ---------------------------------------------------------
PatchFilesStore::PatchFilesStore()
{
  mDirectoryLister = ofDirectory(mBaseFolder);
  mDirectoryLister.allowExt(mExtention);
}

// ---------------------------------------------------------
PatchFilesStore::PatchFilesStore(string baseFolder, string extention)
{
  mBaseFolder = baseFolder;
  mExtention = extention;

  PatchFilesStore();
}

// ---------------------------------------------------------
PatchFilesStore::~PatchFilesStore()
{
}

// ---------------------------------------------------------
void PatchFilesStore::setup(string baseFolder, string extention)
{
  mBaseFolder = baseFolder;
  mExtention = extention;

  PatchFilesStore();
}

// ---------------------------------------------------------
void PatchFilesStore::reloadPatchsFileList()
{
  mDirectoryLister.listDir();
  mPatcheNames.clear();

  mNumFiles = mDirectoryLister.size();

  for (int i = 0; i < mDirectoryLister.size(); i++) {
    string fullPath = mDirectoryLister.getPath(i);
    size_t pos =fullPath.find_last_of("\\");
	fullPath = fullPath.substr(pos + 1);

	pos = fullPath.find_last_of("."+mExtention);

	fullPath = fullPath.substr(0, pos - (mExtention.length()));

    mPatcheNames.push_back(fullPath);
  }
}

// ---------------------------------------------------------
bool PatchFilesStore::save(string nakedFilename, ofParameterGroup& toSave)
{
	string fn = mBaseFolder + "/" + nakedFilename + "." + mExtention;
	ofLogNotice() << "PatchFilesStore::save - Save patch to " << fn;

	ofxXmlSettings tmpxmlset;
	ofSerialize(tmpxmlset, toSave);
	tmpxmlset.saveFile(fn);
	return true;
}

// ---------------------------------------------------------
bool PatchFilesStore::save(int patchId, ofParameterGroup& toSave)
{
  if (mPatcheNames.size() < 0)
  {
    ofLogError() << "PatchFilesStore::Save - No patches in the list";
    return false;
  }

  if (patchId < 0 || patchId >= mPatcheNames.size())
  {
    ofLogError() << "PatchFilesStore::Save - Patche Id [" << patchId << "] out of range";
    return false;
  }
  
  save(mPatcheNames[patchId], toSave);

  return true;
}

// ---------------------------------------------------------
bool PatchFilesStore::load(string nakedFilename, ofParameterGroup& loaded)
{
	string fn = mBaseFolder + "/" + nakedFilename + "." + mExtention;
	ofLogNotice() << "PatchParams::Load - Load patch from " << fn;
	
	ofxXmlSettings tmpxmlset;
	if (!tmpxmlset.loadFile(fn))
	{
	ofLogError() << "PatchParams::Load - Fail to load patch " << fn;
	return false;
	}

	ofDeserialize(tmpxmlset, loaded);

	return true;
}

// ---------------------------------------------------------
bool PatchFilesStore::load(int patchId, ofParameterGroup& loaded)
{
  if (mPatcheNames.size() < 0)
  {
    ofLogError() << "PatchFilesStore::Save - No patches in the list";
    return false;
  }

  if (patchId < 0 || patchId > mPatcheNames.size())
  {
    ofLogError() << "PatchFilesStore::Save - Patche Id [" << patchId << "] out of range";
    return false;
  }

  load(mPatcheNames[patchId], loaded);

  return true;
}

