#include <combine/knownformats.h>
#include <combine/util.h>

#include <algorithm>
#include <fstream>

LIBCOMBINE_CPP_NAMESPACE_USE


bool
KnownFormats::isFormat(const std::string &formatKey,
                       const std::string &format)
{
  std::map<std::string,std::vector<std::string> >::iterator it = 
    mKnownFormats.find(formatKey);

  if (it != mKnownFormats.end())
  {
    std::vector<std::string>& knownFormats = it->second;
    std::vector<std::string>::iterator foundIt = 
       std::find(knownFormats.begin(), knownFormats.end(), format);
    return foundIt != knownFormats.end();
  }


  if (formatKey == "sbml" && format.find("http://identifiers.org/combine.specifications/sbml") == 0)
    return true;
  if (formatKey == "sedml" && format.find("http://identifiers.org/combine.specifications/sed") == 0)
    return true;
  if (formatKey == "sbgn" && format.find("http://identifiers.org/combine.specifications/sbgn") == 0)
    return true;

  return false;

}

std::string
KnownFormats::lookupFormat(const std::string& format)
{
  std::map<std::string, std::vector<std::string> >::iterator it = 
     mKnownFormats.find(format);

  if (it != mKnownFormats.end())
  {
    std::vector<std::string>& knownFormats = it->second;
    return knownFormats.front();
  }
  return "";
}

std::string KnownFormats::guessFormat(const std::string &fileName)
{
  std::string ext = Util::getExtension(fileName);
  if (ext == "xml")
  {
    std::ifstream file(fileName.c_str(), std::ios::binary);
    std::vector<char> buffer(256);
    file.read( &buffer[0], buffer.size() );
    std::string snippet( buffer.begin(), buffer.end() );

    if (snippet.find("<sbml") != std::string::npos)
      return lookupFormat("sbml");
    if (snippet.find("<sedML")!= std::string::npos)
      return lookupFormat("sedml");
    if (snippet.find("<cell")!= std::string::npos)
      return lookupFormat("cellml");
    if (snippet.find("<COPASI") != std::string::npos)
      return lookupFormat("copasi");
  }

  return lookupFormat(ext);
}

std::vector<std::string>
KnownFormats::getFormatKeys()
{
  std::vector<std::string> result;
  std::map<std::string, std::vector<std::string> >::iterator it = 
     mKnownFormats.begin();

  for (;it != mKnownFormats.end(); ++it)
    result.push_back(it->first);
  return result;
}


std::map<std::string, std::vector<std::string> >
KnownFormats::mKnownFormats = KnownFormats::initializeMap();

std::map<std::string, std::vector<std::string> >&
KnownFormats::getKnownFormats()
{
  return mKnownFormats;
}

void 
KnownFormats::addKnownFormat(const std::string& formatKey, const std::string& format)
{
  std::map<std::string, std::vector<std::string> >::iterator it =
    mKnownFormats.find(formatKey);

  if (it == mKnownFormats.end())
  {
    std::vector<std::string> temp; 
    temp.push_back(format);
    mKnownFormats[formatKey] = temp;
  }
  else
  {
    mKnownFormats[formatKey].push_back(format);
  }
}


std::map<std::string, std::vector<std::string> >
KnownFormats::initializeMap()
{
#if 0
  std::map<std::string, std::vector<std::string> > temp = {
    { "sbml",{
      "http://identifiers.org/combine.specifications/sbml",
      "http://identifiers.org/combine.specifications/sbml.level-1.version-1",
      "http://identifiers.org/combine.specifications/sbml.level-1.version-2",
      "http://identifiers.org/combine.specifications/sbml.level-2.version-1",
      "http://identifiers.org/combine.specifications/sbml.level-2.version-2",
      "http://identifiers.org/combine.specifications/sbml.level-2.version-3",
      "http://identifiers.org/combine.specifications/sbml.level-2.version-4",
      "http://identifiers.org/combine.specifications/sbml.level-2.version-5",
      "http://identifiers.org/combine.specifications/sbml.level-3.version-1",
      "http://identifiers.org/combine.specifications/sbml.level-3.version-2",
      "http://identifiers.org/combine.specifications/sbml.level-1.version.1",
      "http://identifiers.org/combine.specifications/sbml.level-1.version.2",
      "http://identifiers.org/combine.specifications/sbml.level-2.version.1",
      "http://identifiers.org/combine.specifications/sbml.level-2.version.2",
      "http://identifiers.org/combine.specifications/sbml.level-2.version.3",
      "http://identifiers.org/combine.specifications/sbml.level-2.version.4",
      "http://identifiers.org/combine.specifications/sbml.level-2.version.5",
      "http://identifiers.org/combine.specifications/sbml.level-3.version.1",
      "http://identifiers.org/combine.specifications/sbml.level-3.version.2",
    } },
    { "sedml",
    {
      "http://identifiers.org/combine.specifications/sed-ml",
      "http://identifiers.org/combine.specifications/sedml",
      "http://identifiers.org/combine.specifications/sed-ml.level-1.version-1",
      "http://identifiers.org/combine.specifications/sed-ml.level-1.version-2",
      "http://identifiers.org/combine.specifications/sed-ml.level-1.version-3"
    } },
    { "cellml",{ "http://identifiers.org/combine.specifications/cellml" } },
    { "sed-ml",
    {
      "http://identifiers.org/combine.specifications/sed-ml",
      "http://identifiers.org/combine.specifications/sedml",
      "http://identifiers.org/combine.specifications/sed-ml.level-1.version-1",
      "http://identifiers.org/combine.specifications/sed-ml.level-1.version-2",
      "http://identifiers.org/combine.specifications/sed-ml.level-1.version-3"
    } },
    { "sbgn",{ "http://identifiers.org/combine.specifications/sbgn" } },
    { "omex",{ "http://identifiers.org/combine.specifications/omex-metadata" } },
    { "manifest",{
      "http://identifiers.org/combine.specifications/omex",
      "http://identifiers.org/combine.specifications/omex-manifest",
      "http://identifiers.org/combine.specifications/omex.version-1",
    } },
    { "copasi",{ "application/x-copasi" } },
    { "sedx",{ "application/x-sed-ml-archive" } },
    { "png",{ "image/png" } },
    { "csv",{ "text/csv" } },
    { "323",{ "text/h323" } },
    { "acx",{ "application/internet-property-stream" } },
    { "ai",{ "application/postscript" } },
    { "aif",{ "audio/x-aiff" } },
    { "aifc",{ "audio/x-aiff" } },
    { "aiff",{ "audio/x-aiff" } },
    { "asf",{ "video/x-ms-asf" } },
    { "asr",{ "video/x-ms-asf" } },
    { "asx",{ "video/x-ms-asf" } },
    { "au",{ "audio/basic" } },
    { "avi",{ "video/x-msvideo" } },
    { "axs",{ "application/olescript" } },
    { "bas",{ "text/plain" } },
    { "bcpio",{ "application/x-bcpio" } },
    { "bin",{ "application/octet-stream" } },
    { "bmp",{ "image/bmp" } },
    { "c",{ "text/plain" } },
    { "cat",{ "application/vnd.ms-pkiseccat" } },
    { "cdf",{ "application/x-cdf" } },
    { "cer",{ "application/x-x509-ca-cert" } },
    { "class",{ "application/octet-stream" } },
    { "clp",{ "application/x-msclip" } },
    { "cmx",{ "image/x-cmx" } },
    { "cod",{ "image/cis-cod" } },
    { "cpio",{ "application/x-cpio" } },
    { "crd",{ "application/x-mscardfile" } },
    { "crl",{ "application/pkix-crl" } },
    { "crt",{ "application/x-x509-ca-cert" } },
    { "csh",{ "application/x-csh" } },
    { "css",{ "text/css" } },
    { "dcr",{ "application/x-director" } },
    { "der",{ "application/x-x509-ca-cert" } },
    { "dir",{ "application/x-director" } },
    { "dll",{ "application/x-msdownload" } },
    { "dms",{ "application/octet-stream" } },
    { "doc",{ "application/msword" } },
    { "dot",{ "application/msword" } },
    { "dvi",{ "application/x-dvi" } },
    { "dxr",{ "application/x-director" } },
    { "eps",{ "application/postscript" } },
    { "etx",{ "text/x-setext" } },
    { "evy",{ "application/envoy" } },
    { "exe",{ "application/octet-stream" } },
    { "fif",{ "application/fractals" } },
    { "flr",{ "x-world/x-vrml" } },
    { "gif",{ "image/gif" } },
    { "gtar",{ "application/x-gtar" } },
    { "gz",{ "application/x-gzip" } },
    { "h",{ "text/plain" } },
    { "hdf",{ "application/x-hdf" } },
    { "hlp",{ "application/winhlp" } },
    { "hqx",{ "application/mac-binhex40" } },
    { "hta",{ "application/hta" } },
    { "htc",{ "text/x-component" } },
    { "htm",{ "text/html" } },
    { "html",{ "text/html" } },
    { "htt",{ "text/webviewhtml" } },
    { "ico",{ "image/x-icon" } },
    { "ief",{ "image/ief" } },
    { "iii",{ "application/x-iphone" } },
    { "ins",{ "application/x-internet-signup" } },
    { "isp",{ "application/x-internet-signup" } },
    { "jfif",{ "image/pipeg" } },
    { "jpe",{ "image/jpeg" } },
    { "jpeg",{ "image/jpeg" } },
    { "jpg",{ "image/jpeg" } },
    { "js",{ "application/x-javascript" } },
    { "latex",{ "application/x-latex" } },
    { "lha",{ "application/octet-stream" } },
    { "lsf",{ "video/x-la-asf" } },
    { "lsx",{ "video/x-la-asf" } },
    { "lzh",{ "application/octet-stream" } },
    { "m",{ "application/x-matlab" } },
    { "mat",{ "application/x-matlab" } },
    { "m13",{ "application/x-msmediaview" } },
    { "m14",{ "application/x-msmediaview" } },
    { "m3u",{ "audio/x-mpegurl" } },
    { "man",{ "application/x-troff-man" } },
    { "mdb",{ "application/x-msaccess" } },
    { "me",{ "application/x-troff-me" } },
    { "mht",{ "message/rfc822" } },
    { "mhtml",{ "message/rfc822" } },
    { "mid",{ "audio/mid" } },
    { "mny",{ "application/x-msmoney" } },
    { "mov",{ "video/quicktime" } },
    { "movie",{ "video/x-sgi-movie" } },
    { "mp2",{ "video/mpeg" } },
    { "mp3",{ "audio/mpeg" } },
    { "mpa",{ "video/mpeg" } },
    { "mpe",{ "video/mpeg" } },
    { "mpeg",{ "video/mpeg" } },
    { "mpg",{ "video/mpeg" } },
    { "mpp",{ "application/vnd.ms-project" } },
    { "mpv2",{ "video/mpeg" } },
    { "ms",{ "application/x-troff-ms" } },
    { "mvb",{ "application/x-msmediaview" } },
    { "nws",{ "message/rfc822" } },
    { "oda",{ "application/oda" } },
    { "p10",{ "application/pkcs10" } },
    { "p12",{ "application/x-pkcs12" } },
    { "p7b",{ "application/x-pkcs7-certificates" } },
    { "p7c",{ "application/x-pkcs7-mime" } },
    { "p7m",{ "application/x-pkcs7-mime" } },
    { "p7r",{ "application/x-pkcs7-certreqresp" } },
    { "p7s",{ "application/x-pkcs7-signature" } },
    { "pbm",{ "image/x-portable-bitmap" } },
    { "pdf",{ "application/pdf" } },
    { "pfx",{ "application/x-pkcs12" } },
    { "pgm",{ "image/x-portable-graymap" } },
    { "pko",{ "application/ynd.ms-pkipko" } },
    { "pma",{ "application/x-perfmon" } },
    { "pmc",{ "application/x-perfmon" } },
    { "pml",{ "application/x-perfmon" } },
    { "pmr",{ "application/x-perfmon" } },
    { "pmw",{ "application/x-perfmon" } },
    { "pnm",{ "image/x-portable-anymap" } },
    { "pot,",{ "application/vnd.ms-powerpoint" } },
    { "ppm",{ "image/x-portable-pixmap" } },
    { "pps",{ "application/vnd.ms-powerpoint" } },
    { "ppt",{ "application/vnd.ms-powerpoint" } },
    { "prf",{ "application/pics-rules" } },
    { "ps",{ "application/postscript" } },
    { "pub",{ "application/x-mspublisher" } },
    { "qt",{ "video/quicktime" } },
    { "ra",{ "audio/x-pn-realaudio" } },
    { "ram",{ "audio/x-pn-realaudio" } },
    { "ras",{ "image/x-cmu-raster" } },
    { "rgb",{ "image/x-rgb" } },
    { "rmi",{ "audio/mid" } },
    { "roff",{ "application/x-troff" } },
    { "rtf",{ "application/rtf" } },
    { "rtx",{ "text/richtext" } },
    { "scd",{ "application/x-msschedule" } },
    { "sct",{ "text/scriptlet" } },
    { "setpay",{ "application/set-payment-initiation" } },
    { "setreg",{ "application/set-registration-initiation" } },
    { "sh",{ "application/x-sh" } },
    { "shar",{ "application/x-shar" } },
    { "sit",{ "application/x-stuffit" } },
    { "snd",{ "audio/basic" } },
    { "spc",{ "application/x-pkcs7-certificates" } },
    { "spl",{ "application/futuresplash" } },
    { "src",{ "application/x-wais-source" } },
    { "sst",{ "application/vnd.ms-pkicertstore" } },
    { "stl",{ "application/vnd.ms-pkistl" } },
    { "stm",{ "text/html" } },
    { "svg",{ "image/svg+xml" } },
    { "sv4cpio",{ "application/x-sv4cpio" } },
    { "sv4crc",{ "application/x-sv4crc" } },
    { "swf",{ "application/x-shockwave-flash" } },
    { "t",{ "application/x-troff" } },
    { "tar",{ "application/x-tar" } },
    { "tcl",{ "application/x-tcl" } },
    { "tex",{ "application/x-tex" } },
    { "texi",{ "application/x-texinfo" } },
    { "texinfo",{ "application/x-texinfo" } },
    { "tgz",{ "application/x-compressed" } },
    { "tif",{ "image/tiff" } },
    { "tiff",{ "image/tiff" } },
    { "tr",{ "application/x-troff" } },
    { "trm",{ "application/x-msterminal" } },
    { "tsv",{ "text/tab-separated-values" } },
    { "txt",{ "text/plain" } },
    { "uls",{ "text/iuls" } },
    { "ustar",{ "application/x-ustar" } },
    { "vcf",{ "text/x-vcard" } },
    { "vrml",{ "x-world/x-vrml" } },
    { "wav",{ "audio/x-wav" } },
    { "wcm",{ "application/vnd.ms-works" } },
    { "wdb",{ "application/vnd.ms-works" } },
    { "wks",{ "application/vnd.ms-works" } },
    { "wmf",{ "application/x-msmetafile" } },
    { "wps",{ "application/vnd.ms-works" } },
    { "wri",{ "application/x-mswrite" } },
    { "wrl",{ "x-world/x-vrml" } },
    { "wrz",{ "x-world/x-vrml" } },
    { "xaf",{ "x-world/x-vrml" } },
    { "xbm",{ "image/x-xbitmap" } },
    { "xla",{ "application/vnd.ms-excel" } },
    { "xlc",{ "application/vnd.ms-excel" } },
    { "xlm",{ "application/vnd.ms-excel" } },
    { "xls",{ "application/vnd.ms-excel" } },
    { "xlt",{ "application/vnd.ms-excel" } },
    { "xlw",{ "application/vnd.ms-excel" } },
    { "xof",{ "x-world/x-vrml" } },
    { "xpm",{ "image/x-xpixmap" } },
    { "xwd",{ "image/x-xwindowdump" } },
    { "xml",{ "application/xml" } },
    { "z",{ "application/x-compress" } },
    { "zip",{ "application/zip" } },
  };

  return temp;
#endif

  std::map<std::string, std::vector<std::string> > result;
  
  {
    std::string temp[] = {
      "text/h323",
    };
    result["323"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/internet-property-stream",
    };
    result["acx"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/postscript",
    };
    result["ai"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "audio/x-aiff",
    };
    result["aif"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "audio/x-aiff",
    };
    result["aifc"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "audio/x-aiff",
    };
    result["aiff"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "video/x-ms-asf",
    };
    result["asf"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "video/x-ms-asf",
    };
    result["asr"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "video/x-ms-asf",
    };
    result["asx"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "audio/basic",
    };
    result["au"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "video/x-msvideo",
    };
    result["avi"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/olescript",
    };
    result["axs"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "text/plain",
    };
    result["bas"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/x-bcpio",
    };
    result["bcpio"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/octet-stream",
    };
    result["bin"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "image/bmp",
    };
    result["bmp"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "text/plain",
    };
    result["c"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/vnd.ms-pkiseccat",
    };
    result["cat"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/x-cdf",
    };
    result["cdf"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "http://identifiers.org/combine.specifications/cellml",
    };
    result["cellml"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/x-x509-ca-cert",
    };
    result["cer"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/octet-stream",
    };
    result["class"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/x-copasi",
    };
    result["copasi"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/x-msclip",
    };
    result["clp"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "image/x-cmx",
    };
    result["cmx"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "image/cis-cod",
    };
    result["cod"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/x-cpio",
    };
    result["cpio"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/x-mscardfile",
    };
    result["crd"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/pkix-crl",
    };
    result["crl"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/x-x509-ca-cert",
    };
    result["crt"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/x-csh",
    };
    result["csh"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "text/css",
    };
    result["css"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "text/csv",
    };
    result["csv"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/x-director",
    };
    result["dcr"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/x-x509-ca-cert",
    };
    result["der"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/x-director",
    };
    result["dir"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/x-msdownload",
    };
    result["dll"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/octet-stream",
    };
    result["dms"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/msword",
    };
    result["doc"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/msword",
    };
    result["dot"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/x-dvi",
    };
    result["dvi"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/x-director",
    };
    result["dxr"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/postscript",
    };
    result["eps"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "text/x-setext",
    };
    result["etx"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/envoy",
    };
    result["evy"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/octet-stream",
    };
    result["exe"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/fractals",
    };
    result["fif"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "x-world/x-vrml",
    };
    result["flr"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "image/gif",
    };
    result["gif"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/x-gtar",
    };
    result["gtar"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/x-gzip",
    };
    result["gz"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "text/plain",
    };
    result["h"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/x-hdf",
    };
    result["hdf"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/winhlp",
    };
    result["hlp"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/mac-binhex40",
    };
    result["hqx"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/hta",
    };
    result["hta"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "text/x-component",
    };
    result["htc"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "text/html",
    };
    result["htm"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "text/html",
    };
    result["html"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "text/webviewhtml",
    };
    result["htt"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "image/x-icon",
    };
    result["ico"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "image/ief",
    };
    result["ief"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/x-iphone",
    };
    result["iii"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/x-internet-signup",
    };
    result["ins"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/x-internet-signup",
    };
    result["isp"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "image/pipeg",
    };
    result["jfif"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "image/jpeg",
    };
    result["jpe"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "image/jpeg",
    };
    result["jpeg"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "image/jpeg",
    };
    result["jpg"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/x-javascript",
    };
    result["js"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/x-latex",
    };
    result["latex"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/octet-stream",
    };
    result["lha"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "video/x-la-asf",
    };
    result["lsf"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "video/x-la-asf",
    };
    result["lsx"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/octet-stream",
    };
    result["lzh"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/x-matlab",
    };
    result["m"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/x-msmediaview",
    };
    result["m13"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/x-msmediaview",
    };
    result["m14"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "audio/x-mpegurl",
    };
    result["m3u"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/x-troff-man",
    };
    result["man"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "http://identifiers.org/combine.specifications/omex",
      "http://identifiers.org/combine.specifications/omex-manifest",
      "http://identifiers.org/combine.specifications/omex.version-1",
    };
    result["manifest"] = std::vector<std::string>(temp, temp + 3);
  }

  {
    std::string temp[] = {
      "application/x-matlab",
    };
    result["mat"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/x-msaccess",
    };
    result["mdb"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/x-troff-me",
    };
    result["me"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "message/rfc822",
    };
    result["mht"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "message/rfc822",
    };
    result["mhtml"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "audio/mid",
    };
    result["mid"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/x-msmoney",
    };
    result["mny"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "video/quicktime",
    };
    result["mov"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "video/x-sgi-movie",
    };
    result["movie"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "video/mpeg",
    };
    result["mp2"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "audio/mpeg",
    };
    result["mp3"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "video/mpeg",
    };
    result["mpa"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "video/mpeg",
    };
    result["mpe"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "video/mpeg",
    };
    result["mpeg"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "video/mpeg",
    };
    result["mpg"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/vnd.ms-project",
    };
    result["mpp"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "video/mpeg",
    };
    result["mpv2"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/x-troff-ms",
    };
    result["ms"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/x-msmediaview",
    };
    result["mvb"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "message/rfc822",
    };
    result["nws"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/oda",
    };
    result["oda"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "http://identifiers.org/combine.specifications/omex-metadata",
    };
    result["omex"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/pkcs10",
    };
    result["p10"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/x-pkcs12",
    };
    result["p12"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/x-pkcs7-certificates",
    };
    result["p7b"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/x-pkcs7-mime",
    };
    result["p7c"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/x-pkcs7-mime",
    };
    result["p7m"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/x-pkcs7-certreqresp",
    };
    result["p7r"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/x-pkcs7-signature",
    };
    result["p7s"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "image/x-portable-bitmap",
    };
    result["pbm"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/pdf",
    };
    result["pdf"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/x-pkcs12",
    };
    result["pfx"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "image/x-portable-graymap",
    };
    result["pgm"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/ynd.ms-pkipko",
    };
    result["pko"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/x-perfmon",
    };
    result["pma"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/x-perfmon",
    };
    result["pmc"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/x-perfmon",
    };
    result["pml"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/x-perfmon",
    };
    result["pmr"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/x-perfmon",
    };
    result["pmw"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "image/png",
    };
    result["png"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "image/x-portable-anymap",
    };
    result["pnm"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/vnd.ms-powerpoint",
    };
    result["pot,"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "image/x-portable-pixmap",
    };
    result["ppm"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/vnd.ms-powerpoint",
    };
    result["pps"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/vnd.ms-powerpoint",
    };
    result["ppt"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/pics-rules",
    };
    result["prf"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/postscript",
    };
    result["ps"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/x-mspublisher",
    };
    result["pub"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "video/quicktime",
    };
    result["qt"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "audio/x-pn-realaudio",
    };
    result["ra"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "audio/x-pn-realaudio",
    };
    result["ram"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "image/x-cmu-raster",
    };
    result["ras"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "image/x-rgb",
    };
    result["rgb"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "audio/mid",
    };
    result["rmi"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/x-troff",
    };
    result["roff"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/rtf",
    };
    result["rtf"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "text/richtext",
    };
    result["rtx"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "http://identifiers.org/combine.specifications/sbgn",
    };
    result["sbgn"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "http://identifiers.org/combine.specifications/sbml",
      "http://identifiers.org/combine.specifications/sbml.level-1.version-1",
      "http://identifiers.org/combine.specifications/sbml.level-1.version-2",
      "http://identifiers.org/combine.specifications/sbml.level-2.version-1",
      "http://identifiers.org/combine.specifications/sbml.level-2.version-2",
      "http://identifiers.org/combine.specifications/sbml.level-2.version-3",
      "http://identifiers.org/combine.specifications/sbml.level-2.version-4",
      "http://identifiers.org/combine.specifications/sbml.level-2.version-5",
      "http://identifiers.org/combine.specifications/sbml.level-3.version-1",
      "http://identifiers.org/combine.specifications/sbml.level-3.version-2",
      "http://identifiers.org/combine.specifications/sbml.level-1.version.1",
      "http://identifiers.org/combine.specifications/sbml.level-1.version.2",
      "http://identifiers.org/combine.specifications/sbml.level-2.version.1",
      "http://identifiers.org/combine.specifications/sbml.level-2.version.2",
      "http://identifiers.org/combine.specifications/sbml.level-2.version.3",
      "http://identifiers.org/combine.specifications/sbml.level-2.version.4",
      "http://identifiers.org/combine.specifications/sbml.level-2.version.5",
      "http://identifiers.org/combine.specifications/sbml.level-3.version.1",
      "http://identifiers.org/combine.specifications/sbml.level-3.version.2",
    };
    result["sbml"] = std::vector<std::string>(temp, temp + 19);
  }

  {
    std::string temp[] = {
      "application/x-msschedule",
    };
    result["scd"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "text/scriptlet",
    };
    result["sct"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "http://identifiers.org/combine.specifications/sed-ml",
      "http://identifiers.org/combine.specifications/sedml",
      "http://identifiers.org/combine.specifications/sed-ml.level-1.version-1",
      "http://identifiers.org/combine.specifications/sed-ml.level-1.version-2",
      "http://identifiers.org/combine.specifications/sed-ml.level-1.version-3",
    };
    result["sed-ml"] = std::vector<std::string>(temp, temp + 5);
  }

  {
    std::string temp[] = {
      "http://identifiers.org/combine.specifications/sed-ml",
      "http://identifiers.org/combine.specifications/sedml",
      "http://identifiers.org/combine.specifications/sed-ml.level-1.version-1",
      "http://identifiers.org/combine.specifications/sed-ml.level-1.version-2",
      "http://identifiers.org/combine.specifications/sed-ml.level-1.version-3",
    };
    result["sedml"] = std::vector<std::string>(temp, temp + 5);
  }

  {
    std::string temp[] = {
      "application/x-sed-ml-archive",
    };
    result["sedx"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/set-payment-initiation",
    };
    result["setpay"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/set-registration-initiation",
    };
    result["setreg"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/x-sh",
    };
    result["sh"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/x-shar",
    };
    result["shar"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/x-stuffit",
    };
    result["sit"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "audio/basic",
    };
    result["snd"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/x-pkcs7-certificates",
    };
    result["spc"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/futuresplash",
    };
    result["spl"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/x-wais-source",
    };
    result["src"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/vnd.ms-pkicertstore",
    };
    result["sst"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/vnd.ms-pkistl",
    };
    result["stl"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "text/html",
    };
    result["stm"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/x-sv4cpio",
    };
    result["sv4cpio"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/x-sv4crc",
    };
    result["sv4crc"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "image/svg+xml",
    };
    result["svg"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/x-shockwave-flash",
    };
    result["swf"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/x-troff",
    };
    result["t"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/x-tar",
    };
    result["tar"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/x-tcl",
    };
    result["tcl"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/x-tex",
    };
    result["tex"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/x-texinfo",
    };
    result["texi"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/x-texinfo",
    };
    result["texinfo"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/x-compressed",
    };
    result["tgz"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "image/tiff",
    };
    result["tif"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "image/tiff",
    };
    result["tiff"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/x-troff",
    };
    result["tr"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/x-msterminal",
    };
    result["trm"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "text/tab-separated-values",
    };
    result["tsv"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "text/plain",
    };
    result["txt"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "text/iuls",
    };
    result["uls"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/x-ustar",
    };
    result["ustar"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "text/x-vcard",
    };
    result["vcf"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "x-world/x-vrml",
    };
    result["vrml"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "audio/x-wav",
    };
    result["wav"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/vnd.ms-works",
    };
    result["wcm"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/vnd.ms-works",
    };
    result["wdb"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/vnd.ms-works",
    };
    result["wks"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/x-msmetafile",
    };
    result["wmf"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/vnd.ms-works",
    };
    result["wps"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/x-mswrite",
    };
    result["wri"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "x-world/x-vrml",
    };
    result["wrl"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "x-world/x-vrml",
    };
    result["wrz"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "x-world/x-vrml",
    };
    result["xaf"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "image/x-xbitmap",
    };
    result["xbm"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/vnd.ms-excel",
    };
    result["xla"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/vnd.ms-excel",
    };
    result["xlc"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/vnd.ms-excel",
    };
    result["xlm"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/vnd.ms-excel",
    };
    result["xls"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/vnd.ms-excel",
    };
    result["xlt"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/vnd.ms-excel",
    };
    result["xlw"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/xml",
    };
    result["xml"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "x-world/x-vrml",
    };
    result["xof"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "image/x-xpixmap",
    };
    result["xpm"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "image/x-xwindowdump",
    };
    result["xwd"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/x-compress",
    };
    result["z"] = std::vector<std::string>(temp, temp + 1);
  }

  {
    std::string temp[] = {
      "application/zip",
    };
    result["zip"] = std::vector<std::string>(temp, temp + 1);
  }



  return result;
};
