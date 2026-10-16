// Imported from doldecomp/ogws (CC0), src/revolution/DVD/dvdFatal.c
#include <revolution/dvd.h>
#include <revolution/os.h>
#include <revolution/sc.h>

typedef void (*FatalFuncPtr)(void);
static FatalFuncPtr FatalFunc = NULL;

const char* const __DVDErrorMessage[] = {
    // clang-format off

    // SC_LANG_JP
    "\n\n\n\x83\x47\x83\x89\x81\x5B\x82\xAA\x94\xAD\x90\xB6\x82\xB5\x82\xDC\x82\xB5\x82\xBD\x81\x42\n\n"
    "\x83\x43\x83\x57\x83\x46\x83\x4E\x83\x67\x83\x7B\x83\x5E\x83\x93\x82\xF0\x89\x9F\x82\xB5\x82\xC4\x83\x66\x83\x42\x83\x58\x83\x4E\x82\xF0\x8E\xE6\x82\xE8\x8F\x6F\x82\xB5\x82\xC4\x82\xA9\n"
    "\x82\xE7\x81\x41\x96\x7B\x91\xCC\x82\xCC\x93\x64\x8C\xB9\x82\xF0OFF\x82\xC9\x82\xB5\x82\xC4\x81\x41\x96\x7B\x91\xCC\x82\xCC\x8E\xE6\x88\xB5\x90\xE0\x96\xBE\x8F\x91\x82\xCC\n"
    "\x8E\x77\x8E\xA6\x82\xC9\x8F\x5D\x82\xC1\x82\xC4\x82\xAD\x82\xBE\x82\xB3\x82\xA2\x81\x42",

    // SC_LANG_EN
    "\n\n\nAn error has occurred.\n"
    "Press the Eject Button, remove the\n"
    "Game Disc, and turn the power off.\n"
    "Please read the Wii operations manual\n"
    "for more information.",

    // SC_LANG_DE
    "\n\n\nEin Fehler ist aufgetreten.\n"
    "Dr\xFC""cke den Ausgabeknopf, entnimm die\n"
    "Game Disc und schalte die Wii-Konsole\n"
    "aus. Bitte lies die Bedienungsanleitung der\n"
    "Wii-Konsole, um weitere Informationen zu\n"
    "erhalten.",

    // SC_LANG_FR
    "\n\n\nUne erreur est survenue.\n"
    "Appuyez sur le bouton EJECT, retirez\n"
    "le disque de jeu et \xE9teignez la console.\n"
    "Veuillez vous r\xE9""f\xE9rer au mode d'emploi\n"
    "de la console pour de plus amples\n"
    "informations.",

    // SC_LANG_SP
    "\n\n\nSe ha producido un error.\n"
    "Pulsa el Bot\xF3n EJECT, saca el disco y\n"
    "apaga la consola. Consulta el manual de\n"
    "instrucciones de la consola Wii para\n"
    "obtener m\xE1s informaci\xF3n.",
    
    // SC_LANG_IT
    "\n\n\nSi \xE8 verificato un errore.\n"
    "Premi il pulsante EJECT, estrai il disco\n"
    "di gioco e spegni la console. Per maggiori\n"
    "informazioni consulta il manuale di\n"
    "istruzioni della console Wii.",
    
    // SC_LANG_NL
    "\n\n\nEr is een fout opgetreden.\n"
    "Druk op de ejectknop, verwijder de\n"
    "speldisk en zet het systeem uit. Lees\n"
    "de Wii-handleiding voor meer informatie."

    // clang-format on
};

void __DVDShowFatalMessage(void) {
    const char* msg;
    GXColor bgColor = {0, 0, 0, 0};
    GXColor textColor = {255, 255, 255, 0};

    if (SCGetLanguage() == SC_LANG_JAPANESE) {
        OSSetFontEncode(OS_FONT_ENCODE_SJIS);
    } else {
        OSSetFontEncode(OS_FONT_ENCODE_ANSI);
    }

    msg = (SCGetLanguage() > SC_LANG_DUTCH) ? __DVDErrorMessage[SC_LANG_ENGLISH]
                                         : __DVDErrorMessage[SCGetLanguage()];

    OSFatal(textColor, bgColor, msg);
}

BOOL DVDSetAutoFatalMessaging(BOOL enable) {
    BOOL enabled;
    BOOL old;

    enabled = OSDisableInterrupts();

    old = (FatalFunc != NULL);

    if (enable) {
        FatalFunc = __DVDShowFatalMessage;
    } else {
        FatalFunc = NULL;
    }

    OSRestoreInterrupts(enabled);
    return old;
}

BOOL __DVDGetAutoFatalMessaging(void) {
    return FatalFunc != NULL;
}

void __DVDPrintFatalMessage(void) {
    if (FatalFunc != NULL) {
        FatalFunc();
    }
}
