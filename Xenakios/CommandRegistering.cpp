/******************************************************************************
/ CommandRegistering.cpp
/
/ Copyright (c) 2009 Tim Payne (SWS), original code by Xenakios
/ http://www.standingwaterstudios.com/reaper
/
/ Permission is hereby granted, free of charge, to any person obtaining a copy
/ of this software and associated documentation files (the "Software"), to deal
/ in the Software without restriction, including without limitation the rights to
/ use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
/ of the Software, and to permit persons to whom the Software is furnished to
/ do so, subject to the following conditions:
/ 
/ The above copyright notice and this permission notice shall be included in all
/ copies or substantial portions of the Software.
/ 
/ THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
/ EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
/ OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
/ NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
/ HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
/ WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
/ FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
/ OTHER DEALINGS IN THE SOFTWARE.
/
******************************************************************************/

#include "stdafx.h"
#include "Parameters.h"

#define MAIN_MENU_TEXT "E&xtensions"
#define MAIN_MENU_POS 8  // where to put main menu.  Negative counts from right, positive counts from left

using namespace std;

void DoMoveEditCursor32ndLeft(COMMAND_T*)
{
	double curbeats=TimeMap_timeToQN(GetCursorPosition());
	double newbeats=curbeats-(1.0/8.0);
	SetEditCurPos(TimeMap_QNToTime(newbeats),false,false);
}

void DoMoveEditCursor32ndRight(COMMAND_T*)
{
	double curbeats=TimeMap_timeToQN(GetCursorPosition());
	double newbeats=curbeats+(1.0/8.0);
	SetEditCurPos(TimeMap_QNToTime(newbeats),false,false);
}

void DoMoveEditCursor64thLeft(COMMAND_T*)
{
	double curbeats=TimeMap_timeToQN(GetCursorPosition());
	double newbeats=curbeats-(0.0625);
	SetEditCurPos(TimeMap_QNToTime(newbeats),false,false);
}

void DoMoveEditCursor64thRight(COMMAND_T*)
{
	double curbeats=TimeMap_timeToQN(GetCursorPosition());
	double newbeats=curbeats+(0.0625);
	SetEditCurPos(TimeMap_QNToTime(newbeats),false,false);
}

// ***************************************************************************
// Here's where you define all your commands:
// 1) accel structure for the keyboard shortcut
// 2) Text for the action list
// 3) Text for the register command
// 4) Function to be called on command hook
// 5) Menu text
// If you don't want a command to appear in the menu, set menu text to NULL
// Set menu text to SWS_SEPARATOR and rest to NULL to add menu separator
// Can also have SWS_STARTSUBMENU and SWS_ENDSUBMENU
COMMAND_T g_XenCommandTable[] = 
{	//    ACCELL     Name for action list     Unique_Name Function      Menu text/SEPARATOR  Submenu?
	{ { { 0, 0, 1 }, NULL }, SWS_STARTSUBMENU, NULL, "Item/Take selection", },
	{ { DEFACCEL, "Xenakios/SWS: Invert item selection" },										"XENAKIOS_INVERTITEMSELECTION",		DoInvertItemSelection,				"Invert item selection", },
	{ { DEFACCEL, "Xenakios/SWS: Skip select items in selected tracks..." },					"XENAKIOS_SELECT_EVERY_NTH_ITEM",	DoSkipSelectAllItemsOnTracks,		"Skip select items in selected tracks...", },
	{ { DEFACCEL, "Xenakios/SWS: Skip select items from selected items..." },					"XENAKIOS_SKIP_SELECT_FROM_ITEMS",	DoSkipSelectFromSelectedItems,		"Skip select items from selected items...", },
	{ { DEFACCEL, "Xenakios/SWS: Select items to start of track" },								"XENAKIOS_SELITEMSTOSTARTOFTRACK",	DoSelItemsToStartOfTrack,			"Select items to start of track", },
	{ { DEFACCEL, "Xenakios/SWS: Select items to end of track" },								"XENAKIOS_SELITEMSTOENDOFTRACK",	DoSelItemsToEndOfTrack,				"Select items to end of track", },
	{ { DEFACCEL, "Xenakios/SWS: Select first item(s) of selected track(s)" },					"XENAKIOS_SELFIRSTITEMSOFTRACKS",	DoSelectFirstItemInSelectedTrack,	"Select first item(s) of selected track(s)", },
	{ { DEFACCEL, "Xenakios/SWS: Switch item contents to next cue" },							"XENAKIOS_SWITCHITEMTONEXTCUE",		DoSwitchItemToNextCue,				"Switch item contents to next cue", },
	{ { DEFACCEL, "Xenakios/SWS: Switch item contents to next cue (preserve item length)" },	"XENAKIOS_SWITCHITEMTONEXTCUEPL",	DoSwitchItemToNextCuePresvLen,		"Switch item contents to next cue (preserve item length)", },
	{ { DEFACCEL, "Xenakios/SWS: Switch item contents to previous cue" },						"XENAKIOS_SWITCHITEMTOPREVCUE",		DoSwitchItemToPreviousCue,			"Switch item contents to previous cue", },
	{ { DEFACCEL, "Xenakios/SWS: Switch item contents to previous cue (preserve item length)" },"XENAKIOS_SWITCHITEMTOPREVCUEPL",	DoSwitchItemToPreviousCuePresvLen,	"Switch item contents to previous cue (preserve length)", },
	{ { DEFACCEL, "Xenakios/SWS: Switch item contents to first cue" },							"XENAKIOS_SWITCHITEMTOFIRSTCUE",	DoSwitchItemToFirstCue,				"Switch item contents to first cue", },
	{ { DEFACCEL, "Xenakios/SWS: Switch item contents to random cue" },							"XENAKIOS_SWITCHITEMTORNDCUE",		DoSwitchItemToRandomCue,			"Switch item contents to random cue", },
	{ { DEFACCEL, "Xenakios/SWS: Switch item contents to random cue (preserve item length)" },	"XENAKIOS_SWITCHITEMTORNDCUEPL",	DoSwitchItemToRandomCuePresvLen,	"Switch item contents to random cue (preserve item length)", },
	{ { DEFACCEL, NULL }, NULL, NULL, SWS_SEPARATOR, },
	{ { DEFACCEL, "Xenakios/SWS: Select first take in selected items" },				"XENAKIOS_SELECTFIRSTTAKEOFITEMS",	DoSelectFirstTakesInItems,		"Select first take in selected items", },
	{ { DEFACCEL, "Xenakios/SWS: Select last take in selected items" },					"XENAKIOS_SELECTLASTTAKEOFITEMS",	DoSelectLastTakesInItems,		"Select last take in selected items", },
	{ { DEFACCEL, "Xenakios/SWS: Select takes in selected items, shuffled random" },	"XENAKIOS_SHUFFLESELECTTAKES",		DoShuffleSelectTakesInItems,	"Select takes in selected items, shuffled random", },
	{ { DEFACCEL, "Xenakios/SWS: Select takes of selected items cyclically" },			"XENAKIOS_RRSELECTTAKESOFITEMS",	DoRoundRobinSelectTakes,		"Select takes of selected items cyclically", },
	{ { DEFACCEL, "Xenakios/SWS: Store current selected takes" },						"XENAKIOS_STORECURSELECTEDTAKES",	DoStoreSelectedTakes,			"Store current selected takes", },
	{ { DEFACCEL, "Xenakios/SWS: Recall selected takes" },								"XENAKIOS_RECALLSELECTEDTAKES",		DoRecallSelectedTakes,			"Recall selected takes", },
	{ {}, SWS_ENDSUBMENU, },
	{ { DEFACCEL, NULL }, NULL, NULL, SWS_SEPARATOR, },
	{ { { 0, 0, 2 }, NULL }, SWS_STARTSUBMENU, NULL, "Item/Take manipulation", },
	{ { DEFACCEL, "Xenakios/SWS: Repeat paste..." },					"XENAKIOS_REPEATPASTE", DoRepeatPaste,	"Repeat Paste...", },
	{ { DEFACCEL, NULL }, NULL, NULL, SWS_SEPARATOR, },
	{ { DEFACCEL, "Xenakios/SWS: Choose files for random insert..." },	"XENAKIOS_CHOOSE_FILES_FOR_RANDOMINSERT", DoSelectFiles,	"Choose files for random insert...", },
	{ { DEFACCEL, "Xenakios/SWS: Insert random file" }, "XENAKIOS_INSERT_RANDOMFILE", DoInsertRandom,	"Insert random file", },
	{ { DEFACCEL, "Xenakios/SWS: Insert shuffled random file" }, "XENAKIOS_INSERTSHUFFLEDRANDOMFILE", DoInsertShuffledRandomFile,	"Insert Shuffled random file", },
	{ { DEFACCEL, NULL }, NULL, NULL, SWS_SEPARATOR, },
	{ { DEFACCEL, "Xenakios/SWS: Randomize item positions..." }, "XENAKIOS_RANDOMIZE_ITEMPOS", DoRandomizePositionsDlg,	"Randomize item positions...", },
	{ { DEFACCEL, "Xenakios/SWS: Nudge item positions left, time based" }, "XENAKIOS_NUDGEITEMPOS_MINUS_SECS", DoNudgeItemsLeftSecsAndConfBased, NULL, },
	{ { DEFACCEL, "Xenakios/SWS: Nudge item positions right, time based" }, "XENAKIOS_NUDGEITEMPOS_PLUS_SECS", DoNudgeItemsRightSecsAndConfBased, NULL, },
	{ { DEFACCEL, "Xenakios/SWS: Nudge item positions left, beat based" }, "XENAKIOS_NUDGEITEMPOS_LEFT_BEATS", DoNudgeItemsLeftBeatsAndConfBased, NULL, },
	{ { DEFACCEL, "Xenakios/SWS: Nudge item positions right, beat based" }, "XENAKIOS_NUDGEITEMPOS_RIGHT_BEATS", DoNudgeItemsRightBeatsAndConfBased, NULL, },
	{ { DEFACCEL, "Xenakios/SWS: Move selected items to edit cursor" }, "XENAKIOS_MOVEITEMSTOEDITCURSOR", DoMoveItemsToEditCursor,	"Move selected items to edit cursor", },
	{ { DEFACCEL, "Xenakios/SWS: Move selected items left by item length" }, "XENAKIOS_MOVEITEMSLEFTBYLEN", DoMoveItemsLeftByItemLen,	"Move selected items left by item length", },
	{ { DEFACCEL, "Xenakios/SWS: Trim/untrim item left edge to edit cursor" }, "XENAKIOS_TRIM_LEFTEDGETO_EDCURSOR", DoTrimLeftEdgeToEditCursor,	"Trim/Untrim item left edge to edit cursor", },
	{ { DEFACCEL, "Xenakios/SWS: Trim/untrim item right edge to edit cursor" }, "XENAKIOS_TRIM_RIGHTEDGETO_EDCURSOR", DoTrimRightEdgeToEditCursor,	"Trim/Untrim item right edge to edit cursor", },
	{ { DEFACCEL, "Xenakios/SWS: Scale item positions/lengths by static percentage..." }, "XENAKIOS_SCALEITEMPOS_STATIC", DoScaleItemPosStaticDlg,	"Scale item positions/lengths by static percentage...", },
	{ { DEFACCEL, "Xenakios/SWS: Reposition selected items..." }, "XENAKIOS_REPOSITION_ITEMS", DoReposItemsDlg,	"Reposition selected items...", },
	{ { DEFACCEL, NULL }, NULL, NULL, SWS_SEPARATOR, },
	{ { DEFACCEL, "Xenakios/SWS: Rename selected take(s) (old version)..." }, "XENAKIOS_RENAMEMULTIPLETAKES", DoRenameTakeDlg,	"Rename selected take(s)...", },
	{ { DEFACCEL, "Xenakios/SWS: Auto-rename selected takes..." }, "XENAKIOS_AUTORENAMETAKES", DoAutoRename,	"Auto-rename selected takes...", },
	{ { DEFACCEL, "Xenakios/SWS: Rename selected takes with BWAV Description" }, "XENAKIOS_BROADCAST_TAKERENAME", DoRenameTakesWithBWAVDesc,	"Rename selected takes with BWAV description", },
	{ { DEFACCEL, "Xenakios/SWS: Choose new source file for selected takes..." }, "XENAKIOS_CHANGESOURCEFILE", DoChooseNewSourceFileForSelTakes,	"Choose new source file for selected Takes...", },
	{ { DEFACCEL, "Xenakios/SWS: Resample pitch shift item one semitone down" }, "XENAKIOS_RESAMPLE_SEMIDOWN", DoResampleTakeOneSemitoneDown, NULL, },
	{ { DEFACCEL, "Xenakios/SWS: Resample pitch shift item one semitone up" }, "XENAKIOS_RESAMPLE_SEMIUP", DoResampleTakeOneSemitoneUp, NULL, },
	
	{ { DEFACCEL, "Xenakios/SWS: Nudge item pitch up (resampled) A" }, "XENAKIOS_RESAMPLE_UPNUDA", DoNudgeUpTakePitchResampledA, NULL, },
	{ { DEFACCEL, "Xenakios/SWS: Nudge item pitch down (resampled) A" }, "XENAKIOS_RESAMPLE_DOWNNUDA", DoNudgeDownTakePitchResampledA, NULL, },
	{ { DEFACCEL, "Xenakios/SWS: Nudge item pitch up (resampled) B" }, "XENAKIOS_RESAMPLE_UPNUDB", DoNudgeUpTakePitchResampledB, NULL, },
	{ { DEFACCEL, "Xenakios/SWS: Nudge item pitch down (resampled) B" }, "XENAKIOS_RESAMPLE_DOWNNUDB", DoNudgeDownTakePitchResampledB, NULL, },
	
	{ { DEFACCEL, "Xenakios/SWS: Nudge item pitch down" }, "XENAKIOS_NUDGEITEMPITCHDOWN", DoNudgeItemPitchesDown, NULL, },
	{ { DEFACCEL, "Xenakios/SWS: Nudge item pitch up" }, "XENAKIOS_NUDGEITEMPITCHUP", DoNudgeItemPitchesUp, NULL, },
	{ { DEFACCEL, "Xenakios/SWS: Nudge item pitch down B" }, "XENAKIOS_NUDGEITEMPITCHDOWNB", DoNudgeItemPitchesDownB, NULL, },
	{ { DEFACCEL, "Xenakios/SWS: Nudge item pitch up B" }, "XENAKIOS_NUDGEITEMPITCHUPB", DoNudgeItemPitchesUpB, NULL, },
	
	{ { DEFACCEL, "Xenakios/SWS: Nudge item volume down" }, "XENAKIOS_NUDGEITEMVOLDOWN", DoNudgeItemVolsDown, NULL, },
	
	{ { DEFACCEL, "Xenakios/SWS: Nudge item volume up" }, "XENAKIOS_NUDGEITEMVOLUP", DoNudgeItemVolsUp, NULL, },
	{ { DEFACCEL, "Xenakios/SWS: Nudge active take volume down" }, "XENAKIOS_NUDGETAKEVOLDOWN", DoNudgeTakeVolsDown, NULL, },
	{ { DEFACCEL, "Xenakios/SWS: Nudge active take volume up" }, "XENAKIOS_NUDGETAKEVOLUP", DoNudgeTakeVolsUp, NULL, },
	{ { DEFACCEL, "Xenakios/SWS: Reset item volume to 0.0" }, "XENAKIOS_RESETITEMVOL", DoResetItemVol, NULL, },
	{ { DEFACCEL, "Xenakios/SWS: Reset active take volume to 0.0" }, "XENAKIOS_RESETTAKEVOL", DoResetTakeVol, NULL, },
	
	{ { DEFACCEL, "Xenakios/SWS: Set item rate to 1.0 and pitch to 0.0" }, "XENAKIOS_RESETITEMPITCHANDRATE", DoResetItemRateAndPitch, NULL, },
	
	{ { DEFACCEL, "Xenakios/SWS: Set volume and pan of selected takes..." }, "XENAKIOS_SETPANVOLSELTAKES", DoShowVolPanDialog, NULL, },
	{ { DEFACCEL, "Xenakios/SWS: Set volume of selected items..." }, "XENAKIOS_SETVOLSELITEMS", DoShowItemVolumeDialog, NULL, },
	
	{ { DEFACCEL, "Xenakios/SWS: Toggle selected takes normalized/unity gain" }, "XENAKIOS_TOGGLETAKENORMALIZE", DoToggleTakesNormalize, NULL, },
	{ { DEFACCEL, "Xenakios/SWS: Set fades of selected items to 0.0" }, "XENAKIOS_REMOVEITEMFADES", DoRemoveItemFades, NULL, },
	{ { DEFACCEL, "Xenakios/SWS: Set fades of selected items to configuration A" }, "XENAKIOS_SETITEMFADES", DoSetItemFadesConfLen, NULL, },
	{ { DEFACCEL, "Xenakios/SWS: Set fades of selected items to configuration B" }, "XENAKIOS_SETITEMFADESB", DoSetItemFadesConfLenB, NULL, },
	
	{ { DEFACCEL, "Xenakios/SWS: Pan takes of item symmetrically" }, "XENAKIOS_PANTAKESOFITEMSYM", DoPanTakesSymmetricallyWithUndo, NULL, },
	{ { DEFACCEL, "Xenakios/SWS: Implode items to takes and pan symmetrically" }, "XENAKIOS_IMPLODEITEMSPANSYMMETRICALLY", DoImplodeTakesSetPlaySetSymPans, NULL, },

	{ { DEFACCEL, NULL }, NULL, NULL, SWS_SEPARATOR, },
	{ { DEFACCEL, "Xenakios/SWS: Split items at transients" }, "XENAKIOS_SPLIT_ITEMSATRANSIENTS", DoSplitItemsAtTransients, NULL, },
	{ { DEFACCEL, "Xenakios/SWS: Apply track FX to items and reset volume" }, "XENAKIOS_APPLYTRACKFXSTEREORESETVOL", DoApplyTrackFXStereoAndResetVol,	"Apply track FX to items and reset volume", },
	{ { DEFACCEL, "Xenakios/SWS: Apply track FX to items (mono) and reset volume" }, "XENAKIOS_APPLYTRACKFXMONORESETVOL", DoApplyTrackFXMonoAndResetVol,	"Apply track FX to items (mono) and reset volume", },
	{ { DEFACCEL, "Xenakios/SWS: Move cursor to next transient minus default fade time" }, "XENAKIOS_MOVECURNEXT_TRANSMINUSFADE", DoMoveCurNextTransMinusFade, NULL, },
	{ { DEFACCEL, "Xenakios/SWS: Move cursor to previous transient minus default fade time" }, "XENAKIOS_MOVECURPREV_TRANSMINUSFADE", DoMoveCurPrevTransMinusFade, NULL, },
	{ { DEFACCEL, "Xenakios/SWS: Process item with Rubberband..." }, "XENAKIOS_PROCESSRUBBERBAND", DoShowRubberbandDlg, NULL, },
	
	{ {}, SWS_ENDSUBMENU, },
	{ { DEFACCEL, NULL }, NULL, NULL, SWS_SEPARATOR, },
	{ { { 0, 0, 3 }, NULL }, SWS_STARTSUBMENU, NULL, "Track/Mixer/Envelopes", },
	{ { DEFACCEL, "Xenakios/SWS: Reset volume and pan of selected track(s)" }, "XENAKIOS_RESETTRACKVOLANDPAN1", DoResetTracksVolPan,	"Reset volume and pan of selected track(s)", },
	{ { DEFACCEL, "Xenakios/SWS: Set volume of selected track(s) to 0.0dB" }, "XENAKIOS_RESETTRACKVOL1", DoSetTrackVolumeToZero,	"Set volume of selected track(s) to 0.0dB", },
	
	{ { DEFACCEL, "Xenakios/SWS: Pan selected tracks symmetrically, left to right" }, "XENAKIOS_SYMMETRICAL_CHANPANSLTOR", DoSetSymmetricalpansL2R,	"Pan selected tracks symmetrically, left to right", },
	{ { DEFACCEL, "Xenakios/SWS: Pan selected tracks symmetrically, right to left" }, "XENAKIOS_SYMMETRICAL_CHANPANSRTOL", DoSetSymmetricalpansR2L,	"Pan selected tracks symmetrically, right to left", },
	
	{ { DEFACCEL, "Xenakios/SWS: Pan selected tracks randomly" }, "XENAKIOS_PANTRACKSRANDOM", DoPanTracksRandom,	"Pan selected tracks randomly", },
	{ { DEFACCEL, "Xenakios/SWS: Pan selected tracks to center" }, "XENAKIOS_PANTRACKSCENTER", DoPanTracksCenter,	"Pan selected tracks to center", },
	{ { DEFACCEL, "Xenakios/SWS: Pan selected tracks to left" }, "XENAKIOS_PANTRACKSLEFT", DoPanTracksLeft,	"Pan selected tracks to left", },
	{ { DEFACCEL, "Xenakios/SWS: Pan selected tracks to right" }, "XENAKIOS_PANTRACKSRIGHT", DoPanTracksRight,	"Pan selected tracks to right", },
	
	{ { DEFACCEL, "Xenakios/SWS: Toggle selected tracks visible in mixer" }, "XENAKIOS_TOGTRAXVISMIXER", DoToggleTraxVisMixer,	"Toggle selected tracks visible in mixer", },
	{ { DEFACCEL, "Xenakios/SWS: Set selected tracks pan law to default" }, "XENAKIOS_SELTRAXPANLAWDEF", DoTraxPanLawDefault,	"Set selected tracks pan law to default", },
	{ { DEFACCEL, "Xenakios/SWS: Set selected tracks pan law to 0.0dB" }, "XENAKIOS_SELTRAXPANLAWZERO", DoTraxPanLawZero,	"Set selected tracks pan law to 0.0dB", },
	{ { DEFACCEL, "Xenakios/SWS: Set selected tracks record armed" }, "XENAKIOS_SELTRAX_RECARMED", DoTraxRecArmed,	"Set selected tracks record armed", },
	{ { DEFACCEL, "Xenakios/SWS: Set selected tracks record unarmed" }, "XENAKIOS_SELTRAX_RECUNARMED", DoTraxRecUnArmed,	"Set selected tracks record unarmed", },
	{ { DEFACCEL, "Xenakios/SWS: Select next track(s)" }, "XENAKIOS_SELNEXTTRACK", DoSelectNextTrack,	"Select next track(s)", },
	{ { DEFACCEL, "Xenakios/SWS: Select previous track(s)" }, "XENAKIOS_SELPREVTRACK", DoSelectPreviousTrack,	"Select previous track(s)", },
	{ { DEFACCEL, "Xenakios/SWS: Select next track(s), keeping current selection" }, "XENAKIOS_SELNEXTTRACKKEEP", DoSelectNextTrackKeepCur,	"Select next track(s), keeping current selection", },
	{ { DEFACCEL, "Xenakios/SWS: Select previous track(s), keeping current selection" }, "XENAKIOS_SELPREVTRACKKEEP", DoSelectPrevTrackKeepCur,	"Select previous track(s), keeping current selection", },
	{ { DEFACCEL, "Xenakios/SWS: Bypass FX of selected tracks" }, "XENAKIOS_BYPASSFXOFSELTRAX", DoBypassFXofSelTrax,	"Bypass FX of selected tracks", },
	{ { DEFACCEL, "Xenakios/SWS: Un-bypass FX of selected tracks" }, "XENAKIOS_UNBYPASSFXOFSELTRAX", DoUnBypassFXofSelTrax,	"Un-bypass FX of selected tracks", },
	{ { DEFACCEL, "Xenakios/SWS: Set selected track(s) height(s) to A" }, "XENAKIOS_SELTRAXHEIGHTA", DoSelTraxHeightA,	"Set selected track(s) height(s) to A", },
	{ { DEFACCEL, "Xenakios/SWS: Set selected track(s) height(s) to B" }, "XENAKIOS_SELTRAXHEIGHTB", DoSelTraxHeightB,	"Set selected track(s) height(s) to B", },
	{ { DEFACCEL, "Xenakios/SWS: Store selected track(s) heights" }, "XENAKIOS_STORETRACKHEIGHTS", DoStoreSelTraxHeights,	"Store selected track(s) heights", },
	{ { DEFACCEL, "Xenakios/SWS: Recall selected track(s) heights" }, "XENAKIOS_RECALLTRACKHEIGHTS", DoRecallSelectedTrackHeights,	"Recall selected track(s) heights", },
	{ { DEFACCEL, "Xenakios/SWS: Select tracks with no items" }, "XENAKIOS_SELTRAXNOITEMS", DoSelectTracksWithNoItems,	"Select tracks with no items", },
	{ { DEFACCEL, "Xenakios/SWS: Select tracks with \"BUSS\" in name" }, "XENAKIOS_SELTRAXWITHBUSS", DoSelectTracksContainingBuss,	"Select tracks with \"BUSS\" in name", },
	{ { DEFACCEL, "Xenakios/SWS: Unselect tracks with \"BUSS\" in name" }, "XENAKIOS_UNSELTRAXWITHBUSS", DoUnSelectTracksContainingBuss,	"Unselect tracks with \"BUSS\" in name", },
	{ { DEFACCEL, "Xenakios/SWS: Select last track of folder" }, "XENAKIOS_SELLASTTRACKOFFOLDER", DoSelectLastTrackOfFolder,	"Select last track of folder", },
	
	{ { DEFACCEL, "Xenakios/SWS: Dismantle selected folder" }, "XENAKIOS_SELTRACKTONOTFOLDER", DoSetSelectedTrackNormal,	"Dismantle selected folder", },
	
	{ { DEFACCEL, "Xenakios/SWS: Set selected tracks as folder" }, "XENAKIOS_SELTRACKSASFOLDER", DoSetSelectedTracksAsFolder,	"Set selected tracks as folder", },
	{ { DEFACCEL, "Xenakios/SWS: Toggle visibility of selected folder parent's children in mixer" }, "XENAKIOS_BLEHFOLDDUMP", DoFolderDepthDump,	"Toggle visibility of selected folder parent's children in mixer", },
	
	{ { DEFACCEL, "Xenakios/SWS: Rename selected track(s)..." }, "XENAKIOS_RENAMETRAXDLG", DoRenameTracksDlg,	"Rename selected track(s)...", },
	{ { DEFACCEL, "Xenakios/SWS: Minimize selected tracks send panel height in mixer" }, "XENAKIOS_MINIZMIXSENDHEIGHT", DoMinMixSendPanelH, NULL, },
	{ { DEFACCEL, "Xenakios/SWS: Minimize selected tracks send & fx panel height in mixer" }, "XENAKIOS_MINIZMIXSENDFXHEIGHT", DoMinMixSendAndFxPanelH, NULL, },
	{ { DEFACCEL, "Xenakios/SWS: Maximize selected tracks fx panel height in mixer" }, "XENAKIOS_MAXMIXFXPANHEIGHT", DoMaxMixFxPanHeight, NULL, },
	{ {}, SWS_ENDSUBMENU, },
	{ { DEFACCEL, NULL }, NULL, NULL, SWS_SEPARATOR, },
	{ { DEFACCEL, NULL }, SWS_STARTSUBMENU, NULL, "Misc/Experimental", },
	{ { DEFACCEL, "Xenakios/SWS: Save project markers as text..." }, "XENAKIOS_SAVE_MARKERS_AS_TEXT", DoSaveMarkersAsTextFile,	"Save project markers as text...", },
	{ { DEFACCEL, "Xenakios/SWS: Launch external tool 1" }, "XENAKIOS_LAUNCHEXTTOOL", DoLaunchExtTool,	"Launch external tool 1", 1 },
	{ { DEFACCEL, "Xenakios/SWS: Launch external tool 2" }, "XENAKIOS_LAUNCHEXTTOOL2", DoLaunchExtTool,	"Launch external tool 2", 2 },
	{ { DEFACCEL, "Xenakios/SWS: Jump edit cursor by random amount (exp distribution)" }, "XENAKIOS_JUMPEDITCURSOR_RAND_AMNT", DoJumpEditCursorByRandomAmount,	"Jump edit cursor by random amount (exp distribution)", },
	{ { DEFACCEL, "Xenakios/SWS: Loop and play selected items" }, "XENAKIOS_LOOPANDPLAYSELITEMS", DoLoopAndPlaySelectedItems,	"Loop and play selected items", },
	{ { DEFACCEL, "Xenakios/SWS: Play selected items once" }, "XENAKIOS_TIMERTEST1", DoPlayItemsOnce,	"Play selected items once", },
	{ { DEFACCEL, "Xenakios/SWS: Toggle selected items selected randomly" }, "XENAKIOS_RANDOM_ITEM_SELTOGGLE", DoToggleSelectedItemsRndDlg,	"Toggle selected items selected randomly", },
	{ { DEFACCEL, "Xenakios/SWS: Display item peak gain(s)" }, "XENAKIOS_FINDITEMAUDIOPEAKS", DoAnalyzeAndShowPeakInItemMedia,	"Display item peak gain(s)", },
	{ { DEFACCEL, "Xenakios/SWS: Process item with csound phase vocoder" }, "XENAKIOS_CSOUNDPVOC", DoShowPVocDlg,	"Process item with Csound phase vocoder", },
	{ { DEFACCEL, "Xenakios/SWS: Render item to new take with tail" }, "XENAKIOS_RENDERITEMNEWTAKEWITHTAIL", DoRenderItemsWithTail,	"Render item to new take with tail", },
	{ { DEFACCEL, "Xenakios/SWS: Open associated REAPER project of item" }, "XENAKIOS_OPENASSOCIATED_RPP", DoOpenAssociatedRPP,	"Open associated REAPER project of item", },
	{ { DEFACCEL, "Xenakios/SWS: Take mixer..." }, "XENAKIOS_SHOWTAKEMIXERDLG", DoShowTakeMixerDlg,	"Take mixer...", },
	{ { DEFACCEL, "Xenakios/SWS: Insert random points to selected envelope..." }, "XENAKIOS_CLIPBOARD_TEST1", DoInsertRandomEnvelopePoints,	"Insert random points to selected envelope...", },
	{ { DEFACCEL, "Xenakios/SWS: Insert media file from clipboard" }, "XENAKIOS_INSERTMEDIAFROMCLIPBOARD", DoInsertMediaFromClipBoard,	"Insert media file from clipboard", },
	
	{ { DEFACCEL, "Xenakios/SWS: Erase from item (time based)" }, "XENAKIOS_HOLDKEYTEST1", DoHoldKeyTest1,	"Erase from item (time based)", },
	{ { DEFACCEL, "Xenakios/SWS: Erase from item (beat based)" }, "XENAKIOS_HOLDKEYTEST2", DoHoldKeyTest2,	"Erase from item (beat based)", },
	{ { DEFACCEL, "Xenakios/SWS: Search takes..." }, "XENAKIOS_SEARCH_TAKES", DoSearchTakesDLG,	"Search takes...", },
	{ { DEFACCEL, "Xenakios/SWS: Move cursor right 10 pixels" }, "XENAKIOS_MOVECUR10PIX_RIGHT", DoMoveCursor10pixRight,	"Move cursor right 12 pixels", },
	{ { DEFACCEL, "Xenakios/SWS: Move cursor left 10 pixels" }, "XENAKIOS_MOVECUR10PIX_LEFT", DoMoveCursor10pixLeft,	"Move cursor left 12 pixels", },
	{ { DEFACCEL, "Xenakios/SWS: Move cursor left 10 pixels, creating time selection" }, "XENAKIOS_MOVECUR10PIX_LEFTCTS", DoMoveCursor10pixLeftCreateSel,	"Move cursor left 12 pixels, creating time selection", },
	{ { DEFACCEL, "Xenakios/SWS: Move cursor right 10 pixels, creating time selection" }, "XENAKIOS_MOVECUR10PIX_RIGHTCTS", DoMoveCursor10pixRightCreateSel,	"Move cursor right 12 pixels, creating time selection", },
	{ { DEFACCEL, "Xenakios/SWS: Preview selected media item" }, "XENAKIOS_ITEMASPCM1", DoItemAsPcmSource,	"Preview selected media item", },
	{ { DEFACCEL, "Xenakios/SWS: Move cursor right configured pixels" }, "XENAKIOS_MOVECURRIGHTCONF", DoMoveCurConfPixRight,	"Move cursor right configured pixels", },
	{ { DEFACCEL, "Xenakios/SWS: Move cursor left configured pixels" }, "XENAKIOS_MOVECURRLEFTCONF", DoMoveCurConfPixLeft,	"Move cursor left configured pixels", },
	{ { DEFACCEL, "Xenakios/SWS: Move cursor right configured pixels, creating time selection" }, "XENAKIOS_MOVECURRIGHTCONFCTS", DoMoveCurConfPixRightCts,	"Move cursor right configured pixels,, creating time selection", },
	{ { DEFACCEL, "Xenakios/SWS: Move cursor left configured pixels, creating time selection" }, "XENAKIOS_MOVECURRLEFTCONFCTS", DoMoveCurConfPixLeftCts,	"Move cursor left configured pixels,, creating time selection", },
	{ { DEFACCEL, "Xenakios/SWS: Remap item positions..." }, "XENAKIOS_REMAPITEM_POSITIONS", DoItemPosRemapDlg,	"Remap item positions...", },
	{ { DEFACCEL, "Xenakios/SWS: Move cursor left configured seconds" }, "XENAKIOS_MOVECURRLEFTCONFSECS", DoMoveCurConfSecsLeft,	"Move cursor left configured seconds", },
	{ { DEFACCEL, "Xenakios/SWS: Move cursor right configured seconds" }, "XENAKIOS_MOVECURRRIGHTCONFSECS", DoMoveCurConfSecsRight,	"Move cursor right configured seconds", },
	{ { DEFACCEL, "Xenakios/SWS: Store edit cursor position" }, "XENAKIOS_DOSTORECURPOS", DoStoreEditCursorPosition,	"Store edit cursor position", },
	{ { DEFACCEL, "Xenakios/SWS: Recall edit cursor position" }, "XENAKIOS_DORECALLCURPOS", DoRecallEditCursorPosition,	"Recall edit cursor position", },
	{ { DEFACCEL, "Xenakios/SWS: Delete selected item and source media (immediately!)" }, "XENAKIOS_DELETEITEMANDTAKEMEDIA", DoDeleteItemAndMedia,	"Delete selected item and active take's source media (immediately!)", },
	{ { DEFACCEL, "Xenakios/SWS: Delete selected item and send active take's source media to recycle bin"  }, "XENAKIOS_DELETEITEMANDTAKEMEDIARBIN", DoDelSelItemAndSendActiveTakeMediaToRecycler,	"Delete selected item and send active take's source media to recycle bin", },
	{ { DEFACCEL, "Xenakios/SWS: Delete active take of item and take source media (immediately!)"  }, "XENAKIOS_DELETETAKEANDSOURCEMEDIA", DoNukeTakeAndSourceMedia,	"Delete active take of item and take source media (immediately!)", },
	{ { DEFACCEL, "Xenakios/SWS: Delete active take of item and send source media to recycle bin"  }, "XENAKIOS_DELETETAKEANDRECYCLESOURCEMEDIA", DoDeleteActiveTakeAndRecycleSourceMedia,	"Delete active take of item and send source media to recycle bin", },
	
	{ { DEFACCEL, "Xenakios/SWS: Set next fade in shape for items" }, "XENAKIOS_NEXTFADEINSHAPE", DoSetNextFadeInShape,	"Set next fade in shape for items", },
	{ { DEFACCEL, "Xenakios/SWS: Set previous fade in shape for items" }, "XENAKIOS_PREVFADEINSHAPE", DoSetPrevFadeInShape,	"Set previous fade in shape for items", },
	{ { DEFACCEL, "Xenakios/SWS: Set next fade out shape for items" }, "XENAKIOS_NEXTFADEOUTSHAPE", DoSetNextFadeOutShape,	"Set next fade out shape for items", },
	{ { DEFACCEL, "Xenakios/SWS: Set previous fade out shape for items" }, "XENAKIOS_PREVFADEOUTSHAPE", DoSetPrevFadeOutShape,	"Set previous fade out shape for items", },
	{ { DEFACCEL, "Xenakios/SWS: Set item fades to autofade lengths" }, "XENAKIOS_AUTOFADETOFADE", DoSetFadeToAutofade,	"Set item fades to autofade lengths", },
	{ { DEFACCEL, "Xenakios/SWS: Set item playrate based on item pitch (and reset pitch)" }, "XENAKIOS_ITEMPITCH2PLAYRATE", DoItemPitch2Playrate,	"Set item playrate based on item pitch", },
	{ { DEFACCEL, "Xenakios/SWS: Set item pitch based on item playrate" }, "XENAKIOS_ITEMPLAYRATE2PITCH", DoItemPlayrate2Pitch,	"Set item pitch based on item playrate", },
	{ { DEFACCEL, "Xenakios/SWS: Project media..." }, "XENAKIOS_MANAGEMEDIA", DoShowProjectMediaDlg,	"Show project media...", },
	{ { DEFACCEL, "Xenakios/SWS: Find missing media for project's takes" }, "XENAKIOS_FINDMISSINGMEDIA", DoFindMissingMedia,	"Find missing media for project's takes",    true },
	{ { DEFACCEL, "Xenakios/SWS: Save current contents of actions list to file" }, "XENAKIOS_DODUMPACTIONS", DoDumpActionsWindow,	"Save current contents of actions list to file", },
	{ { DEFACCEL, "Xenakios/SWS: Show/hide floating item/track info" }, "XENAKIOS_SHOWHIDE_ITEMINSPECTOR", DoTglFltItemInspector,	"Show/hide floating item/track info",    true },
	{ { DEFACCEL, "Xenakios/SWS: Spread selected items over 4 tracks" }, "XENAKIOS_SPREADITEMSOVER4TRAX", DoSpreadSelItemsOver4Tracks,	"Spread selected items over 4 tracks",    true },
	{ { DEFACCEL, "Xenakios/SWS: Spread selected items over tracks..." }, "XENAKIOS_SPREADITEMSOVERTRAX", DoShowSpreadItemsDlg,	"Spread selected items over tracks...",    true },
	{ { DEFACCEL, "Xenakios/SWS: Explode selected items to new tracks (keeping positions)" }, "XENAK_SPRDITOVERNEWTX", DoSpeadSelItemsOverNewTx,	"Explode selected items to new tracks (keeping positions)", },
	
	{ { DEFACCEL, "Xenakios/SWS: Load track template 01" }, "XENAKIOS_LOADTRACKTEMPLATE01", DoOpenTrackTemplate, NULL, 1 },
	{ { DEFACCEL, "Xenakios/SWS: Load track template 02" }, "XENAKIOS_LOADTRACKTEMPLATE02", DoOpenTrackTemplate, NULL, 2 },
	{ { DEFACCEL, "Xenakios/SWS: Load track template 03" }, "XENAKIOS_LOADTRACKTEMPLATE03", DoOpenTrackTemplate, NULL, 3 },
	{ { DEFACCEL, "Xenakios/SWS: Load track template 04" }, "XENAKIOS_LOADTRACKTEMPLATE04", DoOpenTrackTemplate, NULL, 4 },
	{ { DEFACCEL, "Xenakios/SWS: Load track template 05" }, "XENAKIOS_LOADTRACKTEMPLATE05", DoOpenTrackTemplate, NULL, 5 },
	{ { DEFACCEL, "Xenakios/SWS: Load track template 06" }, "XENAKIOS_LOADTRACKTEMPLATE06", DoOpenTrackTemplate, NULL, 6 },
	{ { DEFACCEL, "Xenakios/SWS: Load track template 07" }, "XENAKIOS_LOADTRACKTEMPLATE07", DoOpenTrackTemplate, NULL, 7 },
	{ { DEFACCEL, "Xenakios/SWS: Load track template 08" }, "XENAKIOS_LOADTRACKTEMPLATE08", DoOpenTrackTemplate, NULL, 8 },
	{ { DEFACCEL, "Xenakios/SWS: Load track template 09" }, "XENAKIOS_LOADTRACKTEMPLATE09", DoOpenTrackTemplate, NULL, 9 },
	{ { DEFACCEL, "Xenakios/SWS: Load track template 10" }, "XENAKIOS_LOADTRACKTEMPLATE10", DoOpenTrackTemplate, NULL, 10 },
	{ { DEFACCEL, "Xenakios/SWS: Open REAPER project in item BWAV info (autosearch for RPP if necessary)" }, "XENAKIOS_OPENRPPINBWAVAS", DoOpenRPPofBWAVdesc,	"Open REAPER project in item BWAV info", },
	{ { DEFACCEL, "Xenakios/SWS: Select first of selected tracks" }, "XENAKIOS_SELFIRSTOFSELTRAX", DoSelectFirstOfSelectedTracks, NULL, },
	{ { DEFACCEL, "Xenakios/SWS: Select last of selected tracks" }, "XENAKIOS_SELLASTOFSELTRAX", DoSelectLastOfSelectedTracks, NULL, },
	{ { DEFACCEL, "Xenakios/SWS: Insert new track at the top of track list" }, "XENAKIOS_INSNEWTRACKTOP", DoInsertNewTrackAtTop, NULL, },
	{ { DEFACCEL, "Xenakios/SWS: Give track(s) default label" }, "XENAKIOS_TRAXDEFAULTLABEL", DoLabelTraxDefault, NULL, },
	{ { DEFACCEL, "Xenakios/SWS: Insert prefix to track label(s)" }, "XENAKIOS_INSTRACKLABPREF", DoTraxLabelPrefix, NULL, },
	{ { DEFACCEL, "Xenakios/SWS: Insert suffix to track label(s)" }, "XENAKIOS_INSTRACKLABSUFF", DoTraxLabelSuffix, NULL, },
	{ { DEFACCEL, "Xenakios/SWS: Toggle envelope editing mode" }, "XENAKIOS_TOGGLE_ENVEDITMODE", DoToggleEnvEditMode, NULL, },
	{ { DEFACCEL, "Xenakios/SWS: Insert random file, randomize length" }, "XENAKIOS_INSRNDFILE_RNDLEN", DoInsRndFileRndLen,	"Insert random file, randomize length", },
	{ { DEFACCEL, "Xenakios/SWS: Insert random file at time selection" }, "XENAKIOS_INSRNDFILE_ATTIMESEL", DoInsRndFileAtTimeSel,	"Insert random file at time selection", },
	{ { DEFACCEL, "Xenakios/SWS: Insert random file, randomize start offset" }, "XENAK_INSRNDFILE_RNDOFFSET", DoInsRndFileRndOffset,	"Insert random file, randomize start offset", },
	{ { DEFACCEL, "Xenakios/SWS: Insert random file at time selection, randomize offset" }, "XENAK_INSRNDFILE_TIMESELRNDOFFSET", DoInsRndFileRndOffsetAtTimeSel,	"Insert random file at time selection, randomize offset", },
	{ { DEFACCEL, "Xenakios/SWS: Remove time selection (leave loop selection)" }, "XENAK_REMOVETIMESEL", DoRemoveTimeSelectionLeaveLoop, NULL, },
	{ { DEFACCEL, "Xenakios/SWS: Toggle selected tracks height A/B" }, "XENAK_TOGGLETRACKHEIAB", DoToggleTrackHeightAB, NULL, },
	{ { DEFACCEL, "Xenakios/SWS: Implode selected items in-place" }, "XENAK_MATRIXITEMIMPLODE", DoMatrixItemImplode,	"Implode selected items in-place", },
	{ { DEFACCEL, "Xenakios/SWS: Toggle ripple edit (one track) on/off" }, "XENAK_TOGGLERIPPLE1TRACK", DoToggleRippleOneTrack,	"Toggle ripple edit (one track) on/off", },
	{ { DEFACCEL, "Xenakios/SWS: Open (audio) take in external editor 3" }, "XENAKIOS_OPAUEXTED1", DoOpenInExtEditor1, NULL, },
	{ { DEFACCEL, "Xenakios/SWS: Open (audio) take in external editor 4" }, "XENAKIOS_OPAUEXTED2", DoOpenInExtEditor2, NULL, },
	{ { DEFACCEL, "Xenakios/SWS: Item property interpolator..." }, "XENAKIOS_ITEMPROPINTERPDLG", DoShowItemInterpDLG,	"Item property interpolator...", },
	{ { DEFACCEL, "Xenakios/SWS: Nudge section loop length longer" }, "XENAKIOS_NUDGSECTLOOPLENPOS", DoNudgeSectionLoopLenPlus, NULL, },
	{ { DEFACCEL, "Xenakios/SWS: Nudge section loop length shorter" }, "XENAKIOS_NUDGSECTLOOPLENNEG", DoNudgeSectionLoopLenMinus, NULL, },
	{ { DEFACCEL, "Xenakios/SWS: Nudge section loop start later" }, "XENAKIOS_NUDGSECTLOOPSTARTPOS", DoNudgeSectionLoopStartPlus, NULL, },
	{ { DEFACCEL, "Xenakios/SWS: Nudge section loop start earlier" }, "XENAKIOS_NUDGSECTLOOPSTARTNEG", DoNudgeSectionLoopStartMinus, NULL, },
	{ { DEFACCEL, "Xenakios/SWS: Nudge section loop overlap longer" }, "XENAKIOS_NUDGSECTLOOPOLPOS", DoNudgeSectionLoopOlapPlus, NULL, },
	{ { DEFACCEL, "Xenakios/SWS: Nudge section loop overlap shorter" }, "XENAKIOS_NUDGSECTLOOPOLNEG", DoNudgeSectionLoopOlapMinus, NULL, },
	{ { DEFACCEL, "Xenakios/SWS: Scroll track view down (page)" }, "XENAKIOS_TVPAGEDOWN", DoScrollTVPageDown, NULL, },
	{ { DEFACCEL, "Xenakios/SWS: Scroll track view up (page)" }, "XENAKIOS_TVPAGEUP", DoScrollTVPageUp, NULL, },
	{ { DEFACCEL, "Xenakios/SWS: Scroll track view to home" }, "XENAKIOS_TVPAGEHOME", DoScrollTVHome, NULL, },
	{ { DEFACCEL, "Xenakios/SWS: Scroll track view to end" }, "XENAKIOS_TVPAGEEND", DoScrollTVEnd, NULL, },
	{ { DEFACCEL, "Xenakios/SWS: Nudge item contents 1 sample left" }, "XENAKIOS_NUDGEITEMCONT1SAMPLEFT", DoSlipItemContentsOneSampleLeft, NULL, },
	{ { DEFACCEL, "Xenakios/SWS: Nudge item contents 1 sample right" }, "XENAKIOS_NUDGEITEMCONT1SAMPLRIGHT", DoSlipItemContentsOneSampleRight, NULL, },
	{ { DEFACCEL, "Xenakios/SWS: Set render speed to realtime" }, "XENAKIOS_SETRENDERSPEEDRT", DoSetRenderSpeedToRealtime2, NULL, },
	{ { DEFACCEL, "Xenakios/SWS: Set render speed to not limited" }, "XENAKIOS_SETRENDERSPEEDNL", DoSetRenderSpeedToNonLim, NULL, },
	{ { DEFACCEL, "Xenakios/SWS: Store render speed" }, "XENAKIOS_STORERENDERSPEED", DoStoreRenderSpeed, NULL, },
	{ { DEFACCEL, "Xenakios/SWS: Recall render speed" }, "XENAKIOS_RECALLRENDERSPEED", DoRecallRenderSpeed, NULL, },
	{ { DEFACCEL, "Xenakios/SWS: Select items under edit cursor on selected tracks" }, "XENAKIOS_SELITEMSUNDEDCURSELTX", DoSelectItemUnderEditCursorOnSelTrack, NULL, },
	
	{ { DEFACCEL, "Xenakios/SWS: Time selection adaptive delete" }, "XENAKIOS_TSADEL", DoTimeSelAdaptDelete, NULL, },
	{ { DEFACCEL, "Xenakios/SWS: Create new tracks..." }, "XENAKIOS_CREATENEWTX", DoCreateTraxDlg, NULL, },
	{ { DEFACCEL, "Xenakios/SWS: Render receives of selected track as stems" }, "XENAKIOS_RENDERRECEIVESASSTEMS", DoRenderReceivesAsStems, NULL, },
	{ { DEFACCEL, "Xenakios/SWS: Swing item positions..." }, "XENAKIOS_SWINGITEMPOSITIONS", DoSwingItemPositions, NULL, },
	{ { DEFACCEL, "Xenakios/SWS: Switch item source file to next in folder" }, "XENAKIOS_SISFTNEXTIF", DoReplaceItemFileWithNextInFolder, NULL, },
	{ { DEFACCEL, "Xenakios/SWS: Switch item source file to previous in folder" }, "XENAKIOS_SISFTPREVIF", DoReplaceItemFileWithPrevInFolder, NULL, },
	{ { DEFACCEL, "Xenakios/SWS: Switch item source file to random in folder" }, "XENAKIOS_SISFTRANDIF", DoReplaceItemFileWithRandomInFolder, NULL, },
	{ { DEFACCEL, "Xenakios/SWS: Switch item source file to next RPP in folder" }, "XENAKIOS_SISFTNEXTRPPIF", DoReplaceItemFileWithNextRPPInFolder, NULL, },
	{ { DEFACCEL, "Xenakios/SWS: Switch item source file to previous RPP in folder" }, "XENAKIOS_SISFTPREVRPPIF", DoReplaceItemFileWithPrevRPPInFolder,	NULL, },

	{ { DEFACCEL, "Xenakios/SWS: Reverse order of selected items" }, "XENAKIOS_REVORDSELITEMS", DoReverseItemOrder, NULL, },
	{ { DEFACCEL, "Xenakios/SWS: Shuffle order of selected items" }, "XENAKIOS_SHFORDSELITEMS", DoShuffleItemOrder, NULL, },
	{ { DEFACCEL, "Xenakios/SWS: Shuffle order of selected items (2)" }, "XENAKIOS_SHFORDSELITEMS2", DoShuffleItemOrder2, NULL, },
	{ { DEFACCEL, "Xenakios/SWS: Create markers from selected items (name by take source file name)" }, "XENAKIOS_CRTMARKERSFROMITEMS1", DoCreateMarkersFromSelItems1, NULL, },
	{ { DEFACCEL, "Xenakios/SWS: Rename take source file(s)..." }, "XENAKIOS_RENMTAKESOURCEFLS", DoRenameSourceFileDialog666, NULL, },
	{ { DEFACCEL, "Xenakios/SWS: Rename take(s) and source file(s)..." }, "XENAKIOS_RENMTAKEANDSOURCE", DoRenameTakeAndSourceFileDialog, NULL, },
	{ { DEFACCEL, "Xenakios/SWS: Rename take(s)..." }, "XENAKIOS_RENMTAKE", DoRenameTakeDialog666, NULL, },
	{ { DEFACCEL, "Xenakios/SWS: Rename takes with same name..." }, "XENAKIOS_RENMTAKEALL", DoRenameTakeAllDialog666, NULL, },
	{ { DEFACCEL, "Xenakios/SWS: Save item as audio file..." }, "XENAKIOS_SAVEITEMASAUDIO1", DoSaveItemAsFile1, NULL, },
	{ { DEFACCEL, "Xenakios/SWS: Normalize selected takes to dB value..." }, "XENAKIOS_NORMALZTAKESDB", DoNormalizeSelTakesTodB, NULL, },
	{ { DEFACCEL, "Xenakios/SWS: Load project template 01" }, "XENAKIOS_LOADPROJTEMPL01", DoOpenProjectTemplate, NULL, 1 },
	{ { DEFACCEL, "Xenakios/SWS: Load project template 02" }, "XENAKIOS_LOADPROJTEMPL02", DoOpenProjectTemplate, NULL, 2 },
	{ { DEFACCEL, "Xenakios/SWS: Load project template 03" }, "XENAKIOS_LOADPROJTEMPL03", DoOpenProjectTemplate, NULL, 3 },
	{ { DEFACCEL, "Xenakios/SWS: Load project template 04" }, "XENAKIOS_LOADPROJTEMPL04", DoOpenProjectTemplate, NULL, 4 },
	{ { DEFACCEL, "Xenakios/SWS: Load project template 05" }, "XENAKIOS_LOADPROJTEMPL05", DoOpenProjectTemplate, NULL, 5 },
	{ { DEFACCEL, "Xenakios/SWS: Load project template 06" }, "XENAKIOS_LOADPROJTEMPL06", DoOpenProjectTemplate, NULL, 6 },
	{ { DEFACCEL, "Xenakios/SWS: Load project template 07" }, "XENAKIOS_LOADPROJTEMPL07", DoOpenProjectTemplate, NULL, 7 },
	{ { DEFACCEL, "Xenakios/SWS: Load project template 08" }, "XENAKIOS_LOADPROJTEMPL08", DoOpenProjectTemplate, NULL, 8 },
	{ { DEFACCEL, "Xenakios/SWS: Load project template 09" }, "XENAKIOS_LOADPROJTEMPL09", DoOpenProjectTemplate, NULL, 9 },
	{ { DEFACCEL, "Xenakios/SWS: Load project template 10" }, "XENAKIOS_LOADPROJTEMPL10", DoOpenProjectTemplate, NULL, 10 },
	{ { DEFACCEL, "Xenakios/SWS: Remove muted items" }, "XENAKIOS_REMOVMUTEDITEMS", DoDeleteMutedItems, NULL, },
	{ { DEFACCEL, "Xenakios/SWS: Nudge master volume 1dB up" }, "XENAKIOS_NUDMASVOL1DBU", DoNudgeMasterVol1dbUp, NULL, },
	{ { DEFACCEL, "Xenakios/SWS: Nudge master volume 1dB down" }, "XENAKIOS_NUDMASVOL1DBD", DoNudgeMasterVol1dbDown, NULL, },
	{ { DEFACCEL, "Xenakios/SWS: Set master volume to 0dB" }, "XENAKIOS_SETMASTVOLTO0", DoSetMasterToZeroDb, NULL, },
	{ { DEFACCEL, "Xenakios/SWS: Nudge volume of selected track(s) up" }, "XENAKIOS_NUDGSELTKVOLUP", DoNudgeSelTrackVolumeUp, NULL, },
	{ { DEFACCEL, "Xenakios/SWS: Nudge volume of selected track(s) down" }, "XENAKIOS_NUDGSELTKVOLDOWN", DoNudgeSelTrackVolumeDown, NULL, },
	{ { DEFACCEL, "Xenakios/SWS: Reset item length and media offset" }, "XENAKIOS_RESETITEMLENMEDOFFS", DoResetItemsOffsetAndLength, NULL, },
	{ { DEFACCEL, "Xenakios/SWS: Toggle reference track" }, "XENAKIOS_TOGGREFTRACK", DoToggleReferenceTrack, NULL, },
	{ { DEFACCEL, "Xenakios/SWS: Set selected track as reference track" }, "XENAKIOS_SETSELTKREFTRACK", DoSetSelTrackAsRefTrack, NULL, },
	{ { DEFACCEL, "Xenakios/SWS: Shift current envelope to right" }, "XEN_ENV_SHIFTRIGHT", DoShiftEnvelopeLater, NULL, },
	{ { DEFACCEL, "Xenakios/SWS: Shift current envelope to left" }, "XEN_ENV_SHIFTLEFT", DoShiftEnvelopeEarlier, NULL, },
	{ { DEFACCEL, "Xenakios/SWS: Toggle master track send 1 mute" }, "XEN_TOG_MAS_SEND0MUTE", DoToggleMasterSendMute, NULL, 0 },
	{ { DEFACCEL, "Xenakios/SWS: Toggle master track send 2 mute" }, "XEN_TOG_MAS_SEND1MUTE", DoToggleMasterSendMute, NULL, 1 },
	{ { DEFACCEL, "Xenakios/SWS: Toggle master track send 3 mute" }, "XEN_TOG_MAS_SEND2MUTE", DoToggleMasterSendMute, NULL, 2 },
	{ { DEFACCEL, "Xenakios/SWS: Toggle master track send 4 mute" }, "XEN_TOG_MAS_SEND3MUTE", DoToggleMasterSendMute, NULL, 3 },
	{ { DEFACCEL, "Xenakios/SWS: Toggle master track send 5 mute" }, "XEN_TOG_MAS_SEND4MUTE", DoToggleMasterSendMute, NULL, 4 },
	
	{ { DEFACCEL, "Xenakios/SWS: Set master track send 1 muted" }, "XEN_SET_MAS_SEND0MUTE", DoSetMasterSendMute, NULL, 0 },
	{ { DEFACCEL, "Xenakios/SWS: Set master track send 2 muted" }, "XEN_SET_MAS_SEND1MUTE", DoSetMasterSendMute, NULL, 1 },
	{ { DEFACCEL, "Xenakios/SWS: Set master track send 3 muted" }, "XEN_SET_MAS_SEND2MUTE", DoSetMasterSendMute, NULL, 2 },
	{ { DEFACCEL, "Xenakios/SWS: Set master track send 4 muted" }, "XEN_SET_MAS_SEND3MUTE", DoSetMasterSendMute, NULL, 3 },
	{ { DEFACCEL, "Xenakios/SWS: Set master track send 5 muted" }, "XEN_SET_MAS_SEND4MUTE", DoSetMasterSendMute, NULL, 4 },
	{ { DEFACCEL, "Xenakios/SWS: Set master track send 1 unmuted" }, "XEN_UNSET_MAS_SEND0MUTE", DoUnSetMasterSendMute, NULL, 0 },
	{ { DEFACCEL, "Xenakios/SWS: Set master track send 2 unmuted" }, "XEN_UNSET_MAS_SEND1MUTE", DoUnSetMasterSendMute, NULL, 1 },
	{ { DEFACCEL, "Xenakios/SWS: Set master track send 3 unmuted" }, "XEN_UNSET_MAS_SEND2MUTE", DoUnSetMasterSendMute, NULL, 2 },
	{ { DEFACCEL, "Xenakios/SWS: Set master track send 4 unmuted" }, "XEN_UNSET_MAS_SEND3MUTE", DoUnSetMasterSendMute, NULL, 3 },
	{ { DEFACCEL, "Xenakios/SWS: Set master track send 5 unmuted" }, "XEN_UNSET_MAS_SEND4MUTE", DoUnSetMasterSendMute, NULL, 4 },
	{ { DEFACCEL, "Xenakios/SWS: Set all master track sends muted" }, "XEN_SET_MAS_SENDALLMUTE", DoSetAllMastersSendsMuted,	NULL, },
	{ { DEFACCEL, "Xenakios/SWS: Set all master track sends unmuted" }, "XEN_SET_MAS_SENDALLUNMUTE", DoSetAllMastersSendsUnMuted, NULL, },

	{ { DEFACCEL, "Xenakios/SWS: Toggle stop playback at end of time selection" }, "XEN_PREF_STOPATENDLOOP", DoToggleSTopAtEndOfTimeSel, NULL, },
	
	{ { DEFACCEL, "Xenakios/SWS: Rename project markers with ascending numbers" }, "XEN_RENNMARKERSASCNUMBERS", DoRenameMarkersWithAscendingNumbers, NULL, },
	{ { DEFACCEL, "Xenakios/SWS: Set fades of selected items to configuration C" }, "XEN_ITEMFADESTOCONF_C", DoFadesOfSelItemsToConfC, NULL, },
	{ { DEFACCEL, "Xenakios/SWS: Set fades of selected items to configuration D" }, "XEN_ITEMFADESTOCONF_D", DoFadesOfSelItemsToConfD, NULL, },
	{ { DEFACCEL, "Xenakios/SWS: Set fades of selected items to configuration E" }, "XEN_ITEMFADESTOCONF_E", DoFadesOfSelItemsToConfE, NULL, },
	{ { DEFACCEL, "Xenakios/SWS: Set fades of selected items to configuration F" }, "XEN_ITEMFADESTOCONF_F", DoFadesOfSelItemsToConfF, NULL, },
	{ { DEFACCEL, "Xenakios/SWS: Move edit cursor 32nd note left" }, "XEN_MOVE_EDCUR32NDLEFT", DoMoveEditCursor32ndLeft, NULL, },
	{ { DEFACCEL, "Xenakios/SWS: Move edit cursor 32nd note right" }, "XEN_MOVE_EDCUR32NDRIGHT", DoMoveEditCursor32ndRight,	NULL, },
	{ { DEFACCEL, "Xenakios/SWS: Move edit cursor 64th note left" }, "XEN_MOVE_EDCUR64THLEFT", DoMoveEditCursor64thLeft, NULL, },
	{ { DEFACCEL, "Xenakios/SWS: Move edit cursor 64th note right" }, "XEN_MOVE_EDCUR64THRIGHT", DoMoveEditCursor64thRight, NULL, },
	{ {}, SWS_ENDSUBMENU, },
	{ { DEFACCEL, NULL }, NULL, NULL, SWS_SEPARATOR, },
	{ { DEFACCEL, "Xenakios/SWS: Command parameters..." }, "XENAKIOS_SHOW_COMMANDPARAMS", DoShowCommandParameters,	"Command parameters...", },
	{ { DEFACCEL, "Xenakios/SWS: Disk space calculator..." }, "XENAKIOS_DISKSPACECALC", DoShowDiskspaceCalc,	"Disk space calculator...", },
	
	{ {}, LAST_COMMAND, } // Denote end of table
};