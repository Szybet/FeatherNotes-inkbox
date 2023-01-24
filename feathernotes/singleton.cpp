/*
 * Copyright (C) Pedram Pourang (aka Tsu Jan) 2022 <tsujan2000@gmail.com>
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


#include "singleton.h"

#ifdef HAS_X11
#include "x11.h"
#endif

namespace FeatherNotes {

FNSingleton::FNSingleton (int &argc, char **argv) : QApplication (argc, argv)
{

}
/*************************/
FNSingleton::~FNSingleton()
{
    qDeleteAll (Wins);
}
/*************************/
void FNSingleton::quitting()
{
    for (int i = 0; i < Wins.size(); ++i)
        Wins.at (i)->quitting();
}
/*************************/
void FNSingleton::quitSignalReceived()
{
    quitSignalReceived_ = true;
    quit();
}
/*************************/
void FNSingleton::sendInfo (const QStringList &info)
{

}
/*************************/
void FNSingleton::openFile (const QStringList &info)
{
    /* If there is an FN window with the same file path, ignore the command-line option
       and activate it. This is the whole point of making FN a single-instance app. */
    if (!Wins.isEmpty())
    {
        QString filePath;
        if (!info.isEmpty())
        {
            if (info.at (0) != "--min" && info.at (0) != "-m"
                && info.at (0) != "--tray" && info.at (0) != "-t")
            {
                filePath = info.at (0);
            }
            else if (info.size() > 1)
                filePath = info.at (1);
        }
        if (filePath.isEmpty())
            filePath = lastFile_;
        for (int i = 0; i < Wins.size(); ++i)
        {
            if (Wins.at (i)->currentPath() == filePath)
            {
                Wins.at (i)->activateFNWindow();
                return;
            }
        }
    }

    FN *fn = new FN (info, nullptr);
    Wins.append (fn);
}
/*************************/
void FNSingleton::removeWin (FN *win)
{
    Wins.removeOne (win);
    win->deleteLater();
}

}
