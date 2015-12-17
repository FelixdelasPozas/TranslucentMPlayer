/*
 File: ProjectWidgetAction.h
 Created on: 17/12/2015
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

#ifndef PROGRESSWIDGETACTION_H_
#define PROGRESSWIDGETACTION_H_

#include <QWidgetAction>

/** \class ProjectWidgetAction
 * \brief Video progress widget for tray icon.
 *
 */
class ProgressWidgetAction
: public QWidgetAction
{
    Q_OBJECT
  public:
    /** \brief ProgressWidgetAction class constructor.
     *
     */
    explicit ProgressWidgetAction(int maxValue = 100, int currentValue = 0, QObject *parent = nullptr);

    /** \brief ProgressWidgetAction class virtual destructor.
     *
     */
    virtual ~ProgressWidgetAction()
    {}

    /** \brief Sets the value in the progress slider.
     * \param[in] value progress value in [0-MAX].
     *
     */
    void setProgress(int value);

    /** \brief Sets the maximum value of the progress slider.
     * \param[in] value integer value.
     */
    void setMaximumValue(int value);

  private slots:
    /** \brief Emits the play/pause signal accordingly.
     * \param[in] checked true if the button is checked and flase otherwise.
     *
     */
    void onButtonClicked(bool checked);

  signals:
    void play();
    void pause();
    void progressChanged(int);

  protected:
    virtual QWidget *createWidget(QWidget *parent) override final;

  private:
    int m_maxValue; /** maximum value for the progress slider. */
    int m_current;  /** current value for the progress slider. */

};

#endif // PROGRESSWIDGETACTION_H_
