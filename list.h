/*
 * Image plugin to VDR (C++)
 *
 * (C) 2004 Andreas Brachold    <vdr04-at-deltab.de>
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

#ifndef ___IMAGE_LIST_H
#define ___IMAGE_LIST_H

class cSlideShow;
class cImage;
class cFileSource;

class cActivSlideShow
{
  /** The current active filelist with the slide*/
  cSlideShow                  *m_pCurSlideShow;
  /** Current number of Image in slide */  
  unsigned int                m_nCurrentImage;
  /** Total number of Images in slide */  
  unsigned int                m_nTotalImages;
  /** Reference to current Image of this player  */
  cImage                      *m_pCurImage;
  
public:
  cActivSlideShow();
  void Assign(cSlideShow *pCurSlideShow);
  void Shutdown(void);
  cSlideShow *SlideShow(void);
  cImage* GetImage();
  bool PrevImage(int nOffset);
  bool GotoImage(unsigned int nNewPictureIndex);
  bool NextImage(int nOffset);
  int GetJumpNames(int nOffset,cImage* pImage[],const unsigned int nMAX_BILDER);

  void Remove(cFileSource* src);

  /** Deliver the current number of viewed Image */
  int ImageCurrent(void) const    { return m_nCurrentImage;     }
  /** Deliver the total number of viewed Image */
  int ImageTotal(void) const      { return m_nTotalImages;      }

} extern theSlideShow;

#endif				//___IMAGE_LIST_H
