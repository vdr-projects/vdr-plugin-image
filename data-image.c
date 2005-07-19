/*
 * Image plugin to VDR (C++)
 *
 * (C) 2003 Kai Tobias Burwieck <kai@burwieck.net>
 *
 * This code is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This code is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 * Or, point your browser to http://www.gnu.org/copyleft/gpl.html
 */

#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "data-image.h"
#include "data.h"
#include "setup-image.h"

cFileSources ImageSources;

// --- cImage -------------------------------------------------------------

cImage::cImage(const char *szName, cFileSource * pSource)
: m_pSource(pSource)
, m_szFileName(NULL)
, m_szFileNamePNM(NULL)
, m_szFileNameIndex(NULL)
, m_szFileNameZoom(NULL)
{
  if(szName)
    m_szFileName = m_pSource->BuildName(szName);
  m_pSource->Block();
}

cImage::~cImage()
{
  Clear();
  m_pSource->Unblock();
}

const char *cImage::NameIndex()
{ 
  if(!m_szFileNameIndex)
  { 
    if(ImageSetup.m_bHousekeeping)
    { 
      char sz[PATH_MAX];
      strncpy(sz,ImageSetup.TempDir,sizeof(sz));
      strncat(sz,"/IXXXXXX",sizeof(sz));
      mktemp(sz);
      strncat(sz,".pnm",sizeof(sz));
      m_szFileNameIndex = strdup(sz);
    }
    else
    {  
      asprintf(&m_szFileNameIndex, "%s%sI%s.pnm", 
        ImageSetup.TempDir,
        *m_szFileName == '/'?"":"/",
        m_szFileName);    
    }
  }
  return m_szFileNameIndex; 
}

const char *cImage::NamePNM()
{ 
  if(!m_szFileNamePNM)
  { 
    if(ImageSetup.m_bHousekeeping)
    {  
      char sz[PATH_MAX];
      strncpy(sz,ImageSetup.TempDir,sizeof(sz));
      strncat(sz,"/VXXXXXX",sizeof(sz));
      mktemp(sz);
      strncat(sz,".pnm",sizeof(sz));
      m_szFileNamePNM = strdup(sz);
    } 
    else
    {  
      asprintf(&m_szFileNamePNM, "%s%s%s.pnm", 
        ImageSetup.TempDir,
        *m_szFileName == '/'?"":"/",
        m_szFileName);    
    }
  }
  return m_szFileNamePNM; 
}

const char *cImage::NameZoom()
{ 
  if(!m_szFileNameZoom)
  { 
    if(ImageSetup.m_bHousekeeping)
    {  
      char sz[PATH_MAX];
      strncpy(sz,ImageSetup.TempDir,sizeof(sz));
      strncat(sz,"/ZXXXXXX",sizeof(sz));
      mktemp(sz);
      strncat(sz,".pnm",sizeof(sz));
      m_szFileNameZoom = strdup(sz);
    } 
    else
    {  
      asprintf(&m_szFileNameZoom, "%s%sZ%s.pnm", 
        ImageSetup.TempDir,
        *m_szFileName == '/'?"":"/",
        m_szFileName);    
    }
  }
  return m_szFileNameZoom; 
}

bool UnlinkFile(const char *szFile)
{
    struct stat st;
    if(0 == stat(szFile,&st) && S_ISREG(st.st_mode) && 0 != unlink(szFile))
    {
        char szErr[128];
        int nErr = errno;
        szErr[sizeof(szErr)-1] = '\0';
        if(!nErr || 0 != strerror_r(nErr,szErr,sizeof(szErr)-1)) {
            szErr[0] = '\0';
        } 
        esyslog("imageplugin: Can't remove temporary file %s, because: %s.",szFile,szErr[0] != '\0'?szErr:"unknown");
        return false;
    }
    return true;
}

void cImage::Unlink(const char *szName)
{
  if(ImageSetup.m_bHousekeeping)
  {  
    char sz[PATH_MAX];
    // remove /tmp/image/xxx.pnm
    UnlinkFile(szName);
    // remove /tmp/image/xxx.pnm.par
    strncpy(sz,szName,sizeof(sz));
    strncat(sz,".par",sizeof(sz));
    UnlinkFile(sz);
    // remove /tmp/image/xxx.pnm.tmp
    strncpy(sz,szName,sizeof(sz));
    strncat(sz,".tmp",sizeof(sz));
    UnlinkFile(sz);
  }
}


void cImage::Clear(void)
{
  if(m_szFileNameIndex)
  {  
    Unlink(m_szFileNameIndex);
    free(m_szFileNameIndex);
    m_szFileNameIndex = NULL;
  }  

  if(m_szFileNameZoom)
  {  
    Unlink(m_szFileNameZoom);
    free(m_szFileNameZoom);
    m_szFileNameZoom = NULL;
  }  

  if(m_szFileNamePNM)
  {  
    Unlink(m_szFileNamePNM);
    free(m_szFileNamePNM);
    m_szFileNamePNM = NULL;
  }  

  if(m_szFileName)
  {
    free(m_szFileName);
    m_szFileName = NULL;
  }
}

bool cImage::CompareBaseDir(const cFileSource * pSource) const
{
  return 0 == strcmp(m_pSource->BaseDir(),pSource->BaseDir());

}
// -- cSlideShow --------------------------------------------------------------

cSlideShow::cSlideShow(cDirItem * Item)
: m_szFirstImageName(NULL)
, m_DirItem(Item->Source, Item->Subdir, Item->Name, Item->Type)
{
    
}

cSlideShow::~cSlideShow()
{
  if(m_szFirstImageName)
    free(m_szFirstImageName);
}

bool cSlideShow::Load(void)
{
  bool res = false;
  Clear();
  switch (m_DirItem.Type)
	{
	case itFile:
    {
    dsyslog("imageplugin: SlideShow: file %s\n", m_DirItem.Name);
		const char *path = m_DirItem.Subdir;
		res =
		    ScanDir(m_DirItem.Source, path, stFile, m_DirItem.Source->Include(),
			    0, true);
        if(res)
        {
               m_szFirstImageName = strdup(m_DirItem.Name); 
        }
        else
        {
             DoItem(m_DirItem.Source, m_DirItem.Subdir, m_DirItem.Name);
             res = true;
        }
		break;
        }
	case itDir:
	    {
		dsyslog("imageplugin: SlideShow: dir name:%s\n", m_DirItem.Name);
		char *path = m_DirItem.Path();
		res =
		    ScanDir(m_DirItem.Source, path, stFile, m_DirItem.Source->Include(),
			    0, true);
 		free(path);
		break;
	    }
	case itBase:
	    dsyslog("imageplugin: SlideShow: base\n");
	    res =
		ScanDir(m_DirItem.Source, 0, stFile, m_DirItem.Source->Include(), 0,
			true);
	    break;
	default:
	    break;
	}
  return res;
}

void cSlideShow::DoItem(cFileSource * src, const char *subdir,
			 const char *name)
{
  char *path = (char *)name;
  if(subdir)
    path = AddPath(subdir, name);
  Add(new cImage(path, src));
  if(subdir)
    free(path);
}
