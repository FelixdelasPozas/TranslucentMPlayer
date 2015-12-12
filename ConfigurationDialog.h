/*
 File: ConfigurationDialog.h
 Created on: 11/12/2015
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

#ifndef CONFIGURATIONDIALOG_H_
#define CONFIGURATIONDIALOG_H_

// Qt
#include <QDialog>
#include "Ui_ConfigurationDialog.h"

/** \class ConfigurationDialog
 * \brief Dialog for basic options configuration.
 *
 */
class ConfigurationDialog
: public QDialog
, public Ui_ConfigurationDialog
{
    Q_OBJECT
  public:
    /** \brief ConfigurationDialog class constructor.
     * \param[in] parent pointer of QWidget parent of this one.
     * \parma[in] flags window flags.
     *
     */
    explicit ConfigurationDialog(QWidget *parent = nullptr, Qt::WindowFlags flags = 0);

    /** \brief ConfigurationDialog class virtual destructor.
     *
     */
    virtual ~ConfigurationDialog()
    {}

    /** \brief Sets the mplayer path in the text field.
     * \param[in] path mplayer executable absolute file path.
     *
     */
    void setMplayerPath(const QString &path);

    /** \brief Returns the absolute path of the mplayer executable.
     *
     */
    const QString mplayerPath() const;

  public slots:
    virtual void accept() override final;

  protected:
    void closeEvent(QCloseEvent *e);

  private:
    /** \brief Returns the mplayer version string.
     *
     */
    const QString mplayerVersion();

  private slots:
    /** \brief Opens the find files dialog and manages the result.
     *
     */
    void onDirButtonPressed();
};

#endif // CONFIGURATIONDIALOG_H_
