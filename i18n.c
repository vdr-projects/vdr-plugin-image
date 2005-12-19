/*
 * Image plugin to VDR (C++)
 *
 * (C) 2004-2005 Andreas Brachold    <vdr04-at-deltab.de>
 * based on (C) 2003 Kai Tobias Burwieck      <kai-at-burwieck.net>
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

#include <vdr/config.h>
#include "i18n.h"

const tI18nPhrase Phrases[] = {
  { "Image",	/*English*/
    "Bilder",	/*Deutsch*/
    "", // TODO /*Slovenski*/
    "", // TODO /*Italiano*/
    "", // TODO /*Nederlands*
    "", // TODO /*PortuguÍs*/
    "", // TODO /*FranÁais*/
    "", // TODO /*Norsk*/
    "Kuvat",    /*suomi*/
    "", // TODO /*Polski*/
    "", // TODO /*EspaÒol*/
    "", // TODO /*Ellinika*/
    "", // TODO /*Svenska*/
    "", // TODO /*Romaneste*/
    "", // TODO /*Magyar*/
    "", // TODO /*Catal‡*/
    "∏◊ﬁ—‡–÷’›ÿÔ",	// Russian
    "", // TODO Hrvatski
    "", // TODO Eesti
    "", // TODO Dansk
  },
  { "A Image Viewer plugin",	/*English*/
    "Ein Bildbetrachter Plugin",	/*Deutsch*/
    "", // TODO /*Slovenski*/
    "", // TODO /*Italiano*/
    "", // TODO /*Nederlands*
    "", // TODO /*PortuguÍs*/
    "", // TODO /*FranÁais*/
    "", // TODO /*Norsk*/
    "Katso valokuvia ruudullasi",  /*suomi*/
    "", // TODO /*Polski*/
    "", // TODO /*EspaÒol*/
    "", // TODO /*Ellinika*/
    "", // TODO /*Svenska*/
    "", // TODO /*Romaneste*/
    "", // TODO /*Magyar*/
    "", // TODO /*Catal‡*/
    "ø€–”ÿ› ‘€Ô ﬂ‡ﬁ·‹ﬁ‚‡– ÿ◊ﬁ—‡–÷’›ÿŸ",	// Russian
    "", // TODO Hrvatski
    "", // TODO Eesti
    "", // TODO Dansk
  },
  { "Image browser",
    "Bilder Verzeichnisanzeige",
    "Image navigator",
    "", // TODO
    "", // TODO
    "", // TODO
    "Navigateur Images",
    "", // TODO
    "Kuvat - selain",
    "", // TODO
    "", // TODO
    "Image endiksi fakelon",
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "øﬁ⁄–◊–‚Ï ﬂ–ﬂ⁄„ · ÿ◊ﬁ—‡–÷’›ÿÔ‹ÿ",	// Russian
    "", // TODO Hrvatski
    "", // TODO Eesti
    "", // TODO Dansk
  },
  { "Image source",
    "Bilder-Datentr‰ger",
    "Image izvor",
    "", // TODO
    "", // TODO
    "", // TODO
    "Source Images",
    "", // TODO
    "Kuvat - l‰hteet",
    "", // TODO
    "", // TODO
    "Pigi Image",
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "Ωﬁ·ÿ‚’€Ï(source)",	// Russian
    "", // TODO Hrvatski
    "", // TODO Eesti
    "", // TODO Dansk
  },
  { "Parent",
    "Zur¸ck",
    "Nazaj",
    "", // TODO
    "", // TODO
    "", // TODO
    "Parent",
    "", // TODO
    "Takaisin",
    "", // TODO
    "Predecesor", 
    "Piso",
    "Tillbaka",
    "", // TODO
    "", // TODO
    "Anterior",
    "Ω–◊–‘",	// Russian
    "", // TODO Hrvatski
    "", // TODO Eesti
    "", // TODO Dansk
  },
  { "Select",
    "Ausw‰hlen",
    "Izberi",
    "", // TODO
    "", // TODO
    "", // TODO
    "SÈlectionner",
    "", // TODO
    "Valitse",
    "", // TODO
    "Seleccionar", 
    "Epilogi",
    "V‰lj",
    "", // TODO
    "", // TODO
    "Escollir",
    "≤Î—‡–‚Ï",	// Russian
    "", // TODO Hrvatski
    "", // TODO Eesti
    "", // TODO Dansk
  },
  { "Error scanning directory!",
    "Fehler beim Lesen des Verzeichnisses!",
    "Napaka pri pregledovanju direktorija!",
    "", // TODO
    "", // TODO
    "", // TODO
    "Erreur de parcours du rÈpertoire!",
    "", // TODO
    "Hakemiston selaus ep‰onnistui!",
    "", // TODO
    "°Error al leer una carpeta!", 
    "Lathos stin sarosi tou fakelou!",
    "Kunde inte l‰sa katalogen!",
    "", // TODO
    "", // TODO
    "Error al llegir una carpeta!",
    "æËÿ—⁄– Á‚’›ÿÔ “Î—‡–››ﬁŸ ‘ÿ‡’⁄‚ﬁ‡ÿÿ!",	// Russian
    "", // TODO Hrvatski
    "", // TODO Eesti
    "", // TODO Dansk
  },
  { "Source",
    "Datentr‰ger",
    "Izvor",
    "", // TODO
    "", // TODO
    "", // TODO
    "Source",
    "", // TODO
    "L‰hde",
    "", // TODO
    "Origen", 
    "Pigi",
    "K‰lla",
    "", // TODO
    "", // TODO
    "OrÌgen",
    "Ωﬁ·ÿ‚’€Ï",	// Russian
    "", // TODO Hrvatski
    "", // TODO Eesti
    "", // TODO Dansk
  },
  { "Mount",
    "Einbinden",
    "Priklopi",
    "", // TODO
    "", // TODO
    "", // TODO
    "Monter",
    "", // TODO
    "Kiinnit‰",
    "", // TODO
    "Mount", 
    "Sindesi",
    "Montera",
    "", // TODO
    "", // TODO
    "Mount",
    "øﬁ‘⁄€ÓÁÿ‚Ï",	// Russian
    "", // TODO Hrvatski
    "", // TODO Eesti
    "", // TODO Dansk
  },
  { "Unmount",
    "Aush‰ngen",
    "Izklopi",
    "", // TODO
    "", // TODO
    "", // TODO
    "DÈmonter",
    "", // TODO
    "Irrota",
    "", // TODO
    "Unmount",
    "Aposindesi",
    "Avmontera",
    "", // TODO
    "", // TODO
    "Unmount",
    "æ‚⁄€ÓÁ‚Ï",	// Russian
    "", // TODO Hrvatski
    "", // TODO Eesti
    "", // TODO Dansk
  },
  { "Selected source is not mounted!",
    "Ausgew‰hlter Datentr‰ger ist nicht eingebunden!",
    "Izbran izvor ni prikljucen!",
    "", // TODO
    "", // TODO
    "", // TODO
    "Source sÈlectionnÈe non montÈe!",
    "", // TODO
    "Valittua l‰hdett‰ ei ole kiinnitetty!",
    "", // TODO
    "°El origen deseado no est‡ montado!", 
    "Epilegmeni Pigi den ine sindemeni!",
    "Den valda k‰llan ‰r inte monterad!",
    "", // TODO
    "", // TODO
    "l'Origen sel.leccionat no est‡ muntat!",
    "≤Î—‡–››ÎŸ ›ﬁ·ÿ‚’€Ï ›’ ﬂﬁ‘⁄€ÓÁ’›!",	// Russian
    "", // TODO Hrvatski
    "", // TODO Eesti
    "", // TODO Dansk
  },
  { "Mount succeeded",
    "Einbinden erfolgreich",
    "Priklop izveden",
    "", // TODO
    "", // TODO
    "", // TODO
    "Montage rÈussi",
    "", // TODO
    "Kiinnitt‰minen onnistui",
    "", // TODO
    "mount correcto", 
    "I sindesi petixe",
    "Monteringen lyckades",
    "", // TODO
    "", // TODO
    "mount correcte",
    "øﬁ‘⁄€ÓÁ’›ÿ’ ﬂ‡ﬁË€ﬁ „·ﬂ’Ë›ﬁ",	// Russian
    "", // TODO Hrvatski
    "", // TODO Eesti
    "", // TODO Dansk
  },
  { "Mount failed!",
    "Einbinden fehlgeschlagen!",
    "Napaka pri priklopu!",
    "", // TODO
    "", // TODO
    "", // TODO
    "Echec du montage!",
    "", // TODO
    "Kiinnitt‰minen ep‰onnistui!",
    "", // TODO
    "°No he podido montar!", 
    "I sindesi apetixe!",
    "Monteringen misslyckades!",
    "", // TODO
    "", // TODO
    "No he pogut muntar!",
    "æËÿ—⁄– ﬂﬁ‘⁄€ÓÁ’›ÿÔ!",	// Russian
    "", // TODO Hrvatski
    "", // TODO Eesti
    "", // TODO Dansk
  },
  { "Unmount succeeded",
    "Aush‰ngen erfolgreich",
    "Izklop izveden",
    "", // TODO
    "", // TODO
    "", // TODO
    "DÈmontage rÈussi",
    "", // TODO
    "Irrottaminen onnistui",
    "", // TODO
    "…xito al unmount", 
    "I aposindesi itan epitixisi",
    "Avmonteringen lyckades",
    "", // TODO
    "", // TODO
    "unmount amb Ëxit",
    "æ‚⁄€ÓÁ’›ÿ’ ﬂ‡ﬁË€ﬁ „·ﬂ’Ë›ﬁ",	// Russian
    "", // TODO Hrvatski
    "", // TODO Eesti
    "", // TODO Dansk
  },
  { "Unmount failed!",
    "Aush‰ngen fehlgeschlagen!",
    "Napaka pri izklopu!",
    "", // TODO
    "", // TODO
    "", // TODO
    "Echec du dÈmontage!",
    "", // TODO
    "Irrottaminen ep‰onnistui!",
    "", // TODO
    "°No puedo desmontar!", 
    "I aposindesi den itan epitixis!",
    "Avmonteringen misslyckades!",
    "", // TODO
    "", // TODO
    "No puc desmontar!",
    "æËÿ—⁄– ﬁ‚⁄€ÓÁ’›ÿÔ!",	// Russian
    "", // TODO Hrvatski
    "", // TODO Eesti
    "", // TODO Dansk
  },
  { "Eject failed!",
    "Auswerfen fehlgeschlagen!",
    "Napaka pri izmetu!",
    "", // TODO
    "", // TODO
    "", // TODO
    "Echec de l'Èjection!",
    "", // TODO
    "Avaaminen ep‰onnistui!",
    "", // TODO
    "°No puedo expulsar!", 
    "I apovoli apetixe!",
    "Mata ut!",
    "", // TODO
    "", // TODO
    "No puc expulsar!",
    "æËÿ—⁄– “Î—‡ﬁ·– ‘ÿ·⁄–!",	// Russian
    "", // TODO Hrvatski
    "", // TODO Eesti
    "", // TODO Dansk
  },
  { "Select picture via key 1..9!",
    "Bildauswahl ¸ber Taste 1..9!",
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "Valitse kuva n‰pp‰imill‰ 1..9!",
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "≤Î—ﬁ‡ ÿ◊ﬁ—‡–÷’››ÿŸ ﬂ‡ÿ ﬂﬁ‹ﬁÈÿ ⁄›ﬁﬂﬁ⁄ 1..9!",	// Russian
    "", // TODO Hrvatski
    "", // TODO Eesti
    "", // TODO Dansk
  },
  { "Building SlideShow...",
    "Erzeuge Diavorf¸hrung...",
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "Laaditaan diaesityst‰..",
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "¡–◊‘–›ÿ’ ¥ÿ–‰ÿ€Ï‹–",	// Russian
    "", // TODO Hrvatski
    "", // TODO Eesti
    "", // TODO Dansk
  },
  { "Scanning directory...",
    "Durchsuche Verzeichnis...",
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "Scanne le repertoire...",
    "", // TODO
    "Selataan hakemistoa...",
    "", // TODO
    "Leyendo las carpetas..",
    "", // TODO
    "Sˆker igenom katalog...",
    "", // TODO
    "", // TODO
    "Revisant les carpetes..",
    "ø‡ﬁ·‹‚‡ ‘ÿ‡’⁄‚ﬁ‡ÿÿ",	// Russian
    "", // TODO Hrvatski
    "", // TODO Eesti
    "", // TODO Dansk
  },
  { "No Files!",
    "Keine Dateien!",
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "Ei tiedostoja!",
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "ΩÿÁ’”ﬁ ›’ ›–Ÿ‘’›ﬁ!",	// Russian
    "", // TODO Hrvatski
    "", // TODO Eesti
    "", // TODO Dansk
  },
  { "Error building SlideShow!",
    "Fehler beim Erzeugen der Diavorf¸hrung!",
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "Diaesityksen laatiminen ep‰onnistui!",
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "æËÿ—⁄– ·ﬁ◊‘–›ÿÔ ‘ÿ–‰ÿ€Ï‹–!",	// Russian
    "", // TODO Hrvatski
    "", // TODO Eesti
    "", // TODO Dansk
  },
  { "SlideShow ?",
    "Diavorf¸hrung ?",
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "K‰yt‰ diaesityst‰",
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "¥ÿ–‰ÿ€Ï‹?",	// Russian
    "", // TODO Hrvatski
    "", // TODO Eesti
    "", // TODO Dansk
  },
  { "Slide duration (sec)",
    "Anzeigedauer (Sek)",
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "Dian esitysaika (s)",
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "≤‡’‹Ô ﬁ‚ﬁ—‡–÷’›ÿÔ (·’⁄)",	// Russian
    "", // TODO Hrvatski
    "", // TODO Eesti
    "", // TODO Dansk
  },
  { "Directory with temporary files",
    "Verzeichnis mit tempor‰ren Dateien",
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "V‰liaikaistiedostot",
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "¬º¿ ‘ÿ‡’⁄‚ﬁ‡ÿÔ",	// Russian
    "", // TODO Hrvatski
    "", // TODO Eesti
    "", // TODO Dansk
  },
  { "Show Filedate on OSD",
    "Zeige Dateidatum im OSD",
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "N‰yt‰ p‰iv‰m‰‰r‰ n‰ytˆll‰",
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "øﬁ⁄–◊–‚Ï ÿ›‰ﬁ‡‹–ÊÿÓ ﬁ ‰ÎŸ€–Â Á’‡’◊ OSD",	// Russian
    "", // TODO Hrvatski
    "", // TODO Eesti
    "", // TODO Dansk
  },
  { "Repeat SlideShow",
    "Wiederholung der Diavorf¸hrung",
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "Diaesityksen uudelleentoisto",
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "øﬁ“‚ﬁ‡ ‘ÿ–‰ÿ€Ï‹–",	// Russian
    "", // TODO Hrvatski
    "", // TODO Eesti
    "", // TODO Dansk
  },
  { "Show Numbers on index image",
    "Zeige Zahlen im Indexbild",
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "N‰yt‰ numerot indeksikuvassa",
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "øﬁ⁄–◊–‚Ï ›ﬁ‹’‡– “ ÿ›‘’⁄·’",	// Russian
    "", // TODO Hrvatski
    "", // TODO Eesti
    "", // TODO Dansk
  },
  { "Live Audio from primary Device",
    "Live Audio vom prim‰ren Ger‰t",
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "Live-‰‰ni ensisijaiselta sovittimelta",
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "∏·ﬂﬁ€Ï◊ﬁ“–‚Ï –⁄‚ÿ“›ﬁ’(Live) ◊“„⁄ﬁ“ﬁ’ ·ﬁﬂ‡ﬁ“ﬁ÷‘’›ÿ’",	// Russian
    "", // TODO Hrvatski
    "", // TODO Eesti
    "", // TODO Dansk
  },
  { "Convert...",
    "Wandle...",
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "Konvertoi...",
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "⁄ﬁ›“’‡‚–ÊÿÔ",	// Russian
    "", // TODO Hrvatski
    "", // TODO Eesti
    "", // TODO Dansk
  },  
  { "Zoom",
    "Vergrˆﬂere",
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "Suurenna",
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "ø‡ÿ—€ÿ◊ÿ‚Ï(Zoom)",	// Russian
    "", // TODO Hrvatski
    "", // TODO Eesti
    "", // TODO Dansk
  },  
  { "Execute",
    "Ausf¸hren",
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "Suorita",
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "≤Îﬂﬁ€›ÿ‚Ï",	// Russian
    "", // TODO Hrvatski
    "", // TODO Eesti
    "", // TODO Dansk
  },  
  { "Operation failed",	/*English*/
    "Vorgang fehlgeschlagen",	/*Deutsch*/
    "", // TODO /*Slovenski*/
    "", // TODO /*Italiano*/
    "", // TODO /*Nederlands*
    "", // TODO /*PortuguÍs*/
    "", // TODO /*FranÁais*/
    "", // TODO /*Norsk*/
    "Toiminto ep‰onnistui", /*suomi*/
    "", // TODO /*Polski*/
    "", // TODO /*EspaÒol*/
    "", // TODO /*Ellinika*/
    "", // TODO /*Svenska*/
    "", // TODO /*Romaneste*/
    "", // TODO /*Magyar*/
    "", // TODO /*Catal‡*/
    "æﬂ’‡–ÊÿÔ ﬁ·‚–›ﬁ“€’›–",	// Russian
    "", // TODO Hrvatski
    "", // TODO Eesti
    "", // TODO Dansk
  },
  { "Image couldn't load",	/*English*/
    "Konnte Bild nicht lesen",	/*Deutsch*/
    "", // TODO /*Slovenski*/
    "", // TODO /*Italiano*/
    "", // TODO /*Nederlands*
    "", // TODO /*PortuguÍs*/
    "", // TODO /*FranÁais*/
    "", // TODO /*Norsk*/
    "Kuvan lukeminen ep‰onnistui", /*suomi*/
    "", // TODO /*Polski*/
    "", // TODO /*EspaÒol*/
    "", // TODO /*Ellinika*/
    "", // TODO /*Svenska*/
    "", // TODO /*Romaneste*/
    "", // TODO /*Magyar*/
    "", // TODO /*Catal‡*/
    "æËÿ—⁄– Á‚’›ÿÔ ‰–Ÿ€–",	// Russian
    "", // TODO Hrvatski
    "", // TODO Eesti
    "", // TODO Dansk
  },
  { "Script execution failed",	/*English*/
    "Scriptausf¸hrung fehlgeschlagen",	/*Deutsch*/
    "", // TODO /*Slovenski*/
    "", // TODO /*Italiano*/
    "", // TODO /*Nederlands*
    "", // TODO /*PortuguÍs*/
    "", // TODO /*FranÁais*/
    "", // TODO /*Norsk*/
    "Skriptin suoritus ep‰onnistui", /*suomi*/
    "", // TODO /*Polski*/
    "", // TODO /*EspaÒol*/
    "", // TODO /*Ellinika*/
    "", // TODO /*Svenska*/
    "", // TODO /*Romaneste*/
    "", // TODO /*Magyar*/
    "", // TODO /*Catal‡*/
    "æËÿ—⁄– “Îﬂﬁ€›’›ÿÔ ·⁄‡ÿﬂ‚–!",	// Russian
    "", // TODO Hrvatski
    "", // TODO Eesti
    "", // TODO Dansk
  },
  { "Remove temporary files",	/*English*/
    "Lˆsche tempor‰re Dateien",	/*Deutsch*/
    "", // TODO /*Slovenski*/
    "", // TODO /*Italiano*/
    "", // TODO /*Nederlands*
    "", // TODO /*PortuguÍs*/
    "", // TODO /*FranÁais*/
    "", // TODO /*Norsk*/
    "Tyhjenn‰ v‰liaikaistiedostot", /*suomi*/
    "", // TODO /*Polski*/
    "", // TODO /*EspaÒol*/
    "", // TODO /*Ellinika*/
    "", // TODO /*Svenska*/
    "", // TODO /*Romaneste*/
    "", // TODO /*Magyar*/
    "", // TODO /*Catal‡*/
    "·‚ÿ‡–›ÿ’ tmp ‰–Ÿ€ﬁ“",	// Russian
    "", // TODO Hrvatski
    "", // TODO Eesti
    "", // TODO Dansk
  },
  { "Border for Underscan (Height)",	/*English*/
    "Rand f¸r Underscan (Hˆhe)",	/*Deutsch*/
    "", // TODO /*Slovenski*/
    "", // TODO /*Italiano*/
    "", // TODO /*Nederlands*
    "", // TODO /*PortuguÍs*/
    "", // TODO /*FranÁais*/
    "", // TODO /*Norsk*/
    "Reunuksen korkeus keskitykselle", /*suomi*/
    "", // TODO /*Polski*/
    "", // TODO /*EspaÒol*/
    "", // TODO /*Ellinika*/
    "", // TODO /*Svenska*/
    "", // TODO /*Romaneste*/
    "", // TODO /*Magyar*/
    "", // TODO /*Catal‡*/
    "", // TODO Russian
    "", // TODO Hrvatski
    "", // TODO Eesti
    "", // TODO Dansk
  },
  { "Border for Underscan (Width)",	/*English*/
    "Rand f¸r Underscan (Breite)",	/*Deutsch*/
    "", // TODO /*Slovenski*/
    "", // TODO /*Italiano*/
    "", // TODO /*Nederlands*
    "", // TODO /*PortuguÍs*/
    "", // TODO /*FranÁais*/
    "", // TODO /*Norsk*/
    "Reunuksen leveys keskitykselle", /*suomi*/
    "", // TODO /*Polski*/
    "", // TODO /*EspaÒol*/
    "", // TODO /*Ellinika*/
    "", // TODO /*Svenska*/
    "", // TODO /*Romaneste*/
    "", // TODO /*Magyar*/
    "", // TODO /*Catal‡*/
    "", // TODO Russian
    "", // TODO Hrvatski
    "", // TODO Eesti
    "", // TODO Dansk
  },
  { NULL }
};
