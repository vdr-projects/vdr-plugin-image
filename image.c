/*
 * Image plugin to VDR (C++)
 *
 * (C) 2003 Kai Tobias Burwieck <kai@burwieck.net>
 * (C) 2004     "Interpohl"  <interpohl@vdr-portal.de> 
 * (C) 2004     A. Brachold   <vdr04-at-deltab.de>
 * (C) 2004     O. Kreuzinger <Onno@Kreuzinger.biz>
 * (C) 2004     A. Holzhammer for the massive script updates
 *  
 *  based on mp3/mplayer plguin by Stefan Hülswitt <huels@iname.com>
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

#include <getopt.h>
#include <vdr/plugin.h>


#include "setup-image.h"
#include "data-image.h"
#include "menu-image.h"
#include "i18n.h"
#include "commands.h"
#include "liboutput/encode.h"

static const char *VERSION        = "0.2.3";
static const char *DESCRIPTION    = "A Image Viewer plugin";
static const char *MAINMENUENTRY  = "Image";

class cPluginImage : public cPlugin {
public:
  virtual ~cPluginImage();
  virtual const char *Version(void) { return VERSION; }
  virtual const char *Description(void) { return tr(DESCRIPTION); }
  virtual const char *CommandLineHelp(void);
  virtual bool ProcessArgs(int argc, char *argv[]);
  virtual bool Start(void);
  virtual const char *MainMenuEntry(void) { return tr(MAINMENUENTRY); }
  virtual cOsdMenu *MainMenuAction(void);
  virtual cMenuSetupPage *SetupMenu(void);
  virtual bool SetupParse(const char *Name, const char *Value);
  };

bool cPluginImage::SetupParse(const char *szName, const char *szValue)
{
	return ImageSetup.SetupParse(szName,szValue);
}

const char *cPluginImage::CommandLineHelp(void)
{
  static char *help_str=0;
  
  free(help_str);    //                                     for easier orientation, this is column 80|
  asprintf(&help_str,"  -m CMD,   --mount=CMD    use CMD to mount/unmount/eject image sources\n"
                     "                           (default: %s)\n"
                     "  -C CMD,   --convert=CMD  use CMD when converting Images\n"
                     "                           (default: %s)\n",
                    g_szMountScript,
                    g_szConvertScript
                    );
  return help_str;
}

bool cPluginImage::ProcessArgs(int argc, char *argv[])
{
  static struct option long_options[] = {
      { "mount",    required_argument, NULL, 'm' },
      { "convert",  required_argument, NULL, 'C' },
      { NULL }
    };
    
  int c, option_index = 0;
  while((c=getopt_long(argc,argv,"m:C:",long_options,&option_index))!=-1) {
    switch (c) {
      case 'm': g_szMountScript=optarg;break;
      case 'C': g_szConvertScript=optarg;break;
      default:  return false;
      }
    }
  return true;
}

bool cPluginImage::Start(void)
{
  if(!cEncode::Register()) {   
    return false;
  }

  ImageSources.Load(AddDirectory(ConfigDirectory(),  "imagesources.conf"));
  if(ImageSources.Count()<1) {
    esyslog("imageplugin: you must have defined at least one source in imagesources.conf");
    return false;
    }
  
  RegisterI18n(Phrases);
  return true;
}

cPluginImage::~cPluginImage()
{
  cEncode::UnRegister();
}


cOsdMenu *cPluginImage::MainMenuAction(void)
{
  return new cMenuImageBrowse;
}

cMenuSetupPage *cPluginImage::SetupMenu(void)
{
  return new cMenuSetupImage;
}


VDRPLUGINCREATOR(cPluginImage); // Don't touch this!
