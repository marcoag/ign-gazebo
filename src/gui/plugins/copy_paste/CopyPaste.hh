/*
 * Copyright (C) 2021 Open Source Robotics Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
*/

#ifndef IGNITION_GAZEBO_GUI_COPYPASTE_HH_
#define IGNITION_GAZEBO_GUI_COPYPASTE_HH_

#include <memory>

#include <ignition/msgs.hh>

#include "ignition/gazebo/gui/GuiSystem.hh"

namespace ignition
{
namespace gazebo
{
  class CopyPastePrivate;

  /// \brief Plugin for copying/pasting entities in the GUI.
  class CopyPaste : public ignition::gazebo::GuiSystem
  {
    Q_OBJECT

    /// \brief Constructor
    public: CopyPaste();

    /// \brief Destructor
    public: ~CopyPaste() override;

    // Documentation inherited
    public: void LoadConfig(const tinyxml2::XMLElement *_pluginElem) override;

    // Documentation inherited
    public: void Update(const UpdateInfo &_info,
                EntityComponentManager &_ecm) override;

    /// \brief Callback to copy the selected entity
    public slots: void OnCopy();

    /// \brief Callback to paste the data that has been copied, if copied data
    /// exists.
    public slots: void OnPaste();

    // Documentation inherited
    protected: bool eventFilter(QObject *_obj, QEvent *_event) override;

    /// \brief Callback for handling a copy service request
    /// \param[in] _req The service request, which contains the name of the
    /// entity to be copied
    /// \param[out] _resp The service response
    /// \return Whether the service was successful (true) or not (false)
    private: bool CopyServiceCB(const ignition::msgs::StringMsg &_req,
                ignition::msgs::Boolean &_resp);

    /// \brief Callback for handling a paste service request
    /// \param[in] _req The service request
    /// \param[out] _resp The service response
    /// \return Whether the service was successful (true) or not (false)
    private: bool PasteServiceCB(const ignition::msgs::Empty &_req,
                ignition::msgs::Boolean &_resp);

    /// \internal
    /// \brief Pointer to private data
    private: std::unique_ptr<CopyPastePrivate> dataPtr;
  };
}
}

#endif
