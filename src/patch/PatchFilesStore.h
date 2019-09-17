#pragma once

#include "PatchParams.h"

class PatchFilesStore
{
public:
  PatchFilesStore();
  PatchFilesStore(string baseFolder, string extention = "xml");
  ~PatchFilesStore();

  void setup(string baseFolder, string extention = "xml");

  void            reloadPatchsFileList();
  vector<string>& patcheNames();
  size_t          numFiles();
  string          pathAt(int patchId);
  string          buildFullFilename(string nakedName);

  bool            Save(string path, ofParameterGroup toSave);
  bool            Save(int patchId, ofParameterGroup toSave);
  bool            Load(string path, ofParameterGroup& loaded);
  bool            Load(int patchId, ofParameterGroup& loaded);
  
private:
  string          mBaseFolder = "./patches";
  string          mExtention = "xml";
  size_t          mNumFiles = 0;
  ofDirectory     mDirectoryLister;
  
  vector<string>  mPatcheNames;
};


inline vector<string>& PatchFilesStore::patcheNames()
{
  return mPatcheNames;
}

inline size_t PatchFilesStore::numFiles()
{
  return mNumFiles;
}

inline string PatchFilesStore::pathAt(int patchId)
{
  if (patchId >= 0 && patchId < mPatcheNames.size())
  {
    return mPatcheNames[patchId];
  }
  return nullptr;
}

inline string PatchFilesStore::buildFullFilename(string nakedName)
{
  return mBaseFolder + "/" + nakedName + "." + mExtention;
}
