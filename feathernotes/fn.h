/*
 * Copyright (C) Pedram Pourang (aka Tsu Jan) 2016-2022 <tsujan2000@gmail.com>
 *
 * FeatherNotes is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * FeatherNotes is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef FN_H
#define FN_H

//#include <QtGui> // too much
#include <QPointer>
#include <QListWidgetItem>
#include <QSystemTrayIcon>
#include <QMainWindow>
#include "textedit.h"
#include "domitem.h"
#include "lineedit.h"

namespace FeatherNotes {

namespace Ui {
class FN;
}

class DomModel;

class FN : public QMainWindow
{
    Q_OBJECT

public:
    explicit FN (const QStringList& message, QWidget *parent = nullptr);
    ~FN();

    void activateFNWindow (bool noDelay = false);
    void quitting();

    void writeGeometryConfig (bool withLastNodeInfo = true);
    void rememberLastOpenedFile (bool recentNumIsSet = false);
    void writeConfig();

    QString currentPath() const {
        return xmlPath_;
    }

    bool isSizeRem() const {
        return remSize_;
    }
    void remSize (bool rem) {
        remSize_ = rem;
    }

    QSize getWinSize() const {
        return winSize_;
    }
    void setWinSize (const QSize &size) {
        winSize_ = size;
    }

    QSize getStartSize() const {
        return startSize_;
    }
    void setStartSize (const QSize &size) {
        startSize_ = size;
    }

    bool isSplitterRem() const {
        return  remSplitter_;
    }
    void remSplitter (bool rem) {
        remSplitter_ = rem;
    }
    QByteArray getSpltiterState() const;

    QSize getPrefSize() const {
        return prefSize_;
    }
    void setPrefSize (const QSize &s) {
        prefSize_ = s;
    }

    bool isPositionRem() const {
        return remPosition_;
    }
    void remPosition (bool rem) {
        remPosition_ = rem;
    }

    bool hasTray() const {
        return hasTray_;
    }
    void useTray (bool use) {
        hasTray_ = use;
    }

    bool doesMinToTray() const {
        return minToTray_;
    }
    void minToTray (bool yes) {
        minToTray_ = yes;
    }

    bool hasTransparentTree() const {
        return transparentTree_;
    }
    void makeTreeTransparent (bool trans);

    bool hasSmallToolbarIcons() const {
        return smallToolbarIcons_;
    }
    void setToolBarIconSize (bool small);

    bool withoutToolbar() const {
        return noToolbar_;
    }
    bool withoutMenubar() const {
        return noMenubar_;
    }
    void showToolbar (bool show);
    void showMenubar (bool show);

    bool isWrappedByDefault() const {
        return wrapByDefault_;
    }
    void wrapByDefault (bool wrap) {
        wrapByDefault_ = wrap;
    }

    bool isIndentedByDefault() const {
        return indentByDefault_;
    }
    void indentByDefault (bool indent) {
        indentByDefault_ = indent;
    }

    bool hasAutoBracket() const {
        return autoBracket_;
    }
    void autoBracket (bool yes) {
        autoBracket_ = yes;
    }

    bool hasAutoReplace() const {
        return autoReplace_;
    }
    void autoReplace (bool yes) {
        autoReplace_ = yes;
    }

    QString getDateFormat() const {
        return dateFormat_;
    }
    void setDateFormat (const QString &format) {
        dateFormat_ = format;
    }

    int getAutoSave() const {
        return autoSave_;
    }
    void setAutoSave (int interval) {
        autoSave_ = interval;
    }

    void updateCustomizableShortcuts();

    QHash<QString, QString> customShortcutActions() const {
        return customActions_;
    }
    void setActionShortcut (const QString &action, const QString &shortcut) {
        customActions_.insert (action, shortcut);
    }
    void removeShortcut (const QString &action) {
        customActions_.remove (action);
        uncustomizedActions_ << action;
    }

    QHash<QAction*, QKeySequence> defaultShortcuts() const {
        return defaultShortcuts_;
    }

    QStringList reservedShortcuts() const {
        return reservedShortcuts_;
    }

    bool openLastFile() const {
        return openLastFile_;
    }
    void setOpenLastFile (bool openLastFile) {
        openLastFile_ = openLastFile;
    }

    int getRecentFilesNumber();
    void setRecentFilesNumber (int recentNum) {
        recentNum_ = recentNum;
    }
    bool getOpenReccentSeparately() const {
        return openReccentSeparately_;
    }
    void setOpenReccentSeparately (bool separately) {
        openReccentSeparately_ = separately;
    }

    void setCollapsedStates();
    bool getRememberExpanded() const {
        return rememberExpanded_;
    }
    void setRememberExpanded (bool remember) {
        rememberExpanded_ = remember;
    }

    bool getSaveOnExit() const {
        return saveOnExit_;
    }
    void setSaveOnExit (bool saveOnExit) {
        saveOnExit_ = saveOnExit;
    }

#ifdef HAS_HUNSPELL
    QString getDictPath() const {
        return dictPath_;
    }
    void setDictPath (const QString& dictPath) {
        dictPath_ = dictPath;
    }
#endif

private slots:
    bool close();
    void showContextMenu (const QPoint &p);
    void indexExpanded (const QModelIndex &index);
    void indexCollapsed (const QModelIndex &index);
    void fullScreening();
    void rehighlight (TextEdit *textEdit);
    void zoomingIn();
    void zoomingOut();
    void unZooming();
    void newNote();
    void openFile();
    void openFNDoc (const QString &filePath);
    void autoSaving();
    bool saveFile();
    void undoing();
    void redoing();
    void cutText();
    void copyText();
    void pasteText();
    void pasteHTML();
    void deleteText();
    void selectAllText();
    void insertDate();
    void setCursorInsideSelection (bool sel);
    void txtContextMenu (const QPoint &p);
    void copyLink();
    void selChanged (const QItemSelection &selected, const QItemSelection &deselected);
    void setSaveEnabled (bool modified);
    void setUndoEnabled (bool enabled);
    void setRedoEnabled (bool enabled);
    void formatChanged (const QTextCharFormat &format);
    void alignmentChanged();
    void directionChanged();
    void makeBold();
    void makeItalic();
    void makeUnderlined();
    void makeStriked();
    void makeSuperscript();
    void makeSubscript();
    void textColor();
    void bgColor();
    void clearFormat();
    void textAlign (QAction *a);
    void textDirection (QAction *a);
    void makeHeader();
    void insertLink();
    void embedImage();
    void imageEmbed (const QString &path);
    void setImagePath (bool);
    void scaleImage();
    void saveImage();
    void addTable();
    void tableMergeCells();
    void tablePrependRow();
    void tableAppendRow();
    void tablePrependCol();
    void tableAppendCol();
    void tableDeleteRow();
    void tableDeleteCol();
    void expandAll();
    void collapseAll();
    void newNode();
    void deleteNode();
    void moveUpNode();
    void moveLeftNode();
    void moveDownNode();
    void moveRightNode();
    void handleTags();
    void renameNode();
    void nodeIcon();
    void toggleStatusBar();
    void textFontDialog();
    void nodeFontDialog();
    void docColorDialog();
    void toggleWrapping();
    void toggleIndent();
    void prefDialog();
    void nodeChanged (const QModelIndex&, const QModelIndex&);
    void treeChanged();
    void showHideSearch();
    void clearTagsList (int);
    void selectRow (QListWidgetItem *item);
    void chooseRow (int row);
    void find();
    void hlight() const;
    void scrolled (int) const;
    void setSearchFlags();
    void allBtn (bool checked);
    void tagsAndNamesBtn (bool checked);
    void replaceDock();
    void closeReplaceDock (bool visible);
    void resizeDock (bool topLevel);
    void replace();
    void replaceAll();
    void showAndFocus();
    void trayActivated (QSystemTrayIcon::ActivationReason r);
    void activateTray();
    void exportHTML();
    void setHTMLName (bool checked);
    void setHTMLPath (bool);
    void setPswd();
    void reallySetPswrd();
    void checkPswrd();
    void aboutDialog();
    void showHelpDialog();
    void updateRecentAction();
    void updateRecenMenu();
    void openRecentFile();
    void clearRecentMenu();
    void addSketch();
    void toggleTreeView();

    void toggleTextView();

    void addLine();

    void launchDeviceDialog();

#ifdef HAS_HUNSPELL
    void checkSpelling();
#endif

private:
    void enableActions (bool enable);
    void fileOpen (const QString &filePath, bool startup = false, bool startWithLastFile = false);
    bool fileSave (const QString &filePath);
    void closeEvent (QCloseEvent *event);
    void resizeEvent (QResizeEvent *event);
    void changeEvent (QEvent *event);
    void showEvent (QShowEvent *event);
    void showDoc (QDomDocument &doc, int node = -1);
    void setTitle (const QString &fname);
    void showWarningBar (const QString &message, int timeout);
    void notSavedOrOpened (bool notSaved);
    void setNodesTexts();
    bool unSaved (bool modified);
    void setEditorStyleSheet (TextEdit *textEdit);
    TextEdit *newWidget();
    void mergeFormatOnWordOrSelection (const QTextCharFormat &format);
    void setNewFont (DomItem *item, const QTextCharFormat &fmt);
    QTextCursor finding (const QString &str,
                         const QTextCursor &start,
                         QTextDocument::FindFlags flags) const;
    void findInTags();
    void reallySetSearchFlags (bool h);
    void findInNames();
    bool isImageSelected();
    void readShortcuts();
    QString validatedShortcut (const QVariant v, QStringList &added, bool *isValid);
    void readAndApplyConfig (bool startup = true);
    QString nodeAddress (QModelIndex index);
    bool isPswrdCorrect (const QString &file);
    void dragMoveEvent (QDragMoveEvent *event);
    void dragEnterEvent (QDragEnterEvent *event);
    void dropEvent (QDropEvent *event);
    bool event (QEvent *event);
    void noteModified();
    void docProp();
    bool hasBlockingDialog();
    void closeWarningBar();
    void closeNonModalDialogs();
    void closeWinDialogs();
    void updateNodeActions();
    void toggleToolbarView();
    void rightMouseClick();
    QItemSelection savedItemSelected;
    QItemSelection savedItemDeselected;
    void collapseTreeItem();

#ifdef HAS_HUNSPELL
    void spellingCheckingMsg (const QString &msg, bool hasInfo);
#endif

    Ui::FN *ui;
    bool closed_; // Whether FN::closeEvent() is called before quitting.
    //QWidget *dummyWidget; // For hiding the main window while keeping all its state info.
    QSystemTrayIcon *tray_;
    bool quitting_;
    int trayCounter_; // Used when waiting for the system tray to be created at startup.
    int saveNeeded_;
    QFont defaultFont_, nodeFont_;
    QColor bgColor_, fgColor_;
    QColor lastTxtColor_, lastBgColor_;
    DomModel *model_;
    QString xmlPath_;
    QPointer<LineEdit> imagePathEntry_, htmlPahEntry_;
    /* By pairing each widget with a DOM item, we won't need to worry
       about keeping the correspondence between widgets and nodes: */
    QHash<DomItem*, TextEdit*> widgets_;
    QTextDocument::FindFlags searchFlags_; // Whole word and case sensitivity flags.
    QHash<TextEdit*, QString> searchEntries_; // Search entries, one for each QTextEdit.
    bool searchingOtherNode_; // Needed when jumping to another node during search.
    bool rplOtherNode_; // Like above but for replacement.
    int replCount_; // Needed for counting replacements in all nodes.
    QHash<TextEdit*, QList<QTextEdit::ExtraSelection>> greenSels_; // For replaced matches.
    QString txtReplace_; // The replacing text.
    QModelIndexList tagsList_;
    QString linkAtPos_; // Text hyperlink at the right-click position.
    int imgScale_; QString lastImgPath_;
    int recentNum_;
    bool remSize_, isMaxed_, isFull_,
         remSplitter_,
         remPosition_,
         hasTray_,
         minToTray_,
         wrapByDefault_,
         indentByDefault_,
         transparentTree_,
         smallToolbarIcons_,
         noToolbar_,
         noMenubar_,
         autoBracket_,
         autoReplace_,
         openLastFile_,
         openReccentSeparately_,
         rememberExpanded_,
         saveOnExit_;
    bool shownBefore_, treeViewDND_; // Used internally.
    int lastNode_;
    QString dateFormat_;
    int autoSave_;
    QPoint position_; // Excluding the window frame.
    QSize winSize_, startSize_, prefSize_;
    QTimer *timer_;
    QString pswrd_;
    QHash<QString, QString> customActions_;
    QHash<QAction*, QKeySequence> defaultShortcuts_;
    QStringList uncustomizedActions_, reservedShortcuts_;

#ifdef HAS_HUNSPELL
    QString dictPath_;
#endif
};

}

#endif // FN_H
