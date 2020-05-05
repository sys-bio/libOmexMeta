#include <combine/util.h>
#include <zipper/tools.h>

#include <cstdio>
#include <cstdlib>

#include <fstream>
#include <sstream>

#include <ctime>
#include <cstdlib>
#include <cstring>

LIBCOMBINE_CPP_NAMESPACE_USE

std::string
Util::getTempPath()
{
  char *tmpDir = getenv("TMP");
  if (tmpDir != NULL) return tmpDir;
  tmpDir = getenv("TEMP");
  if (tmpDir != NULL) return tmpDir;
  return ".";
}

std::string
Util::getTempFilename(const std::string& prefix,
                      const std::string& ext)
{
  std::stringstream str;
  str << getTempPath() << "/" << prefix
      << getCurrentMilliseconds() << rand() << rand() 
      << ext;
  return str.str();
}


void 
Util::copyFile(const std::string &source, const std::string &destination)
{
  std::ifstream in(source.c_str(), std::ios::in | std::ios::binary);
  std::ofstream out(destination.c_str(), std::ios::out | std::ios::binary);
  copyStream(in, out);
  in.close();
  out.close();
}

void Util::copyStream(std::istream &in, std::ostream &out)
{
  out << in.rdbuf();
}

std::string 
Util::getExtension(const std::string &fileName)
{
  return fileName.substr(getExtensionIndex(fileName.c_str()));
}

bool 
Util::removeFileOrFolder(const std::string & path)
{
  if (zipper::isDirectory(path))
  {
    zipper::removeFolder(path);
    return true;
  }
  else if (zipper::checkFileExists(path))
  {
    std::remove(path.c_str());
    return true;
  }
  return false;
}

size_t Util::getExtensionIndex(const char* fileName)
{
  size_t len = strlen(fileName);
  size_t idx = len-1;
  for(size_t i = 0; *(fileName+i); i++) {
    if (*(fileName+i) == '.') {
      idx = i;
    } else if (*(fileName + i) == '/' || *(fileName + i) == '\\') {
      idx = len - 1;
    }
  }
  return idx+1;
}

unsigned long
Util::getCurrentMilliseconds()
{
  time_t rawtime;
  struct tm * timeinfo;

  time ( &rawtime );
  timeinfo = gmtime ( &rawtime );
  unsigned long result = (unsigned long)mktime(timeinfo);
  return result;
}
