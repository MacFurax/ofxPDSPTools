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
    mPatcheNames.push_back(fullPath.substr(pos + 1));
  }
}

// ---------------------------------------------------------
bool PatchFilesStore::Save(string path, ofParameterGroup toSave)
{
  ofLogNotice() << "PatchParams::Save - Save patch to " << path;

  ofxXmlSettings tmpxmlset;
  ofSerialize(tmpxmlset, toSave);
  tmpxmlset.saveFile(path);
  return true;
}

// ---------------------------------------------------------
bool PatchFilesStore::Save(int patchId, ofParameterGroup toSave)
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
  
  // TODO check is a trailing \ or / is present at the end, to avoid always adding it
  string fn = mBaseFolder +"/"+ mPatcheNames[patchId];

  Save(fn, toSave);

  return true;
}

// ---------------------------------------------------------
bool PatchFilesStore::Load(string path, ofParameterGroup& loaded)
{
  ofLogNotice() << "PatchParams::Load - Load patch from " << path;

  ofxXmlSettings tmpxmlset;
  if (!tmpxmlset.loadFile(path))
  {
    ofLogError() << "PatchParams::Load - Fail to load patch " << path;
    return false;
  }
  ofDeserialize(tmpxmlset, loaded);
  return true;
}

// ---------------------------------------------------------
bool PatchFilesStore::Load(int patchId, ofParameterGroup& loaded)
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

  // TODO check is a trailing \ or / is present at the end, to avoid always adding it
  string fn = mBaseFolder +"/" + mPatcheNames[patchId];

  Load(fn, loaded);

  return true;
}

