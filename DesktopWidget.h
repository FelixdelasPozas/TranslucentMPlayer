/*
 File: DesktopWidget.h
 Created on: 13/12/2015
 Author: Felix de las Pozas Alvarez

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef DESKTOPWIDGET_H_
#define DESKTOPWIDGET_H_

// Qt
#include <QWidget>

class QEvent;

/** \class DesktopWidget
 * \brief Widget to be on the desktop, invisible to events and always on top,
 *        showing the title and progression of the alarm.
 */
class DesktopWidget
: public QWidget
{
  public:
    /** \brief DesktopWidget class constructor.
     * \param[in] parent raw pointer of the QWidget parent of this one.
     *
     */
    explicit DesktopWidget(QWidget *parent = nullptr);

    /** \brief DesktopWidget class virtual destructor.
     *
     */
    virtual ~DesktopWidget()
    {};

    /** \brief Sets the widget position on the screen.
     * \param[in] position position coordinates.
     *
     */
    void setPosition(const QPoint &position);

    /** \brief Modifies the widget opacity.
     * \param[in] opacity opacity value in [0-100].
     *
     */
    void setOpacity(const int opacity);

    /** \brief Sets the size of the widget.
     * \param[in] size new widget's size.
     *
     */
    void setVideoSize(const QSize &size);

    virtual bool event(QEvent *e) override;
};

#endif // DESKTOPWIDGET_H_
