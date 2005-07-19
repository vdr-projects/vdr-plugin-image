/*
 * Image plugin to VDR (C++)
 *
 * (C) 2004 Andreas Brachold    <vdr04-at-deltab.de>
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

#include <vdr/config.h>
#include "i18n.h"

const tI18nPhrase Phrases[] = {
  { "Image",	/*English*/
    "Bilder",	/*Deutsch*/
    "", // TODO /*Slovenski*/
    "", // TODO /*Italiano*/
    "", // TODO /*Nederlands*
    "", // TODO /*Português*/
    "", // TODO /*Français*/
    "", // TODO /*Norsk*/
    "Kuvat",    /*suomi*/
    "", // TODO /*Polski*/
    "", // TODO /*Español*/
    "", // TODO /*Ellinika*/
    "", // TODO /*Svenska*/
    "", // TODO /*Romaneste*/
    "", // TODO /*Magyar*/
    "", // TODO /*Català*/
  },
  { "A Image Viewer plugin",	/*English*/
    "Ein Bildbetrachter Plugin",	/*Deutsch*/
    "", // TODO /*Slovenski*/
    "", // TODO /*Italiano*/
    "", // TODO /*Nederlands*
    "", // TODO /*Português*/
    "", // TODO /*Français*/
    "", // TODO /*Norsk*/
    "Katso valokuvia ruudullasi",  /*suomi*/
    "", // TODO /*Polski*/
    "", // TODO /*Español*/
    "", // TODO /*Ellinika*/
    "", // TODO /*Svenska*/
    "", // TODO /*Romaneste*/
    "", // TODO /*Magyar*/
    "", // TODO /*Català*/
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
  },
  { "Image source",
    "Bilder-Datenträger",
    "Image izvor",
    "", // TODO
    "", // TODO
    "", // TODO
    "Source Images",
    "", // TODO
    "Kuvat - lähteet",
    "", // TODO
    "", // TODO
    "Pigi Image",
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
  },
  { "Parent",
    "Zurück",
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
  },
  { "Select",
    "Auswählen",
    "Izberi",
    "", // TODO
    "", // TODO
    "", // TODO
    "Sélectionner",
    "", // TODO
    "Valitse",
    "", // TODO
    "Seleccionar", 
    "Epilogi",
    "Välj",
    "", // TODO
    "", // TODO
    "Escollir",
  },
  { "Error scanning directory!",
    "Fehler beim Lesen des Verzeichnisses!",
    "Napaka pri pregledovanju direktorija!",
    "", // TODO
    "", // TODO
    "", // TODO
    "Erreur de parcours du répertoire!",
    "", // TODO
    "Hakemiston selaus epäonnistui!",
    "", // TODO
    "¡Error al leer una carpeta!", 
    "Lathos stin sarosi tou fakelou!",
    "Kunde inte läsa katalogen!",
    "", // TODO
    "", // TODO
    "Error al llegir una carpeta!",
  },
  { "Source",
    "Datenträger",
    "Izvor",
    "", // TODO
    "", // TODO
    "", // TODO
    "Source",
    "", // TODO
    "Lähde",
    "", // TODO
    "Origen", 
    "Pigi",
    "Källa",
    "", // TODO
    "", // TODO
    "Orígen",
  },
  { "Mount",
    "Einbinden",
    "Priklopi",
    "", // TODO
    "", // TODO
    "", // TODO
    "Monter",
    "", // TODO
    "Kiinnitä",
    "", // TODO
    "Mount", 
    "Sindesi",
    "Montera",
    "", // TODO
    "", // TODO
    "Mount",
  },
  { "Unmount",
    "Aushängen",
    "Izklopi",
    "", // TODO
    "", // TODO
    "", // TODO
    "Démonter",
    "", // TODO
    "Irrota",
    "", // TODO
    "Unmount",
    "Aposindesi",
    "Avmontera",
    "", // TODO
    "", // TODO
    "Unmount",
  },
  { "Selected source is not mounted!",
    "Ausgewählter Datenträger ist nicht eingebunden!",
    "Izbran izvor ni prikljucen!",
    "", // TODO
    "", // TODO
    "", // TODO
    "Source sélectionnée non montée!",
    "", // TODO
    "Valittua lähdettä ei ole kiinnitetty!",
    "", // TODO
    "¡El origen deseado no està montado!", 
    "Epilegmeni Pigi den ine sindemeni!",
    "Den valda källan är inte monterad!",
    "", // TODO
    "", // TODO
    "l'Origen sel.leccionat no està muntat!",
  },
  { "Mount succeeded",
    "Einbinden erfolgreich",
    "Priklop izveden",
    "", // TODO
    "", // TODO
    "", // TODO
    "Montage réussi",
    "", // TODO
    "Kiinnittäminen onnistui",
    "", // TODO
    "mount correcto", 
    "I sindesi petixe",
    "Monteringen lyckades",
    "", // TODO
    "", // TODO
    "mount correcte",
  },
  { "Mount failed!",
    "Einbinden fehlgeschlagen!",
    "Napaka pri priklopu!",
    "", // TODO
    "", // TODO
    "", // TODO
    "Echec du montage!",
    "", // TODO
    "Kiinnittäminen epäonnistui!",
    "", // TODO
    "¡No he podido montar!", 
    "I sindesi apetixe!",
    "Monteringen misslyckades!",
    "", // TODO
    "", // TODO
    "No he pogut muntar!",
  },
  { "Unmount succeeded",
    "Aushängen erfolgreich",
    "Izklop izveden",
    "", // TODO
    "", // TODO
    "", // TODO
    "Démontage réussi",
    "", // TODO
    "Irrottaminen onnistui",
    "", // TODO
    "Éxito al unmount", 
    "I aposindesi itan epitixisi",
    "Avmonteringen lyckades",
    "", // TODO
    "", // TODO
    "unmount amb èxit",
  },
  { "Unmount failed!",
    "Aushängen fehlgeschlagen!",
    "Napaka pri izklopu!",
    "", // TODO
    "", // TODO
    "", // TODO
    "Echec du démontage!",
    "", // TODO
    "Irrottaminen epäonnistui!",
    "", // TODO
    "¡No puedo desmontar!", 
    "I aposindesi den itan epitixis!",
    "Avmonteringen misslyckades!",
    "", // TODO
    "", // TODO
    "No puc desmontar!",
  },
  { "Eject failed!",
    "Auswerfen fehlgeschlagen!",
    "Napaka pri izmetu!",
    "", // TODO
    "", // TODO
    "", // TODO
    "Echec de l'éjection!",
    "", // TODO
    "Avaaminen epäonnistui!",
    "", // TODO
    "¡No puedo expulsar!", 
    "I apovoli apetixe!",
    "Mata ut!",
    "", // TODO
    "", // TODO
    "No puc expulsar!",
  },
  { "Select picture via key 1..9!",
    "Bildauswahl über Taste 1..9!",
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "Valitse kuva näppäimillä 1..9!",
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
  },
  { "Building SlideShow...",
    "Erzeuge Diavorführung...",
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "Laaditaan diaesitystä..",
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
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
    "Söker igenom katalog...",
    "", // TODO
    "", // TODO
    "Revisant les carpetes..",
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
  },
  { "Error building SlideShow!",
    "Fehler beim Erzeugen der Diavorführung!",
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "Diaesityksen laatiminen epäonnistui!",
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
  },
  { "SlideShow ?",
    "Diavorführung ?",
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "Käytä diaesitystä",
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
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
  },
  { "Directory with temporary files",
    "Verzeichnis mit temporären Dateien",
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "Väliaikaistiedostot",
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
  },
  { "Show Filedate on OSD",
    "Zeige Dateidatum im OSD",
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "Näytä päivämäärä näytöllä",
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
  },
  { "Repeat SlideShow",
    "Wiederholung der Diavorführung",
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
  },
  { "Show Numbers on index image",
    "Zeige Zahlen im Indexbild",
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "Näytä numerot indeksikuvassa",
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
  },
#if VDRVERSNUM >= 10308
  { "Live Audio from primary Device",
    "Live Audio vom primären Gerät",
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "Live-ääni päävastaanottimelta",
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
    "", // TODO
  },
#endif
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
  },  
  { "Zoom",
    "Vergrößere",
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
  },  
  { "Execute",
    "Ausführen",
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
  },  
  { "Operation failed",	/*English*/
    "Vorgang fehlgeschlagen",	/*Deutsch*/
    "", // TODO /*Slovenski*/
    "", // TODO /*Italiano*/
    "", // TODO /*Nederlands*
    "", // TODO /*Português*/
    "", // TODO /*Français*/
    "", // TODO /*Norsk*/
    "Toiminto epäonnistui", /*suomi*/
    "", // TODO /*Polski*/
    "", // TODO /*Español*/
    "", // TODO /*Ellinika*/
    "", // TODO /*Svenska*/
    "", // TODO /*Romaneste*/
    "", // TODO /*Magyar*/
    "", // TODO /*Català*/
  },
  { "Image couldn't load",	/*English*/
    "Konnte Bild nicht lesen",	/*Deutsch*/
    "", // TODO /*Slovenski*/
    "", // TODO /*Italiano*/
    "", // TODO /*Nederlands*
    "", // TODO /*Português*/
    "", // TODO /*Français*/
    "", // TODO /*Norsk*/
    "Kuvan lukeminen epäonnistui", /*suomi*/
    "", // TODO /*Polski*/
    "", // TODO /*Español*/
    "", // TODO /*Ellinika*/
    "", // TODO /*Svenska*/
    "", // TODO /*Romaneste*/
    "", // TODO /*Magyar*/
    "", // TODO /*Català*/
  },
  { "Script execution failed",	/*English*/
    "Scriptausführung fehlgeschlagen",	/*Deutsch*/
    "", // TODO /*Slovenski*/
    "", // TODO /*Italiano*/
    "", // TODO /*Nederlands*
    "", // TODO /*Português*/
    "", // TODO /*Français*/
    "", // TODO /*Norsk*/
    "Skriptin suoritus epäonnistui", /*suomi*/
    "", // TODO /*Polski*/
    "", // TODO /*Español*/
    "", // TODO /*Ellinika*/
    "", // TODO /*Svenska*/
    "", // TODO /*Romaneste*/
    "", // TODO /*Magyar*/
    "", // TODO /*Català*/
  },
  { "Remove temporary files",	/*English*/
    "Lösche temporäre Dateien",	/*Deutsch*/
    "", // TODO /*Slovenski*/
    "", // TODO /*Italiano*/
    "", // TODO /*Nederlands*
    "", // TODO /*Português*/
    "", // TODO /*Français*/
    "", // TODO /*Norsk*/
    "Tyhjennä väliaikaistiedostot", /*suomi*/
    "", // TODO /*Polski*/
    "", // TODO /*Español*/
    "", // TODO /*Ellinika*/
    "", // TODO /*Svenska*/
    "", // TODO /*Romaneste*/
    "", // TODO /*Magyar*/
    "", // TODO /*Català*/
  },
  { NULL }
};
